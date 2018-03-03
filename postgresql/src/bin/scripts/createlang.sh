#! /bin/sh
#-------------------------------------------------------------------------
#
# createlang --
#   Install a procedural language in a database
#
# Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
# Portions Copyright (c) 1994, Regents of the University of California
#
# $Header: /cvsroot/pgsql-server/src/bin/scripts/createlang.sh,v 1.32 2002/01/03 05:30:04 momjian Exp $
#
#-------------------------------------------------------------------------

CMDNAME=`basename "$0"`
PATHNAME=`echo $0 | sed "s,$CMDNAME\$,,"`

PSQLOPT=
dbname=
langname=
list=
showsql=
PGLIB=

# Check for echo -n vs echo \c

if echo '\c' | grep -s c >/dev/null 2>&1
then
    ECHO_N="echo -n"
    ECHO_C=""
else
    ECHO_N="echo"
    ECHO_C='\c'
fi



# ----------
# Get options, language name and dbname
# ----------
while [ "$#" -gt 0 ]
do
    case "$1" in 
	--help|-\?)
		usage=t
                break
		;;
        --list|-l)
                list=t
                ;;
# options passed on to psql
	--host|-h)
		PSQLOPT="$PSQLOPT -h $2"
		shift;;
        -h*)
                PSQLOPT="$PSQLOPT $1"
                ;;
        --host=*)
                PSQLOPT="$PSQLOPT -h "`echo $1 | sed 's/^--host=//'`
                ;;
	--port|-p)
		PSQLOPT="$PSQLOPT -p $2"
		shift;;
        -p*)
                PSQLOPT="$PSQLOPT $1"
                ;;
        --port=*)
                PSQLOPT="$PSQLOPT -p "`echo $1 | sed 's/^--port=//'`
                ;;
	--username|-U)
		PSQLOPT="$PSQLOPT -U $2"
		shift;;
        -U*)
                PSQLOPT="$PSQLOPT $1"
                ;;
        --username=*)
                PSQLOPT="$PSQLOPT -U "`echo $1 | sed 's/^--username=//'`
                ;;
	--password|-W)
		PSQLOPT="$PSQLOPT -W"
		;;
	--dbname|-d)
		dbname="$2"
		shift;;
        -d*)
                dbname=`echo "$1" | sed 's/^-d//'`
                ;;
        --dbname=*)
                dbname=`echo "$1" | sed 's/^--dbname=//'`
                ;;
# misc options
	--pglib|-L)
                PGLIB="$2"
                shift;;
        -L*)
                PGLIB=`echo "$1" | sed 's/^-L//'`
                ;;
        --pglib=*)
                PGLIB=`echo "$1" | sed 's/^--pglib=//'`
                ;;
	--echo|-e)
		showsql=yes
		;;

	-*)
		echo "$CMDNAME: invalid option: $1" 1>&2
                echo "Try '$CMDNAME --help' for more information." 1>&2
		exit 1
		;;
	 *)
 		if [ "$list" != "t" ]
		then	langname="$1"
			if [ "$2" ]
			then
				shift
				dbname="$1"
			fi
		else	dbname="$1"
		fi
                ;;
    esac
    shift
done

if [ -n "$usage" ]; then	
        echo "$CMDNAME installs a procedural language into a PostgreSQL database."
	echo
	echo "Usage:"
        echo "  $CMDNAME [options] langname [dbname]"
        echo
	echo "Options:"
	echo "  -h, --host=HOSTNAME             Database server host"
	echo "  -p, --port=PORT                 Database server port"
	echo "  -U, --username=USERNAME         Username to connect as"
	echo "  -W, --password                  Prompt for password"
	echo "  -d, --dbname=DBNAME             Database to install language in"
	echo "  -L, --pglib=DIRECTORY           Find language interpreter file in DIRECTORY"
	echo "  -l, --list                      Show a list of currently installed languages"
        echo
	echo "Report bugs to <pgsql-bugs@postgresql.org>."
	exit 0
fi


if [ -z "$dbname" ]; then
        if [ "$PGUSER" ]; then
                dbname="$PGUSER"
        else
                dbname=`${PATHNAME}pg_id -u -n`
        fi
        [ "$?" -ne 0 ] && exit 1
fi


# ----------
# List option, doesn't need langname
# ----------
if [ "$list" ]; then
	sqlcmd="SELECT lanname as \"Name\", lanpltrusted as \"Trusted?\" FROM pg_language WHERE lanispl = TRUE;"
	if [ "$showsql" = yes ]; then
		echo "$sqlcmd"
	fi
        ${PATHNAME}psql $PSQLOPT -d "$dbname" -P 'title=Procedural languages' -c "$sqlcmd"
        exit $?
fi


# ----------
# We can't go any farther without a langname
# ----------
if [ -z "$langname" ]; then
	echo "$CMDNAME: missing required argument language name" 1>&2
        echo "Try '$CMDNAME --help' for help." 1>&2
	exit 1
fi

# ----------
# Check that we have PGLIB
# ----------
if [ -z "$PGLIB" ]; then
	PGLIB='$libdir'
fi

# ----------
# Check if supported and set related values
# ----------

langname=`echo "$langname" | tr 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' 'abcdefghijklmnopqrstuvwxyz'`

case "$langname" in
	plpgsql)
		trusted="TRUSTED "
		handler="plpgsql_call_handler"
		object="plpgsql"
		;;
	pltcl)
		trusted="TRUSTED "
		handler="pltcl_call_handler"
		object="pltcl"
		;;
	pltclu)
		trusted=""
		handler="pltclu_call_handler"
		object="pltcl"
		;;
	plperl)
		trusted="TRUSTED "
		handler="plperl_call_handler"
		object="plperl"
		;;
	plperlu)
		trusted=""
		handler="plperl_call_handler"
		object="plperl"
		;;
	plpython)
		trusted="TRUSTED "
		handler="plpython_call_handler"
		object="plpython"
		;;
	*)
		echo "$CMDNAME: unsupported language \"$langname\"" 1>&2
		echo "Supported languages are plpgsql, pltcl, pltclu, plperl, plperlu, and plpython." 1>&2
		exit 1
        ;;
esac


PSQL="${PATHNAME}psql -A -t -q $PSQLOPT -d $dbname -c"

# ----------
# Make sure the language isn't already installed
# ----------
sqlcmd="SELECT oid FROM pg_language WHERE lanname = '$langname';"
if [ "$showsql" = yes ]; then
	echo "$sqlcmd"
fi
res=`$PSQL "$sqlcmd"`
if [ "$?" -ne 0 ]; then
	echo "$CMDNAME: external error" 1>&2
	exit 1
fi
if [ -n "$res" ]; then
	echo "$CMDNAME: language \"$langname\" is already installed in database $dbname" 1>&2
	# separate exit status for "already installed"
	exit 2
fi

# ----------
# Check whether the call handler exists
# ----------
sqlcmd="SELECT oid FROM pg_proc WHERE proname = '$handler' AND prorettype = 0 AND pronargs = 0;"
if [ "$showsql" = yes ]; then
	echo "$sqlcmd"
fi
res=`$PSQL "$sqlcmd"`
if [ -n "$res" ]; then
	handlerexists=yes
else
	handlerexists=no
fi

# ----------
# Create the call handler and the language
# ----------
if [ "$handlerexists" = no ]; then
	sqlcmd="CREATE FUNCTION \"$handler\" () RETURNS OPAQUE AS '$PGLIB/${object}' LANGUAGE C;"
	if [ "$showsql" = yes ]; then
		echo "$sqlcmd"
	fi
	$PSQL "$sqlcmd"
	if [ "$?" -ne 0 ]; then
		echo "$CMDNAME: language installation failed" 1>&2
		exit 1
	fi
fi

sqlcmd="CREATE ${trusted}LANGUAGE \"$langname\" HANDLER \"$handler\";"
if [ "$showsql" = yes ]; then
	echo "$sqlcmd"
fi
$PSQL "$sqlcmd"
if [ "$?" -ne 0 ]; then
	echo "$CMDNAME: language installation failed" 1>&2
	exit 1
fi

exit 0
