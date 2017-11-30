#include "stdafx.h"
#include <dbghelp.h>
#include "DumpUtil.h"

using namespace std;

#pragma comment(lib, "Dbghelp.lib")

wstring CDumpUtil::m_strDumpFilePath;

void CDumpUtil::SetDumpFilePath(const wchar_t* szDumpFilePath)
{
    m_strDumpFilePath = szDumpFilePath;
}

long __stdcall CDumpUtil::UnhandledExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionInfo)
{
    HANDLE hFile = CreateFile(m_strDumpFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        exit(1);
        return EXCEPTION_EXECUTE_HANDLER;
    }

    MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
    exceptionInfo.ThreadId = GetCurrentThreadId();
    exceptionInfo.ExceptionPointers = pExceptionInfo;
    exceptionInfo.ClientPointers = TRUE;

    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &exceptionInfo, nullptr, nullptr);
    CloseHandle(hFile);

    exit(1);
    return EXCEPTION_EXECUTE_HANDLER;
}

void CDumpUtil::Enable(bool bEnable)
{
    if (bEnable)
    {
        ::SetUnhandledExceptionFilter(UnhandledExceptionFilter);
    }
    else
    {
        ::SetUnhandledExceptionFilter(nullptr);
    }
}