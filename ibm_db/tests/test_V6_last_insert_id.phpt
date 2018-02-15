--TEST--
IBM-DB2: Last Insert ID test
--SKIPIF--
<?php require_once('skipif.inc'); ?>
--FILE--
<?php

require_once('connection.inc');
$conn = db2_connect($database, $user, $password);

if ($conn) {
        echo "Connection succeeded.\n";
        
        $dropTable = 'DROP TABLE lastInsertID';
        
        $createTable = 'CREATE TABLE lastInsertID (id integer GENERATED BY DEFAULT AS IDENTITY, name varchar(20))';
        $insertTable = 'INSERT INTO lastInsertID (name) VALUES (\'Temp Name\')';
        $insertMany = 'INSERT INTO lastInsertID (name) VALUES (\'Temp Name\'), (\'Temp Name\')';

        $stmt = @db2_exec($conn, $dropTable);
        $stmt = @db2_exec($conn, $createTable);

        /* Checking when no insert has been executed. */        
        $ret =  db2_last_insert_id($conn);
        if($ret) {
                echo "Last Insert ID is : " . $ret . "\n";
        } else {
                echo "No Last insert ID.\n";
        }

        /* Inserting many rows from VALUES clause */
        $stmt = db2_exec($conn, $insertMany);
        $ret =  db2_last_insert_id($conn);
        if($ret) {
                echo "Last Insert ID is : " . $ret . "\n";
        } else {
                echo "No Last insert ID.\n";
        }

        /* Checking for single row inserted. */
        $stmt = db2_exec($conn, $insertTable);
        $ret =  db2_last_insert_id($conn);
        if($ret) {
                echo "Last Insert ID is : " . $ret . "\n";
        } else {
                echo "No Last insert ID.\n";
        }
        
        /* Checking when multiple rows has been inserted separately. */
        for ($i = 0;$i < 5;$i++) {
                $stmt = db2_exec($conn, $insertTable);
                $ret =  db2_last_insert_id($conn);
                if($ret) {
                        echo "Last Insert ID is : " . $ret . "\n";
                } else {
                        echo "No Last insert ID.\n";
                }
        }

        db2_close($conn);
}
else {
    echo "Connection failed.";
}

//Testing when there is no serial column in table.
$conn = db2_connect($database, $user, $password);
if ($conn) {
        echo "Connection succeeded.\n";
        
        $dropTable = 'DROP TABLE lastInsertID';
        
        $createTable = 'CREATE TABLE lastInsertID (id integer, name varchar(20))';
        $insertTable = 'INSERT INTO lastInsertID (id, name) VALUES (1, \'Temp Name\')';

        $stmt = @db2_exec($conn, $dropTable);
        $stmt = @db2_exec($conn, $createTable);

        $stmt = db2_exec($conn, $insertTable);
        $ret =  db2_last_insert_id($conn);
        if($ret) {
                echo "Last Insert ID is : " . $ret . "\n";
        } else {
                echo "No Last insert ID.\n";
        }
        
        $stmt = @db2_exec($conn, $dropTable);

        db2_close($conn);
}
else {
    echo "Connection failed.";
}

?>
--EXPECT--
Connection succeeded.
No Last insert ID.
Last Insert ID is : 2
Last Insert ID is : 3
Last Insert ID is : 4
Last Insert ID is : 5
Last Insert ID is : 6
Last Insert ID is : 7
Last Insert ID is : 8
Connection succeeded.
No Last insert ID.
