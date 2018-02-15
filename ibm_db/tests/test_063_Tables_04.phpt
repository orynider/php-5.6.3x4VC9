--TEST--
IBM-DB2: db2_tables() - 4
--SKIPIF--
<?php require_once('skipif.inc'); ?>
--FILE--
<?php

require_once('connection.inc');

$conn = db2_connect($db,$user,$password);

$result = db2_tables($conn, NULL, "SYSIBM", "", "VIEW");

print_r ($result);

db2_free_result($result);

?>
--EXPECTF--
Resource id #%d
