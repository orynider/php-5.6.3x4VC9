#! /bin/sh
#-------------------------------------------------------------------------
#
# pg_ctl.sh--
#    Start/Stop/Restart/HUP/Report status of postmaster
#
# Copyright (c) 2001  PostgreSQL Global Development Group
#
#
# IDENTIFICATION
#    $Header: /cvsroot/pgsql-server/src/bin/pg_ctl/pg_ctl.sh,v 1.25 2001/09/29 03:09:32 momjian Exp $
#
#-------------------------------------------------------------------------

CMDNAME=`basename $0`

help="\
$CMDNAME is a utility to start, stop, restart, reload configuration files,
or report the status of a PostgreSQL server.

Usage:
  $CMDNAME start   [-w] [-D DATADIR] [-s] [-l FILENAME] [-o \"OPTIONS\"]
  $CMDNAME stop    [-W] [-D DATADIR] [-s] [-m SHUTDOWN-MODE]
  $CMDNAME restart [-w] [-D DATADIR] [-s] [-m SHUTDOWN-MODE] [-o \"OPTIONS\"]
  $CMDNAME reload  [-D DATADIR] [-s]
  $CMDNAME status  [-D DATADIR]

Common options:
  -D DATADIR            Location of the database storage area
  -s                    Only print errors, no informational messages
  -w                    Wait until operation completes
  -W                    Do not wait until operation completes
(The default is to wait for shutdown, but not for start or restart.)

If the -D option is omitted, the environment variable PGDATA is used.

Options for start or restart:
  -l FILENAME           Write (or append) server log to FILENAME.  The
                        use of this option is highly recommended.
  -o OPTIONS            Command line options to pass to the postmaster
                        (PostgreSQL server executable)
  -p PATH-TO-POSTMASTER Normally not necessary

Options for stop or restart:
  -m SHUTDOWN-MODE      May be 'smart', 'fast', or 'immediate'

Shutdown modes are:
  smart                 Quit after all clients have disconnected
  fast                  Quit directly, with proper shutdown
  immediate             Quit without complete shutdown; will lead
                        to recovery run on restart

Report bugs to <pgsql-bugs@postgresql.org>."

advice="\
Try '$CMDNAME --help' for more information."


# Placed here during build
bindir='@bindir@'
VERSION='@VERSION@'

# protect the log file
umask 077

# Check for echo -n vs echo \c

if echo '\c' | grep -s c >/dev/null 2>&1
then
    ECHO_N="echo -n"
    ECHO_C=""
else
    ECHO_N="echo"
    ECHO_C='\c'
fi

#
# Find out where we're located
#
if echo "$0" | grep '/' > /dev/null 2>&1 
then
        # explicit dir name given
        self_path=`echo "$0" | sed 's,/[^/]*$,,'`       # (dirname command is not portable)
else
        # look for it in PATH ('which' command is not portable)
        for dir in `echo "$PATH" | sed 's/:/ /g'`
	do
                # empty entry in path means current dir
                [ -z "$dir" ] && dir='.'
                if [ -f "$dir/$CMDNAME" ]
		then
                        self_path="$dir"
                        break
                fi
        done
fi

# Check if needed programs actually exist in path
if [ -x "$self_path/postmaster" ] && [ -x "$self_path/psql" ]; then
    PGPATH="$self_path"
elif [ -x "$bindir/postmaster" ] && [ -x "$bindir/psql" ]; then
    PGPATH="$bindir"
else
    echo "The programs 'postmaster' and 'psql' are needed by $CMDNAME but" 1>&2
    echo "were not found in the directory '$bindir'." 1>&2
    echo "Check your installation." 1>&2
    exit 1
fi

po_path="$PGPATH/postmaster"

wait=
wait_seconds=60
logfile=
silence_echo=
shutdown_mode=smart

while [ "$#" -gt 0 ]
do
    case "$1" in
	-h|--help|-\?)
	    echo "$help"
	    exit 0
	    ;;
        -V|--version)
	    echo "pg_ctl (PostgreSQL) $VERSION"
	    exit 0
	    ;;
	-D)
	    shift
	    # pass environment into new postmaster
	    PGDATA="$1"
	    export PGDATA
	    ;;
	-l)
	    logfile="$2"
	    shift;;
	-l*)
	    logfile=`echo "$1" | sed 's/^-l//'`
	    ;;
	-m)
	    shutdown_mode="$2"
	    shift;;
	-m*)
	    shutdown_mode=`echo "$1" | sed 's/^-m//'`
	    ;;
	-o)
	    shift
	    POSTOPTS="$1"
	    ;;
	-p)
	    shift
	    po_path="$1"
	    ;;
	-s)
	    silence_echo=:
	    ;;
	-w)
	    wait=yes
	    ;;
	-W)
	    wait=no
	    ;;
	-*)
	    echo "$CMDNAME: invalid option: $1" 1>&2
	    echo "$advice" 1>&2
	    exit 1
	    ;;
	start)
	    op="start"
	    ;;
	stop)
	    op="stop"
	    ;;
	restart)
	    op="restart"
	    ;;
	reload)
	    op="reload"
	    ;;
	status)
	    op="status"
	    ;;
	*)
	    echo "$CMDNAME: invalid operation mode: $1" 1>&2
	    echo "$advice" 1>&2
	    exit 1
	    ;;
    esac
    shift
done

if [ x"$op" = x"" ];then
    echo "$CMDNAME: no operation mode specified" 1>&2
    echo "$advice" 1>&2
    exit 1
fi

if [ -z "$PGDATA" ];then
    echo "$CMDNAME: no database directory or environment variable \$PGDATA is specified" 1>&2
    echo "$advice" 1>&2
    exit 1
fi

if [ -z "$wait" ]; then
    case "$op" in
	start)      wait=no;;
	stop)       wait=yes;;
	restart)    wait=no;;   # must wait on shutdown anyhow
    esac
fi


case "$shutdown_mode" in
    s|smart)
	sig="-TERM"
	;;
    f|fast)
	sig="-INT"
	;;
    i|immediate)
	sig="-QUIT"
	;;
    *)
	echo "$CMDNAME: invalid shutdown mode: $1" 1>&2
	echo "$advice" 1>&2
	exit 1
	;;
esac

if [ "$op" = "reload" ];then
	sig="-HUP"
	wait=no
fi

DEFPOSTOPTS=$PGDATA/postmaster.opts.default
POSTOPTSFILE=$PGDATA/postmaster.opts
PIDFILE=$PGDATA/postmaster.pid

if [ "$op" = "status" ];then
    if [ -f "$PIDFILE" ];then
	PID=`sed -n 1p $PIDFILE`
	if [ "$PID" -lt 0 ];then
	    PID=`expr 0 - $PID`
	    echo "$CMDNAME: postgres is running (pid: $PID)"
	else
	    echo "$CMDNAME: postmaster is running (pid: $PID)"
	    echo "Command line was:"
	    cat "$POSTOPTSFILE"
	fi
	exit 0
    else
	echo "$CMDNAME: postmaster or postgres is not running"
	exit 1
    fi
fi

if [ "$op" = "stop" -o "$op" = "restart" -o "$op" = "reload" ];then
    if [ -f "$PIDFILE" ];then
	PID=`sed -n 1p $PIDFILE`
	if [ "$PID" -lt 0 ];then
	    PID=`expr 0 - $PID`
	    echo "$CMDNAME: Cannot restart postmaster.  postgres is running (pid: $PID)" 1>&2
	    echo "Please terminate postgres and try again." 1>&2
	    exit 1
	fi

	kill "$sig" $PID

	# wait for postmaster to shut down
	if [ "$wait" = yes -o "$op" = restart ];then
	    cnt=0
	    $silence_echo $ECHO_N "waiting for postmaster to shut down..."$ECHO_C

	    while :
	    do
		if [ -f "$PIDFILE" ];then
		    $silence_echo $ECHO_N "."$ECHO_C
		    cnt=`expr $cnt + 1`
		    if [ "$cnt" -gt "$wait_seconds" ];then
			$silence_echo echo " failed"
			echo "$CMDNAME: postmaster does not shut down" 1>&2
			exit 1
		    fi
		else
		    break
		fi
		sleep 1
	    done
	    $silence_echo echo "done"
	fi

	if [ "$op" = "reload" ];then
	    $silence_echo echo "postmaster successfully signaled"
	else
	    $silence_echo echo "postmaster successfully shut down"
	fi

    else # ! -f $PIDFILE
	echo "$CMDNAME: cannot find $PIDFILE" 1>&2
	echo "Is postmaster running?" 1>&2
	if [ "$op" = "restart" ];then
	    echo "starting postmaster anyway" 1>&2
	else
	    exit 1
	fi
    fi
fi # stop, restart, reload

if [ "$op" = "start" -o "$op" = "restart" ];then
    oldpid=""
    if [ -f "$PIDFILE" ];then
	echo "$CMDNAME: Another postmaster may be running.  Trying to start postmaster anyway." 1>&2
	oldpid=`sed -n 1p $PIDFILE`
    fi

    # no -o given
    if [ -z "$POSTOPTS" ];then
	if [ "$op" = "start" ];then
	    # if we are in start mode, then look for postmaster.opts.default
	    if [ -f "$DEFPOSTOPTS" ]; then
		eval set X "`cat $DEFPOSTOPTS`"; shift
	    fi
	else
	    # if we are in restart mode, then look for postmaster.opts
	    eval set X "`cat $POSTOPTSFILE`"; shift
            po_path="$1"
            shift
	fi
    else # -o given
        eval set X "$POSTOPTS"; shift
    fi

    if [ -n "$logfile" ]; then
        "$po_path" "$@" </dev/null >>$logfile 2>&1 &
    else
        # when starting without log file, redirect stderr to stdout, so
        # pg_ctl can be invoked with >$logfile and still have pg_ctl's
        # stderr on the terminal.
        "$po_path" "$@" </dev/null 2>&1 &
    fi

    # if had an old lockfile, check to see if we were able to start
    if [ -n "$oldpid" ];then
	sleep 1
	if [ -f "$PIDFILE" ];then
	    if [ "`sed -n 1p $PIDFILE`" = "$oldpid" ];then
		echo "$CMDNAME: cannot start postmaster" 1>&2
		echo "Examine the log output." 1>&2
		exit 1
	    fi
        fi
    fi

    # wait for postmaster to start
    if [ "$wait" = yes ];then
	cnt=0
	$silence_echo $ECHO_N "waiting for postmaster to start..."$ECHO_C
	while :
	do
# FIXME:  This is horribly misconceived.
# 1) If password authentication is set up, the connection will fail.
# 2) If a virtual host is set up, the connection may fail.
# 3) If network traffic filters are set up tight enough, the connection
#    may fail.
# 4) When no Unix domain sockets are available, the connection will
#    fail.  (Using TCP/IP by default ain't better.)
# 5) When a different port is configured, the connection will fail
#    or go to the wrong server.
# 6) If the dynamic loader is not set up correctly (for this user/at
#    this time), psql will fail (to find libpq).
# 7) If psql is misconfigured, this may fail.
	    if "$PGPATH/psql" -l >/dev/null 2>&1
	    then
		break;
	    else
		$silence_echo $ECHO_N "."$ECHO_C
		cnt=`expr $cnt + 1`
		if [ "$cnt" -gt "$wait_seconds" ];then
		    $silence_echo echo "failed"
		    echo "$CMDNAME: postmaster does not start" 1>&2
		    exit 1
		fi
		sleep 1
	    fi
	done
	$silence_echo echo "done"
    fi
    $silence_echo echo "postmaster successfully started"
fi # start or restart

exit 0
