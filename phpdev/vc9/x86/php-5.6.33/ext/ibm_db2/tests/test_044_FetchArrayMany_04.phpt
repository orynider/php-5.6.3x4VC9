--TEST--
IBM-DB2: db2_fetch_array() - several rows 3
--SKIPIF--
<?php require_once('skipif.inc'); ?>
--FILE--
<?php

require_once('connection.inc');

$conn = db2_connect($db,$username,$password);

$result = db2_exec($conn, "select * from sales");

while ($row = db2_fetch_array($result)) {
printf ("%-10s ",$row['0']);
printf ("%-15s ",$row['1']);
printf ("%-15s ",$row['2']);
printf ("%4s",$row['3']);
print "\n";
}


?>
--EXPECT--
1995-12-31 LUCCHESSI       Ontario-South      1
1995-12-31 LEE             Ontario-South      3
1995-12-31 LEE             Quebec             1
1995-12-31 LEE             Manitoba           2
1995-12-31 GOUNOT          Quebec             1
1996-03-29 LUCCHESSI       Ontario-South      3
1996-03-29 LUCCHESSI       Quebec             1
1996-03-29 LEE             Ontario-South      2
1996-03-29 LEE             Ontario-North      2
1996-03-29 LEE             Quebec             3
1996-03-29 LEE             Manitoba           5
1996-03-29 GOUNOT          Ontario-South      3
1996-03-29 GOUNOT          Quebec             1
1996-03-29 GOUNOT          Manitoba           7
1996-03-30 LUCCHESSI       Ontario-South      1
1996-03-30 LUCCHESSI       Quebec             2
1996-03-30 LUCCHESSI       Manitoba           1
1996-03-30 LEE             Ontario-South      7
1996-03-30 LEE             Ontario-North      3
1996-03-30 LEE             Quebec             7
1996-03-30 LEE             Manitoba           4
1996-03-30 GOUNOT          Ontario-South      2
1996-03-30 GOUNOT          Quebec            18
1996-03-30 GOUNOT          Manitoba           1
1996-03-31 LUCCHESSI       Manitoba           1
1996-03-31 LEE             Ontario-South     14
1996-03-31 LEE             Ontario-North      3
1996-03-31 LEE             Quebec             7
1996-03-31 LEE             Manitoba           3
1996-03-31 GOUNOT          Ontario-South      2
1996-03-31 GOUNOT          Quebec             1
1996-04-01 LUCCHESSI       Ontario-South      3
1996-04-01 LUCCHESSI       Manitoba           1
1996-04-01 LEE             Ontario-South      8
1996-04-01 LEE             Ontario-North       
1996-04-01 LEE             Quebec             8
1996-04-01 LEE             Manitoba           9
1996-04-01 GOUNOT          Ontario-South      3
1996-04-01 GOUNOT          Ontario-North      1
1996-04-01 GOUNOT          Quebec             3
1996-04-01 GOUNOT          Manitoba           7
