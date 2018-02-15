--TEST--
IBM-DB2: db2_rollback() - insert
--SKIPIF--
<?php require_once('skipif.inc'); ?>
--FILE--
<?php

require_once('connection.inc');

$conn = db2_connect($database, $user, $password);

if ($conn) {
    $stmt = db2_exec( $conn, "SELECT count(*) FROM animals" );
    $res = db2_fetch_array( $stmt );
    $rows = $res[0];
    echo $rows."\n";
    
    db2_autocommit( $conn, 0 );
    $ac = db2_autocommit( $conn );
    if( $ac != 0 ) {
       echo "Cannot set DB2_AUTOCOMMIT_OFF\nCannot run test\n";
       exit;
    }
    
    db2_exec( $conn, "INSERT INTO animals values (7,'bug','Brain Bug',10000.1)" );
    
    $stmt = db2_exec( $conn, "SELECT count(*) FROM animals" );
    $res = db2_fetch_array( $stmt );
    $rows = $res[0];
    echo $rows."\n";
    
    db2_rollback( $conn );
    
    $stmt = db2_exec( $conn, "SELECT count(*) FROM animals" );
    $res = db2_fetch_array( $stmt );
    $rows = $res[0];
    echo $rows."\n";
    db2_close($conn);
}
else {
    echo "Connection failed.\n";
}

?>
--EXPECT--
7
8
7
