/*
  +----------------------------------------------------------------------+
  | PHP Version 4                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2002 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available at through the world-wide-web at                           |
  | http://www.php.net/license/3_0.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Eric COLINET <e.colinet@laposte.net>                         |
  +----------------------------------------------------------------------+
*/


#include "shlobj.h"

/*
HICON GetSysFileIcon( const char * file, bool large )
{
	SHFILEINFO shInfo;
	if( SHGetFileInfo( file, 0, &shInfo, sizeof(SHFILEINFO), large?SHGFI_ICON|SHGFI_LARGEICON:SHGFI_ICON|SHGFI_SMALLICON)==0 )
		return NULL;
	return shInfo.hIcon;
}

*/


extern "C" int php_browse_for_folder( HWND wnd, const char * display, char path_buf[MAX_PATH] )
{
	BROWSEINFO binfo;
	LPITEMIDLIST itmlist;
	LPMALLOC pAlloc;

	binfo.hwndOwner= wnd;
	binfo.pidlRoot= NULL;
	binfo.pszDisplayName= path_buf;
	binfo.lpszTitle= display;
//	binfo.ulFlags= BIF_USENEWUI ; // VC7
	binfo.ulFlags= 0;
	binfo.lpfn= NULL;
	binfo.lParam= 0;
	binfo.iImage= 0;


	itmlist= SHBrowseForFolder( &binfo );
	path_buf[0]= 0;
	if( itmlist==NULL ) return 0;
	
	if( !SHGetPathFromIDList( itmlist, path_buf ) ) return 0; // A tester avec chemin de plus de 260 char

	// free itmlist
	SHGetMalloc( &pAlloc );
	pAlloc->Free( itmlist );
    pAlloc->Release();

	return 1;
}


extern "C" int php_create_link(LPCSTR lpszPathObj, LPSTR lpszPathLink, LPSTR lpszArgs, LPSTR lpszDesc, LPSTR lpszWorkingDir) 
{ 
    HRESULT hres; 
    IShellLink* psl; 
    
    if( !lpszPathObj || !lpszPathLink || !*lpszPathObj || !*lpszPathLink )
        return 0;

   // Get a pointer to the IShellLink interface. 
    hres = CoCreateInstance(CLSID_ShellLink, NULL, 
        CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl); 
    if (SUCCEEDED(hres)) { 
        IPersistFile* ppf; 
 
        // Set the path to the shortcut target and add the 
        // description. 
        psl->SetPath(lpszPathObj); 
        if( lpszDesc )
            psl->SetDescription(lpszDesc); 
        if( lpszArgs )
            psl->SetArguments(lpszArgs); 
        if( lpszWorkingDir )
            psl-> SetWorkingDirectory(lpszWorkingDir);

       // Query IShellLink for the IPersistFile interface for saving the 
       // shortcut in persistent storage. 
        hres = psl->QueryInterface( IID_IPersistFile, 
            (void**)&ppf); 
 
        if (SUCCEEDED(hres)) { 
            WORD wsz[MAX_PATH]; 
 
            // Ensure that the string is ANSI. 
            MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1, 
                wsz, MAX_PATH); 
 
            // Save the link by calling IPersistFile::Save. 
            hres = ppf->Save( wsz, TRUE); 
            ppf->Release(); 
        } 
        psl->Release(); 
    } 

	if( SUCCEEDED(hres) )
        return 1;
    else
        return 0;
}

