#include <iostream>
#include <Windows.h>
#include <urlmon.h>
#include <wininet.h>
#include <iomanip>
#include <tchar.h>
#include <winerror.h>
//#include "hark.h"
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")
using namespace std;
#ifdef _UNICODE
#define tcout wcout
#else
#define tcout cout
#endif
int main()
{
    const TCHAR url[] = _T("\
https://raw.gitmirror.com/China-hjz/BadMouse/master/versions.json\
");
    const TCHAR filePath[] = _T("versions.json");
    DeleteUrlCacheEntry(url);
    HRESULT r = URLDownloadToFileW(NULL, url, filePath, 0, NULL);
    if (SUCCEEDED(r))
    {
        tcout << _T("Downloaded OK") << endl;
    }
    else
    {
        tcout << _T("An error occured : error code = 0x") << hex << r << endl;
    }

    return 0;
}