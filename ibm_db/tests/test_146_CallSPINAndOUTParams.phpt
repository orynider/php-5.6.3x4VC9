--TEST--
IBM-DB2: Call a stored procedure with IN and OUT parameters
--SKIPIF--
<?php require_once('skipif.inc'); ?>
--FILE--
<?php

require_once('connection.inc');

$conn = db2_connect($database, $user, $password);
db2_autocommit( $conn, DB2_AUTOCOMMIT_OFF );

if ($conn) {
    $sql = 'CALL match_animal(?, ?, ?)';
    $stmt = db2_prepare($conn, $sql);

    $name = "Peaches";
    $second_name = "Rickety Ride";
    $weight = 0;
    db2_bind_param($stmt, 1, "name", DB2_PARAM_IN);
    db2_bind_param($stmt, 2, "second_name", DB2_PARAM_INOUT);
    db2_bind_param($stmt, 3, "weight", DB2_PARAM_OUT);

    print "Values of bound parameters _before_ CALL:\n";
    print "  1: {$name} 2: {$second_name} 3: {$weight}\n\n";

    if (db2_execute($stmt)) {
            print "Values of bound parameters _after_ CALL:\n";
            print "  1: {$name} 2: {$second_name} 3: {$weight}\n\n";

            print "Results:\n";
            while ($row = db2_fetch_array($stmt)) {
                    print "  " . trim($row[0]) . ", " . trim($row[1]) . ", {$row[2]}\n";	
            }
    }
    db2_rollback($conn);
}
?>
--EXPECT--
Values of bound parameters _before_ CALL:
  1: Peaches 2: Rickety Ride 3: 0

Values of bound parameters _after_ CALL:
  1: Peaches 2: TRUE 3: 12

Results:
  Peaches, dog, 12.30
  Pook, cat, 3.20
  Rickety Ride, goat, 9.70
  Smarty, horse, 350.00
  Sweater, llama, 150.00
