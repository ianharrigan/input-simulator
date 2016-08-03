#include "MouseImpl.h"

#include <math.h>
#include <stdio.h>

MouseImpl::MouseImpl() {
    m_hwnd = NULL;
    m_offsetX = -1;
    m_offsetY = -1;
    m_delay = 3;
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
        m_offsetX = windowRect.left;
        m_offsetY = windowRect.top;

        RECT clientRect;
        GetClientRect(m_hwnd, &clientRect);

        int deltaX = windowCX - clientRect.right;
        int deltaY = windowCY - clientRect.bottom;

        m_offsetX += deltaX / 2;
        m_offsetY += deltaY / 2;

        // TODO: should detect if there is a windows menu and adjust based on its height - this is a hack / assumption
        m_offsetY += 25;
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
