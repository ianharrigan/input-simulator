#pragma once

#define WINVER 0x0500
#include <windows.h>
#undef RegisterClass

class ProcessImpl {
    public:
        ProcessImpl();
        ~ProcessImpl();

        BOOL Open(const char* file, int wait = 0);
        BOOL Kill(int processId = 0);
        DWORD GetProcessId();
    private:
        DWORD m_dwProcessId;
};

