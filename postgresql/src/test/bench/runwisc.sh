#!/bin/sh
# $Header: /cvsroot/pgsql-server/src/test/bench/runwisc.sh,v 1.4 1999/05/23 18:53:30 momjian Exp $
# 
# Note that in our published benchmark numbers, we executed the command in the
# following fashion:
#
# time $POSTGRES -texecutor -tplanner -f hashjoin -Q bench
#
if [ ! -d $1 ]; then
        echo " you must specify a valid data directory "
        exit
fi

if [ -d ./obj ]; then
	cd ./obj
fi

echo =============== vacuuming benchmark database... =================
echo "vacuum" | postgres -D${1} -Q bench > /dev/null

echo =============== running benchmark... =================
time postgres -D${1} -texecutor -tplanner -Q bench < bench.sql
