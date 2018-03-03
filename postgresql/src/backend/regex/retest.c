/*
 * a simple regexp debug program
 *
 * $Header: /cvsroot/pgsql-server/src/backend/regex/retest.c,v 1.4 1999/07/17 20:17:34 momjian Exp $
 */

#include "postgres.h"
#include "regex/regex.h"

int
main()
{
	int			sts;
	regex_t		re;
	char		buf[1024];
	char	   *p;

	printf("type in regexp string: ");
	if (!fgets(buf, sizeof(buf), stdin))
		exit(0);
	p = strchr(buf, '\n');
	if (p)
		*p = '\0';

	sts = pg95_regcomp(&re, buf, 1);
	printf("regcomp: parses \"%s\" and returns %d\n", buf, sts);
	for (;;)
	{
		printf("type in target string: ");
		if (!fgets(buf, sizeof(buf), stdin))
			exit(0);
		p = strchr(buf, '\n');
		if (p)
			*p = '\0';

		sts = pg95_regexec(&re, buf, 0, 0, 0);
		printf("regexec: returns %d\n", sts);
	}
}

void
elog(int lev, const char *fmt,...)
{
}
