#pragma once

#define WINVER 0x0500
#include <windows.h>
#undef RegisterClass

class KeyBoardImpl {
    public:
        KeyBoardImpl();
        ~KeyBoardImpl();
        void SetWindowHandle(const void* hwnd);
        void SetDelay(int delay);

        void Down(char c);
        void Up(char c);
        void Press(char c);
        void Type(const char* string);

    private:
        WORD getCode(char c);
        void SimulateKey(char c, DWORD type);
        BOOL ValidWindow();

    private:
        HWND m_hwnd;
        int m_delay;
};

