--TEST--
IBM-DB2: 1.9.7 - IBM i ignore user profile (operator no QSQSRVR jobs)
--SKIPIF--
<?php 
putenv("IBM_DB_I5_TEST=1");
putenv("IBM_DB_i5_ignore_userid=1"); /* before include this test */
require_once('skipif.inc'); 
?>
--FILE--
<?php
putenv("IBM_DB_I5_TEST=1");
putenv("IBM_DB_i5_ignore_userid=1"); /* before include this test */

require_once('connection.inc');
require_once('xmlservice.inc');

putenv("IBM_DB_i5_ignore_userid=1");
$conn1 = db2_connect($database, $user, $password);
$xml = xmlservice_diag($conn1);
$key1 = xmlservice_diag_jobinfo($xml);
echo "$key1\n";
db2_close($conn1);

putenv("IBM_DB_i5_ignore_userid=1");
$conn2 = db2_connect($database, $user, $password);
$xml = xmlservice_diag($conn2);
$key2 = xmlservice_diag_jobinfo($xml);
echo "$key2\n";
db2_close($conn2);

if (strpos($key1,"QSQSRVR") === false) {
  echo "success\n";
} else {
  echo "failed ($key1 is QSQSRVR)\n";
}

if (strpos($key2,"QSQSRVR") === false) {
  echo "success\n";
} else {
  echo "failed ($key2 is QSQSRVR)\n";
}

if ($key1 == $key2) {
  echo "success\n";
} else {
  echo "failed ($key1 == $key2)\n";
}


putenv("IBM_DB_i5_ignore_userid=0");
$conn3 = db2_connect($database, $user, $password);
$xml = xmlservice_diag($conn3);
$key3 = xmlservice_diag_jobinfo($xml);
echo "$key3\n";

putenv("IBM_DB_i5_ignore_userid=0");
$conn4 = db2_connect($database, $user, $password);
$xml = xmlservice_diag($conn4);
$key4 = xmlservice_diag_jobinfo($xml);
echo "$key4\n";


if (strpos($key3,"QSQSRVR") === false) {
  echo "failed ($key3 not QSQSRVR)\n";
} else {
  echo "success\n";
}

if (strpos($key4,"QSQSRVR") === false) {
  echo "failed ($key4 not QSQSRVR)\n";
} else {
  echo "success\n";
}


if ($key1 != $key3) {
  echo "success\n";
} else {
  echo "failed ($key1 == $key3)\n";
}

if ($key3 != $key4) {
  echo "success\n";
} else {
  echo "failed ($key3 == $key4)\n";
}


?>
--EXPECTF--
%s
success
success
success
%s
success
success
success
success

