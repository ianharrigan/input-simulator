#pragma once

#define WINVER 0x0500
#include <windows.h>
#undef RegisterClass

class MouseImpl {
    public:
        MouseImpl();
        ~MouseImpl();
        void SetWindowHandle(const void* hwnd);
        void SetDelay(int delay);

        void Up(int x, int y);
        void Down(int x, int y);
        void Move(int x, int y);
        void Click(int x, int y);
        void Stroke(int fromX, int fromY, int toX, int toY);
        void SetOffsetY(int offset);

    private:
        void CalcOffset();
        void SimulateMouse(int x, int y, DWORD type);
        BOOL ValidWindow();
        int GetMenuHeight();

    private:
        HWND m_hwnd;
        int m_offsetX;
        int m_offsetY;
        int m_delay;

        int m_userOffsetY;
};
