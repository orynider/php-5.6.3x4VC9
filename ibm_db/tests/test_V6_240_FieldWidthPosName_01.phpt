--TEST--
IBM-DB2: db2_field_width() - by position and name
--SKIPIF--
<?php require_once('skipif.inc'); ?>
--FILE--
<?php

require_once('connection.inc');

$conn = db2_connect($db,$user,$password);

$result = db2_exec($conn, "select * from sales");
$result2 = db2_exec($conn, "select * from staff");
$result3 = db2_exec($conn, "select * from emp_photo");

for ($i=0; $i < db2_num_fields($result); $i++) 
{
   print $i . ":" . db2_field_width($result,$i) . "\n";
}
print "\n-----\n";
for ($i=0; $i < db2_num_fields($result2); $i++) 
{
   print $i . ":" . db2_field_width($result2,db2_field_name($result2,$i)) . "\n";
}
print "\n-----\n";
for ($i=0; $i < 3; $i++) 
{
   print $i . ":" . db2_field_width($result3,$i) . "," . db2_field_display_size($result3,$i)."\n";
}

print "\n-----\n";
print "region:" . db2_field_type($result,'region') . "\n";

print "5:" . db2_field_type($result2,5) . "\n";

?>
--EXPECT--
0:10
1:15
2:15
3:4

-----
0:2
1:9
2:2
3:5
4:2
5:1794
6:1794

-----
0:6,6
1:10,10
2:102400,102400

-----
region:
5:real
