--TEST--
IBM-DB2: db2_bind_param: INSERT statement - NULL parameter
--SKIPIF--
<?php require_once('skipif.inc'); ?>
--FILE--
<?php

require_once('connection.inc');
$conn = db2_connect($database, $user, $password);
db2_autocommit( $conn, DB2_AUTOCOMMIT_OFF );

$insert1 = "INSERT INTO animals (id, breed, name, weight)
    VALUES (NULL, 'ghost', NULL, ?)";
$select = 'SELECT id, breed, name, weight FROM animals WHERE weight IS NULL';

if ($conn) {
    $stmt = db2_prepare( $conn, $insert1);

    $animal = NULL;
    db2_bind_param($stmt, 1, "animal");

    if (db2_execute($stmt)) {
        $stmt = db2_exec($conn, $select);
	while ($row = db2_fetch_array($stmt)) {
            var_dump($row);
        }
    }
    db2_rollback($conn);
}
else 
{
    echo "Connection failed.\n";
}

?>
--EXPECT--
array(4) {
  [0]=>
  NULL
  [1]=>
  string(5) "ghost"
  [2]=>
  NULL
  [3]=>
  NULL
}
