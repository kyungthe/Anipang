#ifndef TRACE
#include <Windows.h>
#include <strsafe.h>
#include <assert.h>
#if defined(_DEBUG) || defined(FORCE_XTRACE)
#define TRACE_BUF_SIZE 4096 
#define TRACE          _DbgPrintf
#ifndef ASSERT
#define ASSERT   assert
#endif
inline void __cdecl _DbgPrintf(LPCTSTR str, ...)
{
	TCHAR   buff[TRACE_BUF_SIZE];
	DWORD   dwError;
	va_list    ap;
	dwError = GetLastError();
	va_start(ap, str);
	StringCbVPrintf(buff, sizeof buff, str, ap);
	va_end(ap);
	OutputDebugString(buff);
	SetLastError(dwError);
}
#else
#define TRACE 1 ? (void) 0 : _DbgPrintf 
inline void _DbgPrintf(const char *str, ...) {}
#endif
#endif