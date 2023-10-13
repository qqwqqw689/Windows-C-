#include <windows.h>
// windows.h is the main header file for WinAPI.
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#define BUFSIZE 4096

//  _tmain, a preprocessor macro defined in tchar.h.
//  _tmain resolves to main unless _UNICODE is defined.
//  In that case, _tmain resolves to wmain. 
int _tmain()
{
    TCHAR chNewEnv[BUFSIZE];
    // TCHAR
    // MAPI(Messaging Application Programming Interface)
    // clients can use the TCHAR data type to represent
    // a string of either the WCHAR or char type.
    LPTSTR lpszCurrentVariable;
    // LPTSTR
    // An LPWSTR if UNICODE is defined, an LPSTR otherwise. 
    // LPWSTR
    // A pointer to a null-terminated string of 16-bit Unicode characters.
    // LPSTR
    // A pointer to a null-terminated string of 8-bit Windows (ANSI)
    DWORD dwFlags = 0;
    // DWORD
    // A 32-bit unsigned integer. 
    TCHAR szAppName[] = TEXT("ex3.exe");
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    BOOL fSuccess;

    // Copy environment strings into an environment block. 

    lpszCurrentVariable = (LPTSTR)chNewEnv;
    if (FAILED(StringCchCopy(lpszCurrentVariable, BUFSIZE, TEXT("MySetting=A"))))
    {
        printf("String copy failed\n");
        return FALSE;
    }

    lpszCurrentVariable += lstrlen(lpszCurrentVariable) + 1;
    if (FAILED(StringCchCopy(lpszCurrentVariable, BUFSIZE, TEXT("MyVersion=2"))))
    {
        printf("String copy failed\n");
        return FALSE;
    }

    // Terminate the block with a NULL byte. 

    lpszCurrentVariable += lstrlen(lpszCurrentVariable) + 1;
    *lpszCurrentVariable = (TCHAR)0;

    // Create the child process, specifying a new environment block. 

    SecureZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

#ifdef UNICODE
    dwFlags = CREATE_UNICODE_ENVIRONMENT;
#endif

    fSuccess = CreateProcess(szAppName, NULL, NULL, NULL, TRUE, dwFlags,
        (LPVOID)chNewEnv,   // new environment block
        NULL, &si, &pi);

    if (!fSuccess)
    {
        printf("CreateProcess failed (%d)\n", GetLastError());
        return FALSE;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    return TRUE;
}
