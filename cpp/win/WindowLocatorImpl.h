#pragma once

#define WINVER 0x0500
#include <windows.h>
#undef RegisterClass

class WindowLocatorImpl {
    public:
        WindowLocatorImpl();
        ~WindowLocatorImpl();

        BOOL FindByTitle(const char* title);
        void BringToFront();
        BOOL HasWindow();
        void* GetWindow();

    private:
        static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

    private:
        HWND m_hwnd;
        char m_title[255];
};

