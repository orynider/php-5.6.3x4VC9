<?php

namespace SDK;

use SDK\Build\Dependency\Fetcher;
use SDK\Cache;
use SDK\Exception;

class Config
{
	/* Config variables. */
	protected static $depsHost = 'windows.php.net';
	protected static $depsPort = 80;
	protected static $depsBaseUri = "/downloads/php-sdk/deps";
	/* protected static $sdkNugetFeedUrl = "http://127.0.0.1/sdk/nuget"; */
	protected static $all_branches = array ();
	protected static $all_old_branches = array ();
	protected static $all_new_branche = array ();	
	protected static $knownBranches = array ();
	protected static $UnknownBranches = array ();
	/* Helper props and methods. */
	protected static $currentBranchName = NULL;
	protected static $currentArchName = NULL;
	protected static $currentCrtName = NULL;
	protected static $currentStabilityName = NULL;
	protected static $depsLocalPath = NULL;

	public static function getDepsHost() : string
	{/*{{{*/
		return self::$depsHost;
	}/*}}}*/

	public static function getDepsPort() : string
	{/*{{{*/
		return self::$depsPort;
	}/*}}}*/

	public static function getDepsBaseUri() : string
	{/*{{{*/
		return self::$depsBaseUri;
	}/*}}}*/

	public static function setCurrentArchName(string $arch) : void
	{/*{{{*/
		$arch = strtolower($arch);

		if ("x64" != $arch && "x86" != $arch) {
			throw new Exception("Unknown arch keyword, either x86 or x64 is accepted");
		}

		self::$currentArchName = $arch;
	}	/*}}}*/

	public static function getCurrentArchName() : string
	{/*{{{*/
		if (NULL === self::$currentArchName) {
			/* XXX this might be not true for other compilers! */
			passthru("where cl.exe >nul", $status);
			if ($status) {
				throw new Exception("Couldn't find cl.exe.");
			}

			exec("cl.exe /? 2>&1", $a, $status);
			if ($status) {
				throw new Exception("Couldn't execute cl.exe.");
			}

			if (preg_match(",x64,", $a[0])) {
				self::setCurrentArchName("x64");
			} else {
				self::setCurrentArchName("x86");
			}
		}
		return self::$currentArchName;
	}	/*}}}*/

	public static function setCurrentCrtName(string $crt) : void
	{/*{{{*/
		self::$currentCrtName = $crt;
	}	/*}}}*/

	public static function getCurrentCrtName() : ?string
	{/*{{{*/
		if (NULL === self::$currentCrtName) {
			$all_branches = Config::getKnownBranches();
			$old_branches = Config::getUnknownBranches();			
			if (isset($all_branches[Config::getCurrentBranchName()])) {
				$branch = $all_branches[Config::getCurrentBranchName()];
			}
			else if (isset($old_branches[Config::getCurrentBranchName()])) {
				$branch = $old_branches[Config::getCurrentBranchName()];
			}
			else {
				throw new Exception("Couldn't find configuration for branch '" . Config::getCurrentBranchName() . "'");
			}
			
			if (count($branch) > 1) {
				throw new Exception("Multiple CRTs are available for this branch, please choose one from " . implode(",", array_keys($branch)));
			}

			self::setCurrentCrtName(array_keys($branch)[0]);
		}

		return self::$currentCrtName;
	}	/*}}}*/

	public static function setCurrentStabilityName(string $stability) : void
	{/*{{{*/
		if ("stable" != $stability && "staging" != $stability) {
			throw new Exception("Unknown stability keyword, either stable or staging is accepted");
		}

		self::$currentStabilityName = $stability;
	}	/*}}}*/

	public static function getCurrentStabilityName() : ?string
	{/*{{{*/
		if (NULL === self::$currentStabilityName) {
			if ("master" == Config::getCurrentBranchName()) {
				Config::setCurrentStabilityName("staging");
			} else {
				Config::setCurrentStabilityName("stable");
			}
		}

		return self::$currentStabilityName;
	}	/*}}}*/

	public static function getKnownBranches() : array
	{/*{{{*/
		if (empty(self::$knownBranches)) {
			$cache_file = "known_branches.txt";
			$cache = new Cache(self::getDepsLocalPath());
			$fetcher = new Fetcher(self::$depsHost, self::$depsPort);

			$tmp = $fetcher->getByUri(self::$depsBaseUri . "/series/");
			if (false !== $tmp) {
				$data = array();
				if (preg_match_all(",/packages-(.+)-(vc\d+)-(x86|x64)-(stable|staging)\.txt,U", $tmp, $m, PREG_SET_ORDER)) {
					foreach ($m as $b) {
						if (!isset($data[$b[1]])) {
							$data[$b[1]] = array();
						}

						$data[$b[1]][$b[2]][] = array("arch" => $b[3], "stability" => $b[4]);
					}

					$cache->cachecontent($cache_file, json_encode($data, JSON_PRETTY_PRINT), true);
				}
			} else {
				/* It might be ok to use cached branches list, if a fetch failed. */
				$tmp = $cache->getCachedContent($cache_file, true);
				if (NULL == $tmp) {
					throw new Exception("No cached branches list found");
				}
				$data = json_decode($tmp, true);
			}

			if (!is_array($data) || empty($data)) {
				throw new Exception("Failed to fetch supported branches");
			}
			self::$knownBranches = $data;
		}

		return self::$knownBranches;
	}/*}}}*/					
	
	public static function getUnknownBranches() : array
	{/*{{{*/		
		if (empty(self::$UnknownBranches)) {
			$data = array();
			$data['5.6'] = array(
				/*
				'vc7.1' => Array(
						0 => Array(
							'arch' => (string) 'x64', 
							'stability' => (string) 'stable',
						), 
						1 => Array(
							'arch' => (string) 'x64', 
							'stability' => (string) 'staging',
						),
						2 => Array(
							'arch' => (string) 'x86', 
							'stability' => (string) 'stable',
						), 
						3 => Array(
							'arch' => (string) 'x86', 
							'stability' => (string) 'staging',
						),
				),
				*/
				'vc9' => Array(
						0 => Array(
							'arch' => (string) 'x64', 
							'stability' => (string) 'stable',
						), 
						1 => Array(
							'arch' => (string) 'x64', 
							'stability' => (string) 'staging',
						),
						2 => Array(
							'arch' => (string) 'x86', 
							'stability' => (string) 'stable',
						), 
						3 => Array(
							'arch' => (string) 'x86', 
							'stability' => (string) 'staging',
						),
				),
				/*
				'vc11' => Array(
						0 => Array(
							'arch' => (string) 'x64', 
							'stability' => (string) 'stable',
						), 
						1 => Array(
							'arch' => (string) 'x64', 
							'stability' => (string) 'staging',
						),
						2 => Array(
							'arch' => (string) 'x86', 
							'stability' => (string) 'stable',
						), 
						3 => Array(
							'arch' => (string) 'x86', 
							'stability' => (string) 'staging',
						),
				),
				*/				
			);
			//$data = json_decode($data, true);
			if (!is_array($data) || empty($data)) {
				throw new Exception("Failed to fetch supported branches");
			}
			self::$UnknownBranches = $data;				
		}
		return self::$UnknownBranches;
	}/*}}}*/	

	public static function setCurrentBranchName(string $name) : void
	{/*{{{*/		
		self::$currentBranchName = array_merge(self::getUnknownBranches(), self::getKnownBranches());
		if (!array_key_exists($name, self::$currentBranchName)) {
			throw new Exception("Unsupported branch '$name'");
		}		
		self::$currentBranchName = $name;
	}/*}}}*/

	public static function guessCurrentBranchName() : ?string
	{/*{{{*/
		$branch = NULL;

		/* Try to figure out the branch. For now it only works if CWD is in php-src. */
		$fl = "main/php_version.h";
		if (file_exists($fl)) {
			$s = file_get_contents($fl);
			$major = $minor = NULL;

			if (preg_match(",PHP_MAJOR_VERSION (\d+),", $s, $m)) {
				$major = $m[1];
			}
			if (preg_match(",PHP_MINOR_VERSION (\d+),", $s, $m)) {
				$minor = $m[1];
			}

			if (is_numeric($major) && is_numeric($minor)) {
				$branch = "$major.$minor";
			}
		}

		return $branch;
	}/*}}}*/

	public static function getCurrentBranchName() : string
	{/*{{{*/
		if (NULL == self::$currentBranchName) {
			$branch = self::guessCurrentBranchName();
			self::setCurrentBranchName($branch);
		}
	
		return self::$currentBranchName;
	}/*}}}*/

	public static function getCurrentBranchData() : array
	{/*{{{*/
		$ret = array();
		$branches = self::getKnownBranches();
		$old_branches = self::getUnknownBranches();
		$current_branch_name = self::getCurrentBranchName();
		if ((!array_key_exists($current_branch_name, $branches)) && (array_key_exists($current_branch_name, $old_branches))) {
				$cur_crt = Config::getCurrentCrtName(); //VC9		
				$data = $old_branches[$current_branch_name][$cur_crt]; //[5.6][VC9]
				if (count($old_branches[$current_branch_name]) > 1) {
					if (NULL === $cur_crt) {
						throw new Exception("More than one CRT is available for branch '$current_branch_name', pass one explicitly.");
					}
					$cur_crt_usable = false;
					foreach (array_keys($old_branches[$current_branch_name]) as $crt) {
						if ($cur_crt == $crt) {
							$cur_crt_usable = true;
							break;
						}
					}
					if (!$cur_crt_usable) {
						throw new Exception("The passed CRT '$cur_crt' doesn't match any availbale for branch '$current_branch_name'");
					}
					$data = $old_branches[$current_branch_name][$cur_crt];
				} else {
					/* Evaluate CRTs, to avoid ambiquity. */
					list($crt, $data) = each($old_branches[$current_branch_name]);
					if ($crt != $cur_crt) {
						throw new Exception("The passed CRT '$cur_crt' doesn't match any availbale for branch '$current_branch_name'");
					}
				}
				/* Last step, filter by arch and stability. */
				foreach ($data as $d) {
					if (self::getCurrentArchName() == $d["arch"]) {
						if (self::getCurrentStabilityName() == $d["stability"]) {							
							$ret["crt"] = $crt;
							$ret["arch"] = $d["arch"];
							$ret["stability"] = $d["stability"];
						}
					}
				}
				if (!$ret["stability"]) {
					throw new Exception("Failed to find config with stability '" . self::getCurrentStabilityName() . "'");
				}
				if (!$ret["crt"]) {
					throw new Exception("Failed to find config with arch '" . self::getCurrentArchName() . "'");
				}
				return $ret;				
		}
		if (!array_key_exists($current_branch_name, $branches)) {
			throw new Exception("Unknown branch '$current_branch_name'");
		}		
		$cur_crt = Config::getCurrentCrtName();
		if (count($branches[$current_branch_name]) > 1) {
			if (NULL === $cur_crt) {
				throw new Exception("More than one CRT is available for branch '$current_branch_name', pass one explicitly.");
			}

			$cur_crt_usable = false;
			foreach (array_keys($branches[$current_branch_name]) as $crt) {
				if ($cur_crt == $crt) {
					$cur_crt_usable = true;
					break;
				}
			}
			if (!$cur_crt_usable) {
				throw new Exception("The passed CRT '$cur_crt' doesn't match any availbale for branch '$current_branch_name'");
			}
			$data = $branches[$current_branch_name][$cur_crt];
		} else {
			/* Evaluate CRTs, to avoid ambiquity. */
			list($crt, $data) = each($branches[$current_branch_name]);
			if ($crt != $cur_crt) {
				throw new Exception("The passed CRT '$cur_crt' doesn't match any availbale for branch '$current_branch_name'");
			}
		}

		$ret["name"] = $current_branch_name;
		$ret["crt"] = $crt;

		/* Last step, filter by arch and stability. */
		foreach ($data as $d) {
			if (self::getCurrentArchName() == $d["arch"]) {
				if (self::getCurrentStabilityName() == $d["stability"]) {
					$ret["arch"] = $d["arch"];
					$ret["stability"] = $d["stability"];
				}
			}
		}

		if (!$ret["stability"]) {
			throw new Exception("Failed to find config with stability '" . self::getCurrentStabilityName() . "'");
		}
		if (!$ret["crt"]) {
			throw new Exception("Failed to find config with arch '" . self::getCurrentArchName() . "'");
		}

		return $ret; 
	}/*}}}*/

	public static function getSdkNugetFeedUrl() : string
	{/*{{{*/
		return self::$sdkNugetFeedUrl;
	}/*}}}*/

	public static function getSdkPath() : string
	{/*{{{*/
		$path = getenv("PHP_SDK_ROOT_PATH");

		if (!$path) {
			throw new Exception("PHP_SDK_ROOT_PATH isn't set!");
		}

		$path = realpath($path);
		if (!file_exists($path)) {
			throw new Exception("The path '$path' is non existent.");
		}

		return $path;
	}/*}}}*/

	public static function getSdkVersion() : string
	{/*{{{*/
		$path = self::getSdkPath() . DIRECTORY_SEPARATOR . "VERSION";

		if (!file_exists($path)) {
			throw new Exception("Couldn't find the SDK version file.");
		}

		return file_get_contents($path);
	}/*}}}*/

	public static function getDepsLocalPath() : ?string
	{/*{{{*/
		if (NULL == self::$depsLocalPath) {
			if (file_exists("../deps")) {
				self::setDepsLocalPath(realpath("../deps"));
			} else if (file_exists("main/php_version.h")) {
				/* Deps dir might not exist. */
				self::setDepsLocalPath(realpath("..") . DIRECTORY_SEPARATOR . "deps");
			}
		}

		return self::$depsLocalPath;
	}/*}}}*/

	public static function setDepsLocalPath(string $path) : void
	{/*{{{*/
		self::$depsLocalPath = $path;
	}/*}}}*/

	public static function getCacheDir() : string
	{/*{{{*/
		$path = self::getSdkPath() . DIRECTORY_SEPARATOR . ".cache";

		if (!file_exists($path)) {
			if (!mkdir($path)) {
				throw new Exception("Failed to create '$path'");
			}
		}

		return $path;
	}/*}}}*/

	public static function getTmpDir() : string
	{/*{{{*/
		$path = self::getSdkPath() . DIRECTORY_SEPARATOR . ".tmp";

		if (!file_exists($path)) {
			if (!mkdir($path)) {
				throw new Exception("Failed to create '$path'");
			}
		}

		return $path;
	}/*}}}*/
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
