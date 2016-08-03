#include "MouseImpl.h"

#include <math.h>
#include <stdio.h>

MouseImpl::MouseImpl() {
    m_hwnd = NULL;
    m_offsetX = -1;
    m_offsetY = -1;
    m_delay = 3;
    m_userOffsetY = 0;
}

MouseImpl::~MouseImpl() {
}

void MouseImpl::SetWindowHandle(const void* hwnd) {
    m_hwnd = (HWND) hwnd;
}

void MouseImpl::SetDelay(int delay) {
    m_delay = delay;
}

void MouseImpl::Up(int x, int y) {
    SimulateMouse(x, y, MOUSEEVENTF_LEFTUP);
}

void MouseImpl::Down(int x, int y) {
    SimulateMouse(x, y, MOUSEEVENTF_LEFTDOWN);
}

void MouseImpl::Move(int x, int y) {
    SimulateMouse(x, y, MOUSEEVENTF_MOVE);
}

void MouseImpl::Click(int x, int y) {
    Move(x, y);
    Down(x, y);
    Up(x, y);
}

void MouseImpl::Stroke(int fromX, int fromY, int toX, int toY) {
    Move(fromX, fromY);
    Down(fromX, fromY);

    double deltaX = toX - fromX;
    double deltaY = toY - fromY;

    double max = fabs(deltaX);
    if (fabs(deltaY) > max) {
        max = fabs(deltaY);
    }

    double x = fromX;
    double y = fromY;

    for (int i = 0; i < max; i++) {
        x += deltaX / max;
        y += deltaY / max;

        Move((int) x, (int) y);
    }

    Up((int) x, (int) y);
}

void MouseImpl::CalcOffset() {
    if (m_hwnd != NULL) {
        RECT windowRect;
        GetWindowRect(m_hwnd, &windowRect);
        int windowCX = windowRect.right - windowRect.left;
        int windowCY = windowRect.bottom - windowRect.top;
        
        //printf("WINDOW RECT: top=%d, left=%d, bottom=%d, right=%d\n", windowRect.top, windowRect.left, windowRect.bottom, windowRect.right);
        
        m_offsetX = windowRect.left;
        m_offsetY = windowRect.top;

        RECT clientRect;
        GetClientRect(m_hwnd, &clientRect);
        //printf("CLIENT RECT: top=%d, left=%d, bottom=%d, right=%d\n", clientRect.top, clientRect.left, clientRect.bottom, clientRect.right);

        int deltaX = windowCX - clientRect.right;
        int deltaY = windowCY - clientRect.bottom;

        /*
        m_offsetX += deltaX;
        m_offsetY += deltaY;
        */
        m_offsetX += GetSystemMetrics(SM_CXSIZEFRAME);
        m_offsetY += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYSIZEFRAME);

        m_offsetY += GetMenuHeight();
        m_offsetY += m_userOffsetY;
    }
}

void MouseImpl::SimulateMouse(int x, int y, DWORD type) {
    if (ValidWindow() == TRUE) {
        CalcOffset();

        x += m_offsetX;
        y += m_offsetY;

        double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
        double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
        double fx = x*(65535.0f / fScreenWidth);
        double fy = y*(65535.0f / fScreenHeight);
        INPUT Input = { 0 };
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = type | MOUSEEVENTF_ABSOLUTE;
        Input.mi.dx = (LONG)fx;
        Input.mi.dy = (LONG)fy;
        ::SendInput(1, &Input, sizeof(INPUT));

        Sleep(m_delay);
    }
}

BOOL MouseImpl::ValidWindow() {
    if (m_hwnd == NULL) {
        return FALSE;
    }

    return IsWindow(m_hwnd);
}

int MouseImpl::GetMenuHeight() {
    if (ValidWindow() == FALSE) {
        return 0;
    }
    int cy = 0;
    HMENU m = GetMenu(m_hwnd);
    if (m != NULL) {
        cy = GetSystemMetrics(SM_CYMENU);
    }
    return cy;
}

void MouseImpl::SetOffsetY(int offset) {
    m_userOffsetY = offset;
}