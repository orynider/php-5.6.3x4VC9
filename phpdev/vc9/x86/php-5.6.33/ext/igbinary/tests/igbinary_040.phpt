--TEST--
b0rked random data test
--SKIPIF--
--FILE--
<?php

if(!extension_loaded('igbinary')) {
	dl('igbinary.' . PHP_SHLIB_SUFFIX);
}

function test() {
	$serialized = igbinary_serialize(null);
	$serialized = substr($serialized, 0, -1);

	$length = mt_rand(1, 255);
	for ($i = 0; $i < $length; ++$i) {
		$serialized .= chr(mt_rand(0, 255));
	}

	// if returned null everything is OK
	if (($unserialized = igbinary_unserialize($serialized)) === null) {
		return true;
	}

	error_reporting(E_ALL);
	// whole data is read?
	$reserialized = igbinary_serialize($unserialized);
	if ($serialized === $reserialized) {
		return true;
	}
	if (is_string($reserialized) && strlen($reserialized) < strlen($serialized) && strncmp($reserialized, $serialized, 0) === 0) {
		// TODO: Fix this in releases, after verifying that session and APCU don't have additional data such as null bytes appended.
		// If there are unused bytes, then the code should assume that the provided data is corrupt, and return false.
		return true;
	}

	echo bin2hex($serialized), "\n";
	echo bin2hex($reserialized), "\n";
	var_dump($unserialized);

	return false;
}

mt_srand(0xface);
for ($i = 0; $i < 100; ++$i) {
	error_reporting(E_ERROR | E_PARSE);
	if (!test()) break;
}

?>
--EXPECT--
