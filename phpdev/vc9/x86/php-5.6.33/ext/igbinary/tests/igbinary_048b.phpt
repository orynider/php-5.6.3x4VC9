--TEST--
Object test, __set not called for private attr in extended class
--SKIPIF--
<?php
// http://php.net/manual/en/class.sessionhandlerinterface.php (PHP 5 >= 5.4.0)
if (version_compare(phpversion(), "5.4.0", "<")) {
    exit("skip php version less than 5.4.x");
}
--FILE--
<?php

class Bar {
    public $a = [];
    public $b = array();
    public $c = NULL;
    private $_d = NULL;
    public function __set($name,$value) {
        echo 'magic function called for ' . $name . ' with ' . var_export($value, true) . PHP_EOL;
    }
}

class Foo extends Bar {
    public $m;
}

$x = new Foo();
$x->a = [1, 2, 3];
$x->nonexistent = 'aaa';

unserialize(serialize($x));
--EXPECT--
magic function called for nonexistent with 'aaa'
