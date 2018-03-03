/*
 * Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $Id: password.c,v 1.40 2001/10/25 05:49:30 momjian Exp $
 *
 */

#include <errno.h>
#include <unistd.h>

#include "postgres.h"

#ifdef HAVE_CRYPT_H
#include <crypt.h>
#endif

#include "libpq/libpq.h"
#include "libpq/password.h"
#include "libpq/crypt.h"
#include "miscadmin.h"
#include "storage/fd.h"


int
verify_password(const Port *port, const char *user, const char *password)
{
	char	   *pw_file_fullname;
	FILE	   *pw_file;

	pw_file_fullname = (char *) palloc(strlen(DataDir) + strlen(port->auth_arg) + 2);
	strcpy(pw_file_fullname, DataDir);
	strcat(pw_file_fullname, "/");
	strcat(pw_file_fullname, port->auth_arg);

	pw_file = AllocateFile(pw_file_fullname, PG_BINARY_R);
	if (!pw_file)
	{
		snprintf(PQerrormsg, PQERRORMSG_LENGTH,
			"verify_password: Unable to open password file \"%s\": %s\n",
				 pw_file_fullname, strerror(errno));
		fputs(PQerrormsg, stderr);
		pqdebug("%s", PQerrormsg);

		pfree(pw_file_fullname);

		return STATUS_ERROR;
	}

	pfree(pw_file_fullname);

	while (!feof(pw_file))
	{
		char		pw_file_line[255],
				   *p,
				   *test_user,
				   *test_pw;

		if (fgets(pw_file_line, sizeof(pw_file_line), pw_file) == NULL)
			pw_file_line[0] = '\0';
		/* kill the newline */
		if (strlen(pw_file_line) > 0 &&
			pw_file_line[strlen(pw_file_line) - 1] == '\n')
			pw_file_line[strlen(pw_file_line) - 1] = '\0';

		p = pw_file_line;

		test_user = strtok(p, ":");
		if (!test_user || test_user[0] == '\0')
			continue;
		test_pw = strtok(NULL, ":");

		if (strcmp(user, test_user) == 0)
		{
			/* we're outta here one way or the other, so close file */
			FreeFile(pw_file);

			/*
			 * If the password is empty or "+" then we use the regular
			 * pg_shadow passwords. If we use crypt then we have to use
			 * pg_shadow passwords no matter what.	This is because the
			 * current code needs non-encrypted passwords to encrypt with
			 * a random salt.
			 */
			if (port->auth_method == uaMD5 ||
				port->auth_method == uaCrypt ||
				test_pw == NULL ||
				test_pw[0] == '\0' ||
				strcmp(test_pw, "+") == 0)
				return md5_crypt_verify(port, user, password);

			/* external password file is crypt-only */
			if (strcmp(crypt(password, test_pw), test_pw) == 0)
			{
				/* it matched. */
				return STATUS_OK;
			}

			snprintf(PQerrormsg, PQERRORMSG_LENGTH,
					 "verify_password: password mismatch for '%s'.\n",
					 user);
			fputs(PQerrormsg, stderr);
			pqdebug("%s", PQerrormsg);

			return STATUS_ERROR;
		}
	}

	FreeFile(pw_file);

	snprintf(PQerrormsg, PQERRORMSG_LENGTH,
			 "verify_password: user '%s' not found in password file.\n",
			 user);
	fputs(PQerrormsg, stderr);
	pqdebug("%s", PQerrormsg);

	return STATUS_ERROR;
}
