--TEST--
IBM-DB2: insert and retrieve XML data
--SKIPIF--
<?php 
require_once('skipif.inc'); 
require_once('skipif2.inc'); 
require_once('skipif3.inc'); 
?>
--FILE--
<?php

require_once('connection.inc');

$conn = db2_connect($database, $user, $password);

$drop = 'DROP TABLE xmlTest';
$result = @db2_exec($conn, $drop);

$create = 'CREATE TABLE xmlTest (id INTEGER, data XML)';
$result = db2_exec($conn, $create);

$insert = "INSERT INTO xmlTest values (0, '<TEST><function><xml/></function></TEST>')";

db2_exec( $conn, $insert );

if ($conn) {
	$sql =  "SELECT data FROM xmlTest";
	$stmt = db2_prepare( $conn, $sql );
	db2_execute($stmt);
	while($result = db2_fetch_assoc($stmt)) {
		print_r($result);
		echo "\n";
	}
	$drop = 'DROP TABLE xmlTest';
	$result = @db2_exec($conn, $drop);
	db2_close($conn);
}
else {
	echo "Connection failed.\n";
}

?>
--EXPECT--
Array
(
    [DATA] => <?xml version="1.0" encoding="UTF-8" ?><TEST><function><xml/></function></TEST>
)
