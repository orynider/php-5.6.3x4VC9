--TEST--
IBM-DB2: db2_columns() - 3 - table
--SKIPIF--
<?php require_once('skipif.inc'); ?>
--FILE--
<?php

require_once('connection.inc');

$conn = db2_connect($db,$username,$password);

if ($conn) {
	$result = db2_columns($conn,NULL,strtoupper($username),"EMP_RESUME");	
	$i = 0;
	while ($row = db2_fetch_both($result)) {
	        // IS_NULLABLE (index 10) is NULLABLE (index 17)
		if ($row['COLUMN_NAME'] != 'EMP_ROWID' && $i < 3) {
			printf ("%s,%s,%s,%s\n", $row[1], 
				$row[2], $row[3], $row[10]);
		}
		$i++;
	}
} else {
	echo 'no connection: ' . db2_conn_errormsg();	
}

?>
--EXPECTF--
%s,EMP_RESUME,EMPNO,0
%s,EMP_RESUME,RESUME_FORMAT,0
%s,EMP_RESUME,RESUME,1
