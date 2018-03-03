#! /bin/sh
# $Header: /cvsroot/pgsql-server/src/test/regress/pg_regress.sh,v 1.23 2002/01/03 21:52:05 tgl Exp $

me=`basename $0`
: ${TMPDIR=/tmp}
TMPFILE=$TMPDIR/pg_regress.$$

help="\
PostgreSQL regression test driver

Usage: $me [options...] [extra tests...]

Options:
  --debug                   turn on debug mode in programs that are run
  --inputdir=DIR            take input files from DIR (default \`.')
  --multibyte=ENCODING      use ENCODING as the multibyte encoding, and
                            also run a test by the same name
  --outputdir=DIR           place output files in DIR (default \`.')
  --schedule=FILE           use test ordering schedule from FILE
                            (may be used multiple times to concatenate)
  --temp-install[=DIR]      create a temporary installation (in DIR)

Options for \`temp-install' mode:
  --top-builddir=DIR        (relative) path to top level build directory

Options for using an existing installation:
  --host=HOST               use postmaster running on HOST
  --port=PORT               use postmaster running at PORT
  --user=USER               connect as USER

The exit status is 0 if all tests passed, 1 if some tests failed, and 2
if the tests could not be run for some reason.

Report bugs to <pgsql-bugs@postgresql.org>."


message(){
    _dashes='==============' # 14
    _spaces='                                      ' # 38
    _msg=`echo "$1$_spaces" | cut -c 1-38`
    echo "$_dashes $_msg $_dashes"
}


# ----------
# Unset locale settings
# ----------

unset LC_COLLATE LC_CTYPE LC_MONETARY LC_MESSAGES LC_NUMERIC LC_TIME LC_ALL LANG LANGUAGE


# ----------
# Check for echo -n vs echo \c
# ----------

if echo '\c' | grep c >/dev/null 2>&1; then
    ECHO_N='echo -n'
    ECHO_C=''
else
    ECHO_N='echo'
    ECHO_C='\c'
fi


# ----------
# Initialize default settings
# ----------

: ${inputdir=.}
: ${outputdir=.}

libdir='@libdir@'
pkglibdir='@pkglibdir@'
bindir='@bindir@'
datadir='@datadir@'
host_platform='@host_tuple@'
enable_shared='@enable_shared@'
GCC=@GCC@

if [ "$GCC" = yes ]; then
    compiler=gcc
else
    compiler=cc
fi

unset mode
unset schedule
unset debug
unset top_builddir
unset temp_install
unset multibyte

dbname=regression
hostname=localhost

: ${GMAKE='@GMAKE@'}


# ----------
# Parse command line options
# ----------

while [ "$#" -gt 0 ]
do
    case $1 in
        --help|-\?)
                echo "$help"
                exit 0;;
        --version)
                echo "pg_regress (PostgreSQL @VERSION@)"
                exit 0;;
        --debug)
                debug=yes
                shift;;
        --inputdir=*)
                inputdir=`expr "x$1" : "x--inputdir=\(.*\)"`
                shift;;
        --multibyte=*)
                multibyte=`expr "x$1" : "x--multibyte=\(.*\)"`
                shift;;
        --temp-install)
                temp_install=./tmp_check
                shift;;
        --temp-install=*)
                temp_install=`expr "x$1" : "x--temp-install=\(.*\)"`
                shift;;
        --outputdir=*)
                outputdir=`expr "x$1" : "x--outputdir=\(.*\)"`
                shift;;
        --schedule=*)
                foo=`expr "x$1" : "x--schedule=\(.*\)"`
                schedule="$schedule $foo"
                shift;;
        --top-builddir=*)
                top_builddir=`expr "x$1" : "x--top-builddir=\(.*\)"`
                shift;;
        --host=*)
                PGHOST=`expr "x$1" : "x--host=\(.*\)"`
                export PGHOST
                shift;;
        --port=*)
                PGPORT=`expr "x$1" : "x--port=\(.*\)"`
                export PGPORT
                shift;;
        --user=*)
                PGUSER=`expr "x$1" : "x--user=\(.*\)"`
                export PGUSER
                shift;;
        -*)
                echo "$me: invalid argument $1" 1>&2
                exit 2;;
        *)
                extra_tests="$extra_tests $1"
                shift;;
    esac
done


# ----------
# When on QNX or BeOS, don't use Unix sockets.
# ----------

case $host_platform in
    *-*-qnx* | *beos*)
        unix_sockets=no;;
    *)
        unix_sockets=yes;;
esac


# ----------
# Set up diff to ignore horizontal white space differences.
# ----------

case $host_platform in
    *-*-qnx*)
        DIFFFLAGS=-b;;
    *)
        DIFFFLAGS=-w;;
esac


# ----------
# Set backend timezone and datestyle explicitly
#
# To pass the horology test in its current form, the postmaster must be
# started with PGDATESTYLE=ISO, while the frontend must be started with
# PGDATESTYLE=Postgres.  We set the postmaster values here and change
# to the frontend settings after the postmaster has been started.
# ----------

PGTZ='PST8PDT'; export PGTZ
PGDATESTYLE='ISO,US'; export PGDATESTYLE


# ----------
# Exit trap to remove temp file and shut down postmaster
# ----------

# Note:  There are some stupid shells (even among recent ones) that
# ignore the argument to exit (as in `exit 1') if there is an exit
# trap.  The trap (and thus the shell script) will then always exit
# with the result of the last shell command before the `exit'.  Hence
# we have to write `(exit x); exit' below this point.

trap '
    savestatus=$?
    if [ -n "$postmaster_pid" ]; then
        kill -2 "$postmaster_pid"
        wait "$postmaster_pid"
        unset postmaster_pid
    fi
    rm -f "$TMPFILE" && exit $savestatus
' 0

trap '
    savestatus=$?
    echo; echo "caught signal"
    if [ -n "$postmaster_pid" ]; then
        echo "signalling fast shutdown to postmaster with pid $postmaster_pid"
        kill -2 "$postmaster_pid"
        wait "$postmaster_pid"
        unset postmaster_pid
    fi
    (exit $savestatus); exit
' 1 2 13 15



# ----------
# Scan resultmap file to find which platform-specific expected files to use.
# The format of each line of the file is
#         testname/hostplatformpattern=substitutefile
# where the hostplatformpattern is evaluated per the rules of expr(1),
# namely, it is a standard regular expression with an implicit ^ at the start.
# What hostplatformpattern will be matched against is the config.guess output
# followed by either ':gcc' or ':cc' (independent of the actual name of the
# compiler executable).
#
# The tempfile hackery is needed because some shells will run the loop
# inside a subshell, whereupon shell variables set therein aren't seen
# outside the loop :-(
# ----------

cat /dev/null >$TMPFILE
if [ -f "$inputdir/resultmap" ]
then
    while read LINE
    do
	HOSTPAT=`expr "$LINE" : '.*/\(.*\)='`
	if [ `expr "$host_platform:$compiler" : "$HOSTPAT"` -ne 0 ]
	then
	    # remove hostnamepattern from line so that there are no shell
	    # wildcards in SUBSTLIST; else later 'for' could expand them!
	    TESTNAME=`expr "$LINE" : '\(.*\)/'`
	    SUBST=`echo "$LINE" | sed 's/^.*=//'`
	    echo "$TESTNAME=$SUBST" >> $TMPFILE
	fi
    done <"$inputdir/resultmap"
fi
SUBSTLIST=`cat $TMPFILE`
rm -f $TMPFILE


LOGDIR=$outputdir/log

if [ x"$temp_install" != x"" ]
then
    if echo x"$temp_install" | grep -v '^x/' >/dev/null 2>&1; then
        temp_install="`pwd`/$temp_install"
    fi

    bindir=$temp_install/install/$bindir
    libdir=$temp_install/install/$libdir
    pkglibdir=$temp_install/install/$pkglibdir
    datadir=$temp_install/install/$datadir
    PGDATA=$temp_install/data

    if [ "$unix_sockets" = no ]; then
        PGHOST=$hostname
        export PGHOST
    else
        unset PGHOST
    fi
    PGPORT=65432
    export PGPORT

    # ----------
    # Set up shared library paths, needed by psql and pg_encoding
    # (if you run multibyte).  LD_LIBRARY_PATH covers many platforms,
    # feel free to account for others as well.
    # ----------

    if [ -n "$LD_LIBRARY_PATH" ]; then
        LD_LIBRARY_PATH="$libdir:$LD_LIBRARY_PATH"
    else
        LD_LIBRARY_PATH=$libdir
    fi
    export LD_LIBRARY_PATH

    # ----------
    # Windows needs shared libraries in PATH. (Only those linked into
    # executables, not dlopen'ed ones)
    # ----------
    case $host_platform in *-*-cygwin*)
        PATH=$libdir:$PATH
        export PATH
        ;;
    esac

    if [ -d "$temp_install" ]; then
        message "removing existing temp installation"
        rm -rf "$temp_install"
    fi

    message "creating temporary installation"
    if [ ! -d "$LOGDIR" ]; then
        mkdir -p "$LOGDIR" || { (exit 2); exit; }
    fi
    $GMAKE -C "$top_builddir" DESTDIR="$temp_install/install" install with_perl=no with_python=no >"$LOGDIR/install.log" 2>&1

    if [ $? -ne 0 ]
    then
        echo
        echo "$me: installation failed"
        echo "Examine $LOGDIR/install.log for the reason."
        echo
        (exit 2); exit
    fi


    message "initializing database system"
    [ "$debug" = yes ] && initdb_options='--debug'
    "$bindir/initdb" -D "$PGDATA" -L "$datadir" --noclean $initdb_options >"$LOGDIR/initdb.log" 2>&1

    if [ $? -ne 0 ]
    then
        echo
        echo "$me: initdb failed"
        echo "Examine $LOGDIR/initdb.log for the reason."
        echo
        (exit 2); exit
    fi


    # ----------
    # Start postmaster
    # ----------

    message "starting postmaster"
    [ "$debug" = yes ] && postmaster_options="$postmaster_options -d 5"
    [ "$unix_sockets" = no ] && postmaster_options="$postmaster_options -i"
    "$bindir/postmaster" -D "$PGDATA" -F $postmaster_options >"$LOGDIR/postmaster.log" 2>&1 &
    postmaster_pid=$!

    # Wait till postmaster is able to accept connections (normally only
    # a second or so, but Cygwin is reportedly *much* slower).  Don't
    # wait forever, however.
    i=0
    max=60
    until "$bindir/psql" $psql_options template1 </dev/null 2>/dev/null
    do
        i=`expr $i + 1`
        if [ $i -ge $max ]
        then
            break
        fi
        if kill -0 $postmaster_pid >/dev/null 2>&1
        then
            : still starting up
        else
            break
        fi
        sleep 1
    done

    if kill -0 $postmaster_pid >/dev/null 2>&1
    then
        echo "running on port $PGPORT with pid $postmaster_pid"
    else
        echo
        echo "$me: postmaster did not start"
        echo "Examine $LOGDIR/postmaster.log for the reason."
        echo
        (exit 2); exit
    fi

else # not temp-install

    # If Unix sockets are not available, use the local host by default.
    if [ "$unix_sockets" = no ]; then
        PGHOST=$hostname
        export PGHOST
    fi

    if [ -n "$PGPORT" ]; then
        port_info="port $PGPORT"
    else
        port_info="default port"
    fi

    if [ -n "$PGHOST" ]; then
        echo "(using postmaster on $PGHOST, $port_info)"
    else
        echo "(using postmaster on Unix socket, $port_info)"
    fi
    message "dropping database \"$dbname\""
    "$bindir/dropdb" $psql_options "$dbname"
    # errors can be ignored
fi


# ----------
# Set up SQL shell for the test.
# ----------

PSQL="$bindir/psql -a -q -X $psql_options"


# ----------
# Set frontend timezone and datestyle explicitly
# ----------

PGTZ='PST8PDT'; export PGTZ
PGDATESTYLE='Postgres,US'; export PGDATESTYLE


# ----------
# Set up multibyte environment
# ----------

if [ -n "$multibyte" ]; then
    PGCLIENTENCODING=$multibyte
    export PGCLIENTENCODING
    encoding_opt="-E $multibyte"
else
    unset PGCLIENTENCODING
fi


# ----------
# Create the regression database
# We use template0 so that any installation-local cruft in template1
# will not mess up the tests.
# ----------

message "creating database \"$dbname\""
"$bindir/createdb" $encoding_opt $psql_options --template template0 "$dbname"
if [ $? -ne 0 ]; then
    echo "$me: createdb failed"
    (exit 2); exit
fi


# ----------
# Remove regressuser* and regressgroup* user accounts.
# ----------

message "dropping regression test user accounts"
"$bindir/psql" $psql_options -c 'drop group regressgroup1; drop group regressgroup2; drop user regressuser1, regressuser2, regressuser3, regressuser4;' $dbname 2>/dev/null
if [ $? -eq 2 ]; then
    echo "$me: could not drop user accounts"
    (exit 2); exit
fi


# ----------
# Install the PL/pgSQL language in it
# ----------

if [ "$enable_shared" = yes ]; then
        message "installing PL/pgSQL"
        "$bindir/createlang" -L "$pkglibdir" $psql_options plpgsql $dbname
        if [ $? -ne 0 ] && [ $? -ne 2 ]; then
            echo "$me: createlang failed"
            (exit 2); exit
        fi
fi


# ----------
# Let's go
# ----------

message "running regression test queries"

if [ ! -d "$outputdir/results" ]; then
    mkdir -p "$outputdir/results" || { (exit 2); exit; }
fi
result_summary_file=$outputdir/regression.out
diff_file=$outputdir/regression.diffs

cat /dev/null >"$result_summary_file"
cat /dev/null >"$diff_file"

lno=0
(
    [ "$enable_shared" != yes ] && echo "ignore: plpgsql"
    cat $schedule </dev/null
    for x in $extra_tests; do
        echo "test: $x"
    done
) | sed 's/[ 	]*#.*//g' | \
while read line
do
    # Count line numbers
    lno=`expr $lno + 1`
    [ -z "$line" ] && continue

    set X $line; shift

    if [ x"$1" = x"ignore:" ]; then
        shift
        ignore_list="$ignore_list $@"
        continue
    elif [ x"$1" != x"test:" ]; then
        echo "$me:$schedule:$lno: syntax error"
        (exit 2); exit
    fi

    shift

    # ----------
    # Start tests
    # ----------

    if [ $# -eq 1 ]; then
        # Run a single test
        formatted=`echo $1 | awk '{printf "%-20.20s", $1;}'`
        $ECHO_N "test $formatted ... $ECHO_C"

        $PSQL -d "$dbname" <"$inputdir/sql/$1.sql" >"$outputdir/results/$1.out" 2>&1
    else
        # Start a parallel group
        $ECHO_N "parallel group ($# tests): $ECHO_C"
        for name do
            ( $PSQL -d $dbname <"$inputdir/sql/$name.sql" >"$outputdir/results/$name.out" 2>&1
              $ECHO_N " $name$ECHO_C"
            ) &
        done
        wait
        echo
    fi

    # ----------
    # Run diff
    # (We do not want to run the diffs immediately after each test,
    # because they would certainly get corrupted if run in parallel
    # subshells.)
    # ----------

    for name do
        if [ $# -ne 1 ]; then
            formatted=`echo "$name" | awk '{printf "%-20.20s", $1;}'`
            $ECHO_N "     $formatted ... $ECHO_C"
        fi

        # Check list extracted from resultmap to see if we should compare
        # to a system-specific expected file.
        # There shouldn't be multiple matches, but take the last if there are.

        EXPECTED="$inputdir/expected/${name}.out"
        for LINE in $SUBSTLIST
        do
            if [ `expr "$LINE" : "$name="` -ne 0 ]
            then
                SUBST=`echo "$LINE" | sed 's/^.*=//'`
                EXPECTED="$inputdir/expected/${SUBST}.out"
            fi
        done

        diff $DIFFFLAGS $EXPECTED $outputdir/results/${name}.out >/dev/null 2>&1
        case $? in
            0)
                echo "ok";;
            1)
                ( diff $DIFFFLAGS -C3 $EXPECTED $outputdir/results/${name}.out
                  echo
                  echo "======================================================================"
                  echo ) >> "$diff_file"
                if echo " $ignore_list " | grep " $name " >/dev/null 2>&1 ; then
                    echo "failed (ignored)"
                else
                    echo "FAILED"
                fi
                ;;
            2)
                # desaster struck
                echo "trouble" 1>&2
                (exit 2); exit;;
        esac
    done
done | tee "$result_summary_file" 2>&1

[ $? -ne 0 ] && exit

# ----------
# Server shutdown
# ----------

if [ -n "$postmaster_pid" ]; then
    message "shutting down postmaster"
    kill -15 "$postmaster_pid"
    unset postmaster_pid
fi

rm -f "$TMPFILE"


# ----------
# Evaluation
# ----------

count_total=`cat "$result_summary_file" | grep '\.\.\.' | wc -l | sed 's/ //g'`
count_ok=`cat "$result_summary_file" | grep '\.\.\. ok' | wc -l | sed 's/ //g'`
count_failed=`cat "$result_summary_file" | grep '\.\.\. FAILED' | wc -l | sed 's/ //g'`
count_ignored=`cat "$result_summary_file" | grep '\.\.\. failed (ignored)' | wc -l | sed 's/ //g'`

echo
if [ $count_total -eq $count_ok ]; then
    msg="All $count_total tests passed."
    result=0
elif [ $count_failed -eq 0 ]; then
    msg="$count_ok of $count_total tests passed, $count_ignored failed test(s) ignored."
    result=0
elif [ $count_ignored -eq 0 ]; then
    msg="$count_failed of $count_total tests failed."
    result=1
else
    msg="`expr $count_failed + $count_ignored` of $count_total tests failed, $count_ignored of these failures ignored."
    result=1
fi

dashes=`echo " $msg " | sed 's/./=/g'`
echo "$dashes"
echo " $msg "
echo "$dashes"
echo

if [ -s "$diff_file" ]; then
    echo "The differences that caused some tests to fail can be viewed in the"
    echo "file \`$diff_file'.  A copy of the test summary that you see"
    echo "above is saved in the file \`$result_summary_file'."
    echo
else
    rm -f "$diff_file" "$result_summary_file"
fi


(exit $result); exit
