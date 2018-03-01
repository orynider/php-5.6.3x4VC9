/*
  +----------------------------------------------------------------------+
  | See COPYING file for further copyright information                   |
  +----------------------------------------------------------------------+
  | Author: Oleg Grenrus <oleg.grenrus@dynamoid.com>                     |
  | See CREDITS for contributors                                         |
  +----------------------------------------------------------------------+
*/

#ifdef PHP_WIN32
# include "ig_win32.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include "hash.h"
#include "zend.h"

/* {{{ nextpow2 */
/** Next power of 2.
 * @param n Integer.
 * @return next to n power of 2 .
 */
inline static uint32_t nextpow2(uint32_t n) {
	uint32_t m = 1;
	while (m < n) {
		m = m << 1;
	}

	return m;
}
/* }}} */
/* {{{ hash_si_init */
int hash_si_init(struct hash_si *h, size_t size) {
	size = nextpow2(size);

	h->mask = size - 1;
	h->used = 0;
	h->data = (struct hash_si_pair *) emalloc(sizeof(struct hash_si_pair) * size);
	if (h->data == NULL) {
		return 1;
	}

	memset(h->data, 0, sizeof(struct hash_si_pair) * size);

	return 0;
}
/* }}} */
/* {{{ hash_si_deinit */
void hash_si_deinit(struct hash_si *h) {
	size_t i;

	for (i = 0; i <= h->mask; i++) {
		if (h->data[i].key_zstr != NULL) {
			zend_string_release(h->data[i].key_zstr);
		}
	}

	efree(h->data);

	h->mask = 0;
	h->used = 0;
}
/* }}} */
/* {{{ _hash_si_find */
/** Returns index of key, or where it should be.
 * @param h Pointer to hash_si struct.
 * @param key_zstr Pointer to key. (Will initialize ZSTR_H(key_zstr) if not already initialized)
 * @return index.
 */
inline static struct hash_si_pair *_hash_si_find(const struct hash_si *h, const zend_string *key_zstr, const uint32_t key_hash) {
	size_t mask;
	struct hash_si_pair *it;
	const struct hash_si_pair *last_element;
	uint32_t increment;
	uint32_t elem_key_hash;

	assert(h != NULL);

	mask = h->mask;
	it = &(h->data[key_hash & mask]);

	elem_key_hash = it->key_hash;
	if (elem_key_hash == 0) {
		/* This slot is empty - PHP guarantees hashes are non-zero */
		return it;
	}
	if (key_hash == elem_key_hash) {
		const zend_string *elem_key_zstr = it->key_zstr;
		if (key_zstr == elem_key_zstr || (
					ZSTR_LEN(key_zstr) == ZSTR_LEN(elem_key_zstr) &&
					EXPECTED(!memcmp(ZSTR_VAL(key_zstr), ZSTR_VAL(elem_key_zstr), ZSTR_LEN(elem_key_zstr))))) {
			/* We found an identical key. */
			return it;
		}
	}

	increment = ((key_hash >> 16) & 6) | 1; /* An odd number < size to increment by (1, 3, 5, or 7). Avoid clumping. */
	last_element = h->data + mask;

	/* Continue scanning, we'll reach an empty element eventually (odd number increment over a hash table of size (2^n) will traverse the entire map). */
	while (1) {
		it += increment;
		if (it > last_element) {
			it -= (mask + 1);
		}

		elem_key_hash = it->key_hash;
		if (elem_key_hash == 0) {
			/* This slot is empty - PHP guarantees hashes are non-zero */
			return it;
		}
		if (key_hash == elem_key_hash) {
			const zend_string *elem_key_zstr = it->key_zstr;
			if (EXPECTED(key_zstr == elem_key_zstr || (
		                ZSTR_LEN(key_zstr) == ZSTR_LEN(elem_key_zstr) &&
		                EXPECTED(!memcmp(ZSTR_VAL(key_zstr), ZSTR_VAL(elem_key_zstr), ZSTR_LEN(elem_key_zstr)))))) {
				/* We found an identical key. */
				return it;
			}
		}
		/* linear probing by increment if we found a different key */
	}
}
/* }}} */
/* {{{ hash_si_rehash */
/** Rehash/resize hash_si.
 * @param h Pointer to hash_si struct.
 */
inline static void hash_si_rehash(struct hash_si *h) {
	size_t i;
	size_t size;
	struct hash_si newh;
	struct hash_si_pair *data;
	struct hash_si_pair *new_data;

	assert(h != NULL);
	size = h->mask + 1;

	hash_si_init(&newh, size * 2);
	data = h->data;
	new_data = newh.data;

	for (i = 0; i < size; i++) {
		const struct hash_si_pair *old_pair = &data[i];
		const zend_string *key_zstr = old_pair->key_zstr;
		if (key_zstr != NULL) {
			/* We already computed the hash, avoid recomputing it. */
			struct hash_si_pair *new_data_entry = _hash_si_find((const struct hash_si*) &newh, key_zstr, old_pair->key_hash);
			*new_data_entry = *old_pair;
		}
	}

	efree(h->data);
	h->data = new_data;
	h->mask = size * 2 - 1;
}
/* }}} */
/* {{{ hash_si_insert */
/*
int hash_si_insert(struct hash_si *h, const char *key, size_t key_len, uint32_t value) {
	uint32_t hv;

	if (h->size / 4 * 3 < h->used + 1) {
		hash_si_rehash(h);
	}

	hv = _hash_si_find(h, key, key_len);

	if (h->data[hv].key == NULL) {
		h->data[hv].key = (char *) emalloc(key_len + 1);
		if (h->data[hv].key == NULL) {
			return 1;
		}
		memcpy(h->data[hv].key, key, key_len);
		h->data[hv].key[key_len] = '\0';
		h->data[hv].key_len = key_len;

		h->used++;
	} else {
		return 2;
	}

	h->data[hv].value = value;

	return 0;
}
*/
/* }}} */
/* {{{ hash_si_find */
/*
int hash_si_find(struct hash_si *h, const char *key, size_t key_len, uint32_t *value) {
	uint32_t hv;

	assert(h != NULL);

	hv = _hash_si_find(h, key, key_len);

	if (h->data[hv].key == NULL) {
		return 1;
	} else {
		*value = h->data[hv].value;
		return 0;
	}
}
*/
/* }}} */
/* {{{ hash_si_find_or_insert */
struct hash_si_result hash_si_find_or_insert(struct hash_si *h, zend_string *key_zstr, uint32_t value) {
	struct hash_si_result result;
	struct hash_si_pair *pair;
	uint32_t key_hash = ZSTR_HASH(key_zstr);

	pair = _hash_si_find(h, key_zstr, key_hash);

	if (pair->key_zstr == NULL) {
		zend_string_addref(key_zstr);

		/* Having already computed the hash in the zend_string, insert that into the hash table */
		pair->key_zstr = key_zstr;
		pair->key_hash = key_hash;
		pair->value = value;

		h->used++;
		if (h->mask * 3 / 4 < h->used) {
			hash_si_rehash(h);
		}

		result.code = hash_si_code_inserted;
		return result;
	} else {
		result.code = hash_si_code_exists;
		result.value = pair->value;
		return result;
	}
}
/* }}} */
/* {{{ hash_si_traverse */
/*
void hash_si_traverse(struct hash_si *h, int (*traverse_function) (const char *key, size_t key_len, uint32_t value)) {
	size_t i;

	assert(h != NULL && traverse_function != NULL);

	for (i = 0; i < h->size; i++) {
		if (h->data[i].key != NULL && traverse_function(h->data[i].key, h->data[i].key_len, h->data[i].value) != 1) {
			return;
		}
	}
}
*/
/* }}} */
/* {{{ hash_si_size */
size_t hash_si_size(struct hash_si *h) {
	assert(h != NULL);

	return h->used;
}
/* }}} */
/* {{{ hash_si_capacity */
size_t hash_si_capacity(struct hash_si *h) {
	assert(h != NULL);

	return h->mask + 1;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 2
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
