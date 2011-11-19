#include "XipNeheUtility.h"
#include <string>


/*
std::string convertRGBtoHex(const int num) 
{
    
      static std::string hexDigits = "0123456789ABCDEF";
    
      std::string rgbhex;
    
      for (int i=(3*2) - 1; i>=0; i--) {
        
          rgbhex += hexDigits[((num >> i*4) & 0xF)];
      }
      
      return rgbhex;
      
}


      
std::string convertRGBtoHex(const int r,const int g,const int b) 
{
          
    int rgbNum = ((r & 0xff) << 16)
            
    | ((g & 0xff) << 8)
            
    | (b & 0xff);
          
     return convertRGBtoHex(rgbNum);
          
} */

#include <xip/system/standard.h>
#include <stdio.h>


///////////////////////////////////////////////////////////////////////////////
//
// GetNextNameValue()
//
// Purpose:     Get first/next name/value pair from registry
//
// Parameters:  key       - handle to open key, or predefined key
//              pszSubkey - subkey name
//              pszName   - pointer to buffer that receives the value string
//              pszData   - pointer to buffer that receives the data string
//
// Returns:     LONG - return code from registry function; ERROR_SUCCESS = success
//
// Notes:       If pszSubkey, pszName, and pszData are all NULL, then the open
//              handle will be closed.
//
//              The first time GetNextNameValue is called, pszSubkey should be
//              specified.  On subsequent calls, pszSubkey should be NULL or
//              an empty string.
//
static LONG GetNextNameValue(HKEY key, LPCTSTR pszSubkey, LPTSTR pszName, LPTSTR pszData)
{
	static HKEY hkey = NULL;	// registry handle, kept open between calls
	static DWORD dwIndex = 0;	// count of values returned
	LONG retval;

	// if all parameters are NULL then close key
	if (pszSubkey == NULL && pszName == NULL && pszData == NULL)
	{
		if (hkey)
			RegCloseKey(hkey);
		hkey = NULL;
		return ERROR_SUCCESS;
	}

	// if subkey is specified then open key (first time)
	if (pszSubkey && pszSubkey[0] != 0)
	{
		retval = RegOpenKeyEx(key, pszSubkey, 0, KEY_READ, &hkey);
		if (retval != ERROR_SUCCESS)
		{
			return retval;
		}
		dwIndex = 0;
	}
	else
	{
		dwIndex++;
	}

	*pszName = 0;
	*pszData = 0;

	TCHAR szValueName[MAX_PATH];
	DWORD dwValueNameSize = sizeof(szValueName)-1;
	BYTE szValueData[MAX_PATH];
	DWORD dwValueDataSize = sizeof(szValueData)-1;
	DWORD dwType = 0;

	retval = RegEnumValue(hkey, dwIndex, szValueName, &dwValueNameSize, NULL,
		&dwType, szValueData, &dwValueDataSize);
	if (retval == ERROR_SUCCESS)
	{
		lstrcpy(pszName, (LPTSTR)szValueName);
		lstrcpy(pszData, (LPTSTR)szValueData);
	}

	return retval;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFontFile()
//
// Purpose:     Find the name of font file from the font name
//
// Parameters:  lpszFontName     - name of font
//              lpszDisplayName  - pointer to buffer where font display name
//                                 will be copied
//              nDisplayNameSize - size of display name buffer in TCHARs
//              lpszFontFile     - pointer to buffer where font file name
//                                 will be copied
//              nFontFileSize    - size of font file buffer in TCHARs
//
// Returns:     BOOL - TRUE = success
//
// Notes:       This is *not* a foolproof method for finding the name of a
//              font file. If a font has been installed in a normal manner,
//              and if it is in the Windows "Font" directory, then this method
//              will probably work. It will probably work for most screen
//              fonts and TrueType fonts. However, this method might not work
//              for fonts that are created or installed dynamically, or that
//              are specific to a particular device, or that are not installed
//              into the font directory.
//
int getFontFile(const char* mbFontName,
				 char* lpszDisplayName,
				 int nDisplayNameSize,
				 char* lpszFontFile,
				 int nFontFileSize)
{
	// convert to UNICODE if needed
	#ifdef _UNICODE
	    TCHAR lpszFontName[2 * MAX_PATH];
	    wsprintf(lpszFontName, L"%hs", mbFontName);
	#else
	    LPCTSTR lpszFontName = mbFontName;
	#endif
	
	if (!lpszFontName || lpszFontName[0] == 0)
		return FALSE;

	if (!lpszDisplayName)
		return FALSE;

	if (!lpszFontFile)
		return FALSE;

	lpszDisplayName[0] = '\0';
	lpszFontFile[0] = '\0';

	TCHAR szName[2 * MAX_PATH];
	TCHAR szData[2 * MAX_PATH];

	OSVERSIONINFO osinfo;
	osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	if (!GetVersionEx(&osinfo))
		return FALSE;


	LPCTSTR szFontPath = 0;

	if (osinfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
		szFontPath = "Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";
	else
		szFontPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Fonts";

	BOOL bResult = FALSE;

	while (GetNextNameValue(HKEY_LOCAL_MACHINE, szFontPath, szName, szData) == ERROR_SUCCESS)
	{
		szName[strlen(lpszFontName)] = 0;
		if (lstrcmpi(lpszFontName, szName) == 0)
		{
			char systemDir[MAX_PATH];
			::GetWindowsDirectoryA(systemDir, MAX_PATH);

			#ifdef _UNICODE
			_snprintf(lpszDisplayName, nDisplayNameSize-1, "%S", szName);
			_snprintf(lpszFontFile, nFontFileSize-1, "%s\\Fonts\\%S", systemDir, szData);
			#else
			
			strncpy(lpszDisplayName, szName, nDisplayNameSize-1);
			//strncpy(lpszFontFile, szData, nFontFileSize-1);

			//::GetWindowsDirectory(systemDir, MAX_PATH);
			_snprintf(lpszFontFile, nFontFileSize-1, "%s\\Fonts\\%s", systemDir, szData);
            #endif
			bResult = TRUE;
			break;
		}

		szFontPath = 0;	// this will get next value, same key
	}

	GetNextNameValue(HKEY_LOCAL_MACHINE, NULL, NULL, NULL);	// close the registry key

	return bResult;
}


unsigned int convertRGBtoHex(const int r,const int g,const int b)
{

  unsigned int rgbNum = ( ((r & 0xff) << 16)

    | (( g & 0xff) << 8)

    | (( b & 0xff) ) );

  rgbNum = (rgbNum << 8) | 0xff;

 // rgbNum = 0xffff;

  return rgbNum;

  //return 0xff0000ff;
}
