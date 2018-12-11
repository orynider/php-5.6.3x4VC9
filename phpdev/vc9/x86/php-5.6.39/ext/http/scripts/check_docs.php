#!/usr/bin/env php
<?php
// $Id$

function re($file, $re, &$m=NULL) {
	global $doc;
	return file_exists("$doc/$file") ? preg_match($re, file_get_contents("$doc/$file"), $m) : 0;
}
function fe($file) {
	global $doc;
	return file_exists("$doc/$file");
}
function fg($path, &$g=NULL) {
	global $doc;
	return count($g = glob("$doc/$path"));
}

$ext = "http";
$doc = "/home/mike/Development/src/php/phpdoc/en/trunk/reference/$ext";
$ref = new ReflectionExtension($ext);

printf("Undocumented INI options:\n");
foreach ($ref->getINIEntries() as $name => $tmp) {
	re("configuration.xml", "#<entry>$name</entry>#") or printf("\t%s (%s)\n", $name, $tmp);
}
printf("\n");

printf("Undocumented stream filters:\n");
foreach (preg_grep("/^$ext\./", stream_get_filters()) as $filter) {
	fe(sprintf("streamfilters/%s.xml", substr($filter, 5))) or printf("\t%s\n", $filter);
}
printf("\n");

printf("Undocumented constants:\n");
foreach ($ref->getConstants() as $name => $tmp) {
	re("constants.xml", "#<constant>$name</constant>#") or printf("\t%s (%s)\n", $name, $tmp);
}
printf("\n");


printf("Undocumented functions:\n");
foreach ($ref->getFunctions() as $func) {
	/* @var $func ReflectionFunction */
	fg(sprintf("functions/*/%s.xml", strtr($func->getName(),'_','-'))) or printf("\t%s()\n", $func->getName());
}
printf("\n");

printf("Undocumented classes/members:\n");
foreach ($ref->getClasses() as $class) {
	 if (substr($class->getName(), -strlen("Exception")) === "Exception") continue;
	/* @var $class ReflectionClass */
	fg(sprintf("%s.xml", $class->getName())) or printf(" %s\n", $class->getName());
	foreach ($class->getConstants() as $name => $tmp) {
		re($class->getName().".xml", "#>$name<#") or printf("\t%s::%s (%s)\n", $class->getName(), $name, $tmp);
	}
	foreach ($class->getProperties() as $prop) {
		/* @var $prop ReflectionProperty */
		$prop->isPrivate() or re($class->getName().".xml", "#>{$prop->getName()}<#") or printf("\t%s::$%s\n", $class->getName(), $prop->getName());
	}
	foreach ($class->getMethods() as $meth) {
		/* @var $meth ReflectionMethod */
		try {
			$meth->getPrototype();
		} catch (Exception $ex) {
			// if getPrototype throws an exception it's definitely not a method declared in an interface
			$meth->isPrivate() or fg(sprintf("%s/%s.xml", $class->getName(), strtr(trim($meth->getName(),'_'),'_','-'))) or printf("\t%s%s::%s()\n", $meth->isStatic()?'static ':'', $class->getName(), $meth->getName());
		}
		
	}
	printf("\n");
}
printf("\n");

printf("Undocumented request options:\n");
if (is_file($file = dirname(__FILE__)."/../http_request_api.c")) {
	if (preg_match_all("#(?:http_request_option\(request,\s*options,\s*\")(\w+)(?=\")#", file_get_contents($file), $match)) {
		foreach ($match[1] as $opt) {
			re("request-options.xml", "#<term>\s*$opt#") or printf("\t%s\n", $opt);
		}
		printf("\n");
		printf("List of request option entities:\n");
		foreach ($match[1] as $opt) {
			printf("\t<!ENTITY link.http.request.option.%1\$s '<link linkend=\"http.request.option.%1\$s\"><literal>%1\$s</literal> request option</link>'>\n", $opt);
		}
	}
} else {
	printf("\thttp_request_api.c not found\n");
}
printf("\n");

?>
