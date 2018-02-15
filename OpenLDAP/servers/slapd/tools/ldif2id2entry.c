//#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../slap.h"
#include "../back-ldbm/back-ldbm.h"

#define DEFAULT_CONFIGFILE	"/usr/local/etc/slapd.conf"
#define MAXARGS      		100

extern struct dbcache	*ldbm_cache_open();
extern void		attr_index_config();
extern int		strcasecmp();
extern int		nbackends;
extern Backend		*backends;
extern int		ldap_debug;

int		ldap_debug;
int		ldap_syslog;
int		ldap_syslog_level;
int		global_schemacheck;
int		num_entries_sent;
int		num_bytes_sent;
int		active_threads;
char		*default_referral;
struct objclass	*global_oc;
time_t		currenttime;
pthread_t	listener_tid;
pthread_mutex_t	num_sent_mutex;
pthread_mutex_t	entry2str_mutex;
pthread_mutex_t	active_threads_mutex;
pthread_mutex_t	new_conn_mutex;
pthread_mutex_t	currenttime_mutex;
pthread_mutex_t	replog_mutex;
pthread_mutex_t	ops_mutex;
pthread_mutex_t	regex_mutex;

static int	make_index();

static char	*tailorfile;
static char	*inputfile;
 
static void
usage( char *name )
{
	fprintf( stderr, "usage: %s -i inputfile [-d debuglevel] [-f configfile] [-n databasenumber]\n", name );
	exit( 1 );
}

main( int argc, char **argv )
{
	int		i, cargc, indb, stop, status;
	char		*cargv[MAXARGS];
	char		*defargv[MAXARGS];
	char		*linep, *buf;
	char		line[BUFSIZ], idbuf[BUFSIZ];
	int      	lmax, lcur;
	int		dbnum;
	ID		id;
	struct dbcache	*db;
	Backend		*be;
	struct berval	bv;
	struct berval	*vals[2];
	Avlnode		*avltypes = NULL;
	FILE		*fp;
	extern char	*optarg;

	tailorfile = DEFAULT_CONFIGFILE;
	dbnum = -1;
	while ( (i = getopt( argc, argv, "d:f:i:n:" )) != EOF ) {
		switch ( i ) {
		case 'd':	/* turn on debugging */
			ldap_debug = atoi( optarg );
			break;

		case 'f':	/* specify a tailor file */
			tailorfile = strdup( optarg );
			break;

		case 'i':	/* input file */
			inputfile = strdup( optarg );
			break;

		case 'n':	/* which config file db to index */
			dbnum = atoi( optarg ) - 1;
			break;

		default:
			usage( argv[0] );
			break;
		}
	}
	if ( inputfile == NULL ) {
		usage( argv[0] );
	} else {
		if ( freopen( inputfile, "r", stdin ) == NULL ) {
			perror( inputfile );
			exit( 1 );
		}
	}

	/*
	 * initialize stuff and figure out which backend we're dealing with
	 */

	init();
	read_config( tailorfile, &be, NULL );

	if ( dbnum == -1 ) {
		for ( dbnum = 0; dbnum < nbackends; dbnum++ ) {
			if ( strcasecmp( backends[dbnum].be_type, "ldbm" )
			    == 0 ) {
				break;
			}
		}
		if ( dbnum == nbackends ) {
			fprintf( stderr, "No ldbm database found in config file\n" );
			exit( 1 );
		}
	} else if ( dbnum < 0 || dbnum > (nbackends-1) ) {
		fprintf( stderr, "Database number selected via -n is out of range\n" );
		fprintf( stderr, "Must be in the range 1 to %d (number of databases in the config file)\n", nbackends );
		exit( 1 );
	} else if ( strcasecmp( backends[dbnum].be_type, "ldbm" ) != 0 ) {
		fprintf( stderr, "Database number %d selected via -n is not an ldbm database\n", dbnum );
		exit( 1 );
	}
	be = &backends[dbnum];

	if ( (db = ldbm_cache_open( be, "id2entry", LDBM_SUFFIX, LDBM_NEWDB ))
	    == NULL ) {
		perror( "id2entry file" );
		exit( 1 );
	}

	id = 0;
	stop = 0;
	buf = NULL;
	lcur = lmax = 0;
	vals[0] = &bv;
	vals[1] = NULL;
	while ( ! stop ) {
		char		*type, *val, *s;
		int		vlen;
		Datum		key, data;

		if ( fgets( line, sizeof(line), stdin ) != NULL ) {
			int     len, idlen;

			len = strlen( line );
			if ( buf == NULL || *buf == '\0' ) {
				sprintf( idbuf, "%d\n", id + 1 );
				idlen = strlen( idbuf );
			} else {
				idlen = 0;
			}

			while ( lcur + len + idlen + 1 > lmax ) {
				lmax += BUFSIZ;
				buf = (char *) ch_realloc( buf, lmax );
			}

			if ( idlen > 0 ) {
				strcpy( buf + lcur, idbuf );
				lcur += idlen;
			}
			strcpy( buf + lcur, line );
			lcur += len;
		} else {
			stop = 1;
		}
		if ( line[0] == '\n' || stop && buf && *buf ) {
			if ( *buf != '\n' ) {
				id++;
				key.dptr = (char *) &id;
				key.dsize = sizeof(ID);
				data.dptr = buf;
				data.dsize = strlen( buf ) + 1;
				if ( ldbm_store( db->dbc_db, key, data,
				    LDBM_INSERT ) != 0 ) {
					perror( "id2entry ldbm_store" );
					exit( 1 );
				}
			}
			*buf = '\0';
			lcur = 0;
			line[0] = '\0';
		}
	}
	(*be->be_close)( be );

	id++;
	sprintf( line, "%s/NEXTID",
	    ((struct ldbminfo *) be->be_private)->li_directory );
	if ( (fp = fopen( line, "w" )) == NULL ) {
		perror( line );
		fprintf( stderr, "Could not write next id %ld\n", id );
	} else {
		fprintf( fp, "%ld\n", id );
		fclose( fp );
	}

	exit( 0 );
}
