#!/bin/sh
#-------------------------------------------------------------------------
#
# initlocation.sh--
#     Create a secondary PostgreSQL database storage area.  
# 
# Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
# Portions Copyright (c) 1994, Regents of the University of California
#
#
# IDENTIFICATION
#    $Header: /cvsroot/pgsql-server/src/bin/initlocation/initlocation.sh,v 1.12 2001/09/30 22:17:50 momjian Exp $
#
#-------------------------------------------------------------------------

exit_nicely(){
    echo "$CMDNAME failed."
    rm -rf "$PGALTDATA"
    exit 1
}


CMDNAME=`basename $0`
EffectiveUser=`id -n -u 2>/dev/null || whoami 2>/dev/null`

if [ "$USER" = 'root' -o "$LOGNAME" = 'root' ]
then
    echo "You cannot run $CMDNAME as root. Please log in (using, e.g., 'su')"
    echo "as the (unprivileged) user that will own the server process."
    exit 1
fi

Location=

while [ "$#" -gt 0 ]
do
    case "$1" in
        # These options are not really necessary, but what the heck.
	--location=*)
            Location=`echo $1 | sed 's/^--pgdata=//'`
            ;;
	--location)
            Location="$2"
            shift;;
	-D)
            Location="$2"
            shift;;

	--help|-\?)
            usage=t
            break;;

	-*)
            echo "$CMDNAME: invalid option: $1" 1>&2
            echo "Try '$CMDNAME --help' for more information." 1>&2
            exit 1
            ;;
	*)
            Location="$1"
            ;;
	esac
	shift
done


if [ "$usage" ]; then
        echo "$CMDNAME initializes an alternative filesystem location for database creation."
	echo ""
	echo "Usage:"
        echo "  $CMDNAME LOCATION"
	echo
	echo "Please read the description of the CREATE DATABASE command for details."
	echo
        echo "Report bugs to <pgsql-bugs@postgresql.org>."
	exit 0
fi


if [ -z "$Location" ]; then
	echo "$CMDNAME: missing required argument LOCATION" 1>&2
        echo "Try '$CMDNAME -?' for help." 1>&2
	exit 1
fi


#
# Here's what's going on:
#
# You can call initlocation ENVAR (no dollar sign), then ENVAR will
# (a) be tested whether it is valid as a path, or
# (b) be resolved as an environment variable.
# The latter has been the traditional behaviour.
#
# You can call initlocation $ENVAR, which will of course be resolved
# by the shell, or initlocation some/path (containing at least one slash).
# Then you just take that path.
# This should appease users who are confused by the above behavour.
#

echo "$Location" | grep '/' >/dev/null 2>&1

if [ "$?" -ne 0 -a ! -d "$Location" ]; then
    PGALTDATA=`printenv $Location 2> /dev/null`
    if [ -z "$PGALTDATA" ]; then
        echo "$CMDNAME: environment variable $Location not set" 1>&2
        exit 1
    fi
    haveenv=t
else
    PGALTDATA="$Location"
    haveenv=f
fi

echo "The location will be initialized with username \"$EffectiveUser\"."
echo "This user will own all the files and must also own the server process."
echo

# -----------------------------------------------------------------------
# Create the data directory if necessary
# -----------------------------------------------------------------------

# don't want to leave anything lying around
trap 'echo "Caught signal." ; exit_nicely' 1 2 3 15

# umask must disallow access to group, other for files and dirs
umask 077

if [ ! -d "$PGALTDATA" ]; then
	echo "Creating directory $PGALTDATA"
	mkdir "$PGALTDATA"
	if [ "$?" -ne 0 ]; then
            echo "$CMDNAME: could not create $PGALTDATA" 1>&2
            echo "Make sure $PGALTDATA is a valid path and that you have permission to access it." 1>&2
            exit_nicely
        fi
else
        echo "Fixing permissions on pre-existing directory $PGALTDATA"
	chmod go-rwx "$PGALTDATA" || exit_nicely
fi


if [ ! -d "$PGALTDATA"/base ]; then
	echo "Creating directory $PGALTDATA/base"
	mkdir "$PGALTDATA/base"
	if [ "$?" -ne 0 ]; then
            echo "$CMDNAME: could not create $PGALTDATA/base" 1>&2
            echo "Make sure $PGALTDATA/base is a valid path and that you have permission to access it." 1>&2
            exit_nicely
        fi
else
        echo "Fixing permissions on pre-existing directory $PGALTDATA/base"
	chmod go-rwx "$PGALTDATA/base" || exit_nicely
fi

echo
echo "$CMDNAME is complete."
# We can only suggest them these commands if they used the environment
# variable notation. Otherwise they would be induced to use an absolute
# path, which the backend won't allow by default.
if [ "$haveenv" = "t" ]; then
    echo "You can now create a database using"
    echo "  CREATE DATABASE <name> WITH LOCATION = '$Location'"
    echo "in SQL, or"
    echo "  createdb <name> -D '$Location'"
    echo "from the shell."
fi
echo

exit 0
