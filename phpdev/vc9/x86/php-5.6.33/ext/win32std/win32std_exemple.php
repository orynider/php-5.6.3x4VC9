<?
	function err( $txt ) { echo "ERROR: ".$txt."\n"; exit; }


	/* Message box exemple */
	if( win_message_box( "Hey !\n\nThis is win32std extension test\n\nAre you realy sure you want to start it ?", MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2 )!=MB_IDYES ) return FALSE;


	/* Browse exemple */
	$filter= array( 
		"HTML File" => "*.htm;*.html", 
		"INI File" => "*.ini", 
		"All file" => "*.*" );
	echo win_browse_file( 1, NULL, 'a_file', 'ext', $filter )."\n";
	echo win_browse_folder(NULL, "Choose a dir")."\n";


	/* Shell execute exemple */
	win_shell_execute( 'c:\\', "find" );


	/* beep exemple */
	if( !win_beep('*') )
		echo "Unable to beep !\n";
	else
		echo "Bip !\n";


	/* Sound exemple */
	if( !win_play_wav( "%WINDIR%\Media\ringin.wav", 1 ) ) 
		echo "Unable to play sound !\n";
	else {
		echo "Playing sound !\n";

		sleep(1);
		if( !win_play_wav( NULL ) )
			echo "Unable to stop playing sound !\n";
		else
			echo "Play stopped !\n";
	} 


	/* Reg exemple */
	$strMainKey= 'Control Panel';
	$mainKey= reg_open_key( HKEY_CURRENT_USER, $strMainKey );
	if( !$mainKey ) err( "Can't open '$strMainKey' !" );
	echo "'$strMainKey' Key opened\n\nKeys:\n";
	print_r( reg_enum_key($mainKey) );
	for( $i= 0; $key= reg_enum_key($mainKey, $i); $i++ ) {
		echo "\t$key\n";
	}
	echo "\nValues:\n";
	print_r( reg_enum_value($mainKey) );
	for( $i= 0; $value= reg_enum_value($mainKey, $i); $i++ ) {
		echo "\t$value=".reg_get_value($mainKey, $value)."\n";
	}
	reg_close_key($mainKey);


	/* Res exemple */
	$file= realpath('test_resourceDll.dll');
	if( empty($file) ) err( 'The res exemple need a file !' );
	res_set( $file, 'A_TYPE', 'A_RC_NAME', 'The time: '.date('d-m-Y h:i') );

	echo "Res Stream read: ".file_get_contents('res://'.$file.'/A_TYPE/A_RC_NAME')."\n\n";

	$h= res_open( $file );
	if( !$h ) err( "can't open ".$file );

	
	echo "Res list of '$file': \n";
	$list= res_list_type($h, true);
	if( $list===FALSE ) err( "Can't list type" );
	
	for( $i= 0; $i<count($list); $i++ ) {
		echo $list[$i]."\n";
		$res= res_list($h, $list[$i]);
		for( $j= 0; $j<count($res); $j++ ) {
			echo "\t".$res[$j]."\n";
		}
	}
	echo "Res get: ".res_get( $h, 'A_TYPE', 'A_RC_NAME' )."\n\n";
	res_close( $h );

?>