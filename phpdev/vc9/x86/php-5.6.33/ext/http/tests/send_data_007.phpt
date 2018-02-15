--TEST--
http_send_data() NIL-NIL range
--SKIPIF--
<?php 
include 'skip.inc';
checkcgi();
checkmin("5.2.5");
?>
--ENV--
HTTP_RANGE=bytes=0-0
--FILE--
<?php
http_send_content_type('text/plain');
http_send_data("abc");
?>
--EXPECTF--
Status: 206%s
X-Powered-By: PHP/%s
Content-Type: text/plain
Accept-Ranges: bytes
Content-Range: bytes 0-0/3
Content-Length: 1

a
