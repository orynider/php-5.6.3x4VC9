--TEST--
Unserialize invalid data (php 7.2+)
--SKIPIF--
<?php
if (!extension_loaded('igbinary')) {
	echo "skip no igbinary";
}
if (PHP_VERSION_ID < 70200) {
    echo "Skip php 7.2+ required\n";
}
?>
--FILE--
<?php

$o = new stdClass();
$o->{"1"} = "manual";
$datas = array(
	87817,
	-1,
	array(1,2,3,"testing" => 10, "foo"),
	true,
	false,
	0.187182,
	"dakjdh98389\000",
	null,
	(object)array(1,2,3),
    $o,
);

error_reporting(0);
foreach ($datas as $data) {
	$str = igbinary_serialize($data);
	$len = strlen($str);

	// truncated
	for ($i = 0; $i < $len - 1; $i++) {
		$v = igbinary_unserialize(substr($str, 0, $i));
		if (is_object($data) && $v !== null && $v == $data) {
			continue;
		} elseif ($v !== null && $v != FALSE && $v !== $data) {
			echo "output at $i:\n";
			var_dump($v);
			echo "vs.\n";
			var_dump($data);
		}
	}

	// padded
	$str .= "98398afa\000y21_ ";
	$v = igbinary_unserialize($str);
	if ($v !== $data && !(is_object($data) && $v == $data)) {
		echo "padded should get original\n";
		var_dump($v);
		echo "vs.\n";
		var_dump($data);
	}
}
?>
--EXPECT--
