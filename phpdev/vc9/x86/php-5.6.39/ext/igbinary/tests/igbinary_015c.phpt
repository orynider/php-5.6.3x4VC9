--TEST--
Check for serialization handler
--SKIPIF--
<?php
if (!extension_loaded('session')) {
	exit('skip session extension not loaded');
}

ob_start();
phpinfo(INFO_MODULES);
$str = ob_get_clean();

$array = explode("\n", $str);
$array = preg_grep('/^igbinary session support.*yes/', $array);
if (!$array) {
	exit('skip igbinary session handler not available');
}
?>
--FILE--
<?php

$output = '';

function open($path, $name) {
	return true;
}

function close() {
	return true;
}

function read($id) {
    global $output;
    $output .= "read($id)\n";
	return '';
}

function write($id, $data) {
	global $output;
	$output .= "write($id): data:(" . bin2hex($data) . ")\n";
	return true;
}

function destroy($id) {
	return true;
}

function gc($time) {
	return true;
}

ini_set('session.serialize_handler', 'igbinary');

session_set_save_handler('open', 'close', 'read', 'write', 'destroy', 'gc');
session_id('abcdef10231512dfaz_12311');

session_start();

// save an empty session
session_write_close();

echo $output;

/*
 * you can add regression tests for your extension here
 *
 * the output of your test code has to be equal to the
 * text in the --EXPECT-- section below for the tests
 * to pass, differences between the output and the
 * expected text are interpreted as failure
 *
 * see php5/README.TESTING for further information on
 * writing regression tests
 */
?>
--EXPECT--
read(abcdef10231512dfaz_12311)
write(abcdef10231512dfaz_12311): data:()
