#pragma once

#define WINVER 0x0500
#include <windows.h>
#undef RegisterClass

class WindowLocatorImpl {
    public:
        WindowLocatorImpl();
        ~WindowLocatorImpl();

        BOOL FindByTitle(const char* title);
        BOOL FindByProcessId(DWORD processId);
        void BringToFront();
        BOOL HasWindow();
        void* GetWindow();
        void Close();

    private:
        static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

    private:
        HWND m_hwnd;
        char m_title[255];
        DWORD m_dwProcessId;
};

