#include "WindowLocatorImpl.h"

#include <stdio.h>

WindowLocatorImpl::WindowLocatorImpl() {
    m_hwnd = NULL;
    m_dwProcessId = 0;
}

WindowLocatorImpl::~WindowLocatorImpl() {
}

BOOL WindowLocatorImpl::FindByTitle(const char* title) {
    m_hwnd = NULL;
    m_dwProcessId = 0;
    strcpy(m_title, title);
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(this));
    return HasWindow();
}

BOOL WindowLocatorImpl::FindByProcessId(DWORD processId) {
    m_hwnd = NULL;
    m_dwProcessId = processId;
    strcpy(m_title, "");
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

void WindowLocatorImpl::Close() {
    if (HasWindow() == FALSE) {
        return;
    }

    ::SendMessage(m_hwnd, WM_CLOSE, NULL, NULL);
    ::SendMessage(m_hwnd, WM_QUIT, NULL, NULL);
    ::SendMessage(m_hwnd, WM_DESTROY, NULL, NULL);

    CloseHandle(m_hwnd);
    m_hwnd = NULL;
}

BOOL WindowLocatorImpl::EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    WindowLocatorImpl *pThis = reinterpret_cast<WindowLocatorImpl *>(lParam);
    char title[255];

    GetWindowText(hwnd, title, 255);
    if (strlen(title) == 0) {
        return TRUE;
    }

    if (IsWindowVisible(hwnd) == FALSE) {
        return TRUE;
    }

    DWORD dwProcessId = 0;
    GetWindowThreadProcessId(hwnd, &dwProcessId);

    BOOL continueEnum = TRUE;
    if (strlen(pThis->m_title) > 0) {
        if (strcmp(title, pThis->m_title) == 0) {
            pThis->m_hwnd = hwnd;
            continueEnum = FALSE;
        }
    } else if (pThis->m_dwProcessId > 0) {
        if (dwProcessId == pThis->m_dwProcessId) {
            pThis->m_hwnd = hwnd;
            continueEnum = FALSE;
        }
    }

    if (continueEnum == FALSE) {
        pThis->m_dwProcessId = dwProcessId;
        strcpy(pThis->m_title, title);
    }

    return continueEnum;
}