#ifndef NOSETPROCTITLE
/*
 * Copyright (c) 1990,1991 Regents of the University of Michigan.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of Michigan at Ann Arbor. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 */

char	**Argv;		/* pointer to original (main's) argv */
int	Argc;		/* original argc */

/*
 * takes a printf-style format string (fmt) and up to three parameters (a,b,c)
 * this clobbers the original argv...
 */

/* VARARGS */
setproctitle( fmt, a, b, c )
char *fmt;
{
	static char *endargv = (char *)0;
	char	*s;
	int		i;
	char	buf[ 1024 ];

	if ( endargv == (char *)0 ) {
		/* set pointer to end of original argv */
		endargv = Argv[ Argc-1 ] + strlen( Argv[ Argc-1 ] );
	}
	sprintf( buf, fmt, a, b, c );
	/* make ps print "([prog name])" */
	s = Argv[0];
	*s++ = '-';
	i = strlen( buf );
	if ( i > endargv - s - 2 ) {
		i = endargv - s - 2;
		buf[ i ] = '\0';
	}
	strcpy( s, buf );
	s += i;
	while ( s < endargv ) *s++ = ' ';
}
#endif /* NOSETPROCTITLE */
