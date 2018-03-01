/*
  +----------------------------------------------------------------------+
  | See COPYING file for further copyright information                   |
  +----------------------------------------------------------------------+
  | Author: Oleg Grenrus <oleg.grenrus@dynamoid.com>                     |
  | See CREDITS for contributors                                         |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef PHP_WIN32
# include "ig_win32.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "zend_alloc.h"
#include "ext/standard/info.h"
#include "ext/standard/php_var.h"

#if HAVE_PHP_SESSION && !defined(COMPILE_DL_SESSION)
# include "ext/session/php_session.h"
#endif

#include "ext/standard/php_incomplete_class.h"

/* Note: there are no checks for APC (project from which APCU was forked) */
#if defined(HAVE_APCU_SUPPORT)
# include "ext/apcu/apc_serializer.h"
#endif /* HAVE_APCU_SUPPORT */

#include "php_igbinary.h"

#include "igbinary.h"

#include <assert.h>
#include <ctype.h>

#ifndef PHP_WIN32
# include <inttypes.h>
# include <stdbool.h>
# include <stdint.h>
#endif


#include <stddef.h>
#include "hash.h"
#include "hash_ptr.h"
#include "zend_alloc.h"

#if HAVE_PHP_SESSION && !defined(COMPILE_DL_SESSION)
/** Session serializer function prototypes. */
PS_SERIALIZER_FUNCS(igbinary);
#endif /* HAVE_PHP_SESSION && !defined(COMPILE_DL_SESSION) */

#if defined(HAVE_APCU_SUPPORT)
/** Apc serializer function prototypes */
static int APC_SERIALIZER_NAME(igbinary) (APC_SERIALIZER_ARGS);
static int APC_UNSERIALIZER_NAME(igbinary) (APC_UNSERIALIZER_ARGS);
#endif

/* {{{ Types */
enum igbinary_type {
	/* 00 */ igbinary_type_null,			/**< Null. */

	/* 01 */ igbinary_type_ref8,			/**< Array reference. */
	/* 02 */ igbinary_type_ref16,			/**< Array reference. */
	/* 03 */ igbinary_type_ref32,			/**< Array reference. */

	/* 04 */ igbinary_type_bool_false,		/**< Boolean true. */
	/* 05 */ igbinary_type_bool_true,		/**< Boolean false. */

	/* 06 */ igbinary_type_long8p,			/**< Long 8bit positive. */
	/* 07 */ igbinary_type_long8n,			/**< Long 8bit negative. */
	/* 08 */ igbinary_type_long16p,			/**< Long 16bit positive. */
	/* 09 */ igbinary_type_long16n,			/**< Long 16bit negative. */
	/* 0a */ igbinary_type_long32p,			/**< Long 32bit positive. */
	/* 0b */ igbinary_type_long32n,			/**< Long 32bit negative. */

	/* 0c */ igbinary_type_double,			/**< Double. */

	/* 0d */ igbinary_type_string_empty,	/**< Empty string. */

	/* 0e */ igbinary_type_string_id8,		/**< String id. */
	/* 0f */ igbinary_type_string_id16,		/**< String id. */
	/* 10 */ igbinary_type_string_id32,		/**< String id. */

	/* 11 */ igbinary_type_string8,			/**< String. */
	/* 12 */ igbinary_type_string16,		/**< String. */
	/* 13 */ igbinary_type_string32,		/**< String. */

	/* 14 */ igbinary_type_array8,			/**< Array. */
	/* 15 */ igbinary_type_array16,			/**< Array. */
	/* 16 */ igbinary_type_array32,			/**< Array. */

	/* 17 */ igbinary_type_object8,			/**< Object. */
	/* 18 */ igbinary_type_object16,		/**< Object. */
	/* 19 */ igbinary_type_object32,		/**< Object. */

	/* 1a */ igbinary_type_object_id8,		/**< Object string id. */
	/* 1b */ igbinary_type_object_id16,		/**< Object string id. */
	/* 1c */ igbinary_type_object_id32,		/**< Object string id. */

	/* 1d */ igbinary_type_object_ser8,		/**< Object serialized data. */
	/* 1e */ igbinary_type_object_ser16,	/**< Object serialized data. */
	/* 1f */ igbinary_type_object_ser32,	/**< Object serialized data. */

	/* 20 */ igbinary_type_long64p,			/**< Long 64bit positive. */
	/* 21 */ igbinary_type_long64n,			/**< Long 64bit negative. */

	/* 22 */ igbinary_type_objref8,			/**< Object reference. */
	/* 23 */ igbinary_type_objref16,		/**< Object reference. */
	/* 24 */ igbinary_type_objref32,		/**< Object reference. */

	/* 25 */ igbinary_type_ref,				/**< Simple reference */
};

/** Serializer data.
 * @author Oleg Grenrus <oleg.grenrus@dynamoid.com>
 */
struct igbinary_serialize_data {
	uint8_t *buffer;			/**< Buffer. */
	size_t buffer_size;			/**< Buffer size. */
	size_t buffer_capacity;		/**< Buffer capacity. */
	bool scalar;				/**< Serializing scalar. */
	bool compact_strings;		/**< Check for duplicate strings. */
	struct hash_si strings;		/**< Hash of already serialized strings. */
	struct hash_si_ptr references;	/**< Hash of already serialized potential references. (non-NULL uintptr_t => int32_t) */
	int references_id;		/**< Number of things that the unserializer might think are references. >= length of references */
	int string_count;			/**< Serialized string count, used for back referencing */
	int error;					/**< Error number. Not used. */
	struct igbinary_memory_manager	mm; /**< Memory management functions. */
};

/*
Object {
   reference {scalar, object, array, null} (convert to reference, share reference in zval_ref)
   object {} (convert to zend_object, share zend_object* in reference)
   array {} (convert to zend_array, share zend_array* in reference)
}
*/
enum zval_ref_type {
	IG_REF_IS_REFERENCE,  // Points to zend_reference
	IG_REF_IS_OBJECT,  // Points to zend_object
	IG_REF_IS_ARRAY,  // Points to zend_object
};

struct igbinary_value_ref {
	// We reuse temporary values for object properties that are references or arrays.
	union {
		zend_reference *reference;
		zend_object *object;
		zend_array *array;
	} reference;
	enum zval_ref_type type;
};

/** Unserializer data.
 * @author Oleg Grenrus <oleg.grenrus@dynamoid.com>
 */
struct igbinary_unserialize_data {
	const uint8_t *buffer;			/**< Buffer. */
	const uint8_t *buffer_end;		/**< Buffer size. */
	const uint8_t *buffer_ptr;		/**< Current read offset. */

	zend_string **strings;          /**< Unserialized strings. */
	size_t strings_count;			/**< Unserialized string count. */
	size_t strings_capacity;		/**< Unserialized string array capacity. */

	struct igbinary_value_ref *references; /**< Unserialized Arrays/Objects/References */
	size_t references_count;		/**< Unserialized array/objects count. */
	size_t references_capacity;		/**< Unserialized array/object array capacity. */

	zend_object **wakeup;			/**< objects for calls to __wakeup. */
	size_t wakeup_count;			/**< count of objects in array for calls to __wakeup */
	size_t wakeup_capacity;			/**< capacity of objects in array for calls to __wakeup */

	int error;						/**< Error number. Not used. */
	smart_string string0_buf;			/**< Temporary buffer for strings */
};

#define IGB_REF_VAL_2(igsd, n)	((igsd)->references[(n)])
#define IGB_NEEDS_MORE_DATA(igsd, n)	UNEXPECTED((size_t)((igsd)->buffer_end - (igsd)->buffer_ptr) < (n))
#define IGB_REMAINING_BYTES(igsd)	((unsigned int)((igsd)->buffer_end - (igsd)->buffer_ptr))
#define IGB_BUFFER_OFFSET(igsd)	((unsigned int)((igsd)->buffer_ptr - (igsd)->buffer))

#define WANT_CLEAR     (0)
#define WANT_REF       (1<<1)

/* }}} */
/* {{{ Memory allocator wrapper prototypes */
static inline void *igbinary_mm_wrapper_malloc(size_t size, void *context);
static inline void *igbinary_mm_wrapper_realloc(void *ptr, size_t size, void *context);
static inline void igbinary_mm_wrapper_free(void *ptr, void *context);
/* }}} */
/* {{{ Serializing functions prototypes */
inline static int igbinary_serialize_data_init(struct igbinary_serialize_data *igsd, bool scalar, struct igbinary_memory_manager *memory_manager);
inline static void igbinary_serialize_data_deinit(struct igbinary_serialize_data *igsd, int free_buffer);

inline static int igbinary_serialize_header(struct igbinary_serialize_data *igsd);

inline static int igbinary_serialize8(struct igbinary_serialize_data *igsd, uint8_t i);
inline static int igbinary_serialize16(struct igbinary_serialize_data *igsd, uint16_t i);
inline static int igbinary_serialize32(struct igbinary_serialize_data *igsd, uint32_t i);
inline static int igbinary_serialize64(struct igbinary_serialize_data *igsd, uint64_t i);

inline static int igbinary_serialize_null(struct igbinary_serialize_data *igsd);
inline static int igbinary_serialize_bool(struct igbinary_serialize_data *igsd, int b);
inline static int igbinary_serialize_long(struct igbinary_serialize_data *igsd, zend_long l);
inline static int igbinary_serialize_double(struct igbinary_serialize_data *igsd, double d);
inline static int igbinary_serialize_string(struct igbinary_serialize_data *igsd, zend_string *s);
inline static int igbinary_serialize_chararray(struct igbinary_serialize_data *igsd, const char *s, size_t len);

inline static int igbinary_serialize_array(struct igbinary_serialize_data *igsd, zval *z, bool object, bool incomplete_class);
inline static int igbinary_serialize_array_ref(struct igbinary_serialize_data *igsd, zval *z, bool object);
inline static int igbinary_serialize_array_sleep(struct igbinary_serialize_data *igsd, zval *z, HashTable *ht, zend_class_entry *ce, bool incomplete_class);
inline static int igbinary_serialize_object_name(struct igbinary_serialize_data *igsd, zend_string *name);
inline static int igbinary_serialize_object(struct igbinary_serialize_data *igsd, zval *z);

static int igbinary_serialize_zval(struct igbinary_serialize_data *igsd, zval *z);
/* }}} */
/* {{{ Unserializing functions prototypes */
inline static int igbinary_unserialize_data_init(struct igbinary_unserialize_data *igsd);
inline static void igbinary_unserialize_data_deinit(struct igbinary_unserialize_data *igsd);

inline static int igbinary_unserialize_header(struct igbinary_unserialize_data *igsd);

inline static uint8_t igbinary_unserialize8(struct igbinary_unserialize_data *igsd);
inline static uint16_t igbinary_unserialize16(struct igbinary_unserialize_data *igsd);
inline static uint32_t igbinary_unserialize32(struct igbinary_unserialize_data *igsd);
inline static uint64_t igbinary_unserialize64(struct igbinary_unserialize_data *igsd);

inline static int igbinary_unserialize_long(struct igbinary_unserialize_data *igsd, enum igbinary_type t, zend_long *ret);
inline static int igbinary_unserialize_double(struct igbinary_unserialize_data *igsd, enum igbinary_type t, double *ret);
inline static zend_string * igbinary_unserialize_string(struct igbinary_unserialize_data *igsd, enum igbinary_type t);
inline static zend_string * igbinary_unserialize_chararray(struct igbinary_unserialize_data *igsd, enum igbinary_type t);

inline static int igbinary_unserialize_array(struct igbinary_unserialize_data *igsd, enum igbinary_type t, zval *const z, int flags);
inline static int igbinary_unserialize_object(struct igbinary_unserialize_data *igsd, enum igbinary_type t, zval *const z, int flags);
inline static int igbinary_unserialize_object_ser(struct igbinary_unserialize_data *igsd, enum igbinary_type t, zval *const z, zend_class_entry *ce);
inline static int igbinary_unserialize_ref(struct igbinary_unserialize_data *igsd, enum igbinary_type t, zval *const z, int flags);

inline static int igbinary_unserialize_zval(struct igbinary_unserialize_data *igsd, zval *const z, int flags);
/* }}} */
/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_igbinary_serialize, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_igbinary_unserialize, 0, 0, 1)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */
/* {{{ igbinary_functions[] */
/** Exported php functions. */
zend_function_entry igbinary_functions[] = {
	PHP_FE(igbinary_serialize,                arginfo_igbinary_serialize)
	PHP_FE(igbinary_unserialize,              arginfo_igbinary_unserialize)
	PHP_FE_END
};
/* }}} */

/* {{{ igbinary dependencies */
static const zend_module_dep igbinary_module_deps[] = {
	ZEND_MOD_REQUIRED("standard")
#if HAVE_PHP_SESSION && !defined(COMPILE_DL_SESSION)
	ZEND_MOD_REQUIRED("session")
#endif
#if defined(HAVE_APCU_SUPPORT)
	ZEND_MOD_OPTIONAL("apcu")
#endif
	ZEND_MOD_END
};
/* }}} */

/* {{{ igbinary_module_entry */
zend_module_entry igbinary_module_entry = {
#if ZEND_MODULE_API_NO >= 20050922
	STANDARD_MODULE_HEADER_EX, NULL,
	igbinary_module_deps,
#elif ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"igbinary",
	igbinary_functions,
	PHP_MINIT(igbinary),
	PHP_MSHUTDOWN(igbinary),
	NULL,
	NULL,
	PHP_MINFO(igbinary),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_IGBINARY_VERSION, /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

ZEND_DECLARE_MODULE_GLOBALS(igbinary)

/* {{{ ZEND_GET_MODULE */
#ifdef COMPILE_DL_IGBINARY
ZEND_GET_MODULE(igbinary)
#endif
/* }}} */

/* {{{ INI entries */
PHP_INI_BEGIN()
	STD_PHP_INI_BOOLEAN("igbinary.compact_strings", "1", PHP_INI_ALL, OnUpdateBool, compact_strings, zend_igbinary_globals, igbinary_globals)
PHP_INI_END()
/* }}} */

/* {{{ php_igbinary_init_globals */
static void php_igbinary_init_globals(zend_igbinary_globals *igbinary_globals) {
	igbinary_globals->compact_strings = 1;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(igbinary) {
	(void) type;
	(void) module_number;
	ZEND_INIT_MODULE_GLOBALS(igbinary, php_igbinary_init_globals, NULL);

#if HAVE_PHP_SESSION && !defined(COMPILE_DL_SESSION)
	php_session_register_serializer("igbinary",
		PS_SERIALIZER_ENCODE_NAME(igbinary),
		PS_SERIALIZER_DECODE_NAME(igbinary));
#endif

#if defined(HAVE_APCU_SUPPORT)
	apc_register_serializer("igbinary",
		APC_SERIALIZER_NAME(igbinary),
		APC_UNSERIALIZER_NAME(igbinary),
		NULL);
#endif

	REGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */
/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(igbinary) {
	(void) type;
	(void) module_number;

#ifdef ZTS
	ts_free_id(igbinary_globals_id);
#endif

	/*
	 * Clean up ini entries.
	 * Aside: It seems like the php_session_register_serializer unserializes itself, since MSHUTDOWN in ext/wddx/wddx.c doesn't exist?
	 */
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */
/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(igbinary) {
	(void) zend_module;
	php_info_print_table_start();
	php_info_print_table_row(2, "igbinary support", "enabled");
	php_info_print_table_row(2, "igbinary version", PHP_IGBINARY_VERSION);
#if defined(HAVE_APCU_SUPPORT)
	php_info_print_table_row(2, "igbinary APCU serializer ABI", APC_SERIALIZER_ABI);
#else
	php_info_print_table_row(2, "igbinary APC serializer ABI", "no");
#endif
#if HAVE_PHP_SESSION && !defined(COMPILE_DL_SESSION)
	php_info_print_table_row(2, "igbinary session support", "yes");
#else
	php_info_print_table_row(2, "igbinary session support", "no");
#endif
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ igsd management */
/* Append to list of references to take out later. Returns SIZE_MAX on allocation error. */
static inline size_t igsd_append_ref(struct igbinary_unserialize_data *igsd, struct igbinary_value_ref v)
{
	size_t ref_n;
	if (igsd->references_count + 1 >= igsd->references_capacity) {
		while (igsd->references_count + 1 >= igsd->references_capacity) {
			igsd->references_capacity *= 2;
		}

		struct igbinary_value_ref *new_references = erealloc(igsd->references, sizeof(igsd->references[0]) * igsd->references_capacity);
		if (new_references == NULL) {
			return SIZE_MAX;
		}
		igsd->references = new_references;
	}


	ref_n = igsd->references_count++;
	IGB_REF_VAL_2(igsd, ref_n) = v;
	return ref_n;
}

static inline int igsd_defer_wakeup(struct igbinary_unserialize_data *igsd, zend_object* object) {
	if (igsd->wakeup_count >= igsd->wakeup_capacity) {
		if (igsd->wakeup_capacity == 0) {
			igsd->wakeup_capacity = 2;
			igsd->wakeup = emalloc(sizeof(igsd->wakeup[0]) * igsd->wakeup_capacity);
		} else {
			igsd->wakeup_capacity *= 2;
			igsd->wakeup = erealloc(igsd->wakeup, sizeof(igsd->wakeup[0]) * igsd->wakeup_capacity);
			if (igsd->wakeup == NULL) {
				return 1;
			}
		}
	}

	igsd->wakeup[igsd->wakeup_count++] = object;
	return 0;
}
/* }}} */

/* {{{ igbinary_finish_wakeup }}} */
static int igbinary_finish_wakeup(struct igbinary_unserialize_data* igsd) {
	if (igsd->wakeup_count == 0) { /* nothing to do */
		return 0;
	}
	zval fname;
	size_t i;
	ZVAL_STRINGL(&fname, "__wakeup", sizeof("__wakeup") - 1);
	for (i = 0; i < igsd->wakeup_count; i++) {
		zval retval;  /* return value of __wakeup */
		zval rval;
		zend_object *obj = igsd->wakeup[i];
		ZVAL_OBJ(&rval, obj);
		if (call_user_function_ex(CG(function_table), &rval, &fname, &retval, 0, 0, 1, NULL) == FAILURE || Z_ISUNDEF(retval)) {
			GC_FLAGS(obj) |= IS_OBJ_DESTRUCTOR_CALLED;
		}
		zval_ptr_dtor(&retval);
		if (EG(exception)) {
			size_t j;
			zval_dtor(&fname);
			/* Don't call __destruct for any of the objects which __wakeup wasn't called on yet, either */
			for (j = i + 1; j < igsd->wakeup_count; j++) {
				GC_FLAGS(igsd->wakeup[j]) |= IS_OBJ_DESTRUCTOR_CALLED;
			}
			return 1;
		}
	}
	zval_dtor(&fname);
	return 0;
}

/* {{{ Memory allocator wrappers */
static inline void *igbinary_mm_wrapper_malloc(size_t size, void *context)
{
	(void)context;
	return emalloc(size);
}

static inline void *igbinary_mm_wrapper_realloc(void *ptr, size_t size, void *context)
{
	(void)context;
	return erealloc(ptr, size);
}

static inline void igbinary_mm_wrapper_free(void *ptr, void *context)
{
	(void)context;
	efree(ptr);
}
/* }}} */
/* {{{ int igbinary_serialize(uint8_t**, size_t*, zval*) */
IGBINARY_API int igbinary_serialize(uint8_t **ret, size_t *ret_len, zval *z) {
	return igbinary_serialize_ex(ret, ret_len, z, NULL);
}
/* }}} */
/* {{{ int igbinary_serialize_ex(uint8_t**, size_t*, zval*, igbinary_memory_manager*) */
IGBINARY_API int igbinary_serialize_ex(uint8_t **ret, size_t *ret_len, zval *z, struct igbinary_memory_manager *memory_manager) {
	struct igbinary_serialize_data igsd;
	uint8_t *tmpbuf;
	// While we can't get passed references through the PHP_FUNCTIONs igbinary declares, third party code can call us igbinary's methods with references.
	// See https://github.com/php-memcached-dev/php-memcached/issues/326
	if (Z_TYPE_P(z) == IS_INDIRECT) {
		z = Z_INDIRECT_P(z);
	}
	ZVAL_DEREF(z);

	if (igbinary_serialize_data_init(&igsd, Z_TYPE_P(z) != IS_OBJECT && Z_TYPE_P(z) != IS_ARRAY, memory_manager)) {
		zend_error(E_WARNING, "igbinary_serialize: cannot init igsd");
		return 1;
	}

	if (igbinary_serialize_header(&igsd) != 0) {
		zend_error(E_WARNING, "igbinary_serialize: cannot write header");
		igbinary_serialize_data_deinit(&igsd, 1);
		return 1;
	}

	if (igbinary_serialize_zval(&igsd, z) != 0) {
		igbinary_serialize_data_deinit(&igsd, 1);
		return 1;
	}

	/* Explicit nul termination */
	if (igbinary_serialize8(&igsd, 0) != 0) {
		igbinary_serialize_data_deinit(&igsd, 1);
		return 1;
	}

	/* shrink buffer to the real length, ignore errors */
	tmpbuf = (uint8_t *) igsd.mm.realloc(igsd.buffer, igsd.buffer_size, igsd.mm.context);
	if (tmpbuf != NULL) {
		igsd.buffer = tmpbuf;
	}

	/* Set return values */
	*ret_len = igsd.buffer_size - 1;
	*ret = igsd.buffer;

	igbinary_serialize_data_deinit(&igsd, 0);

	return 0;
}
/* }}} */
/* {{{ int igbinary_unserialize(const uint8_t *, size_t, zval **) */
IGBINARY_API int igbinary_unserialize(const uint8_t *buf, size_t buf_len, zval *z) {
	struct igbinary_unserialize_data igsd;

	igbinary_unserialize_data_init(&igsd);

	igsd.buffer = buf;
	igsd.buffer_ptr = buf;
	igsd.buffer_end = buf + buf_len;

	if (igbinary_unserialize_header(&igsd)) {
		igbinary_unserialize_data_deinit(&igsd);
		return 1;
	}

	if (igbinary_unserialize_zval(&igsd, z, WANT_CLEAR)) {
		igbinary_unserialize_data_deinit(&igsd);
		return 1;
	}

	if (igbinary_finish_wakeup(&igsd)) {
		igbinary_unserialize_data_deinit(&igsd);
		return 1;
	}
	igbinary_unserialize_data_deinit(&igsd);

	return 0;
}
/* }}} */
/* {{{ proto string igbinary_unserialize(mixed value) */
PHP_FUNCTION(igbinary_unserialize) {
	char *string = NULL;
	size_t string_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &string, &string_len) == FAILURE) {
		RETURN_NULL();
	}

	if (string_len <= 0) {
		RETURN_FALSE;
	}

	if (igbinary_unserialize((uint8_t *) string, string_len, return_value) != 0) {
		/* FIXME: is this a good place? a catch all */
		zval_ptr_dtor(return_value);
		RETURN_NULL();
	}
}
/* }}} */
/* {{{ proto mixed igbinary_serialize(string value) */
PHP_FUNCTION(igbinary_serialize) {
	zval *z;
	uint8_t *string;
	size_t string_len;


	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &z) == FAILURE) {
		RETURN_NULL();
	}

	if (igbinary_serialize(&string, &string_len, z) != 0) {
		RETURN_NULL();
	}

	RETVAL_STRINGL((char *)string, string_len);
	efree(string);
}
/* }}} */
#if HAVE_PHP_SESSION && !defined(COMPILE_DL_SESSION)
/* {{{ Serializer encode function */
PS_SERIALIZER_ENCODE_FUNC(igbinary)
{
	zval* session_vars;
	zend_string *result;
	struct igbinary_serialize_data igsd;

	session_vars = &(PS(http_session_vars));
	if (Z_ISREF_P(session_vars)) {
		session_vars = Z_REFVAL_P(session_vars);
	}
	if (Z_TYPE_P(session_vars) == IS_ARRAY && zend_hash_num_elements(Z_ARRVAL_P(session_vars)) == 0) {
		return ZSTR_EMPTY_ALLOC();
	}
	if (igbinary_serialize_data_init(&igsd, false, NULL)) {
		zend_error(E_WARNING, "igbinary_serialize: cannot init igsd");
		return ZSTR_EMPTY_ALLOC();
	}

	if (igbinary_serialize_header(&igsd) != 0) {
		zend_error(E_WARNING, "igbinary_serialize: cannot write header");
		igbinary_serialize_data_deinit(&igsd, 1);
		return ZSTR_EMPTY_ALLOC();
	}

	if (igbinary_serialize_array(&igsd, session_vars, false, false) != 0) {
		igbinary_serialize_data_deinit(&igsd, 1);
		zend_error(E_WARNING, "igbinary_serialize: cannot serialize session variables");
		return ZSTR_EMPTY_ALLOC();
	}

	/* Copy the buffer to a new zend_string */
	/* TODO: Clean up igsd->mm, and make this a pointer swap instead? It's only used for building up the serialization data buffer. */
	result = zend_string_init((const char*)igsd.buffer, igsd.buffer_size, 0);
	igbinary_serialize_data_deinit(&igsd, 1);

	return result;
}
/* }}} */
/* {{{ Serializer decode function */
/* This is similar to PS_SERIALIZER_DECODE_FUNC(php) from ext/session/session.c */
PS_SERIALIZER_DECODE_FUNC(igbinary) {
	HashTable *tmp_hash;
	zval z;
	zval *d;
	zend_string *key;

	struct igbinary_unserialize_data igsd;

	if (!val || vallen==0) {
		return SUCCESS;
	}

	if (igbinary_unserialize_data_init(&igsd) != 0) {
		return FAILURE;
	}

	igsd.buffer = (const uint8_t*) val;
	igsd.buffer_ptr = igsd.buffer;
	igsd.buffer_end = igsd.buffer + vallen;

	if (igbinary_unserialize_header(&igsd)) {
		igbinary_unserialize_data_deinit(&igsd);
		return FAILURE;
	}

	if (igbinary_unserialize_zval(&igsd, &z, WANT_CLEAR)) {
		igbinary_unserialize_data_deinit(&igsd);
		return FAILURE;
	}

	if (igbinary_finish_wakeup(&igsd)) {
		igbinary_unserialize_data_deinit(&igsd);
		return FAILURE;
	}

	igbinary_unserialize_data_deinit(&igsd);

	tmp_hash = HASH_OF(&z);
	if (tmp_hash == NULL) {
		zval_ptr_dtor(&z);
		return FAILURE;
	}

	ZEND_HASH_FOREACH_STR_KEY_VAL(tmp_hash, key, d) {
		if (key == NULL) {  /* array key is a number, how? Skip it. */
			/* ??? */
			continue;
		}
		if (php_set_session_var(key, d, NULL)) { /* Added to session successfully */
			/* Refcounted types such as arrays, objects, references need to have references incremented manually, so that zval_ptr_dtor doesn't clean up pointers they include. */
			/* Non-refcounted types have the data copied. */
			Z_TRY_ADDREF_P(d);
		}
	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor(&z);

	return SUCCESS;
}
/* }}} */
#endif /* HAVE_PHP_SESSION && !defined(COMPILE_DL_SESSION) */

#if defined(HAVE_APCU_SUPPORT)
/* {{{ apc_serialize function */
static int APC_SERIALIZER_NAME(igbinary) ( APC_SERIALIZER_ARGS ) {
	(void)config;

	if (igbinary_serialize(buf, buf_len, (zval *)value) == 0) {
		/* flipped semantics */
		return 1;
	}
	return 0;
}
/* }}} */
/* {{{ apc_unserialize function */
static int APC_UNSERIALIZER_NAME(igbinary) ( APC_UNSERIALIZER_ARGS ) {
	(void)config;

	if (igbinary_unserialize(buf, buf_len, value) == 0) {
		/* flipped semantics - Succeeded. */
		return 1;
	}
	/* Failed. free return value */
	zval_ptr_dtor(value);
	ZVAL_NULL(value); /* and replace the incomplete value with null just in case APCU uses it in the future */
	return 0;
}
/* }}} */
#endif

/* {{{ igbinary_serialize_data_init */
/** Inits igbinary_serialize_data. */
inline static int igbinary_serialize_data_init(struct igbinary_serialize_data *igsd, bool scalar, struct igbinary_memory_manager *memory_manager) {
	int r = 0;

	if (memory_manager == NULL) {
		igsd->mm.alloc = igbinary_mm_wrapper_malloc;
		igsd->mm.realloc = igbinary_mm_wrapper_realloc;
		igsd->mm.free = igbinary_mm_wrapper_free;
		igsd->mm.context = NULL;
	} else {
		igsd->mm = *memory_manager;
	}

	igsd->buffer = NULL;
	igsd->buffer_size = 0;
	igsd->buffer_capacity = 32;
	igsd->string_count = 0;
	igsd->error = 0;

	igsd->buffer = (uint8_t *) igsd->mm.alloc(igsd->buffer_capacity, igsd->mm.context);
	if (igsd->buffer == NULL) {
		return 1;
	}

	igsd->scalar = scalar;
	if (!igsd->scalar) {
		hash_si_init(&igsd->strings, 16);
		hash_si_ptr_init(&igsd->references, 16);
		igsd->references_id = 0;
	}

	igsd->compact_strings = (bool)IGBINARY_G(compact_strings);

	return r;
}
/* }}} */
/* {{{ igbinary_serialize_data_deinit */
/** Deinits igbinary_serialize_data. */
inline static void igbinary_serialize_data_deinit(struct igbinary_serialize_data *igsd, int free_buffer) {
	if (free_buffer && igsd->buffer) {
		igsd->mm.free(igsd->buffer, igsd->mm.context);
	}

	if (!igsd->scalar) {
		hash_si_deinit(&igsd->strings);
		hash_si_ptr_deinit(&igsd->references);
	}
}
/* }}} */
/* {{{ igbinary_serialize_header */
/** Serializes header. */
inline static int igbinary_serialize_header(struct igbinary_serialize_data *igsd) {
	return igbinary_serialize32(igsd, IGBINARY_FORMAT_VERSION); /* version */
}
/* }}} */
/* {{{ igbinary_serialize_resize */
/** Expands igbinary_serialize_data. */
inline static int igbinary_serialize_resize(struct igbinary_serialize_data *igsd, size_t size) {
	if (igsd->buffer_size + size < igsd->buffer_capacity) {
		return 0;
	}

	while (igsd->buffer_size + size >= igsd->buffer_capacity) {
		igsd->buffer_capacity *= 2;
	}

	igsd->buffer = (uint8_t *) igsd->mm.realloc(igsd->buffer, igsd->buffer_capacity, igsd->mm.context);
	if (igsd->buffer == NULL)
		return 1;

	return 0;
}
/* }}} */
/* {{{ igbinary_serialize8 */
/** Serialize 8bit value. */
inline static int igbinary_serialize8(struct igbinary_serialize_data *igsd, uint8_t i) {
	if (UNEXPECTED(igbinary_serialize_resize(igsd, 1))) {
		return 1;
	}

	igsd->buffer[igsd->buffer_size++] = i;
	return 0;
}
/* }}} */
/* {{{ igbinary_serialize16 */
/** Serialize 16bit value. */
inline static int igbinary_serialize16(struct igbinary_serialize_data *igsd, uint16_t i) {
	uint8_t* append_buffer;
	if (UNEXPECTED(igbinary_serialize_resize(igsd, 2))) {
		return 1;
	}
	append_buffer = &igsd->buffer[igsd->buffer_size];
	append_buffer[0] = (uint8_t) (i >> 8 & 0xff);
	append_buffer[1] = (uint8_t) (i & 0xff);
	igsd->buffer_size += 2;

	return 0;
}
/* }}} */
/* {{{ igbinary_serialize32 */
/** Serialize 32bit value. */
inline static int igbinary_serialize32(struct igbinary_serialize_data *igsd, uint32_t i) {
	uint8_t* append_buffer;
	if (UNEXPECTED(igbinary_serialize_resize(igsd, 4))) {
		return 1;
	}

	append_buffer = &igsd->buffer[igsd->buffer_size];
	append_buffer[0] = (uint8_t) (i >> 24 & 0xff);
	append_buffer[1] = (uint8_t) (i >> 16 & 0xff);
	append_buffer[2] = (uint8_t) (i >> 8 & 0xff);
	append_buffer[3] = (uint8_t) (i & 0xff);
	igsd->buffer_size += 4;

	return 0;
}
/* }}} */
/* {{{ igbinary_serialize64 */
/** Serialize 64bit value. */
inline static int igbinary_serialize64(struct igbinary_serialize_data *igsd, uint64_t i) {
	uint8_t* append_buffer;
	if (UNEXPECTED(igbinary_serialize_resize(igsd, 8))) {
		return 1;
	}

	append_buffer = &igsd->buffer[igsd->buffer_size];
	append_buffer[0] = (uint8_t) (i >> 56 & 0xff);
	append_buffer[1] = (uint8_t) (i >> 48 & 0xff);
	append_buffer[2] = (uint8_t) (i >> 40 & 0xff);
	append_buffer[3] = (uint8_t) (i >> 32 & 0xff);
	append_buffer[4] = (uint8_t) (i >> 24 & 0xff);
	append_buffer[5] = (uint8_t) (i >> 16 & 0xff);
	append_buffer[6] = (uint8_t) (i >> 8 & 0xff);
	append_buffer[7] = (uint8_t) (i & 0xff);
	igsd->buffer_size += 8;

	return 0;
}
/* }}} */
/* {{{ igbinary_serialize_null */
/** Serializes null. */
inline static int igbinary_serialize_null(struct igbinary_serialize_data *igsd) {
	return igbinary_serialize8(igsd, igbinary_type_null);
}
/* }}} */
/* {{{ igbinary_serialize_bool */
/** Serializes bool. */
inline static int igbinary_serialize_bool(struct igbinary_serialize_data *igsd, int b) {
	return igbinary_serialize8(igsd, (uint8_t) (b ? igbinary_type_bool_true : igbinary_type_bool_false));
}
/* }}} */
/* {{{ igbinary_serialize_long */
/** Serializes zend_long. */
inline static int igbinary_serialize_long(struct igbinary_serialize_data *igsd, zend_long l) {
	zend_long k = l >= 0 ? l : -l;
	bool p = l >= 0;

	/* -ZEND_LONG_MIN is 0 otherwise. */
	if (l == ZEND_LONG_MIN) {
#if SIZEOF_ZEND_LONG == 8
		if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_long64n) != 0) {
			return 1;
		}

		if (igbinary_serialize64(igsd, (uint64_t) 0x8000000000000000) != 0) {
			return 1;
		}
#elif SIZEOF_ZEND_LONG == 4
		if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_long32n) != 0) {
			return 1;
		}
		if (igbinary_serialize32(igsd, (uint32_t) 0x80000000) != 0) {
			return 1;
		}
#else
#error "Strange sizeof(zend_long)."
#endif
		return 0;
	}

	if (k <= 0xff) {
		if (igbinary_serialize8(igsd, (uint8_t) (p ? igbinary_type_long8p : igbinary_type_long8n)) != 0) {
			return 1;
		}

		if (igbinary_serialize8(igsd, (uint8_t) k) != 0) {
			return 1;
		}
	} else if (k <= 0xffff) {
		if (igbinary_serialize8(igsd, (uint8_t) (p ? igbinary_type_long16p : igbinary_type_long16n)) != 0) {
			return 1;
		}

		if (igbinary_serialize16(igsd, (uint16_t) k) != 0) {
			return 1;
		}
#if SIZEOF_ZEND_LONG == 8
	} else if (k <= 0xffffffff) {
		if (igbinary_serialize8(igsd, (uint8_t) (p ? igbinary_type_long32p : igbinary_type_long32n)) != 0) {
			return 1;
		}

		if (igbinary_serialize32(igsd, (uint32_t) k) != 0) {
			return 1;
		}
	} else {
		if (igbinary_serialize8(igsd, (uint8_t) (p ? igbinary_type_long64p : igbinary_type_long64n)) != 0) {
			return 1;
		}
		if (igbinary_serialize64(igsd, (uint64_t) k) != 0) {
			return 1;
		}
	}
#elif SIZEOF_ZEND_LONG == 4
	} else {
		if (igbinary_serialize8(igsd, (uint8_t) (p ? igbinary_type_long32p : igbinary_type_long32n)) != 0) {
			return 1;
		}
		if (igbinary_serialize32(igsd, (uint32_t) k) != 0) {
			return 1;
		}
	}
#else
#error "Strange sizeof(zend_long)."
#endif

	return 0;
}
/* }}} */
/* {{{ igbinary_serialize_double */
/** Serializes double. */
inline static int igbinary_serialize_double(struct igbinary_serialize_data *igsd, double d) {
	union {
		double d;
		uint64_t u;
	} u;

	if (igbinary_serialize8(igsd, igbinary_type_double) != 0) {
		return 1;
	}

	u.d = d;

	return igbinary_serialize64(igsd, u.u);
}
/* }}} */
/* {{{ igbinary_serialize_string */
/** Serializes string.
 * Serializes each string once, after first time uses pointers.
 */
inline static int igbinary_serialize_string(struct igbinary_serialize_data *igsd, zend_string *s) {
	const size_t len = ZSTR_LEN(s);
	if (len == 0) {
		if (igbinary_serialize8(igsd, igbinary_type_string_empty) != 0) {
			return 1;
		}

		return 0;
	}

	if (!igsd->scalar && igsd->compact_strings) {
		struct hash_si_result result = hash_si_find_or_insert(&igsd->strings, s, igsd->string_count);
		if (result.code == hash_si_code_exists) {
			uint32_t value = result.value;
			if (value <= 0xff) {
				if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_string_id8) != 0) {
					return 1;
				}

				if (igbinary_serialize8(igsd, (uint8_t) value) != 0) {
					return 1;
				}
			} else if (value <= 0xffff) {
				if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_string_id16) != 0) {
					return 1;
				}

				if (igbinary_serialize16(igsd, (uint16_t) value) != 0) {
					return 1;
				}
			} else {
				if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_string_id32) != 0) {
					return 1;
				}

				if (igbinary_serialize32(igsd, (uint32_t) value) != 0) {
					return 1;
				}
			}
			return 0;
		} else if (EXPECTED(result.code == hash_si_code_inserted)) {
			/* Fall through to igbinary_serialize_chararray */
		} else {
			return 1;  /* Failed to allocate copy of string */
		}
	}

	igsd->string_count++; /* A new string is being serialized - update count so that duplicate class names can be used. */
	if (igbinary_serialize_chararray(igsd, ZSTR_VAL(s), len) != 0) {
		return 1;
	}
	return 0;
}
/* }}} */
/* {{{ igbinary_serialize_chararray */
/** Serializes string data. */
inline static int igbinary_serialize_chararray(struct igbinary_serialize_data *igsd, const char *s, size_t len) {
	if (len <= 0xff) {
		if (igbinary_serialize8(igsd, igbinary_type_string8) != 0) {
			return 1;
		}

		if (igbinary_serialize8(igsd, len) != 0) {
			return 1;
		}
	} else if (len <= 0xffff) {
		if (igbinary_serialize8(igsd, igbinary_type_string16) != 0) {
			return 1;
		}

		if (igbinary_serialize16(igsd, len) != 0) {
			return 1;
		}
	} else {
		if (igbinary_serialize8(igsd, igbinary_type_string32) != 0) {
			return 1;
		}

		if (igbinary_serialize32(igsd, len) != 0) {
			return 1;
		}
	}

	if (igbinary_serialize_resize(igsd, len)) {
		return 1;
	}

	memcpy(igsd->buffer+igsd->buffer_size, s, len);
	igsd->buffer_size += len;

	return 0;
}
/* }}} */
/* {{{ igbinay_serialize_array */
/** Serializes array or objects inner properties. */
inline static int igbinary_serialize_array(struct igbinary_serialize_data *igsd, zval *z, bool object, bool incomplete_class) {
	/* If object=true: z is IS_OBJECT */
	/* If object=false: z is either IS_ARRAY, or IS_REFERENCE pointing to an IS_ARRAY. */
	HashTable *h;
	size_t n;
	zval *d;
	zval *z_original;

	zend_string *key;
	zend_long key_index;

	z_original = z;
	ZVAL_DEREF(z);

	/* hash */
	h = object ? Z_OBJPROP_P(z) : HASH_OF(z);

	/* hash size */
	n = h ? zend_hash_num_elements(h) : 0;

	/* incomplete class magic member */
	if (n > 0 && incomplete_class) {
		--n;
	}

	/* if it is an array or a reference to an array, then add a reference unique to that **reference** to that array */
	if (!object && igbinary_serialize_array_ref(igsd, z_original, false) == 0) {
		return 0;
	}

	if (n <= 0xff) {
		if (igbinary_serialize8(igsd, igbinary_type_array8) != 0) {
			return 1;
		}

		if (igbinary_serialize8(igsd, n) != 0) {
			return 1;
		}
	} else if (n <= 0xffff) {
		if (igbinary_serialize8(igsd, igbinary_type_array16) != 0) {
			return 1;
		}

		if (igbinary_serialize16(igsd, n) != 0) {
			return 1;
		}
	} else {
		if (igbinary_serialize8(igsd, igbinary_type_array32) != 0) {
			return 1;
		}

		if (igbinary_serialize32(igsd, n) != 0) {
			return 1;
		}
	}

	if (n == 0) {
		return 0;
	}

	/* serialize properties. */
	ZEND_HASH_FOREACH_KEY_VAL(h, key_index, key, d) {
		/* skip magic member in incomplete classes */
		if (incomplete_class && strcmp(ZSTR_VAL(key), MAGIC_MEMBER) == 0) {
			continue;
		}

		if (key == NULL) {
			/* Key is numeric */
			if (igbinary_serialize_long(igsd, key_index) != 0) {
				return 1;
			}
		} else {
			/* Key is string */
			if (igbinary_serialize_string(igsd, key) != 0) {
				return 1;
			}
		}

		if (d == NULL) {
			php_error_docref(NULL, E_NOTICE, "Received NULL value from hash.");
			return 1;
		}

		/* https://wiki.php.net/phpng-int - This is a weak pointer, completely different from a PHP reference (&$foo has a type of IS_REFERENCE) */
		if (Z_TYPE_P(d) == IS_INDIRECT) {
			d = Z_INDIRECT_P(d);
		}
		/* we should still add element even if it's not OK,
		 * since we already wrote the length of the array before */
		if (Z_TYPE_P(d) == IS_UNDEF) {
			if (igbinary_serialize_null(igsd)) {
				return 1;
			}
		} else {
			if (igbinary_serialize_zval(igsd, d)) {
				return 1;
			}
		}
	} ZEND_HASH_FOREACH_END();

	return 0;
}
/* }}} */
/* {{{ igbinary_serialize_array_ref */
/** Serializes array reference (or reference in an object). Returns 0 on success. */
inline static int igbinary_serialize_array_ref(struct igbinary_serialize_data *igsd, zval *z, bool object) {
	size_t t;
	zend_uintptr_t key;  /* The address of the pointer to the zend_refcounted struct or other struct */
	static int INVALID_KEY;  /* Not used, but we take the pointer of this knowing other zvals wont share it*/

	/* Similar to php_var_serialize_intern's first part, as well as php_add_var_hash, for printing R: (reference) or r:(object) */
	/* However, it differs from the built in serialize() in that references to objects are preserved when serializing and unserializing? (TODO check, test for backwards compatibility) */
	zend_bool is_ref = Z_ISREF_P(z);
	/* Do I have to dereference object references so that reference ids will be the same as in php5? */
	/* If I do, then more tests fail. */
	/* is_ref || IS_OBJECT implies it has a unique refcounted struct */
	if (object && Z_TYPE_P(z) == IS_OBJECT) {
		key = (zend_uintptr_t) Z_OBJ_HANDLE_P(z); /* expand object handle(uint32_t), cast to 32-bit/64-bit pointer */
	} else if (is_ref) {
		/* NOTE: PHP removed switched from `zval*` to `zval` for the values stored in HashTables. If an array has two references to the same ZVAL, then those references will have different zvals. We use Z_COUNTED_P(ref), which will be the same iff the references are the same */
		/* IS_REF implies there is a unique reference counting pointer for the reference */
		key = (zend_uintptr_t) Z_COUNTED_P(z);
	} else if (Z_TYPE_P(z) == IS_ARRAY) {
		if (Z_REFCOUNTED_P(z)) {
			key = (zend_uintptr_t) Z_COUNTED_P(z);
		} else { /* Not sure if this could be a constant */
			key = (zend_uintptr_t) z;
		}
	} else {
		/* Nothing else is going to reference this when this is serialized, this isn't ref counted or an object, shouldn't be reached. */
		/* Increment the reference id for the deserializer, give up. */
		++igsd->references_id;
		php_error_docref(NULL, E_NOTICE, "igbinary_serialize_array_ref expected either object or reference (param object=%s), got neither (zend_type=%d)", object ? "true" : "false", (int)Z_TYPE_P(z));
		return 1;
	}

	/* FIXME hack? If the top-level element was an array, we assume that it can't be a reference when we serialize it, */
	/* because that's the way it was serialized in php5. */
	/* Does this work with different forms of recursive arrays? */
	if (igsd->references_id == 0 && !object) {
		key = (zend_uintptr_t)&INVALID_KEY;
	}

	t = hash_si_ptr_find_or_insert(&igsd->references, key, igsd->references_id);
	if (t == SIZE_MAX) {
		igsd->references_id++;
		return 1;
	} else {
		enum igbinary_type type;
		if (t <= 0xff) {
			type = object ? igbinary_type_objref8 : igbinary_type_ref8;
			if (igbinary_serialize8(igsd, (uint8_t) type) != 0) {
				return 1;
			}

			if (igbinary_serialize8(igsd, (uint8_t) t) != 0) {
				return 1;
			}
		} else if (t <= 0xffff) {
			type = object ? igbinary_type_objref16 : igbinary_type_ref16;
			if (igbinary_serialize8(igsd, (uint8_t) type) != 0) {
				return 1;
			}

			if (igbinary_serialize16(igsd, (uint16_t) t) != 0) {
				return 1;
			}
		} else {
			type = object ? igbinary_type_objref32 : igbinary_type_ref32;
			if (igbinary_serialize8(igsd, (uint8_t) type) != 0) {
				return 1;
			}

			if (igbinary_serialize32(igsd, (uint32_t) t) != 0) {
				return 1;
			}
		}

		return 0;
	}

	return 1;
}
/* }}} */
/* {{{ igbinary_serialize_array_sleep */
/** Serializes object's properties array with __sleep -function. */
inline static int igbinary_serialize_array_sleep(struct igbinary_serialize_data *igsd, zval *z, HashTable *h, zend_class_entry *ce, bool incomplete_class) {
	HashTable *object_properties;
	size_t n = zend_hash_num_elements(h);
	zval *d;
	zval *v;

	zend_string *key;

	/* Decrease array size by one, because of magic member (with class name) */
	if (n > 0 && incomplete_class) {
		--n;
	}

	/* Serialize array id. */
	if (n <= 0xff) {
		if (igbinary_serialize8(igsd, igbinary_type_array8) != 0) {
			return 1;
		}

		if (igbinary_serialize8(igsd, n) != 0) {
			return 1;
		}
	} else if (n <= 0xffff) {
		if (igbinary_serialize8(igsd, igbinary_type_array16) != 0) {
			return 1;
		}

		if (igbinary_serialize16(igsd, n) != 0) {
			return 1;
		}
	} else {
		if (igbinary_serialize8(igsd, igbinary_type_array32) != 0) {
			return 1;
		}

		if (igbinary_serialize32(igsd, n) != 0) {
			return 1;
		}
	}

	if (n == 0) {
		return 0;
	}

	object_properties = Z_OBJPROP_P(z);

	ZEND_HASH_FOREACH_STR_KEY_VAL(h, key, d) {
		/* skip magic member in incomplete classes */
		if (incomplete_class && key != NULL && strcmp(ZSTR_VAL(key), MAGIC_MEMBER) == 0) {
			continue;
		}

		if (d == NULL || Z_TYPE_P(d) != IS_STRING) {
			php_error_docref(NULL, E_NOTICE, "__sleep should return an array only "
					"containing the names of instance-variables to "
					"serialize");

			/* we should still add element even if it's not OK,
			 * since we already wrote the length of the array before
			 * serialize null as key-value pair */
			if (igbinary_serialize_null(igsd) != 0) {
				return 1;
			}
		} else {
			zend_string *prop_name = Z_STR_P(d);

			if ((v = zend_hash_find(object_properties, prop_name)) != NULL) {
				if (igbinary_serialize_string(igsd, prop_name) != 0) {
					return 1;
				}

				if (Z_TYPE_P(v) == IS_INDIRECT) {
					v = Z_INDIRECT_P(v);
				}
				if (igbinary_serialize_zval(igsd, v) != 0) {
					return 1;
				}
			} else if (ce) {
				zend_string *mangled_prop_name;

				v = NULL;

				do {
					/* try private */
					// TODO: check for FAILURE
					mangled_prop_name = zend_mangle_property_name(ZSTR_VAL(ce->name), ZSTR_LEN(ce->name),
						ZSTR_VAL(prop_name), ZSTR_LEN(prop_name), ce->type & ZEND_INTERNAL_CLASS);
					v = zend_hash_find(object_properties, mangled_prop_name);

					/* try protected */
					if (v == NULL) {
						zend_string_release(mangled_prop_name);
						mangled_prop_name = zend_mangle_property_name("*", 1,
							ZSTR_VAL(prop_name), ZSTR_LEN(prop_name), ce->type & ZEND_INTERNAL_CLASS);

						v = zend_hash_find(object_properties, mangled_prop_name);
					}

					/* Neither property exist */
					if (v == NULL) {
						zend_string_release(mangled_prop_name);

						php_error_docref(NULL, E_NOTICE, "\"%s\" returned as member variable from __sleep() but does not exist", Z_STRVAL_P(d));
						if (igbinary_serialize_string(igsd, Z_STR_P(d)) != 0) {
							return 1;
						}

						if (igbinary_serialize_null(igsd) != 0) {
							return 1;
						}

						break;
					}

					if (Z_TYPE_P(v) == IS_INDIRECT) {
						v = Z_INDIRECT_P(v);
					}

					if (igbinary_serialize_string(igsd, mangled_prop_name) != 0) {
						zend_string_release(mangled_prop_name);
						return 1;
					}

					zend_string_release(mangled_prop_name);
					if (igbinary_serialize_zval(igsd, v) != 0) {
						return 1;
					}
				} while (0);

			} else {
				/* if all else fails, just serialize the value in anyway. */
				if (igbinary_serialize_string(igsd, Z_STR_P(d)) != 0) {
					return 1;
				}

				if (Z_TYPE_P(v) == IS_INDIRECT) {
					v = Z_INDIRECT_P(v);
				}

				if (igbinary_serialize_zval(igsd, v) != 0) {
					return 1;
				}
			}
		}
	} ZEND_HASH_FOREACH_END();

	return 0;
}
/* }}} */
/* {{{ igbinary_serialize_object_name */
/** Serialize object name. */
inline static int igbinary_serialize_object_name(struct igbinary_serialize_data *igsd, zend_string *class_name) {
	struct hash_si_result result = hash_si_find_or_insert(&igsd->strings, class_name, igsd->string_count);
	if (result.code == hash_si_code_inserted) {
		const size_t name_len = ZSTR_LEN(class_name);
		igsd->string_count += 1;

		if (name_len <= 0xff) {
			if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_object8) != 0) {
				return 1;
			}

			if (igbinary_serialize8(igsd, (uint8_t) name_len) != 0) {
				return 1;
			}
		} else if (name_len <= 0xffff) {
			if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_object16) != 0) {
				return 1;
			}

			if (igbinary_serialize16(igsd, (uint16_t) name_len) != 0) {
				return 1;
			}
		} else {
			if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_object32) != 0) {
				return 1;
			}

			if (igbinary_serialize32(igsd, (uint32_t) name_len) != 0) {
				return 1;
			}
		}

		if (igbinary_serialize_resize(igsd, name_len)) {
			return 1;
		}

		memcpy(igsd->buffer+igsd->buffer_size, ZSTR_VAL(class_name), name_len);
		igsd->buffer_size += name_len;
	} else if (EXPECTED(result.code == hash_si_code_exists)) {
		/* already serialized string */
		uint32_t value = result.value;
		if (value <= 0xff) {
			if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_object_id8) != 0) {
				return 1;
			}

			if (igbinary_serialize8(igsd, (uint8_t) value) != 0) {
				return 1;
			}
		} else if (value <= 0xffff) {
			if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_object_id16) != 0) {
				return 1;
			}

			if (igbinary_serialize16(igsd, (uint16_t) value) != 0) {
				return 1;
			}
		} else {
			if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_object_id32) != 0) {
				return 1;
			}

			if (igbinary_serialize32(igsd, (uint32_t) value) != 0) {
				return 1;
			}
		}
	} else {
		return 1; /* Failed to allocate copy of string */
	}

	return 0;
}
/* }}} */
/* {{{ igbinary_serialize_object */
/** Serialize object.
 * @see ext/standard/var.c
 * */
inline static int igbinary_serialize_object(struct igbinary_serialize_data *igsd, zval *z) {
	PHP_CLASS_ATTRIBUTES;

	zend_class_entry *ce;

	zval f;
	zval h;

	int r = 0;

	unsigned char *serialized_data = NULL;
	size_t serialized_len;


	if (igbinary_serialize_array_ref(igsd, z, true) == 0) {
		return 0;
	}

	ce = Z_OBJCE_P(z);

	/* custom serializer */
	if (ce && ce->serialize != NULL) {
		if (ce->serialize(z, &serialized_data, &serialized_len, (zend_serialize_data *)NULL) == SUCCESS && !EG(exception)) {
			if (igbinary_serialize_object_name(igsd, ce->name) != 0) {
				if (serialized_data) {
					efree(serialized_data);
				}
				return 1;
			}


			if (serialized_len <= 0xff) {
				if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_object_ser8) != 0) {
					if (serialized_data) {
						efree(serialized_data);
					}
					return 1;
				}

				if (igbinary_serialize8(igsd, (uint8_t) serialized_len) != 0) {
					if (serialized_data) {
						efree(serialized_data);
					}
					return 1;
				}
			} else if (serialized_len <= 0xffff) {
				if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_object_ser16) != 0) {
					if (serialized_data) {
						efree(serialized_data);
					}
					return 1;
				}

				if (igbinary_serialize16(igsd, (uint16_t) serialized_len) != 0) {
					if (serialized_data) {
						efree(serialized_data);
					}
					return 1;
				}
			} else {
				if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_object_ser32) != 0) {
					if (serialized_data) {
						efree(serialized_data);
					}
					return 1;
				}

				if (igbinary_serialize32(igsd, (uint32_t) serialized_len) != 0) {
					if (serialized_data) {
						efree(serialized_data);
					}
					return 1;
				}
			}

			if (igbinary_serialize_resize(igsd, serialized_len)) {
				if (serialized_data) {
					efree(serialized_data);
				}

				return 1;
			}

			memcpy(igsd->buffer+igsd->buffer_size, serialized_data, serialized_len);
			igsd->buffer_size += serialized_len;
		} else if (EG(exception)) {
			/* exception, return failure */
			r = 1;
		} else {
			/* Serialization callback failed, assume null output */
			r = igbinary_serialize_null(igsd);
		}

		if (serialized_data) {
			efree(serialized_data);
		}

		return r;
	}

	/* serialize class name */
	PHP_SET_CLASS_ATTRIBUTES(z);
	if (igbinary_serialize_object_name(igsd, class_name) != 0) {
		PHP_CLEANUP_CLASS_ATTRIBUTES();
		return 1;
	}
	PHP_CLEANUP_CLASS_ATTRIBUTES();

	if (ce && ce != PHP_IC_ENTRY && zend_hash_str_exists(&ce->function_table, "__sleep", sizeof("__sleep") - 1)) {
		/* function name string */
		ZVAL_STRINGL(&f, "__sleep", sizeof("__sleep") - 1);

		ZVAL_UNDEF(&h);
		/* calling z->__sleep */
		r = call_user_function_ex(CG(function_table), z, &f, &h, 0, 0, 1, NULL);

		zval_dtor(&f);

		if (r == SUCCESS && !EG(exception)) {
			r = 0;

			if (Z_TYPE(h) == IS_UNDEF) {
				/* FIXME: is this ok? */
				/* Valid, but skip */
			} else if (HASH_OF(&h)) {
				r = igbinary_serialize_array_sleep(igsd, z, HASH_OF(&h), ce, incomplete_class);
			} else {
				php_error_docref(NULL, E_NOTICE, "__sleep should return an array only "
						"containing the names of instance-variables to "
						"serialize");

				/* empty array */
				r = igbinary_serialize8(igsd, igbinary_type_array8);
				if (r == 0) {
					r = igbinary_serialize8(igsd, 0);
				}
			}
		} else {
			r = 1;
		}

		/* cleanup */
		zval_ptr_dtor(&h);

		return r;
	} else {
		return igbinary_serialize_array(igsd, z, true, incomplete_class);
	}
}
/* }}} */
/* {{{ igbinary_serialize_zval */
/** Serialize zval. */
static int igbinary_serialize_zval(struct igbinary_serialize_data *igsd, zval *z) {
	if (Z_ISREF_P(z)) {
		if (igbinary_serialize8(igsd, (uint8_t) igbinary_type_ref) != 0) {
			return 1;
		}

		switch (Z_TYPE_P(Z_REFVAL_P(z))) {
		case IS_ARRAY:
			return igbinary_serialize_array(igsd, z, false, false);
		case IS_OBJECT:
			break; /* Fall through */
		default:
			/* Serialize a reference if zval already added */
			if (igbinary_serialize_array_ref(igsd, z, false) == 0) {
				return 0;
			}
			/* Fall through */
		}

		ZVAL_DEREF(z);
	}
	switch (Z_TYPE_P(z)) {
		case IS_RESOURCE:
			return igbinary_serialize_null(igsd);
		case IS_OBJECT:
			return igbinary_serialize_object(igsd, z);
		case IS_ARRAY:
			/* if is_ref, then php5 would have called igbinary_serialize_array_ref */
			return igbinary_serialize_array(igsd, z, false, false);
		case IS_STRING:
			return igbinary_serialize_string(igsd, Z_STR_P(z));
		case IS_LONG:
			return igbinary_serialize_long(igsd, Z_LVAL_P(z));
		case IS_NULL:
			return igbinary_serialize_null(igsd);
		case IS_UNDEF:
			// As of php 7.1.3, started seeing "zval has unknown type 0"
			zend_error(E_WARNING, "igbinary_serialize_zval: zval has unexpected type IS_UNDEF(0)");
			return igbinary_serialize_null(igsd);
		case IS_TRUE:
			return igbinary_serialize_bool(igsd, 1);
		case IS_FALSE:
			return igbinary_serialize_bool(igsd, 0);
		case IS_DOUBLE:
			return igbinary_serialize_double(igsd, Z_DVAL_P(z));
		default:
			zend_error(E_ERROR, "igbinary_serialize_zval: zval has unknown type %d", (int)Z_TYPE_P(z));
			/* not reached */
			return 1;
	}

	return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_data_init */
/** Inits igbinary_unserialize_data_init. */
inline static int igbinary_unserialize_data_init(struct igbinary_unserialize_data *igsd) {
	smart_string empty_str = { 0 };

	igsd->buffer = NULL;
	igsd->buffer_end = NULL;
	igsd->buffer_ptr = NULL;

	igsd->strings = NULL;
	igsd->strings_count = 0;
	igsd->strings_capacity = 4;
	igsd->string0_buf = empty_str;

	igsd->error = 0;
	igsd->references = NULL;
	igsd->references_count = 0;
	igsd->references_capacity = 4;

	igsd->references = emalloc(sizeof(igsd->references[0]) * igsd->references_capacity);
	if (igsd->references == NULL) {
		return 1;
	}

	igsd->strings = (zend_string **) emalloc(sizeof(zend_string *) * igsd->strings_capacity);
	if (igsd->strings == NULL) {
		efree(igsd->references);
		igsd->references = NULL;
		return 1;
	}

	/** Don't bother allocating zvals which __wakeup, probably not common */
	igsd->wakeup = NULL;
	igsd->wakeup_count = 0;
	igsd->wakeup_capacity = 0;

	return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_data_deinit */
/** Deinits igbinary_unserialize_data_init. */
inline static void igbinary_unserialize_data_deinit(struct igbinary_unserialize_data *igsd) {
	if (igsd->strings) {
		size_t i;
		for (i = 0; i < igsd->strings_count; i++) {
			zend_string *s = igsd->strings[i];
#if ZEND_DEBUG
			ZEND_ASSERT(GC_REFCOUNT(s) >= 1);
#endif
			zend_string_release(s);

		}

		efree(igsd->strings);
		igsd->strings = NULL;
	}

	if (igsd->references) {
		efree(igsd->references);
		igsd->references = NULL;
	}
	if (igsd->wakeup) {
		/*
		size_t i;
		size_t n = igsd->wakeup_count;
		for (i = 0; i < n; i++) {
			convert_to_null(&igsd->wakeup[i]);
		}
		*/
		efree(igsd->wakeup);
	}

	smart_string_free(&igsd->string0_buf);

	return;
}
/* }}} */
/* {{{ igbinary_unserialize_header_emit_warning */
/* Precondition: igsd->buffer_size >= 4 */
inline static void igbinary_unserialize_header_emit_warning(struct igbinary_unserialize_data *igsd, int version) {
	int i;
	char buf[9], *it;
	for (i = 0; i < 4; i++) {
		if (!isprint((int)igsd->buffer[i])) {
			if (version != 0 && (((unsigned int)version) & 0xff000000) == (unsigned int)version) {
				// Check if high order byte was set instead of low order byte
				zend_error(E_WARNING, "igbinary_unserialize_header: unsupported version: %u, should be %u or %u (wrong endianness?)", (unsigned int) version, 0x00000001, (unsigned int) IGBINARY_FORMAT_VERSION);
				return;
			}
			// Binary data, or a version number from a future release.
			zend_error(E_WARNING, "igbinary_unserialize_header: unsupported version: %u, should be %u or %u", (unsigned int) version, 0x00000001, (unsigned int) IGBINARY_FORMAT_VERSION);
			return;
		}
	}

	for (it = buf, i = 0; i < 4; i++) {
		char c = igsd->buffer[i];
		if (c == '"' || c == '\\') {
			*it++ = '\\';
		}
		*it++ = c;
	}
	*it = '\0';
	zend_error(E_WARNING, "igbinary_unserialize_header: unsupported version: \"%s\"..., should begin with a binary version header of \"\\x00\\x00\\x00\\x01\" or \"\\x00\\x00\\x00\\x%02x\"", buf, (int)IGBINARY_FORMAT_VERSION);
}
/* }}} */
/* {{{ igbinary_unserialize_header */
/** Unserialize header. Check for version. */
inline static int igbinary_unserialize_header(struct igbinary_unserialize_data *igsd) {
	uint32_t version;

	if (IGB_NEEDS_MORE_DATA(igsd, 5)) {
		zend_error(E_WARNING, "igbinary_unserialize_header: expected at least 5 bytes of data, got %u byte(s)", IGB_REMAINING_BYTES(igsd));
		return 1;
	}

	version = igbinary_unserialize32(igsd);

	/* Support older version 1 and the current format 2 */
	if (version == IGBINARY_FORMAT_VERSION || version == 0x00000001) {
		return 0;
	} else {
		igbinary_unserialize_header_emit_warning(igsd, version);
		return 1;
	}
}
/* }}} */
/* {{{ igbinary_unserialize8 */
/** Unserialize 8bit value. */
inline static uint8_t igbinary_unserialize8(struct igbinary_unserialize_data *igsd) {
	return *(igsd->buffer_ptr++);
}
/* }}} */
/* {{{ igbinary_unserialize16 */
/** Unserialize 16bit value. */
inline static uint16_t igbinary_unserialize16(struct igbinary_unserialize_data *igsd) {
	uint16_t ret =
	       ((uint16_t) (igsd->buffer_ptr[0]) << 8) |
	       ((uint16_t) (igsd->buffer_ptr[1]));
	igsd->buffer_ptr += 2;
	return ret;
}
/* }}} */
/* {{{ igbinary_unserialize32 */
/** Unserialize 32bit value. */
inline static uint32_t igbinary_unserialize32(struct igbinary_unserialize_data *igsd) {
	uint32_t ret =
	       ((uint32_t) (igsd->buffer_ptr[0]) << 24) |
	       ((uint32_t) (igsd->buffer_ptr[1]) << 16) |
	       ((uint32_t) (igsd->buffer_ptr[2]) << 8)  |
	       ((uint32_t) (igsd->buffer_ptr[3]));
	igsd->buffer_ptr += 4;
	return ret;
}
/* }}} */
/* {{{ igbinary_unserialize64 */
/** Unserialize 64bit value. */
inline static uint64_t igbinary_unserialize64(struct igbinary_unserialize_data *igsd) {
	uint64_t ret =
	       ((uint64_t) ((igsd->buffer_ptr[0])) << 56) |
	       ((uint64_t) ((igsd->buffer_ptr[1])) << 48) |
	       ((uint64_t) ((igsd->buffer_ptr[2])) << 40) |
	       ((uint64_t) ((igsd->buffer_ptr[3])) << 32) |
	       ((uint64_t) ((igsd->buffer_ptr[4])) << 24) |
	       ((uint64_t) ((igsd->buffer_ptr[5])) << 16) |
	       ((uint64_t) ((igsd->buffer_ptr[6])) << 8)  |
	       ((uint64_t) ((igsd->buffer_ptr[7])) << 0);
	igsd->buffer_ptr += 8;
	return ret;
}
/* }}} */
/* {{{ igbinary_unserialize_long */
/** Unserializes zend_long */
inline static int igbinary_unserialize_long(struct igbinary_unserialize_data *igsd, enum igbinary_type t, zend_long *ret) {
	uint32_t tmp32;
#if SIZEOF_ZEND_LONG == 8
	uint64_t tmp64;
#endif

	if (t == igbinary_type_long8p || t == igbinary_type_long8n) {
		if (IGB_NEEDS_MORE_DATA(igsd, 1)) {
			zend_error(E_WARNING, "igbinary_unserialize_long: end-of-data");
			return 1;
		}

		*ret = (zend_long) (t == igbinary_type_long8n ? -1 : 1) * igbinary_unserialize8(igsd);
	} else if (t == igbinary_type_long16p || t == igbinary_type_long16n) {
		if (IGB_NEEDS_MORE_DATA(igsd, 2)) {
			zend_error(E_WARNING, "igbinary_unserialize_long: end-of-data");
			return 1;
		}

		*ret = (zend_long) (t == igbinary_type_long16n ? -1 : 1) * igbinary_unserialize16(igsd);
	} else if (t == igbinary_type_long32p || t == igbinary_type_long32n) {
		if (IGB_NEEDS_MORE_DATA(igsd, 4)) {
			zend_error(E_WARNING, "igbinary_unserialize_long: end-of-data");
			return 1;
		}

		/* check for boundaries */
		tmp32 = igbinary_unserialize32(igsd);
#if SIZEOF_ZEND_LONG == 4
		if (tmp32 > 0x80000000 || (tmp32 == 0x80000000 && t == igbinary_type_long32p)) {
			zend_error(E_WARNING, "igbinary_unserialize_long: 64bit long on 32bit platform?");
			tmp32 = 0; /* t == igbinary_type_long32p ? LONG_MAX : LONG_MIN; */
		}
#endif
		*ret = (zend_long) (t == igbinary_type_long32n ? -1 : 1) * tmp32;
	} else if (t == igbinary_type_long64p || t == igbinary_type_long64n) {
#if SIZEOF_ZEND_LONG == 8
		if (IGB_NEEDS_MORE_DATA(igsd, 8)) {
			zend_error(E_WARNING, "igbinary_unserialize_long: end-of-data");
			return 1;
		}

		/* check for boundaries */
		tmp64 = igbinary_unserialize64(igsd);
		if (tmp64 > 0x8000000000000000 || (tmp64 == 0x8000000000000000 && t == igbinary_type_long64p)) {
			zend_error(E_WARNING, "igbinary_unserialize_long: too big 64bit long.");
			tmp64 = 0; /* t == igbinary_type_long64p ? LONG_MAX : LONG_MIN */;
		}

		*ret = (zend_long) (t == igbinary_type_long64n ? -1 : 1) * tmp64;
#elif SIZEOF_ZEND_LONG == 4
		/* can't put 64bit long into 32bit one, placeholder zero */
		*ret = 0;
		igbinary_unserialize64(igsd);
		zend_error(E_WARNING, "igbinary_unserialize_long: 64bit long on 32bit platform");
#else
#error "Strange sizeof(zend_long)."
#endif
	} else {
		*ret = 0;
		zend_error(E_WARNING, "igbinary_unserialize_long: unknown type '%02x', position %zu", t, IGB_BUFFER_OFFSET(igsd));
		return 1;
	}

	return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_double */
/** Unserializes double. */
inline static int igbinary_unserialize_double(struct igbinary_unserialize_data *igsd, enum igbinary_type t, double *ret) {
	union {
		double d;
		uint64_t u;
	} u;

	(void) t;

	if (IGB_NEEDS_MORE_DATA(igsd, 8)) {
		zend_error(E_WARNING, "igbinary_unserialize_double: end-of-data");
		return 1;
	}


	u.u = igbinary_unserialize64(igsd);

	*ret = u.d;

	return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_string */
/** Unserializes string. Unserializes both actual string or by string id. Returns NULL on error. */
inline static zend_string* igbinary_unserialize_string(struct igbinary_unserialize_data *igsd, enum igbinary_type t) {
	size_t i;
	zend_string *zstr;
	if (t == igbinary_type_string_id8 || t == igbinary_type_object_id8) {
		if (IGB_NEEDS_MORE_DATA(igsd, 1)) {
			zend_error(E_WARNING, "igbinary_unserialize_string: end-of-data");
			return NULL;
		}
		i = igbinary_unserialize8(igsd);
	} else if (t == igbinary_type_string_id16 || t == igbinary_type_object_id16) {
		if (IGB_NEEDS_MORE_DATA(igsd, 2)) {
			zend_error(E_WARNING, "igbinary_unserialize_string: end-of-data");
			return NULL;
		}
		i = igbinary_unserialize16(igsd);
	} else if (t == igbinary_type_string_id32 || t == igbinary_type_object_id32) {
		if (IGB_NEEDS_MORE_DATA(igsd, 4)) {
			zend_error(E_WARNING, "igbinary_unserialize_string: end-of-data");
			return NULL;
		}
		i = igbinary_unserialize32(igsd);
	} else {
		zend_error(E_WARNING, "igbinary_unserialize_string: unknown type '%02x', position %zu", t, IGB_BUFFER_OFFSET(igsd));
		return NULL;
	}

	if (i >= igsd->strings_count) {
		zend_error(E_WARNING, "igbinary_unserialize_string: string index is out-of-bounds");
		return NULL;
	}

	zstr = igsd->strings[i];
	// Add one more ref - Callers of this will decrease refs as needed
	zend_string_addref(zstr);
	return zstr;
}
/* }}} */
/* {{{ igbinary_unserialize_chararray */
/** Unserializes chararray of string. Returns NULL on error. */
inline static zend_string* igbinary_unserialize_chararray(struct igbinary_unserialize_data *igsd, enum igbinary_type t) {
	size_t l;
	zend_string *zstr;

	if (t == igbinary_type_string8 || t == igbinary_type_object8) {
		if (IGB_NEEDS_MORE_DATA(igsd, 1)) {
			zend_error(E_WARNING, "igbinary_unserialize_chararray: end-of-data");
			return NULL;
		}
		l = igbinary_unserialize8(igsd);
		if (IGB_NEEDS_MORE_DATA(igsd, l)) {
			zend_error(E_WARNING, "igbinary_unserialize_chararray: end-of-data");
			return NULL;
		}
		/* Requires converting these into interned strings. Maybe add one-char in v3 of igbinary format?
		if (l == 1) {
			zstr = ZSTR_CHAR((zend_uchar)igsd->buffer[igsd->buffer_offset]);
			igsd->strings[igsd->strings_count] = zstr;
			igsd->strings_count += 1;
			igsd->buffer_offset++;
			return zstr;
		}
		*/
	} else if (t == igbinary_type_string16 || t == igbinary_type_object16) {
		if (IGB_NEEDS_MORE_DATA(igsd, 2)) {
			zend_error(E_WARNING, "igbinary_unserialize_chararray: end-of-data");
			return NULL;
		}
		l = igbinary_unserialize16(igsd);
		if (IGB_NEEDS_MORE_DATA(igsd, l)) {
			zend_error(E_WARNING, "igbinary_unserialize_chararray: end-of-data");
			return NULL;
		}
	} else if (t == igbinary_type_string32 || t == igbinary_type_object32) {
		if (IGB_NEEDS_MORE_DATA(igsd, 4)) {
			zend_error(E_WARNING, "igbinary_unserialize_chararray: end-of-data");
			return NULL;
		}
		l = igbinary_unserialize32(igsd);
		if (IGB_NEEDS_MORE_DATA(igsd, l)) {
			zend_error(E_WARNING, "igbinary_unserialize_chararray: end-of-data");
			return NULL;
		}
	} else {
		zend_error(E_WARNING, "igbinary_unserialize_chararray: unknown type '%02x', position %zu", t, IGB_BUFFER_OFFSET(igsd));
		return NULL;
	}

	if (igsd->strings_count + 1 > igsd->strings_capacity) {
		zend_string **new_strings;
		igsd->strings_capacity *= 2;

		new_strings = (zend_string **) erealloc(igsd->strings, sizeof(zend_string *) * igsd->strings_capacity);
		if (new_strings == NULL) {
			// The cleanup function will take care of destroying the allocated zend_strings.
			return NULL;
		}
		igsd->strings = new_strings;
	}

	zstr = zend_string_init((const char*)(igsd->buffer + IGB_BUFFER_OFFSET(igsd)), l, 0);

	igsd->buffer_ptr += l;

	if (zstr == NULL) {
		return NULL;
	}
	zend_string_addref(zstr);

	igsd->strings[igsd->strings_count] = zstr;
	igsd->strings_count += 1;
	return zstr;
}
/* }}} */
/* {{{ igbinary_unserialize_array */
/** Unserializes array. */
inline static int igbinary_unserialize_array(struct igbinary_unserialize_data *igsd, enum igbinary_type t, zval *const z, int flags) {
	/* WANT_REF means that z will be wrapped by an IS_REFERENCE */
	size_t n;
	size_t i;

	zval v;
	zval *vp;
	zval *z_deref;

	enum igbinary_type key_type;

	HashTable *h;

	if (t == igbinary_type_array8) {
		if (IGB_NEEDS_MORE_DATA(igsd, 1)) {
			zend_error(E_WARNING, "igbinary_unserialize_array: end-of-data");
			return 1;
		}
		n = igbinary_unserialize8(igsd);
	} else if (t == igbinary_type_array16) {
		if (IGB_NEEDS_MORE_DATA(igsd, 2)) {
			zend_error(E_WARNING, "igbinary_unserialize_array: end-of-data");
			return 1;
		}
		n = igbinary_unserialize16(igsd);
	} else if (t == igbinary_type_array32) {
		if (IGB_NEEDS_MORE_DATA(igsd, 4)) {
			zend_error(E_WARNING, "igbinary_unserialize_array: end-of-data");
			return 1;
		}
		n = igbinary_unserialize32(igsd);
	} else {
		zend_error(E_WARNING, "igbinary_unserialize_array: unknown type '%02x', position %zu", t, IGB_BUFFER_OFFSET(igsd));
		return 1;
	}

	/* n cannot be larger than the number of minimum "objects" in the array */
	if (IGB_NEEDS_MORE_DATA(igsd, n)) {
		zend_error(E_WARNING, "igbinary_unserialize_array: data size %zu smaller that requested array length %zu.", IGB_REMAINING_BYTES(igsd), (unsigned int) n);
		return 1;
	}

	z_deref = z;
	if (flags & WANT_REF) {
		if (!Z_ISREF_P(z)) {
			ZVAL_NEW_REF(z, z);
			z_deref = Z_REFVAL_P(z);
		}
	}
	array_init_size(z_deref, n);
	{
		struct igbinary_value_ref ref;
		if (flags & WANT_REF) {
			// We converted to reference earlier.
			ref.reference.reference = Z_REF_P(z);
			ref.type = IG_REF_IS_REFERENCE;
		} else {
			ref.reference.array = Z_ARR_P(z_deref);
			ref.type = IG_REF_IS_ARRAY;
		}
		/* add the new array to the list of unserialized references */
		if (igsd_append_ref(igsd, ref) == SIZE_MAX) {
			return 1;
		}
	}

	/* empty array */
	if (n == 0) {
		return 0;
	}

	h = HASH_OF(z_deref);
	for (i = 0; i < n; i++) {
		zend_long key_index = 0;
		zend_string *key_str = NULL; /* NULL means use key_index */

		if (IGB_NEEDS_MORE_DATA(igsd, 1)) {
			zend_error(E_WARNING, "igbinary_unserialize_array: end-of-data");
			zval_dtor(z);
			ZVAL_NULL(z);
			return 1;
		}

		key_type = (enum igbinary_type) igbinary_unserialize8(igsd);

		switch (key_type) {
			case igbinary_type_long8p:
			case igbinary_type_long8n:
			case igbinary_type_long16p:
			case igbinary_type_long16n:
			case igbinary_type_long32p:
			case igbinary_type_long32n:
			case igbinary_type_long64p:
			case igbinary_type_long64n:
				if (igbinary_unserialize_long(igsd, key_type, &key_index)) {
					zval_dtor(z);
					ZVAL_UNDEF(z);
					return 1;
				}
				break;
			case igbinary_type_string_id8:
			case igbinary_type_string_id16:
			case igbinary_type_string_id32:
				key_str = igbinary_unserialize_string(igsd, key_type);
				if (key_str == NULL) {
					zval_dtor(z);
					ZVAL_UNDEF(z);
					return 1;
				}
				break;
			case igbinary_type_string8:
			case igbinary_type_string16:
			case igbinary_type_string32:
				key_str = igbinary_unserialize_chararray(igsd, key_type);
				if (key_str == NULL) {
					zval_dtor(z);
					ZVAL_UNDEF(z);
					return 1;
				}
				break;
			case igbinary_type_string_empty:
				key_str = ZSTR_EMPTY_ALLOC();
				break;
			case igbinary_type_null:
				continue;
			default:
				zend_error(E_WARNING, "igbinary_unserialize_array: unknown key type '%02x', position %zu", key_type, IGB_BUFFER_OFFSET(igsd));
				zval_dtor(z);
				ZVAL_UNDEF(z);
				return 1;
		}


		/* first add key into array so references can properly and not stack allocated zvals */
		/* Use NULL because inserting UNDEF into array does not add a new element */
		ZVAL_NULL(&v);
		if (key_str != NULL) {
			vp = zend_hash_update(h, key_str, &v);

			zend_string_release(key_str);
		} else {
			vp = zend_hash_index_update(h, key_index, &v);
		}

		ZEND_ASSERT(vp != NULL);
		if (Z_TYPE_P(vp) == IS_INDIRECT) {
			vp = Z_INDIRECT_P(vp);
		}

		ZEND_ASSERT(vp != NULL);
		if (igbinary_unserialize_zval(igsd, vp, WANT_CLEAR)) {
			/* zval_ptr_dtor(z); */
			/* zval_ptr_dtor(vp); */
			return 1;
		}
	}

	return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_object_properties */
/** Unserializes array of object properties. */
inline static int igbinary_unserialize_object_properties(struct igbinary_unserialize_data *igsd, enum igbinary_type t, zval *const z) {
	/* WANT_REF means that z will be wrapped by an IS_REFERENCE */
	size_t n;
	size_t i;

	zval v;
	zval *vp;
	zval *z_deref;

	enum igbinary_type key_type;

	HashTable *h;
	zend_bool did_extend;

	if (t == igbinary_type_array8) {
		if (IGB_NEEDS_MORE_DATA(igsd, 1)) {
			zend_error(E_WARNING, "igbinary_unserialize_array: end-of-data");
			return 1;
		}
		n = igbinary_unserialize8(igsd);
	} else if (t == igbinary_type_array16) {
		if (IGB_NEEDS_MORE_DATA(igsd, 2)) {
			zend_error(E_WARNING, "igbinary_unserialize_array: end-of-data");
			return 1;
		}
		n = igbinary_unserialize16(igsd);
	} else if (t == igbinary_type_array32) {
		if (IGB_NEEDS_MORE_DATA(igsd, 4)) {
			zend_error(E_WARNING, "igbinary_unserialize_array: end-of-data");
			return 1;
		}
		n = igbinary_unserialize32(igsd);
	} else {
		zend_error(E_WARNING, "igbinary_unserialize_array: unknown type '%02x', position %zu", t, IGB_BUFFER_OFFSET(igsd));
		return 1;
	}

	/* n cannot be larger than the number of minimum "objects" in the array */
	if (IGB_NEEDS_MORE_DATA(igsd, n)) {
		zend_error(E_WARNING, "%s: data size %zu smaller that requested array length %zu.", "igbinary_unserialize_array", IGB_REMAINING_BYTES(igsd), n);
		return 1;
	}

	z_deref = z;
	ZVAL_DEREF(z_deref);

	/* empty array */
	if (n == 0) {
		return 0;
	}

	h = HASH_OF(z_deref);

	did_extend = 0;

	for (i = 0; i < n; i++) {
		zend_string *key_str = NULL; /* NULL means use key_index */

		if (IGB_NEEDS_MORE_DATA(igsd, 1)) {
			zend_error(E_WARNING, "igbinary_unserialize_array: end-of-data");
			zval_dtor(z);
			ZVAL_NULL(z);
			return 1;
		}

		key_type = (enum igbinary_type) igbinary_unserialize8(igsd);

		switch (key_type) {
			case igbinary_type_long8p:
			case igbinary_type_long8n:
			case igbinary_type_long16p:
			case igbinary_type_long16n:
			case igbinary_type_long32p:
			case igbinary_type_long32n:
			case igbinary_type_long64p:
			case igbinary_type_long64n:
			{
				zend_long key_index = 0;
				if (igbinary_unserialize_long(igsd, key_type, &key_index)) {
					zval_dtor(z);
					ZVAL_UNDEF(z);
					return 1;
				}
				key_str = zend_long_to_str(key_index);
				if (UNEXPECTED(key_str == NULL)) {
					zval_dtor(z);
					ZVAL_UNDEF(z);
					return 1;
				}
				break;
			}
			case igbinary_type_string_id8:
			case igbinary_type_string_id16:
			case igbinary_type_string_id32:
				key_str = igbinary_unserialize_string(igsd, key_type);
				if (UNEXPECTED(key_str == NULL)) {
					zval_dtor(z);
					ZVAL_UNDEF(z);
					return 1;
				}
				break;
			case igbinary_type_string8:
			case igbinary_type_string16:
			case igbinary_type_string32:
				key_str = igbinary_unserialize_chararray(igsd, key_type);
				if (UNEXPECTED(key_str == NULL)) {
					zval_dtor(z);
					ZVAL_UNDEF(z);
					return 1;
				}
				break;
			case igbinary_type_string_empty:
				key_str = ZSTR_EMPTY_ALLOC();
				break;
			case igbinary_type_null:
				continue;  /* Skip unserializing this element, serialized with no value. In C, this applies to loop, not switch. */
			default:
				zend_error(E_WARNING, "igbinary_unserialize_array: unknown key type '%02x', position %zu", key_type, IGB_BUFFER_OFFSET(igsd));
				zval_dtor(z);
				ZVAL_UNDEF(z);
				return 1;
		}


		/* first add key into array so references can properly and not stack allocated zvals */
		/* Use NULL because inserting UNDEF into array does not add a new element */
		ZVAL_NULL(&v);
		zval *prototype_value = zend_hash_find(h, key_str);
		if (prototype_value != NULL) {
			if (Z_TYPE_P(prototype_value) == IS_INDIRECT) {
				prototype_value = Z_INDIRECT_P(prototype_value);
			}
			convert_to_null(prototype_value);
			vp = zend_hash_update_ind(h, key_str, &v);
		} else {
			if (!did_extend) {
				zend_long remaining_elements = n - i;
				/* Copied from var_unserializer.re. Need to ensure that IGB_REF_VAL doesn't point to invalid data. */
				/* Worst case: All remaining_elements of the added properties are dynamic. */
				zend_hash_extend(h, zend_hash_num_elements(h) + remaining_elements, (h->u.flags & HASH_FLAG_PACKED));
				did_extend = 1;
			}
			vp = zend_hash_add_new(h, key_str, &v);
		}

		zend_string_release(key_str);

		ZEND_ASSERT(vp != NULL);
		if (Z_TYPE_P(vp) == IS_INDIRECT) {
			vp = Z_INDIRECT_P(vp);
		}

		ZEND_ASSERT(vp != NULL);
		if (igbinary_unserialize_zval(igsd, vp, WANT_CLEAR)) {
			/* zval_ptr_dtor(z); */
			/* zval_ptr_dtor(vp); */
			return 1;
		}
	}

	return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_object_ser */
/** Unserializes object's property array of objects implementing Serializable -interface. */
inline static int igbinary_unserialize_object_ser(struct igbinary_unserialize_data *igsd, enum igbinary_type t, zval *const z, zend_class_entry *ce) {
	size_t n;
	int ret;
	php_unserialize_data_t var_hash;

	if (ce->unserialize == NULL) {
		zend_error(E_WARNING, "Class %s has no unserializer", ce->name);
		return 1;
	}

	if (t == igbinary_type_object_ser8) {
		if (IGB_NEEDS_MORE_DATA(igsd, 1)) {
			zend_error(E_WARNING, "igbinary_unserialize_object_ser: end-of-data");
			return 1;
		}
		n = igbinary_unserialize8(igsd);
	} else if (t == igbinary_type_object_ser16) {
		if (IGB_NEEDS_MORE_DATA(igsd, 2)) {
			zend_error(E_WARNING, "igbinary_unserialize_object_ser: end-of-data");
			return 1;
		}
		n = igbinary_unserialize16(igsd);
	} else if (t == igbinary_type_object_ser32) {
		if (IGB_NEEDS_MORE_DATA(igsd, 4)) {
			zend_error(E_WARNING, "igbinary_unserialize_object_ser: end-of-data");
			return 1;
		}
		n = igbinary_unserialize32(igsd);
	} else {
		zend_error(E_WARNING, "igbinary_unserialize_object_ser: unknown type '%02x', position %zu", t, IGB_BUFFER_OFFSET(igsd));
		return 1;
	}

	if (IGB_NEEDS_MORE_DATA(igsd, n)) {
		zend_error(E_WARNING, "igbinary_unserialize_object_ser: end-of-data");
		return 1;
	}

	PHP_VAR_UNSERIALIZE_INIT(var_hash);
	ret = ce->unserialize(z, ce,
		(const unsigned char*)igsd->buffer_ptr, n,
		(zend_unserialize_data *)&var_hash);
	PHP_VAR_UNSERIALIZE_DESTROY(var_hash);

	if (ret != SUCCESS || EG(exception)) {
		return 1;
	}

	igsd->buffer_ptr += n;

	return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_object */
/** Unserialize object.
 * @see ext/standard/var_unserializer.c
 */
inline static int igbinary_unserialize_object(struct igbinary_unserialize_data *igsd, enum igbinary_type t, zval *const z, int flags) {
	zend_class_entry *ce;

	size_t ref_n;

	zend_string *class_name;

	int r;

	bool incomplete_class = false;
	bool is_from_serialized_data = false;

	zval user_func;
	zval retval;
	zval args[1];

	if (t == igbinary_type_object8 || t == igbinary_type_object16 || t == igbinary_type_object32) {
		class_name = igbinary_unserialize_chararray(igsd, t);
	} else if (t == igbinary_type_object_id8 || t == igbinary_type_object_id16 || t == igbinary_type_object_id32) {
		class_name = igbinary_unserialize_string(igsd, t);
	} else {
		zend_error(E_WARNING, "igbinary_unserialize_object: unknown object type '%02x', position %zu", t, IGB_BUFFER_OFFSET(igsd));
		return 1;
	}

	if (class_name == NULL) {
		return 1;
	}

	do {
		/* Try to find class directly */
		if ((ce = zend_lookup_class(class_name)) != NULL) {
			/* FIXME: lookup class may cause exception in load callback */
			break;
		}

		/* Check for unserialize callback */
		if ((PG(unserialize_callback_func) == NULL) || (PG(unserialize_callback_func)[0] == '\0')) {
			incomplete_class = 1;
			ce = PHP_IC_ENTRY;
			break;
		}

		/* Call unserialize callback */
		ZVAL_STRING(&user_func, PG(unserialize_callback_func));
		/* FIXME: Do we need a str copy? */
		/* FIXME: Release arg[0] */
		/* FIXME: Release class_name */
		ZVAL_STR_COPY(&args[0], class_name);
		if (call_user_function_ex(CG(function_table), NULL, &user_func, &retval, 1, args, 0, NULL) != SUCCESS) {
			php_error_docref(NULL, E_WARNING, "defined (%s) but not found", ZSTR_VAL(class_name));
			incomplete_class = 1;
			ce = PHP_IC_ENTRY;
			zval_ptr_dtor(&args[0]);
			zval_ptr_dtor(&user_func);
			break;
		}
		/* FIXME: always safe? */
		zval_ptr_dtor(&retval);

		/* The callback function may have defined the class */
		ce = zend_lookup_class(class_name);
		if (!ce) {
			php_error_docref(NULL, E_WARNING, "Function %s() hasn't defined the class it was called for", ZSTR_VAL(class_name));
			incomplete_class = true;
			ce = PHP_IC_ENTRY;
		}

		zval_ptr_dtor(&args[0]);
		zval_ptr_dtor(&user_func);
	} while (0);


	/* previous user function call may have raised an exception */
	if (EG(exception)) {
		zend_string_release(class_name);
		return 1;
	}

	/* add this to the list of unserialized references, get the index */
	if (IGB_NEEDS_MORE_DATA(igsd, 1)) {
		zend_error(E_WARNING, "igbinary_unserialize_object: end-of-data");
		zend_string_release(class_name);
		return 1;
	}

	{
		struct igbinary_value_ref ref;
		ref_n = igsd_append_ref(igsd, ref);
		if (ref_n == SIZE_MAX) {
			zend_string_release(class_name);
			return 1;
		}
	}

	t = (enum igbinary_type) igbinary_unserialize8(igsd);
	switch (t) {
		case igbinary_type_array8:
		case igbinary_type_array16:
		case igbinary_type_array32:
		{
			if (object_init_ex(z, ce) != SUCCESS) {
				php_error_docref(NULL, E_NOTICE, "igbinary unable to create object for class entry");
				r = 1;
				break;
			}
			if (incomplete_class) {
				php_store_class_name(z, ZSTR_VAL(class_name), ZSTR_LEN(class_name));
			}
			struct igbinary_value_ref *ref = &IGB_REF_VAL_2(igsd, ref_n);;
			if ((flags & WANT_REF) != 0) {
				ZVAL_MAKE_REF(z);
				ref->reference.reference = Z_REF_P(z);
				ref->type = IG_REF_IS_REFERENCE;
			} else {
				ref->reference.object = Z_OBJ_P(z);
				ref->type = IG_REF_IS_OBJECT;
			}

			r = igbinary_unserialize_object_properties(igsd, t, z);
			break;
		}
		case igbinary_type_object_ser8:
		case igbinary_type_object_ser16:
		case igbinary_type_object_ser32:
		{
			is_from_serialized_data = true;
			// FIXME will this break if z isn't an object?
			r = igbinary_unserialize_object_ser(igsd, t, z, ce);
			if (r != 0) {
				break;
			}

			if (incomplete_class) {
				php_store_class_name(z, ZSTR_VAL(class_name), ZSTR_LEN(class_name));
			}
			struct igbinary_value_ref *ref = &IGB_REF_VAL_2(igsd, ref_n);
			if ((flags & WANT_REF) != 0) {
				ZVAL_MAKE_REF(z);
				ref->reference.reference = Z_REF_P(z);
				ref->type = IG_REF_IS_REFERENCE;
			} else {
				ref->reference.object = Z_OBJ_P(z);
				ref->type = IG_REF_IS_OBJECT;
			}
			break;
		}
		default:
			zend_error(E_WARNING, "igbinary_unserialize_object: unknown object inner type '%02x', position %zu", t, IGB_BUFFER_OFFSET(igsd));
			r = 1;
	}
	zend_string_release(class_name);
	class_name = NULL;

	/* If unserialize was successful, call __wakeup if __wakeup exists for this object. */
	/* (But don't call __wakeup() if Serializable::unserialize was called */
	if (r == 0 && !is_from_serialized_data) {
		struct igbinary_value_ref * const ref = &IGB_REF_VAL_2(igsd, ref_n);
		zval ztemp;
		zend_object *object;
		if (ref->type == IG_REF_IS_OBJECT) {
			object = ref->reference.object;
			ZVAL_OBJ(&ztemp, object);
		} else if (ref->type == IG_REF_IS_REFERENCE) {
			ztemp = ref->reference.reference->val;
			if (Z_TYPE(ztemp) != IS_OBJECT) {
				zend_error(E_WARNING, "igbinary_unserialize_object preparing to __wakeup: got reference to non-object somehow", t, IGB_BUFFER_OFFSET(igsd));
				return 1;
			}
			object = Z_OBJ(ztemp);
		} else {
			zend_error(E_WARNING, "igbinary_unserialize_object preparing to __wakeup: created non-object somehow", t, IGB_BUFFER_OFFSET(igsd));
			return 1;
		}
		zend_class_entry *ztemp_ce;
		/* May have created a reference while deserializing an object, if it was recursive. */
		ztemp_ce = Z_OBJCE(ztemp);
		if (ztemp_ce != PHP_IC_ENTRY &&
			zend_hash_str_exists(&ztemp_ce->function_table, "__wakeup", sizeof("__wakeup") - 1)) {
			if (igsd_defer_wakeup(igsd, object)) {
				r = 1;
			}
		}
	}

	/* ZVAL_COPY_VALUE(z, IGB_REF_VAL(igsd, ref_n)); */

	return r;
}
/* }}} */
/* {{{ igbinary_unserialize_ref */
/** Unserializes array or object by reference. */
inline static int igbinary_unserialize_ref(struct igbinary_unserialize_data *igsd, enum igbinary_type t, zval *const z, int flags) {
	size_t n;

	if (t == igbinary_type_ref8 || t == igbinary_type_objref8) {
		if (IGB_NEEDS_MORE_DATA(igsd, 1)) {
			zend_error(E_WARNING, "igbinary_unserialize_ref: end-of-data");
			return 1;
		}
		n = igbinary_unserialize8(igsd);
	} else if (t == igbinary_type_ref16 || t == igbinary_type_objref16) {
		if (IGB_NEEDS_MORE_DATA(igsd, 2)) {
			zend_error(E_WARNING, "igbinary_unserialize_ref: end-of-data");
			return 1;
		}
		n = igbinary_unserialize16(igsd);
	} else if (t == igbinary_type_ref32 || t == igbinary_type_objref32) {
		if (IGB_NEEDS_MORE_DATA(igsd, 4)) {
			zend_error(E_WARNING, "igbinary_unserialize_ref: end-of-data");
			return 1;
		}
		n = igbinary_unserialize32(igsd);
	} else {
		zend_error(E_WARNING, "igbinary_unserialize_ref: unknown type '%02x', position %zu", t, IGB_BUFFER_OFFSET(igsd));
		return 1;
	}

	if (n >= igsd->references_count) {
		zend_error(E_WARNING, "igbinary_unserialize_ref: invalid reference %zu >= %zu", (int) n, (int)igsd->references_count);
		return 1;
	}

	if (z != NULL) {
		/* FIXME: check with is refcountable or some such */
		zval_ptr_dtor(z);
		ZVAL_UNDEF(z);
	}

	struct igbinary_value_ref* ref_ptr = &IGB_REF_VAL_2(igsd, n);
	struct igbinary_value_ref ref = *ref_ptr;

	/**
	 * Permanently convert the zval in IGB_REF_VAL() into a IS_REFERENCE if it wasn't already one.
	 * TODO: Can there properly be multiple reference groups to an object?
	 * Similar to https://github.com/php/php-src/blob/master/ext/standard/var_unserializer.re , for "R:"
	 * Using `flags` because igbinary_unserialize_ref might be used both for copy on writes ($a = $b = [2]) and by PHP references($a = &$b).
	 */
	if ((flags & WANT_REF) != 0) {
		/* Want to create an IS_REFERENCE, not just to share the same value until modified. */
		switch (ref.type) {
		case IG_REF_IS_OBJECT:
			ZVAL_OBJ(z, ref.reference.object);
			Z_TRY_ADDREF_P(z);
			ZVAL_MAKE_REF(z); /* Convert original zval data to a reference */
			/* replace the entry in IGB_REF_VAL with a reference. */
			ref_ptr->reference.reference = Z_REF_P(z);
			ref_ptr->type = IG_REF_IS_REFERENCE;
			break;
		case IG_REF_IS_ARRAY:
			ZVAL_ARR(z, ref.reference.array);
			Z_TRY_ADDREF_P(z);
			ZVAL_MAKE_REF(z); /* Convert original zval data to a reference */
			/* replace the entry in IGB_REF_VAL with a reference. */
			ref_ptr->reference.reference = Z_REF_P(z);
			ref_ptr->type = IG_REF_IS_REFERENCE;
			break;
		case IG_REF_IS_REFERENCE:
			// This is already a reference, convert into reference count.
			ZVAL_REF(z, ref.reference.reference);
			Z_ADDREF_P(z);
			break;
		}
	} else {
		switch (ref.type) {
		case IG_REF_IS_OBJECT:
			ZVAL_OBJ(z, ref.reference.object);
			Z_TRY_ADDREF_P(z);
			break;
		case IG_REF_IS_ARRAY:
			ZVAL_ARR(z, ref.reference.array);
			Z_TRY_ADDREF_P(z);
			break;
		case IG_REF_IS_REFERENCE:
			ZVAL_COPY(z, &(ref.reference.reference->val));
			break;
		}
	}

	return 0;
}
/* }}} */
/* {{{ igbinary_unserialize_zval */
/** Unserialize zval. */
static int igbinary_unserialize_zval(struct igbinary_unserialize_data *igsd, zval *const z, int flags) {
	enum igbinary_type t;

	zend_long tmp_long;
	double tmp_double;
	zend_string *tmp_str;

	if (IGB_NEEDS_MORE_DATA(igsd, 1)) {
		zend_error(E_WARNING, "igbinary_unserialize_zval: end-of-data");
		return 1;
	}

	t = (enum igbinary_type) igbinary_unserialize8(igsd);

	switch (t) {
		case igbinary_type_ref:
			if (igbinary_unserialize_zval(igsd, z, WANT_REF)) {
				return 1;
			}

			/* If it is already a ref, nothing to do */
			if (Z_ISREF_P(z)) {
				break;
			}

			const zend_uchar type = Z_TYPE_P(z);
			/* Permanently convert the zval in IGB_REF_VAL() into a IS_REFERENCE if it wasn't already one. */
			/* TODO: Support multiple reference groups to the same object */
			/* Similar to https://github.com/php/php-src/blob/master/ext/standard/var_unserializer.re , for "R:" */
			ZVAL_MAKE_REF(z);
			switch (type) {
				case IS_STRING:
				case IS_LONG:
				case IS_NULL:
				case IS_DOUBLE:
				case IS_FALSE:
				case IS_TRUE:
				{
					struct igbinary_value_ref ref;
					ref.reference.reference = Z_REF_P(z);
					ref.type = IG_REF_IS_REFERENCE;
					/* add the unserialized scalar to the list of unserialized references. Objects and arrays were already added in igbinary_unserialize_zval. */
					if (igsd_append_ref(igsd, ref) == SIZE_MAX) {
						return 1;
					}
					break;
				}
				default:
					break;
			}
			break;
		case igbinary_type_objref8:
		case igbinary_type_objref16:
		case igbinary_type_objref32:
		case igbinary_type_ref8:
		case igbinary_type_ref16:
		case igbinary_type_ref32:
			if (igbinary_unserialize_ref(igsd, t, z, flags)) {
				return 1;
			}
			break;
		case igbinary_type_object8:
		case igbinary_type_object16:
		case igbinary_type_object32:
		case igbinary_type_object_id8:
		case igbinary_type_object_id16:
		case igbinary_type_object_id32:
			if (igbinary_unserialize_object(igsd, t, z, flags)) {
				return 1;
			}
			break;
		case igbinary_type_array8:
		case igbinary_type_array16:
		case igbinary_type_array32:
			if (igbinary_unserialize_array(igsd, t, z, flags)) {
				return 1;
			}
			break;
		case igbinary_type_string_empty:
			ZVAL_EMPTY_STRING(z);
			break;
		case igbinary_type_string_id8:
		case igbinary_type_string_id16:
		case igbinary_type_string_id32:
			tmp_str = igbinary_unserialize_string(igsd, t);
			if (tmp_str == NULL) {
				return 1;
			}
			ZVAL_STR(z, tmp_str);
			break;
		case igbinary_type_string8:
		case igbinary_type_string16:
		case igbinary_type_string32:
			tmp_str = igbinary_unserialize_chararray(igsd, t);
			if (tmp_str == NULL) {
				return 1;
			}
			ZVAL_STR(z, tmp_str);
			break;
		case igbinary_type_long8p:
		case igbinary_type_long8n:
		case igbinary_type_long16p:
		case igbinary_type_long16n:
		case igbinary_type_long32p:
		case igbinary_type_long32n:
		case igbinary_type_long64p:
		case igbinary_type_long64n:
			if (igbinary_unserialize_long(igsd, t, &tmp_long)) {
				return 1;
			}
			ZVAL_LONG(z, tmp_long);
			break;
		case igbinary_type_null:
			ZVAL_NULL(z);
			break;
		case igbinary_type_bool_false:
			ZVAL_BOOL(z, 0);
			break;
		case igbinary_type_bool_true:
			ZVAL_BOOL(z, 1);
			break;
		case igbinary_type_double:
			if (igbinary_unserialize_double(igsd, t, &tmp_double)) {
				return 1;
			}
			ZVAL_DOUBLE(z, tmp_double);
			break;
		default:
			zend_error(E_WARNING, "igbinary_unserialize_zval: unknown type '%02x', position %zu", t, IGB_BUFFER_OFFSET(igsd));
			return 1;
	}

	return 0;
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
