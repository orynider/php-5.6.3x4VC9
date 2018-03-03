/* $Header: /cvsroot/pgsql-server/src/interfaces/ecpg/lib/prepare.c,v 1.12 2001/12/23 12:17:41 meskes Exp $ */

#include "postgres_fe.h"

#include <ctype.h>

#include "ecpgtype.h"
#include "ecpglib.h"
#include "ecpgerrno.h"
#include "extern.h"
#include "sqlca.h"

static struct prepared_statement
{
	char	   *name;
	struct statement *stmt;
	struct prepared_statement *next;
}	*prep_stmts = NULL;

static bool
isvarchar(unsigned char c)
{
	if (isalnum(c))
		return true;

	if (c == '_' || c == '>' || c == '-' || c == '.')
		return true;

	if (c >= 128)
		return true;

	return (false);
}

static void
replace_variables(char *text)
{
	char	   *ptr = text;
	bool		string = false;

	for (; *ptr != '\0'; ptr++)
	{
		if (*ptr == '\'')
			string = string ? false : true;

		if (!string && *ptr == ':')
		{
			*ptr = '?';
			for (++ptr; *ptr && isvarchar(*ptr); ptr++)
				*ptr = ' ';
		}
	}
}

/* handle the EXEC SQL PREPARE statement */
bool
ECPGprepare(int lineno, char *name, char *variable)
{
	struct statement *stmt;
	struct prepared_statement *this;

	/* check if we already have prepared this statement */
	for (this = prep_stmts; this != NULL && strcmp(this->name, name) != 0; this = this->next);
	if (this)
	{
		bool		b = ECPGdeallocate(lineno, name);

		if (!b)
			return false;
	}

	this = (struct prepared_statement *) ECPGalloc(sizeof(struct prepared_statement), lineno);
	if (!this)
		return false;

	stmt = (struct statement *) ECPGalloc(sizeof(struct statement), lineno);
	if (!stmt)
	{
		ECPGfree(this);
		return false;
	}

	/* create statement */
	stmt->lineno = lineno;
	stmt->connection = NULL;
	stmt->command = ECPGstrdup(variable, lineno);
	stmt->inlist = stmt->outlist = NULL;

	/* if we have C variables in our statment replace them with '?' */
	replace_variables(stmt->command);

	/* add prepared statement to our list */
	this->name = ECPGstrdup(name, lineno);
	this->stmt = stmt;

	if (prep_stmts == NULL)
		this->next = NULL;
	else
		this->next = prep_stmts;

	prep_stmts = this;
	return true;
}

/* handle the EXEC SQL DEALLOCATE PREPARE statement */
bool
ECPGdeallocate(int lineno, char *name)
{
	struct prepared_statement *this,
			   *prev;

	/* check if we really have prepared this statement */
	for (this = prep_stmts, prev = NULL; this != NULL && strcmp(this->name, name) != 0; prev = this, this = this->next);
	if (this)
	{
		/* okay, free all the resources */
		ECPGfree(this->name);
		ECPGfree(this->stmt->command);
		ECPGfree(this->stmt);
		if (prev != NULL)
			prev->next = this->next;
		else
			prep_stmts = this->next;

		ECPGfree(this);
		return true;
	}
	ECPGraise(lineno, ECPG_INVALID_STMT, name);
	return false;
}

bool
ECPGdeallocate_all(int lineno)
{
	/* deallocate all prepared statements */
	while (prep_stmts != NULL)
	{
		bool		b = ECPGdeallocate(lineno, prep_stmts->name);

		if (!b)
			return false;
	}

	return true;
}

/* return the prepared statement */
char *
ECPGprepared_statement(char *name)
{
	struct prepared_statement *this;

	for (this = prep_stmts; this != NULL && strcmp(this->name, name) != 0; this = this->next);
	return (this) ? this->stmt->command : NULL;
}
