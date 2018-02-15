--TEST--
RarEntry direct instantiation does not crash (PHP 7)
--SKIPIF--
<?php if(!extension_loaded("rar")) die("skip");
if (!defined('PHP_VERSION_ID') || PHP_VERSION_ID < 70000) die("skip for PHP >= 7");
--FILE--
<?php

new RarEntry();

echo "Done\n";
--EXPECTF--
Fatal error: Uncaught Error: Call to private RarEntry::__construct() from invalid context in %s:%d
Stack trace:
#0 {main}
  thrown in %s on line %d
