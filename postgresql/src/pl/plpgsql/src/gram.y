%{
/**********************************************************************
 * gram.y				- Parser for the PL/pgSQL
 *						  procedural language
 *
 * IDENTIFICATION
 *	  $Header: /cvsroot/pgsql-server/src/pl/plpgsql/src/gram.y,v 1.29.2.1 2002/05/21 18:50:18 tgl Exp $
 *
 *	  This software is copyrighted by Jan Wieck - Hamburg.
 *
 *	  The author hereby grants permission  to  use,  copy,	modify,
 *	  distribute,  and	license this software and its documentation
 *	  for any purpose, provided that existing copyright notices are
 *	  retained	in	all  copies  and  that	this notice is included
 *	  verbatim in any distributions. No written agreement, license,
 *	  or  royalty  fee	is required for any of the authorized uses.
 *	  Modifications to this software may be  copyrighted  by  their
 *	  author  and  need  not  follow  the licensing terms described
 *	  here, provided that the new terms are  clearly  indicated  on
 *	  the first page of each file where they apply.
 *
 *	  IN NO EVENT SHALL THE AUTHOR OR DISTRIBUTORS BE LIABLE TO ANY
 *	  PARTY  FOR  DIRECT,	INDIRECT,	SPECIAL,   INCIDENTAL,	 OR
 *	  CONSEQUENTIAL   DAMAGES  ARISING	OUT  OF  THE  USE  OF  THIS
 *	  SOFTWARE, ITS DOCUMENTATION, OR ANY DERIVATIVES THEREOF, EVEN
 *	  IF  THE  AUTHOR  HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
 *	  DAMAGE.
 *
 *	  THE  AUTHOR  AND	DISTRIBUTORS  SPECIFICALLY	 DISCLAIM	ANY
 *	  WARRANTIES,  INCLUDING,  BUT	NOT  LIMITED  TO,  THE	IMPLIED
 *	  WARRANTIES  OF  MERCHANTABILITY,	FITNESS  FOR  A  PARTICULAR
 *	  PURPOSE,	AND NON-INFRINGEMENT.  THIS SOFTWARE IS PROVIDED ON
 *	  AN "AS IS" BASIS, AND THE AUTHOR	AND  DISTRIBUTORS  HAVE  NO
 *	  OBLIGATION   TO	PROVIDE   MAINTENANCE,	 SUPPORT,  UPDATES,
 *	  ENHANCEMENTS, OR MODIFICATIONS.
 *
 **********************************************************************/

#include "plpgsql.h"


static	PLpgSQL_expr	*read_sql_construct(int until,
											const char *expected,
											bool isexpression,
											const char *sqlstart);
static	PLpgSQL_expr	*read_sql_stmt(const char *sqlstart);
static	PLpgSQL_type	*read_datatype(int tok);
static	PLpgSQL_stmt	*make_select_stmt(void);
static	PLpgSQL_stmt	*make_fetch_stmt(void);
static	PLpgSQL_expr	*make_tupret_expr(PLpgSQL_row *row);

%}

%union {
		int32					ival;
		char					*str;
		struct
		{
			char *name;
			int  lineno;
		}						varname;
		struct
		{
			int  nalloc;
			int  nused;
			int	 *nums;
		}						intlist;
		struct
		{
			int  nalloc;
			int  nused;
			PLpgSQL_diag_item *dtitems;
		}						dtlist;
		struct
		{
			int  reverse;
			PLpgSQL_expr *expr;
		}						forilow;
		struct
		{
			char *label;
			int  n_initvars;
			int  *initvarnos;
		}						declhdr;
		PLpgSQL_type			*dtype;
		PLpgSQL_var				*var;
		PLpgSQL_row				*row;
		PLpgSQL_rec				*rec;
		PLpgSQL_recfield		*recfield;
		PLpgSQL_trigarg			*trigarg;
		PLpgSQL_expr			*expr;
		PLpgSQL_stmt			*stmt;
		PLpgSQL_stmts			*stmts;
		PLpgSQL_stmt_block		*program;
		PLpgSQL_nsitem			*nsitem;
}

%type <declhdr> decl_sect
%type <varname> decl_varname
%type <str>		decl_renname
%type <ival>	decl_const, decl_notnull
%type <expr>	decl_defval, decl_cursor_query
%type <dtype>	decl_datatype
%type <row>		decl_rowtype, decl_cursor_args, decl_cursor_arglist
%type <nsitem>	decl_aliasitem
%type <str>		decl_stmts, decl_stmt

%type <expr>	expr_until_semi, expr_until_then, expr_until_loop
%type <expr>	opt_exitcond

%type <ival>	assign_var, cursor_variable
%type <var>		fori_var, cursor_varptr, decl_cursor_arg
%type <varname> fori_varname
%type <forilow> fori_lower
%type <rec>		fors_target

%type <str>		opt_lblname, opt_label
%type <str>		opt_exitlabel
%type <str>		execsql_start

%type <stmts>	proc_sect, proc_stmts, stmt_else, loop_body
%type <stmt>	proc_stmt, pl_block
%type <stmt>	stmt_assign, stmt_if, stmt_loop, stmt_while, stmt_exit
%type <stmt>	stmt_return, stmt_raise, stmt_execsql, stmt_fori
%type <stmt>	stmt_fors, stmt_select, stmt_perform
%type <stmt>	stmt_dynexecute, stmt_dynfors, stmt_getdiag
%type <stmt>	stmt_open, stmt_fetch, stmt_close

%type <intlist>	raise_params
%type <ival>	raise_level, raise_param
%type <str>		raise_msg

%type <dtlist>	getdiag_list
%type <ival>	getdiag_item, getdiag_target

%type <ival>	lno

		/*
		 * Keyword tokens
		 */
%token	K_ALIAS
%token	K_ASSIGN
%token	K_BEGIN
%token	K_CLOSE
%token	K_CONSTANT
%token	K_CURSOR
%token	K_DEBUG
%token	K_DECLARE
%token	K_DEFAULT
%token	K_DIAGNOSTICS
%token	K_DOTDOT
%token	K_ELSE
%token	K_ELSIF
%token	K_END
%token	K_EXCEPTION
%token	K_EXECUTE
%token	K_EXIT
%token	K_FOR
%token	K_FETCH
%token	K_FROM
%token	K_GET
%token	K_IF
%token	K_IN
%token	K_INTO
%token	K_IS
%token	K_LOOP
%token	K_NOT
%token	K_NOTICE
%token	K_NULL
%token	K_OPEN
%token	K_PERFORM
%token	K_ROW_COUNT
%token	K_RAISE
%token	K_RECORD
%token	K_RENAME
%token	K_RESULT_OID
%token	K_RETURN
%token	K_REVERSE
%token	K_SELECT
%token	K_THEN
%token	K_TO
%token	K_TYPE
%token	K_WHEN
%token	K_WHILE

		/*
		 * Other tokens
		 */
%token	T_FUNCTION
%token	T_TRIGGER
%token	T_LABEL
%token	T_STRING
%token	T_VARIABLE
%token	T_ROW
%token	T_ROWTYPE
%token	T_RECORD
%token	T_RECFIELD
%token	T_TGARGV
%token	T_DTYPE
%token	T_WORD
%token	T_NUMBER
%token	T_ERROR

%token	O_OPTION
%token	O_DUMP

%%

pl_function		: T_FUNCTION comp_optsect pl_block opt_semi
					{
						yylval.program = (PLpgSQL_stmt_block *)$3;
					}
				| T_TRIGGER comp_optsect pl_block opt_semi
					{
						yylval.program = (PLpgSQL_stmt_block *)$3;
					}
				;

comp_optsect	:
				| comp_options
				;

comp_options	: comp_options comp_option
				| comp_option
				;

comp_option		: O_OPTION O_DUMP
					{
						plpgsql_DumpExecTree = 1;
					}
				;

opt_semi		:
				| ';'
				;

pl_block		: decl_sect K_BEGIN lno proc_sect K_END
					{
						PLpgSQL_stmt_block *new;

						new = malloc(sizeof(PLpgSQL_stmt_block));
						memset(new, 0, sizeof(PLpgSQL_stmt_block));

						new->cmd_type	= PLPGSQL_STMT_BLOCK;
						new->lineno		= $3;
						new->label		= $1.label;
						new->n_initvars = $1.n_initvars;
						new->initvarnos = $1.initvarnos;
						new->body		= $4;

						plpgsql_ns_pop();

						$$ = (PLpgSQL_stmt *)new;
					}
				;


decl_sect		: opt_label
					{
						plpgsql_ns_setlocal(false);
						$$.label	  = $1;
						$$.n_initvars = 0;
						$$.initvarnos = NULL;
						plpgsql_add_initdatums(NULL);
					}
				| opt_label decl_start
					{
						plpgsql_ns_setlocal(false);
						$$.label	  = $1;
						$$.n_initvars = 0;
						$$.initvarnos = NULL;
						plpgsql_add_initdatums(NULL);
					}
				| opt_label decl_start decl_stmts
					{
						plpgsql_ns_setlocal(false);
						if ($3 != NULL)
							$$.label = $3;
						else
							$$.label = $1;
						$$.n_initvars = plpgsql_add_initdatums(&($$.initvarnos));
					}
				;

decl_start		: K_DECLARE
					{
						plpgsql_ns_setlocal(true);
					}
				;

decl_stmts		: decl_stmts decl_stmt
					{	$$ = $2;	}
				| decl_stmt
					{	$$ = $1;	}
				;

decl_stmt		: '<' '<' opt_lblname '>' '>'
					{	$$ = $3;	}
				| K_DECLARE
					{	$$ = NULL;	}
				| decl_statement
					{	$$ = NULL;	}
				;

decl_statement	: decl_varname decl_const decl_datatype decl_notnull decl_defval
					{
						PLpgSQL_var		*new;

						new = malloc(sizeof(PLpgSQL_var));
						memset(new, 0, sizeof(PLpgSQL_var));

						new->dtype		= PLPGSQL_DTYPE_VAR;
						new->refname	= $1.name;
						new->lineno		= $1.lineno;

						new->datatype	= $3;
						new->isconst	= $2;
						new->notnull	= $4;
						new->default_val = $5;

						plpgsql_adddatum((PLpgSQL_datum *)new);
						plpgsql_ns_additem(PLPGSQL_NSTYPE_VAR, new->varno,
												$1.name);
					}
				| decl_varname K_RECORD ';'
					{
						PLpgSQL_rec		*new;

						new = malloc(sizeof(PLpgSQL_rec));

						new->dtype		= PLPGSQL_DTYPE_REC;
						new->refname	= $1.name;
						new->lineno		= $1.lineno;

						plpgsql_adddatum((PLpgSQL_datum *)new);
						plpgsql_ns_additem(PLPGSQL_NSTYPE_REC, new->recno,
												$1.name);
					}
				| decl_varname decl_rowtype ';'
					{
						$2->dtype		= PLPGSQL_DTYPE_ROW;
						$2->refname		= $1.name;
						$2->lineno		= $1.lineno;

						plpgsql_adddatum((PLpgSQL_datum *)$2);
						plpgsql_ns_additem(PLPGSQL_NSTYPE_ROW, $2->rowno,
												$1.name);
					}
				| decl_varname K_ALIAS K_FOR decl_aliasitem ';'
					{
						plpgsql_ns_additem($4->itemtype,
										$4->itemno, $1.name);
					}
				| K_RENAME decl_renname K_TO decl_renname ';'
					{
						plpgsql_ns_rename($2, $4);
					}
				| decl_varname K_CURSOR
					{ plpgsql_ns_push(NULL); }
				  decl_cursor_args decl_is_from K_SELECT decl_cursor_query
					{
						PLpgSQL_var *new;
						PLpgSQL_expr *curname_def;
						char		buf[1024];
						char		*cp1;
						char		*cp2;

						/* pop local namespace for cursor args */
						plpgsql_ns_pop();

						new = malloc(sizeof(PLpgSQL_var));
						memset(new, 0, sizeof(PLpgSQL_var));

						curname_def = malloc(sizeof(PLpgSQL_expr));
						memset(curname_def, 0, sizeof(PLpgSQL_expr));

						new->dtype		= PLPGSQL_DTYPE_VAR;
						new->refname	= $1.name;
						new->lineno		= $1.lineno;

						curname_def->dtype = PLPGSQL_DTYPE_EXPR;
						strcpy(buf, "SELECT '");
						cp1 = new->refname;
						cp2 = buf + strlen(buf);
						while (*cp1 != '\0')
						{
							if (*cp1 == '\\' || *cp1 == '\'')
								*cp2++ = '\\';
							*cp2++ = *cp1++;
						}
						strcpy(cp2, "'::refcursor");
						curname_def->query = strdup(buf);
						new->default_val = curname_def;

						new->datatype = plpgsql_parse_datatype("refcursor");

						new->cursor_explicit_expr = $7;
						if ($4 == NULL)
							new->cursor_explicit_argrow = -1;
						else
							new->cursor_explicit_argrow = $4->rowno;

						plpgsql_adddatum((PLpgSQL_datum *)new);
						plpgsql_ns_additem(PLPGSQL_NSTYPE_VAR, new->varno,
										   $1.name);
					}
				;

decl_cursor_query :
					{
						PLpgSQL_expr *query;

						plpgsql_ns_setlocal(false);
						query = read_sql_stmt("SELECT ");
						plpgsql_ns_setlocal(true);
						
						$$ = query;
					}
				;

decl_cursor_args :
					{
						$$ = NULL;
					}
				| '(' decl_cursor_arglist ')'
					{
						/* Copy the temp arrays to malloc'd storage */
						int nfields = $2->nfields;
						char **ftmp;
						int *vtmp;

						ftmp = malloc(nfields * sizeof(char *));
						vtmp = malloc(nfields * sizeof(int));
						memcpy(ftmp, $2->fieldnames, nfields * sizeof(char *));
						memcpy(vtmp, $2->varnos, nfields * sizeof(int));

						pfree((char *)($2->fieldnames));
						pfree((char *)($2->varnos));

						$2->fieldnames = ftmp;
						$2->varnos = vtmp;

						plpgsql_adddatum((PLpgSQL_datum *)$2);

						$$ = $2;
					}
				;

decl_cursor_arglist : decl_cursor_arg
					{
						PLpgSQL_row *new;

						new = malloc(sizeof(PLpgSQL_row));
						memset(new, 0, sizeof(PLpgSQL_row));

						new->dtype = PLPGSQL_DTYPE_ROW;
						new->refname = strdup("*internal*");
						new->lineno = yylineno;
						new->rowtypeclass = InvalidOid;
						/*
						 * We make temporary fieldnames/varnos arrays that
						 * are much bigger than necessary.  We will resize
						 * them to just the needed size in the
						 * decl_cursor_args production.
						 */
						new->fieldnames = palloc(1024 * sizeof(char *));
						new->varnos = palloc(1024 * sizeof(int));
						new->nfields = 1;

						new->fieldnames[0] = $1->refname;
						new->varnos[0] = $1->varno;

						$$ = new;
					}
				| decl_cursor_arglist ',' decl_cursor_arg
					{
						int i = $1->nfields++;

						$1->fieldnames[i] = $3->refname;
						$1->varnos[i] = $3->varno;

						$$ = $1;
					}
				;

decl_cursor_arg : decl_varname decl_datatype
					{
						PLpgSQL_var *new;

						new = malloc(sizeof(PLpgSQL_var));
						memset(new, 0, sizeof(PLpgSQL_var));

						new->dtype		= PLPGSQL_DTYPE_VAR;
						new->refname	= $1.name;
						new->lineno		= $1.lineno;

						new->datatype	= $2;
						new->isconst	= false;
						new->notnull	= false;

						plpgsql_adddatum((PLpgSQL_datum *)new);
						plpgsql_ns_additem(PLPGSQL_NSTYPE_VAR, new->varno,
										   $1.name);
						
						$$ = new;
					}
				;

decl_is_from	:	K_IS |		/* Oracle */
					K_FOR;		/* ANSI */

decl_aliasitem	: T_WORD
					{
						PLpgSQL_nsitem *nsi;
						char	*name;

						plpgsql_ns_setlocal(false);
						name = plpgsql_tolower(yytext);
						if (name[0] != '$')
						{
							plpgsql_error_lineno = yylineno;
							elog(ERROR, "can only alias positional parameters");
						}
						nsi = plpgsql_ns_lookup(name, NULL);
						if (nsi == NULL)
						{
							plpgsql_error_lineno = yylineno;
							elog(ERROR, "function has no parameter %s", name);
						}

						plpgsql_ns_setlocal(true);

						$$ = nsi;
					}
				;

decl_rowtype	: T_ROW
					{
						$$ = yylval.row;
					}
				;

decl_varname	: T_WORD
					{
						/* name should be malloc'd for use as varname */
						$$.name = strdup(plpgsql_tolower(yytext));
						$$.lineno  = yylineno;
					}
				;

decl_renname	: T_WORD
					{
						/* the result must be palloc'd, see plpgsql_ns_rename */
						$$ = plpgsql_tolower(yytext);
					}
				;

decl_const		:
					{ $$ = 0; }
				| K_CONSTANT
					{ $$ = 1; }
				;

decl_datatype	:
					{
						/*
						 * If there's a lookahead token, read_datatype
						 * should consume it.
						 */
						$$ = read_datatype(yychar);
						yyclearin;
					}
				;

decl_notnull	:
					{ $$ = 0; }
				| K_NOT K_NULL
					{ $$ = 1; }
				;

decl_defval		: ';'
					{ $$ = NULL; }
				| decl_defkey
					{
						int				tok;
						int				lno;
						PLpgSQL_dstring ds;
						PLpgSQL_expr	*expr;

						lno = yylineno;
						expr = malloc(sizeof(PLpgSQL_expr));
						plpgsql_dstring_init(&ds);
						plpgsql_dstring_append(&ds, "SELECT ");

						expr->dtype   = PLPGSQL_DTYPE_EXPR;
						expr->plan	  = NULL;
						expr->nparams = 0;

						tok = yylex();
						switch (tok)
						{
							case 0:
								plpgsql_error_lineno = lno;
								elog(ERROR, "unexpected end of file");
							case K_NULL:
								if (yylex() != ';')
								{
									plpgsql_error_lineno = lno;
									elog(ERROR, "expected ; after NULL");
								}
								free(expr);
								plpgsql_dstring_free(&ds);

								$$ = NULL;
								break;

							default:
								plpgsql_dstring_append(&ds, yytext);
								while ((tok = yylex()) != ';')
								{
									if (tok == 0)
									{
										plpgsql_error_lineno = lno;
										elog(ERROR, "unterminated default value");
									}
									if (plpgsql_SpaceScanned)
										plpgsql_dstring_append(&ds, " ");
									plpgsql_dstring_append(&ds, yytext);
								}
								expr->query = strdup(plpgsql_dstring_get(&ds));
								plpgsql_dstring_free(&ds);

								$$ = expr;
								break;
						}
					}
				;

decl_defkey		: K_ASSIGN
				| K_DEFAULT

proc_sect		:
					{
							PLpgSQL_stmts	*new;

							new = malloc(sizeof(PLpgSQL_stmts));
							memset(new, 0, sizeof(PLpgSQL_stmts));
							$$ = new;
					}
				| proc_stmts
					{ $$ = $1; }
				;

proc_stmts		: proc_stmts proc_stmt
						{
								if ($1->stmts_used == $1->stmts_alloc) {
									$1->stmts_alloc *= 2;
									$1->stmts = realloc($1->stmts, sizeof(PLpgSQL_stmt *) * $1->stmts_alloc);
								}
								$1->stmts[$1->stmts_used++] = (struct PLpgSQL_stmt *)$2;

								$$ = $1;
						}
				| proc_stmt
						{
								PLpgSQL_stmts	*new;

								new = malloc(sizeof(PLpgSQL_stmts));
								memset(new, 0, sizeof(PLpgSQL_stmts));

								new->stmts_alloc = 64;
								new->stmts_used  = 1;
								new->stmts = malloc(sizeof(PLpgSQL_stmt *) * new->stmts_alloc);
								new->stmts[0] = (struct PLpgSQL_stmt *)$1;

								$$ = new;

						}
				;

proc_stmt		: pl_block ';'
						{ $$ = $1; }
				| stmt_assign
						{ $$ = $1; }
				| stmt_if
						{ $$ = $1; }
				| stmt_loop
						{ $$ = $1; }
				| stmt_while
						{ $$ = $1; }
				| stmt_fori
						{ $$ = $1; }
				| stmt_fors
						{ $$ = $1; }
				| stmt_select
						{ $$ = $1; }
				| stmt_exit
						{ $$ = $1; }
				| stmt_return
						{ $$ = $1; }
				| stmt_raise
						{ $$ = $1; }
				| stmt_execsql
						{ $$ = $1; }
				| stmt_dynexecute
						{ $$ = $1; }
				| stmt_dynfors
						{ $$ = $1; }
				| stmt_perform
						{ $$ = $1; }
				| stmt_getdiag
						{ $$ = $1; }
				| stmt_open
						{ $$ = $1; }
				| stmt_fetch
						{ $$ = $1; }
				| stmt_close
						{ $$ = $1; }
				;

stmt_perform	: K_PERFORM lno expr_until_semi
					{
						PLpgSQL_stmt_assign *new;

						new = malloc(sizeof(PLpgSQL_stmt_assign));
						memset(new, 0, sizeof(PLpgSQL_stmt_assign));

						new->cmd_type = PLPGSQL_STMT_ASSIGN;
						new->lineno   = $2;
						new->varno = -1;
						new->expr  = $3;

						$$ = (PLpgSQL_stmt *)new;
					}
				;

stmt_assign		: assign_var lno K_ASSIGN expr_until_semi
					{
						PLpgSQL_stmt_assign *new;

						new = malloc(sizeof(PLpgSQL_stmt_assign));
						memset(new, 0, sizeof(PLpgSQL_stmt_assign));

						new->cmd_type = PLPGSQL_STMT_ASSIGN;
						new->lineno   = $2;
						new->varno = $1;
						new->expr  = $4;

						$$ = (PLpgSQL_stmt *)new;
					}
				;

stmt_getdiag	: K_GET K_DIAGNOSTICS lno getdiag_list ';'
					{
						PLpgSQL_stmt_getdiag	 *new;

						new = malloc(sizeof(PLpgSQL_stmt_getdiag));
						memset(new, 0, sizeof(PLpgSQL_stmt_getdiag));

						new->cmd_type = PLPGSQL_STMT_GETDIAG;
						new->lineno   = $3;
						new->ndtitems = $4.nused;
						new->dtitems  = malloc(sizeof(PLpgSQL_diag_item) * $4.nused);
						memcpy(new->dtitems, $4.dtitems, sizeof(PLpgSQL_diag_item) * $4.nused);

						$$ = (PLpgSQL_stmt *)new;
					}
				;

getdiag_list : getdiag_list ',' getdiag_target K_ASSIGN getdiag_item
					{
						if ($1.nused == $1.nalloc)
						{
							$1.nalloc *= 2;
							$1.dtitems = repalloc($1.dtitems, sizeof(PLpgSQL_diag_item) * $1.nalloc);
						}
						$1.dtitems[$1.nused].target = $3;
						$1.dtitems[$1.nused].item   = $5;
						$1.nused++;

						$$.nalloc = $1.nalloc;
						$$.nused  = $1.nused;
						$$.dtitems = $1.dtitems;
					}
				| getdiag_target K_ASSIGN getdiag_item
					{
						$$.nalloc = 1;
						$$.nused  = 1;
						$$.dtitems = palloc(sizeof(PLpgSQL_diag_item) * $$.nalloc);
						$$.dtitems[0].target = $1;
						$$.dtitems[0].item   = $3;
					}
				;

getdiag_item : K_ROW_COUNT
					{
						$$ = PLPGSQL_GETDIAG_ROW_COUNT;
					}
				| K_RESULT_OID
					{
						$$ = PLPGSQL_GETDIAG_RESULT_OID;
					}
				;

getdiag_target	: T_VARIABLE
					{
						if (yylval.var->isconst)
						{
							plpgsql_error_lineno = yylineno;
							elog(ERROR, "%s is declared CONSTANT; can not receive diagnostics", yylval.var->refname);
						}
						$$ = yylval.var->varno;
					}
				| T_RECFIELD
					{
						$$ = yylval.recfield->rfno;
					}
				;


assign_var		: T_VARIABLE
					{
						if (yylval.var->isconst)
						{
							plpgsql_error_lineno = yylineno;
							elog(ERROR, "%s is declared CONSTANT", yylval.var->refname);
						}
						$$ = yylval.var->varno;
					}
				| T_RECFIELD
					{
						$$ = yylval.recfield->rfno;
					}
				;

stmt_if			: K_IF lno expr_until_then proc_sect stmt_else K_END K_IF ';'
					{
						PLpgSQL_stmt_if *new;

						new = malloc(sizeof(PLpgSQL_stmt_if));
						memset(new, 0, sizeof(PLpgSQL_stmt_if));

						new->cmd_type	= PLPGSQL_STMT_IF;
						new->lineno		= $2;
						new->cond		= $3;
						new->true_body	= $4;
						new->false_body = $5;

						$$ = (PLpgSQL_stmt *)new;
					}
				;

stmt_else		:
					{
							PLpgSQL_stmts	*new;

							new = malloc(sizeof(PLpgSQL_stmts));
							memset(new, 0, sizeof(PLpgSQL_stmts));
							$$ = new;
					}
				| K_ELSIF lno expr_until_then proc_sect stmt_else
					{
					  /*
					   * Translate the structure:	   into:
					   *
					   * IF c1 THEN					   IF c1 THEN		 
					   *	 ...						   ...				 
					   * ELSIF c2 THEN				   ELSE 
					   *								   IF c2 THEN	
					   *	 ...							   ...				 
					   * ELSE							   ELSE				 
					   *	 ...							   ...				 
					   * END IF							   END IF			 
					   *							   END IF
					   * 
					   */

						PLpgSQL_stmts	*new;
						PLpgSQL_stmt_if *new_if;

						/* first create a new if-statement */
						new_if = malloc(sizeof(PLpgSQL_stmt_if));
						memset(new_if, 0, sizeof(PLpgSQL_stmt_if));

						new_if->cmd_type	= PLPGSQL_STMT_IF;
						new_if->lineno		= $2;
						new_if->cond		= $3;
						new_if->true_body	= $4;
						new_if->false_body	= $5;
						
						/* this is a 'container' for the if-statement */
						new = malloc(sizeof(PLpgSQL_stmts));
						memset(new, 0, sizeof(PLpgSQL_stmts));
						
						new->stmts_alloc = 64;
						new->stmts_used	 = 1;
						new->stmts = malloc(sizeof(PLpgSQL_stmt *) * new->stmts_alloc);
						new->stmts[0] = (struct PLpgSQL_stmt *)new_if;

						$$ = new;
						
					}

				| K_ELSE proc_sect
					{
						$$ = $2;				
					}
				;

stmt_loop		: opt_label K_LOOP lno loop_body
					{
						PLpgSQL_stmt_loop *new;

						new = malloc(sizeof(PLpgSQL_stmt_loop));
						memset(new, 0, sizeof(PLpgSQL_stmt_loop));

						new->cmd_type = PLPGSQL_STMT_LOOP;
						new->lineno   = $3;
						new->label	  = $1;
						new->body	  = $4;

						plpgsql_ns_pop();

						$$ = (PLpgSQL_stmt *)new;
					}
				;

stmt_while		: opt_label K_WHILE lno expr_until_loop loop_body
					{
						PLpgSQL_stmt_while *new;

						new = malloc(sizeof(PLpgSQL_stmt_while));
						memset(new, 0, sizeof(PLpgSQL_stmt_while));

						new->cmd_type = PLPGSQL_STMT_WHILE;
						new->lineno   = $3;
						new->label	  = $1;
						new->cond	  = $4;
						new->body	  = $5;

						plpgsql_ns_pop();

						$$ = (PLpgSQL_stmt *)new;
					}
				;

stmt_fori		: opt_label K_FOR lno fori_var K_IN fori_lower expr_until_loop loop_body
					{
						PLpgSQL_stmt_fori		*new;

						new = malloc(sizeof(PLpgSQL_stmt_fori));
						memset(new, 0, sizeof(PLpgSQL_stmt_fori));

						new->cmd_type = PLPGSQL_STMT_FORI;
						new->lineno   = $3;
						new->label	  = $1;
						new->var	  = $4;
						new->reverse  = $6.reverse;
						new->lower	  = $6.expr;
						new->upper	  = $7;
						new->body	  = $8;

						plpgsql_ns_pop();

						$$ = (PLpgSQL_stmt *)new;
					}
				;

fori_var		: fori_varname
					{
						PLpgSQL_var		*new;

						new = malloc(sizeof(PLpgSQL_var));
						memset(new, 0, sizeof(PLpgSQL_var));

						new->dtype		= PLPGSQL_DTYPE_VAR;
						new->refname	= $1.name;
						new->lineno		= $1.lineno;

						new->datatype	= plpgsql_parse_datatype("integer");
						new->isconst	= false;
						new->notnull	= false;
						new->default_val = NULL;

						plpgsql_adddatum((PLpgSQL_datum *)new);
						plpgsql_ns_additem(PLPGSQL_NSTYPE_VAR, new->varno,
												$1.name);

						plpgsql_add_initdatums(NULL);

						$$ = new;
					}
				;

fori_varname	: T_VARIABLE
					{
						$$.name = strdup(yytext);
						$$.lineno = yylineno;
					}
				| T_WORD
					{
						$$.name = strdup(yytext);
						$$.lineno = yylineno;
					}
				;

fori_lower		:
					{
						int			tok;

						tok = yylex();
						if (tok == K_REVERSE)
						{
							$$.reverse = 1;
						}
						else
						{
							$$.reverse = 0;
							plpgsql_push_back_token(tok);
						}

						$$.expr = plpgsql_read_expression(K_DOTDOT, "..");
					}

stmt_fors		: opt_label K_FOR lno fors_target K_IN K_SELECT expr_until_loop loop_body
					{
						PLpgSQL_stmt_fors		*new;

						new = malloc(sizeof(PLpgSQL_stmt_fors));
						memset(new, 0, sizeof(PLpgSQL_stmt_fors));

						new->cmd_type = PLPGSQL_STMT_FORS;
						new->lineno   = $3;
						new->label	  = $1;
						switch ($4->dtype)
						{
							case PLPGSQL_DTYPE_REC:
								new->rec = $4;
								break;
							case PLPGSQL_DTYPE_ROW:
								new->row = (PLpgSQL_row *)$4;
								break;
							default:
								elog(ERROR, "unknown dtype %d in stmt_fors", $4->dtype);
						}
						new->query = $7;
						new->body  = $8;

						plpgsql_ns_pop();

						$$ = (PLpgSQL_stmt *)new;
					}

stmt_dynfors : opt_label K_FOR lno fors_target K_IN K_EXECUTE expr_until_loop loop_body
					{
						PLpgSQL_stmt_dynfors	*new;

						new = malloc(sizeof(PLpgSQL_stmt_dynfors));
						memset(new, 0, sizeof(PLpgSQL_stmt_dynfors));

						new->cmd_type = PLPGSQL_STMT_DYNFORS;
						new->lineno   = $3;
						new->label	  = $1;
						switch ($4->dtype)
						{
							case PLPGSQL_DTYPE_REC:
								new->rec = $4;
								break;
							case PLPGSQL_DTYPE_ROW:
								new->row = (PLpgSQL_row *)$4;
								break;
							default:
								elog(ERROR, "unknown dtype %d in stmt_dynfors", $4->dtype);
						}
						new->query = $7;
						new->body  = $8;

						plpgsql_ns_pop();

						$$ = (PLpgSQL_stmt *)new;
					}

fors_target		: T_RECORD
					{ $$ = yylval.rec; }
				| T_ROW
					{
						$$ = (PLpgSQL_rec *)(yylval.row);
					}
				;

stmt_select		: K_SELECT lno
					{
						$$ = make_select_stmt();
						$$->lineno = $2;
					}
				;

stmt_exit		: K_EXIT lno opt_exitlabel opt_exitcond
					{
						PLpgSQL_stmt_exit *new;

						new = malloc(sizeof(PLpgSQL_stmt_exit));
						memset(new, 0, sizeof(PLpgSQL_stmt_exit));

						new->cmd_type = PLPGSQL_STMT_EXIT;
						new->lineno   = $2;
						new->label	  = $3;
						new->cond	  = $4;

						$$ = (PLpgSQL_stmt *)new;
					}
				;

stmt_return		: K_RETURN lno
					{
						PLpgSQL_stmt_return *new;
						PLpgSQL_expr	*expr = NULL;
						int				tok;

						new = malloc(sizeof(PLpgSQL_stmt_return));
						memset(new, 0, sizeof(PLpgSQL_stmt_return));

						if (plpgsql_curr_compile->fn_retistuple)
						{
							new->retistuple = true;
							new->retrecno	= -1;
							switch (tok = yylex())
							{
								case K_NULL:
									expr = NULL;
									break;

								case T_ROW:
									expr = make_tupret_expr(yylval.row);
									break;

								case T_RECORD:
									new->retrecno = yylval.rec->recno;
									expr = NULL;
									break;

								default:
									yyerror("return type mismatch in function returning table row");
									break;
							}
							if (yylex() != ';')
								yyerror("expected ';'");
						} else {
							new->retistuple = false;
							expr = plpgsql_read_expression(';', ";");
						}

						new->cmd_type = PLPGSQL_STMT_RETURN;
						new->lineno   = $2;
						new->expr	  = expr;

						$$ = (PLpgSQL_stmt *)new;
					}
				;

stmt_raise		: K_RAISE lno raise_level raise_msg raise_params ';'
					{
						PLpgSQL_stmt_raise		*new;

						new = malloc(sizeof(PLpgSQL_stmt_raise));

						new->cmd_type	= PLPGSQL_STMT_RAISE;
						new->lineno		= $2;
						new->elog_level = $3;
						new->message	= $4;
						new->nparams	= $5.nused;
						new->params		= malloc(sizeof(int) * $5.nused);
						memcpy(new->params, $5.nums, sizeof(int) * $5.nused);

						$$ = (PLpgSQL_stmt *)new;
					}
				| K_RAISE lno raise_level raise_msg ';'
					{
						PLpgSQL_stmt_raise		*new;

						new = malloc(sizeof(PLpgSQL_stmt_raise));

						new->cmd_type	= PLPGSQL_STMT_RAISE;
						new->lineno		= $2;
						new->elog_level = $3;
						new->message	= $4;
						new->nparams	= 0;
						new->params		= NULL;

						$$ = (PLpgSQL_stmt *)new;
					}
				;

raise_msg		: T_STRING
					{
						$$ = strdup(yytext);
					}
				;

raise_level		: K_EXCEPTION
					{
						$$ = ERROR;
					}
				| K_NOTICE
					{
						$$ = NOTICE;
					}
				| K_DEBUG
					{
						$$ = DEBUG;
					}
				;

raise_params	: raise_params raise_param
					{
						if ($1.nused == $1.nalloc)
						{
							$1.nalloc *= 2;
							$1.nums = repalloc($1.nums, sizeof(int) * $1.nalloc);
						}
						$1.nums[$1.nused++] = $2;

						$$.nalloc = $1.nalloc;
						$$.nused  = $1.nused;
						$$.nums   = $1.nums;
					}
				| raise_param
					{
						$$.nalloc = 1;
						$$.nused  = 1;
						$$.nums   = palloc(sizeof(int) * $$.nalloc);
						$$.nums[0] = $1;
					}
				;

raise_param		: ',' T_VARIABLE
					{
						$$ = yylval.var->varno;
					}
				| ',' T_RECFIELD
					{
						$$ = yylval.recfield->rfno;
					}
				| ',' T_TGARGV
					{
						$$ = yylval.trigarg->dno;
					}
				;

loop_body		: proc_sect K_END K_LOOP ';'
					{ $$ = $1; }
				;

stmt_execsql	: execsql_start lno
					{
						PLpgSQL_stmt_execsql	*new;

						new = malloc(sizeof(PLpgSQL_stmt_execsql));
						new->cmd_type = PLPGSQL_STMT_EXECSQL;
						new->lineno   = $2;
						new->sqlstmt  = read_sql_stmt($1);

						$$ = (PLpgSQL_stmt *)new;
					}
				;

stmt_dynexecute : K_EXECUTE lno expr_until_semi
						{
							PLpgSQL_stmt_dynexecute *new;

							new = malloc(sizeof(PLpgSQL_stmt_dynexecute));
							new->cmd_type = PLPGSQL_STMT_DYNEXECUTE;
							new->lineno   = $2;
							new->query	  = $3;

							$$ = (PLpgSQL_stmt *)new;
						}
				;

stmt_open		: K_OPEN lno cursor_varptr
					{
						PLpgSQL_stmt_open *new;
						int				  tok;

						new = malloc(sizeof(PLpgSQL_stmt_open));
						memset(new, 0, sizeof(PLpgSQL_stmt_open));

						new->cmd_type = PLPGSQL_STMT_OPEN;
						new->lineno = $2;
						new->curvar = $3->varno;

						if ($3->cursor_explicit_expr == NULL)
						{
						    tok = yylex();

							if (tok != K_FOR)
							{
								plpgsql_error_lineno = $2;
								elog(ERROR, "syntax error at \"%s\" - expected FOR to open a reference cursor", yytext);
							}

							tok = yylex();
							switch (tok)
							{
								case K_SELECT:
									new->query = read_sql_stmt("SELECT ");
									break;

								case K_EXECUTE:
									new->dynquery = read_sql_stmt("SELECT ");
									break;

								default:
									plpgsql_error_lineno = $2;
									elog(ERROR, "syntax error at \"%s\"", yytext);
							}

						}
						else
						{
							if ($3->cursor_explicit_argrow >= 0)
							{
								char   *cp;

								tok = yylex();

								if (tok != '(')
								{
									plpgsql_error_lineno = yylineno;
									elog(ERROR, "cursor %s has arguments",
										 $3->refname);
								}

								/*
								 * Push back the '(', else read_sql_stmt
								 * will complain about unbalanced parens.
								 */
								plpgsql_push_back_token(tok);

								new->argquery = read_sql_stmt("SELECT ");

								/*
								 * Now remove the leading and trailing parens,
								 * because we want "select 1, 2", not
								 * "select (1, 2)".
								 */
								cp = new->argquery->query;

								if (strncmp(cp, "SELECT", 6) != 0)
								{
									plpgsql_error_lineno = yylineno;
									elog(ERROR, "expected 'SELECT (', got '%s' (internal error)",
										 new->argquery->query);
								}
								cp += 6;
								while (*cp == ' ') /* could be more than 1 space here */
									cp++;
								if (*cp != '(')
								{
									plpgsql_error_lineno = yylineno;
									elog(ERROR, "expected 'SELECT (', got '%s' (internal error)",
										 new->argquery->query);
								}
								*cp = ' ';

								cp += strlen(cp) - 1;

								if (*cp != ')')
								{
									plpgsql_error_lineno = yylineno;
									elog(ERROR, "missing )");
								}
								*cp = '\0';
							}
							else
							{
								tok = yylex();

								if (tok == '(')
								{
									plpgsql_error_lineno = yylineno;
									elog(ERROR, "cursor %s has no arguments", $3->refname);
								}
								
								if (tok != ';')
								{
									plpgsql_error_lineno = yylineno;
									elog(ERROR, "syntax error at \"%s\"", yytext);
								}
							}
						}

						$$ = (PLpgSQL_stmt *)new;
					}
				;

stmt_fetch		: K_FETCH lno cursor_variable K_INTO
					{
						PLpgSQL_stmt_fetch *new;

						new = (PLpgSQL_stmt_fetch *)make_fetch_stmt();
						new->curvar = $3;

						$$ = (PLpgSQL_stmt *)new;
						$$->lineno = $2;
					}
				;

stmt_close		: K_CLOSE lno cursor_variable ';'
					{
						PLpgSQL_stmt_close *new;

						new = malloc(sizeof(PLpgSQL_stmt_close));
						new->cmd_type = PLPGSQL_STMT_CLOSE;
						new->lineno = $2;
						new->curvar = $3;

						$$ = (PLpgSQL_stmt *)new;
					}
				;

cursor_varptr	: T_VARIABLE
					{
						if (yylval.var->datatype->typoid != REFCURSOROID)
						{
							plpgsql_error_lineno = yylineno;
							elog(ERROR, "%s must be of type cursor or refcursor", yylval.var->refname);
						}
						$$ = yylval.var;
					}
				;

cursor_variable	: T_VARIABLE
					{
						if (yylval.var->datatype->typoid != REFCURSOROID)
						{
							plpgsql_error_lineno = yylineno;
							elog(ERROR, "%s must be of type refcursor", yylval.var->refname);
						}
						$$ = yylval.var->varno;
					}
				;

execsql_start	: T_WORD
					{ $$ = strdup(yytext); }
				| T_ERROR
					{ $$ = strdup(yytext); }
				;

expr_until_semi :
					{ $$ = plpgsql_read_expression(';', ";"); }
				;

expr_until_then :
					{ $$ = plpgsql_read_expression(K_THEN, "THEN"); }
				;

expr_until_loop :
					{ $$ = plpgsql_read_expression(K_LOOP, "LOOP"); }
				;

opt_label		:
					{
						plpgsql_ns_push(NULL);
						$$ = NULL;
					}
				| '<' '<' opt_lblname '>' '>'
					{
						plpgsql_ns_push($3);
						$$ = $3;
					}
				;

opt_exitlabel	:
					{ $$ = NULL; }
				| T_LABEL
					{ $$ = strdup(yytext); }
				;

opt_exitcond	: ';'
					{ $$ = NULL; }
				| K_WHEN expr_until_semi
					{ $$ = $2; }
				;

opt_lblname		: T_WORD
					{ $$ = strdup(yytext); }
				;

lno				:
					{
						plpgsql_error_lineno = yylineno;
						$$ = yylineno;
					}
				;

%%


PLpgSQL_expr *
plpgsql_read_expression(int until, const char *expected)
{
	return read_sql_construct(until, expected, true, "SELECT ");
}

static PLpgSQL_expr *
read_sql_stmt(const char *sqlstart)
{
	return read_sql_construct(';', ";", false, sqlstart);
}

static PLpgSQL_expr *
read_sql_construct(int until,
				   const char *expected,
				   bool isexpression,
				   const char *sqlstart)
{
	int					tok;
	int					lno;
	PLpgSQL_dstring		ds;
	int					parenlevel = 0;
	int					nparams = 0;
	int					params[1024];
	char				buf[32];
	PLpgSQL_expr		*expr;

	lno = yylineno;
	plpgsql_dstring_init(&ds);
	plpgsql_dstring_append(&ds, (char *) sqlstart);

	for (;;)
	{
		tok = yylex();
		if (tok == '(')
			parenlevel++;
		else if (tok == ')')
		{
			parenlevel--;
			if (parenlevel < 0)
				elog(ERROR, "mismatched parentheses");
		}
		else if (parenlevel == 0 && tok == until)
			break;
		/*
		 * End of function definition is an error, and we don't expect to
		 * hit a semicolon either (unless it's the until symbol, in which
		 * case we should have fallen out above).
		 */
		if (tok == 0 || tok == ';')
		{
			plpgsql_error_lineno = lno;
			if (parenlevel != 0)
				elog(ERROR, "mismatched parentheses");
			if (isexpression)
				elog(ERROR, "missing %s at end of SQL expression",
					 expected);
			else
				elog(ERROR, "missing %s at end of SQL statement",
					 expected);
			break;
		}
		if (plpgsql_SpaceScanned)
			plpgsql_dstring_append(&ds, " ");
		switch (tok)
		{
			case T_VARIABLE:
				params[nparams] = yylval.var->varno;
				sprintf(buf, " $%d ", ++nparams);
				plpgsql_dstring_append(&ds, buf);
				break;

			case T_RECFIELD:
				params[nparams] = yylval.recfield->rfno;
				sprintf(buf, " $%d ", ++nparams);
				plpgsql_dstring_append(&ds, buf);
				break;

			case T_TGARGV:
				params[nparams] = yylval.trigarg->dno;
				sprintf(buf, " $%d ", ++nparams);
				plpgsql_dstring_append(&ds, buf);
				break;

			default:
				plpgsql_dstring_append(&ds, yytext);
				break;
		}
	}

	expr = malloc(sizeof(PLpgSQL_expr) + sizeof(int) * nparams - sizeof(int));
	expr->dtype			= PLPGSQL_DTYPE_EXPR;
	expr->query			= strdup(plpgsql_dstring_get(&ds));
	expr->plan			= NULL;
	expr->nparams		= nparams;
	while(nparams-- > 0)
		expr->params[nparams] = params[nparams];
	plpgsql_dstring_free(&ds);

	return expr;
}

static PLpgSQL_type *
read_datatype(int tok)
{
	int					lno;
	PLpgSQL_dstring		ds;
	PLpgSQL_type		*result;
	bool				needspace = false;
	int					parenlevel = 0;

	lno = yylineno;

	/* Often there will be a lookahead token, but if not, get one */
	if (tok == YYEMPTY)
		tok = yylex();

	if (tok == T_DTYPE)
	{
		/* lexer found word%TYPE and did its thing already */
		return yylval.dtype;
	}

	plpgsql_dstring_init(&ds);

	while (tok != ';')
	{
		if (tok == 0)
		{
			plpgsql_error_lineno = lno;
			if (parenlevel != 0)
				elog(ERROR, "mismatched parentheses");
			elog(ERROR, "incomplete datatype declaration");
		}
		/* Possible followers for datatype in a declaration */
		if (tok == K_NOT || tok == K_ASSIGN || tok == K_DEFAULT)
			break;
		/* Possible followers for datatype in a cursor_arg list */
		if ((tok == ',' || tok == ')') && parenlevel == 0)
			break;
		if (tok == '(')
			parenlevel++;
		else if (tok == ')')
			parenlevel--;
		if (needspace)
			plpgsql_dstring_append(&ds, " ");
		needspace = true;
		plpgsql_dstring_append(&ds, yytext);

		tok = yylex();
	}

	plpgsql_push_back_token(tok);

	plpgsql_error_lineno = lno;	/* in case of error in parse_datatype */

	result = plpgsql_parse_datatype(plpgsql_dstring_get(&ds));

	plpgsql_dstring_free(&ds);

	return result;
}


static PLpgSQL_stmt *
make_select_stmt()
{
	int					tok;
	int					lno;
	PLpgSQL_dstring		ds;
	int					nparams = 0;
	int					params[1024];
	char				buf[32];
	PLpgSQL_expr		*expr;
	PLpgSQL_row			*row = NULL;
	PLpgSQL_rec			*rec = NULL;
	PLpgSQL_stmt_select *select;
	int					have_nexttok = 0;

	lno = yylineno;
	plpgsql_dstring_init(&ds);
	plpgsql_dstring_append(&ds, "SELECT ");

	while((tok = yylex()) != K_INTO)
	{
		if (tok == ';')
		{
			PLpgSQL_stmt_execsql		*execsql;

			expr = malloc(sizeof(PLpgSQL_expr) + sizeof(int) * nparams - sizeof(int));
			expr->dtype			= PLPGSQL_DTYPE_EXPR;
			expr->query			= strdup(plpgsql_dstring_get(&ds));
			expr->plan			= NULL;
			expr->nparams		= nparams;
			while(nparams-- > 0)
				expr->params[nparams] = params[nparams];
			plpgsql_dstring_free(&ds);

			execsql = malloc(sizeof(PLpgSQL_stmt_execsql));
			execsql->cmd_type = PLPGSQL_STMT_EXECSQL;
			execsql->sqlstmt  = expr;

			return (PLpgSQL_stmt *)execsql;
		}

		if (plpgsql_SpaceScanned)
			plpgsql_dstring_append(&ds, " ");
		switch (tok)
		{
			case T_VARIABLE:
				params[nparams] = yylval.var->varno;
				sprintf(buf, " $%d ", ++nparams);
				plpgsql_dstring_append(&ds, buf);
				break;

			case T_RECFIELD:
				params[nparams] = yylval.recfield->rfno;
				sprintf(buf, " $%d ", ++nparams);
				plpgsql_dstring_append(&ds, buf);
				break;

			case T_TGARGV:
				params[nparams] = yylval.trigarg->dno;
				sprintf(buf, " $%d ", ++nparams);
				plpgsql_dstring_append(&ds, buf);
				break;

			default:
				if (tok == 0)
				{
					plpgsql_error_lineno = yylineno;
					elog(ERROR, "unexpected end of file");
				}
				plpgsql_dstring_append(&ds, yytext);
				break;
		}
	}

	tok = yylex();
	switch (tok)
	{
		case T_ROW:
			row = yylval.row;
			break;

		case T_RECORD:
			rec = yylval.rec;
			break;

		case T_VARIABLE:
		case T_RECFIELD:
			{
				PLpgSQL_var		*var;
				PLpgSQL_recfield *recfield;
				int				nfields = 1;
				char			*fieldnames[1024];
				int				varnos[1024];

				switch (tok)
				{	
					case T_VARIABLE:
						var = yylval.var;
						fieldnames[0] = strdup(yytext);
						varnos[0]	  = var->varno;
						break;

					case T_RECFIELD:
						recfield = yylval.recfield;
						fieldnames[0] = strdup(yytext);
						varnos[0]	  = recfield->rfno;
						break;
				}

				while ((tok = yylex()) == ',')
				{
					tok = yylex();
					switch(tok)
					{
						case T_VARIABLE:
							var = yylval.var;
							fieldnames[nfields] = strdup(yytext);
							varnos[nfields++]	= var->varno;
							break;

						case T_RECFIELD:
							recfield = yylval.recfield;
							fieldnames[0] = strdup(yytext);
							varnos[0]	  = recfield->rfno;
							break;

						default:
							plpgsql_error_lineno = yylineno;
							elog(ERROR, "plpgsql: %s is not a variable or record field", yytext);
					}
				}
				row = malloc(sizeof(PLpgSQL_row));
				row->dtype = PLPGSQL_DTYPE_ROW;
				row->refname = strdup("*internal*");
				row->lineno = yylineno;
				row->rowtypeclass = InvalidOid;
				row->nfields = nfields;
				row->fieldnames = malloc(sizeof(char *) * nfields);
				row->varnos = malloc(sizeof(int) * nfields);
				while (--nfields >= 0)
				{
					row->fieldnames[nfields] = fieldnames[nfields];
					row->varnos[nfields] = varnos[nfields];
				}

				plpgsql_adddatum((PLpgSQL_datum *)row);

				have_nexttok = 1;
			}
			break;

		default:
			{
				if (plpgsql_SpaceScanned)
					plpgsql_dstring_append(&ds, " ");
				plpgsql_dstring_append(&ds, yytext);

				while(1)
				{
					tok = yylex();
					if (tok == ';')
					{
						PLpgSQL_stmt_execsql	*execsql;

						expr = malloc(sizeof(PLpgSQL_expr) + sizeof(int) * nparams - sizeof(int));
						expr->dtype				= PLPGSQL_DTYPE_EXPR;
						expr->query				= strdup(plpgsql_dstring_get(&ds));
						expr->plan				= NULL;
						expr->nparams	= nparams;
						while (nparams-- > 0)
							expr->params[nparams] = params[nparams];
						plpgsql_dstring_free(&ds);

						execsql = malloc(sizeof(PLpgSQL_stmt_execsql));
						execsql->cmd_type = PLPGSQL_STMT_EXECSQL;
						execsql->sqlstmt  = expr;

						return (PLpgSQL_stmt *)execsql;
					}

					if (plpgsql_SpaceScanned)
						plpgsql_dstring_append(&ds, " ");
					switch (tok)
					{
						case T_VARIABLE:
							params[nparams] = yylval.var->varno;
							sprintf(buf, " $%d ", ++nparams);
							plpgsql_dstring_append(&ds, buf);
							break;

						case T_RECFIELD:
							params[nparams] = yylval.recfield->rfno;
							sprintf(buf, " $%d ", ++nparams);
							plpgsql_dstring_append(&ds, buf);
							break;

						case T_TGARGV:
							params[nparams] = yylval.trigarg->dno;
							sprintf(buf, " $%d ", ++nparams);
							plpgsql_dstring_append(&ds, buf);
							break;

						default:
							if (tok == 0)
							{
								plpgsql_error_lineno = yylineno;
								elog(ERROR, "unexpected end of file");
							}
							plpgsql_dstring_append(&ds, yytext);
							break;
					}
				}
			}
	}

	/************************************************************
	 * Eat up the rest of the statement after the target fields
	 ************************************************************/
	while(1)
	{
		if (!have_nexttok) {
			tok = yylex();
		}
		have_nexttok = 0;
		if (tok == ';') {
			break;
		}

		if (plpgsql_SpaceScanned)
			plpgsql_dstring_append(&ds, " ");
		switch (tok)
		{
			case T_VARIABLE:
				params[nparams] = yylval.var->varno;
				sprintf(buf, " $%d ", ++nparams);
				plpgsql_dstring_append(&ds, buf);
				break;

			case T_RECFIELD:
				params[nparams] = yylval.recfield->rfno;
				sprintf(buf, " $%d ", ++nparams);
				plpgsql_dstring_append(&ds, buf);
				break;

			case T_TGARGV:
				params[nparams] = yylval.trigarg->dno;
				sprintf(buf, " $%d ", ++nparams);
				plpgsql_dstring_append(&ds, buf);
				break;

			default:
				if (tok == 0)
				{
					plpgsql_error_lineno = yylineno;
					elog(ERROR, "unexpected end of file");
				}
				plpgsql_dstring_append(&ds, yytext);
				break;
		}
	}

	expr = malloc(sizeof(PLpgSQL_expr) + sizeof(int) * nparams - sizeof(int));
	expr->dtype			= PLPGSQL_DTYPE_EXPR;
	expr->query			= strdup(plpgsql_dstring_get(&ds));
	expr->plan			= NULL;
	expr->nparams		= nparams;
	while(nparams-- > 0)
		expr->params[nparams] = params[nparams];
	plpgsql_dstring_free(&ds);

	select = malloc(sizeof(PLpgSQL_stmt_select));
	memset(select, 0, sizeof(PLpgSQL_stmt_select));
	select->cmd_type = PLPGSQL_STMT_SELECT;
	select->rec		 = rec;
	select->row		 = row;
	select->query	 = expr;

	return (PLpgSQL_stmt *)select;
}


static PLpgSQL_stmt *
make_fetch_stmt()
{
	int					tok;
	PLpgSQL_row		   *row = NULL;
	PLpgSQL_rec		   *rec = NULL;
	PLpgSQL_stmt_fetch *fetch;
	int					have_nexttok = 0;

	tok = yylex();
	switch (tok)
	{
		case T_ROW:
			row = yylval.row;
			break;

		case T_RECORD:
			rec = yylval.rec;
			break;

		case T_VARIABLE:
		case T_RECFIELD:
			{
				PLpgSQL_var		*var;
				PLpgSQL_recfield *recfield;
				int				nfields = 1;
				char			*fieldnames[1024];
				int				varnos[1024];

				switch (tok)
				{	
					case T_VARIABLE:
						var = yylval.var;
						fieldnames[0] = strdup(yytext);
						varnos[0]	  = var->varno;
						break;

					case T_RECFIELD:
						recfield = yylval.recfield;
						fieldnames[0] = strdup(yytext);
						varnos[0]	  = recfield->rfno;
						break;
				}

				while ((tok = yylex()) == ',')
				{
					tok = yylex();
					switch(tok)
					{
						case T_VARIABLE:
							var = yylval.var;
							fieldnames[nfields] = strdup(yytext);
							varnos[nfields++]	= var->varno;
							break;

						case T_RECFIELD:
							recfield = yylval.recfield;
							fieldnames[0] = strdup(yytext);
							varnos[0]	  = recfield->rfno;
							break;

						default:
							plpgsql_error_lineno = yylineno;
							elog(ERROR, "plpgsql: %s is not a variable or record field", yytext);
					}
				}
				row = malloc(sizeof(PLpgSQL_row));
				row->dtype = PLPGSQL_DTYPE_ROW;
				row->refname = strdup("*internal*");
				row->lineno = yylineno;
				row->rowtypeclass = InvalidOid;
				row->nfields = nfields;
				row->fieldnames = malloc(sizeof(char *) * nfields);
				row->varnos = malloc(sizeof(int) * nfields);
				while (--nfields >= 0)
				{
					row->fieldnames[nfields] = fieldnames[nfields];
					row->varnos[nfields] = varnos[nfields];
				}

				plpgsql_adddatum((PLpgSQL_datum *)row);

				have_nexttok = 1;
			}
			break;

		default:
			plpgsql_error_lineno = yylineno;
			elog(ERROR, "syntax error at '%s'", yytext);
	}

	if (!have_nexttok)
		tok = yylex();

	if (tok != ';')
	{
		plpgsql_error_lineno = yylineno;
		elog(ERROR, "syntax error at '%s'", yytext);
	}

	fetch = malloc(sizeof(PLpgSQL_stmt_select));
	memset(fetch, 0, sizeof(PLpgSQL_stmt_fetch));
	fetch->cmd_type = PLPGSQL_STMT_FETCH;
	fetch->rec		 = rec;
	fetch->row		 = row;

	return (PLpgSQL_stmt *)fetch;
}


static PLpgSQL_expr *
make_tupret_expr(PLpgSQL_row *row)
{
	PLpgSQL_dstring		ds;
	PLpgSQL_expr		*expr;
	int					i;
	char				buf[16];

	expr = malloc(sizeof(PLpgSQL_expr) + sizeof(int) * (row->nfields - 1));
	expr->dtype			= PLPGSQL_DTYPE_EXPR;

	plpgsql_dstring_init(&ds);
	plpgsql_dstring_append(&ds, "SELECT ");

	for (i = 0; i < row->nfields; i++)
	{
		sprintf(buf, "%s$%d", (i > 0) ? "," : "", i + 1);
		plpgsql_dstring_append(&ds, buf);
		expr->params[i] = row->varnos[i];
	}

	expr->query			= strdup(plpgsql_dstring_get(&ds));
	expr->plan			= NULL;
	expr->plan_argtypes = NULL;
	expr->nparams		= row->nfields;

	plpgsql_dstring_free(&ds);
	return expr;
}
