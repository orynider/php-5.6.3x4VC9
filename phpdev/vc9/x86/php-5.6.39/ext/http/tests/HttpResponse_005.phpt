--TEST--
HttpResponse file not found
--SKIPIF--
<?php
include 'skip.inc';
checkcgi();
checkmin("5.2.5");
?>
--FILE--
<?php
ini_set("error_reporting", 0);
ini_set("default_mimetype", "text/plain");

HttpResponse::setContentType("application/pdf");
HttpResponse::setContentDisposition("doc.pdf");
HttpResponse::setFile("__nonexistant__.pdf");
HttpResponse::send();
?>
--EXPECTF--
Status: 404%s
X-Powered-By: PHP/%s
Content-Type: text/plain

File not found
