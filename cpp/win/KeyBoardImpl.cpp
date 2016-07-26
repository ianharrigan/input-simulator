#include "KeyBoardImpl.h"

KeyBoardImpl::KeyBoardImpl() {
    m_hwnd = NULL;
    m_delay = 25;
}

KeyBoardImpl::~KeyBoardImpl() {
}

void KeyBoardImpl::SetWindowHandle(const void* hwnd) {
    m_hwnd = (HWND) hwnd;
}

void KeyBoardImpl::SetDelay(int delay) {
    m_delay = delay;
}

void KeyBoardImpl::Down(char c) {
    SimulateKey(c, 0);
}

void KeyBoardImpl::Up(char c) {
    SimulateKey(c, KEYEVENTF_KEYUP);
}

void KeyBoardImpl::Press(char c) {
    Down(c);
    Up(c);
}

void KeyBoardImpl::Type(const char* string) {
    for (int i = 0; i < strlen(string); i++) {
        char c = string[i];
        switch (c) {
        default:
            Press(c);
            break;
        }
    }
}

WORD KeyBoardImpl::getCode(char c) {
    if (c == VK_CONTROL || c == VK_DELETE) {
        return c;
    }
    HKL currentKBL = GetKeyboardLayout(0);
    return VkKeyScanEx(c, currentKBL);
}

void KeyBoardImpl::SimulateKey(char c, DWORD type) {
    if (ValidWindow() == TRUE) {
        INPUT ip;

        // Set up a generic keyboard event.
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0; // hardware scan code for key
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        // Press the key
        ip.ki.wVk = getCode(c); // virtual-key code
        ip.ki.dwFlags = type;
        SendInput(1, &ip, sizeof(INPUT));

        Sleep(m_delay);
    }
}

BOOL KeyBoardImpl::ValidWindow() {
    if (m_hwnd == NULL) {
        return FALSE;
    }

    return IsWindow(m_hwnd);
}
