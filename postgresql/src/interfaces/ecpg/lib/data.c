/* $Header: /cvsroot/pgsql-server/src/interfaces/ecpg/lib/data.c,v 1.23 2002/01/08 23:34:47 tgl Exp $ */

#include "postgres_fe.h"

#include <stdlib.h>
#include <string.h>

#include "ecpgtype.h"
#include "ecpglib.h"
#include "ecpgerrno.h"
#include "extern.h"
#include "sqlca.h"

bool
ECPGget_data(const PGresult *results, int act_tuple, int act_field, int lineno,
		 enum ECPGttype type, enum ECPGttype ind_type,
		 char *var, char *ind, long varcharsize, long offset,
		 long ind_offset, bool isarray)
{
	char	   *pval = (char *) PQgetvalue(results, act_tuple, act_field);

	ECPGlog("ECPGget_data line %d: RESULT: %s offset: %ld\n", lineno, pval ? pval : "", offset);

	/* pval is a pointer to the value */
	/* let's check is it really is an array if it should be one */
	if (isarray)
	{
		if (*pval != '{')
		{
			ECPGraise(lineno, ECPG_DATA_NOT_ARRAY, NULL);
			return (false);
		}

		switch (type)
		{
			case ECPGt_char:
			case ECPGt_unsigned_char:
			case ECPGt_varchar:
				break;

			default:
				pval++;
				break;
		}
	}

	/* We will have to decode the value */

	/*
	 * check for null value and set indicator accordingly
	 */
	switch (ind_type)
	{
		case ECPGt_short:
		case ECPGt_unsigned_short:
/*			((short *) ind)[act_tuple] = -PQgetisnull(results, act_tuple, act_field);*/
			*((short *) (ind + ind_offset*act_tuple)) = -PQgetisnull(results, act_tuple, act_field);
			break;
		case ECPGt_int:
		case ECPGt_unsigned_int:
/*			((int *) ind)[act_tuple] = -PQgetisnull(results, act_tuple, act_field);*/
			*((int *) (ind + ind_offset*act_tuple)) = -PQgetisnull(results, act_tuple, act_field);
			break;
		case ECPGt_long:
		case ECPGt_unsigned_long:
/*			((long *) ind)[act_tuple] = -PQgetisnull(results, act_tuple, act_field);*/
			*((long *) (ind + ind_offset*act_tuple)) = -PQgetisnull(results, act_tuple, act_field);
			break;
#ifdef HAVE_LONG_LONG_INT_64
		case ECPGt_long_long:
		case ECPGt_unsigned_long_long:
/*			((long long int *) ind)[act_tuple] = -PQgetisnull(results, act_tuple, act_field);*/
			*((long long int *) (ind + ind_offset*act_tuple)) = -PQgetisnull(results, act_tuple, act_field);
			break;
/*		case ECPGt_unsigned_long_long:
			((unsigned long long int *) ind)[act_tuple] = -PQgetisnull(results, act_tuple, act_field);
			break;*/
#endif   /* HAVE_LONG_LONG_INT_64 */
		case ECPGt_NO_INDICATOR:
			if (PQgetisnull(results, act_tuple, act_field))
			{
				ECPGraise(lineno, ECPG_MISSING_INDICATOR, NULL);
				return (false);
			}
			break;
		default:
			ECPGraise(lineno, ECPG_UNSUPPORTED, ECPGtype_name(ind_type));
			return (false);
			break;
	}

	do
	{
		switch (type)
		{
				long		res;
				unsigned long ures;
				double		dres;
				char	   *scan_length;

			case ECPGt_short:
			case ECPGt_int:
			case ECPGt_long:
				if (pval)
				{
					res = strtol(pval, &scan_length, 10);
					if ((isarray && *scan_length != ',' && *scan_length != '}')
						|| (!isarray && *scan_length != '\0'))	/* Garbage left */
					{
						ECPGraise(lineno, ECPG_INT_FORMAT, pval);
						return (false);
					}
				}
				else
					res = 0L;

				switch (type)
				{
					case ECPGt_short:
/*						((short *) var)[act_tuple] = (short) res;*/
						*((short *) (var + offset*act_tuple)) = (short) res;
						break;
					case ECPGt_int:
/*						((int *) var)[act_tuple] = (int) res;*/
						*((int *) (var + offset*act_tuple)) = (int) res;
						break;
					case ECPGt_long:
/*						((long *) var)[act_tuple] = res;*/
						*((long *) (var + offset*act_tuple)) = (long) res;
						break;
					default:
						/* Cannot happen */
						break;
				}
				break;

			case ECPGt_unsigned_short:
			case ECPGt_unsigned_int:
			case ECPGt_unsigned_long:
				if (pval)
				{
					ures = strtoul(pval, &scan_length, 10);
					if ((isarray && *scan_length != ',' && *scan_length != '}')
						|| (!isarray && *scan_length != '\0'))	/* Garbage left */
					{
						ECPGraise(lineno, ECPG_UINT_FORMAT, pval);
						return (false);
					}
				}
				else
					ures = 0L;

				switch (type)
				{
					case ECPGt_unsigned_short:
/*						((unsigned short *) var)[act_tuple] = (unsigned short) ures;*/
						*((unsigned short *) (var + offset*act_tuple)) = (unsigned short) ures;
						break;
					case ECPGt_unsigned_int:
/*						((unsigned int *) var)[act_tuple] = (unsigned int) ures;*/
						*((unsigned int *) (var + offset*act_tuple)) = (unsigned int) ures;
						break;
					case ECPGt_unsigned_long:
/*						((unsigned long *) var)[act_tuple] = ures;*/
						*((unsigned long *) (var + offset*act_tuple)) = (unsigned long) ures;
						break;
					default:
						/* Cannot happen */
						break;
				}
				break;

#ifdef HAVE_LONG_LONG_INT_64
#ifdef HAVE_STRTOLL
			case ECPGt_long_long:
				if (pval)
				{
/*					((long long int *) var)[act_tuple] = strtoll(pval, &scan_length, 10);*/
					*((long long int *) (var + offset*act_tuple)) = strtoll(pval, &scan_length, 10);
					if ((isarray && *scan_length != ',' && *scan_length != '}')
						|| (!isarray && *scan_length != '\0'))	/* Garbage left */
					{
						ECPGraise(lineno, ECPG_INT_FORMAT, pval);
						return (false);
					}
				}
				else
/*					((long long int *) var)[act_tuple] = (long long) 0;*/
					*((long long int *) (var + offset*act_tuple)) = (long long) 0;

				break;
#endif   /* HAVE_STRTOLL */
#ifdef HAVE_STRTOULL
			case ECPGt_unsigned_long_long:
				if (pval)
				{
/*					((unsigned long long int *) var)[act_tuple] = strtoull(pval, &scan_length, 10);*/
					*((unsigned long long int *) (var + offset*act_tuple)) =  strtoull(pval, &scan_length, 10);
					if ((isarray && *scan_length != ',' && *scan_length != '}')
						|| (!isarray && *scan_length != '\0'))	/* Garbage left */
					{
						ECPGraise(lineno, ECPG_UINT_FORMAT, pval);
						return (false);
					}
				}
				else
/*					((unsigned long long int *) var)[act_tuple] = (long long) 0;*/
					*((unsigned long long int *) (var + offset*act_tuple)) = (long long) 0;

				break;
#endif   /* HAVE_STRTOULL */
#endif   /* HAVE_LONG_LONG_INT_64 */

			case ECPGt_float:
			case ECPGt_double:
				if (pval)
				{
					if (isarray && *pval == '"')
						dres = strtod(pval + 1, &scan_length);
					else
						dres = strtod(pval, &scan_length);

					if (isarray && *scan_length == '"')
						scan_length++;

					if ((isarray && *scan_length != ',' && *scan_length != '}')
						|| (!isarray && *scan_length != '\0'))	/* Garbage left */
					{
						ECPGraise(lineno, ECPG_FLOAT_FORMAT, pval);
						return (false);
					}
				}
				else
					dres = 0.0;

				switch (type)
				{
					case ECPGt_float:
/*						((float *) var)[act_tuple] = dres;*/
						*((float *) (var + offset*act_tuple)) =  dres;
						break;
					case ECPGt_double:
/*						((double *) var)[act_tuple] = dres;*/
						*((double *) (var + offset*act_tuple)) =  dres;
						break;
					default:
						/* Cannot happen */
						break;
				}
				break;

			case ECPGt_bool:
				if (pval)
				{
					if (pval[0] == 'f' && pval[1] == '\0')
					{
						if (offset == sizeof(char))
/*							((char *) var)[act_tuple] = false;*/
							*((char *) (var + offset*act_tuple)) =  false;
						else if (offset == sizeof(int))
/*							((int *) var)[act_tuple] = false;*/
							*((int *) (var + offset*act_tuple)) =  false;
						else
							ECPGraise(lineno, ECPG_CONVERT_BOOL, "different size");
						break;
					}
					else if (pval[0] == 't' && pval[1] == '\0')
					{
						if (offset == sizeof(char))
/*							((char *) var)[act_tuple] = true;*/
							*((char *) (var + offset*act_tuple)) =  true;
						else if (offset == sizeof(int))
/*							((int *) var)[act_tuple] = true;*/
							*((int *) (var + offset*act_tuple)) =  true;
						else
							ECPGraise(lineno, ECPG_CONVERT_BOOL, "different size");
						break;
					}
					else if (pval[0] == '\0' && PQgetisnull(results, act_tuple, act_field))
					{
						/* NULL is valid */
						break;
					}
				}

				ECPGraise(lineno, ECPG_CONVERT_BOOL, pval);
				return (false);
				break;

			case ECPGt_char:
			case ECPGt_unsigned_char:
				{
					strncpy((char *) ((long) var + offset * act_tuple), pval, varcharsize);
					if (varcharsize && varcharsize < strlen(pval))
					{
						/* truncation */
						switch (ind_type)
						{
							case ECPGt_short:
							case ECPGt_unsigned_short:
/*								((short *) ind)[act_tuple] = strlen(pval);*/
								*((short *) (ind + ind_offset*act_tuple)) = strlen(pval);
								break;
							case ECPGt_int:
							case ECPGt_unsigned_int:
/*								((int *) ind)[act_tuple] = strlen(pval);*/
								*((int *) (ind + ind_offset*act_tuple)) = strlen(pval);
								break;
							case ECPGt_long:
							case ECPGt_unsigned_long:
/*								((long *) ind)[act_tuple] = strlen(pval);*/
								*((long *) (ind + ind_offset*act_tuple)) = strlen(pval);
								break;
#ifdef HAVE_LONG_LONG_INT_64
							case ECPGt_long_long:
							case ECPGt_unsigned_long_long:
								*((long long int *) (ind + ind_offset*act_tuple)) = strlen(pval);
								break;
#endif   /* HAVE_LONG_LONG_INT_64 */
							default:
								break;
						}
						sqlca.sqlwarn[0] = sqlca.sqlwarn[1] = 'W';
					}
				}
				break;

			case ECPGt_varchar:
				{
					struct ECPGgeneric_varchar *variable =
					(struct ECPGgeneric_varchar *) ((long) var + offset * act_tuple);

					variable->len = strlen(pval);
					if (varcharsize == 0)
						strncpy(variable->arr, pval, variable->len);
					else
						strncpy(variable->arr, pval, varcharsize);

					if (varcharsize > 0 && variable->len > varcharsize)
					{
						/* truncation */
						switch (ind_type)
						{
							case ECPGt_short:
							case ECPGt_unsigned_short:
/*								((short *) ind)[act_tuple] = variable->len;*/
								*((short *) (ind + offset*act_tuple)) = variable->len;
								break;
							case ECPGt_int:
							case ECPGt_unsigned_int:
/*								((int *) ind)[act_tuple] = variable->len;*/
								*((int *) (ind + offset*act_tuple)) = variable->len;
								break;
							case ECPGt_long:
							case ECPGt_unsigned_long:
/*								((long *) ind)[act_tuple] = variable->len;*/
								*((long *) (ind + offset*act_tuple)) = variable->len;
								break;
#ifdef HAVE_LONG_LONG_INT_64
							case ECPGt_long_long:
							case ECPGt_unsigned_long_long:
								*((long long int *) (ind + ind_offset*act_tuple)) = variable->len;
								break;
#endif   /* HAVE_LONG_LONG_INT_64 */
							default:
								break;
						}
						sqlca.sqlwarn[0] = sqlca.sqlwarn[1] = 'W';

						variable->len = varcharsize;
					}
				}
				break;

			default:
				ECPGraise(lineno, ECPG_UNSUPPORTED, ECPGtype_name(type));
				return (false);
				break;
		}
		if (isarray)
		{
			bool		string = false;

			/* set array to next entry */
			++act_tuple;

			/* set pval to the next entry */
			for (; string || (*pval != ',' && *pval != '}'); ++pval)
				if (*pval == '"')
					string = string ? false : true;

			if (*pval == ',')
				++pval;
		}
	} while (isarray && *pval != '}');

	return (true);
}
