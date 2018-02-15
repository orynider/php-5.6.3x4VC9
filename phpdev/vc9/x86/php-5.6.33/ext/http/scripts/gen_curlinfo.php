#!/usr/bin/env php
<?php
// $Id$

error_reporting(0);

function failure() {
	// this is why error_get_last() should return a stdClass object
	$error = error_get_last();
	fprintf(STDERR, "FAILURE: %s\n", $error["message"]);
	exit(-1);
}

function file_re($file, $pattern, $all = true) {
	static $path;
	
	$path or $path = isset($_SERVER['argv'][1]) ? $_SERVER['argv'][1].'/include/curl/' : "/usr/local/include/curl/";
	
	if ($content = file_get_contents($path . $file)) {
		if ($all) {
			if (preg_match_all($pattern, $content, $matches, PREG_SET_ORDER)) {
				return $matches;
			}
		} else {
			if (preg_match($pattern, $content, $matches)) {
				return $matches;
			}
		}
		trigger_error("no match in $file for $pattern");
	}
	failure();
}

$ifdefs = array(
	'COOKIELIST' => 'HTTP_CURL_VERSION(7,14,1)',
	'PRIMARY_IP' => 'HTTP_CURL_VERSION(7,19,0)',
	'APPCONNECT_TIME' => 'HTTP_CURL_VERSION(7,19,0)',
	'REDIRECT_URL' => 'HTTP_CURL_VERSION(7,18,2)',
    'CONDITION_UNMET' => 'HTTP_CURL_VERSION(7,19,4)',
    'PRIMARY_PORT' => 'HTTP_CURL_VERSION(7,21,0)',
    'LOCAL_PORT' => 'HTTP_CURL_VERSION(7,21,0)',
    'LOCAL_IP' => 'HTTP_CURL_VERSION(7,21,0)',
);
$exclude = array(
    'PRIVATE', 'LASTSOCKET', 'FTP_ENTRY_PATH', 'CERTINFO',
    'RTSP_SESSION_ID', 'RTSP_CLIENT_CSEQ', 'RTSP_SERVER_CSEQ', 'RTSP_CSEQ_RECV'
);

$translate = array(
	'HTTP_CONNECTCODE' => "connect_code",
	'COOKIELIST' => 'cookies',
);

$templates = array(
'STRING' => 
'	if (CURLE_OK == curl_easy_getinfo(request->ch, %s, &c)) {
		add_assoc_string_ex(&array, "%s", sizeof("%2$s"), c ? c : "", 1);
	}
',
'DOUBLE' => 
'	if (CURLE_OK == curl_easy_getinfo(request->ch, %s, &d)) {
		add_assoc_double_ex(&array, "%s", sizeof("%2$s"), d);
	}
',
'LONG' => 
'	if (CURLE_OK == curl_easy_getinfo(request->ch, %s, &l)) {
		add_assoc_long_ex(&array, "%s", sizeof("%2$s"), l);
	}
',
'SLIST' =>
'	if (CURLE_OK == curl_easy_getinfo(request->ch, %s, &s)) {
		MAKE_STD_ZVAL(subarray);
		array_init(subarray);
		for (p = s; p; p = p->next) {
			if (p->data) {
				add_next_index_string(subarray, p->data, 1);
			}
		}
		add_assoc_zval_ex(&array, "%s", sizeof("%2$s"), subarray);
		curl_slist_free_all(s);
	}
',
);

$infos = file_re('curl.h', '/^\s*(CURLINFO_(\w+))\s*=\s*CURLINFO_(STRING|LONG|DOUBLE|SLIST)\s*\+\s*\d+\s*,?\s*$/m');

ob_start();
foreach ($infos as $info) {
	list(, $full, $short, $type) = $info;
	if (in_array($short, $exclude)) continue;
	if (isset($ifdefs[$short])) printf("#if %s\n", $ifdefs[$short]);
	printf($templates[$type], $full, strtolower((isset($translate[$short])) ? $translate[$short] : $short));
	if (isset($ifdefs[$short])) printf("#endif\n");
}

file_put_contents("http_request_info.c", 
	preg_replace('/(\/\* BEGIN \*\/\n).*(\/\* END \*\/)/s', '$1'. ob_get_contents() .'$2',
		file_get_contents("http_request_info.c")));

?>
