#include "WindowLocatorImpl.h"

#include <stdio.h>

WindowLocatorImpl::WindowLocatorImpl() {
    m_hwnd = NULL;
}

WindowLocatorImpl::~WindowLocatorImpl() {
}

BOOL WindowLocatorImpl::FindByTitle(const char* title) {
    m_hwnd = NULL;
    strcpy(m_title, title);
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(this));
    return HasWindow();
}

void WindowLocatorImpl::BringToFront() {
    if (m_hwnd != NULL) {
        ::SetForegroundWindow(m_hwnd);
    }
}

BOOL WindowLocatorImpl::HasWindow() {
    return (m_hwnd != NULL);
}

void* WindowLocatorImpl::GetWindow() {
    return m_hwnd;
}

BOOL WindowLocatorImpl::EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    WindowLocatorImpl *pThis = reinterpret_cast<WindowLocatorImpl *>(lParam);
    char title[255];

    GetWindowText(hwnd, title, 255);
    if (strlen(title) == 0) {
        return true;
    }

    if (strcmp(title, pThis->m_title) == 0) {
        pThis->m_hwnd = hwnd;
        return false;
    }

    return true;
}