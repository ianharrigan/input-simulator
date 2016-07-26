#pragma once

#define WINVER 0x0500
#include <windows.h>
#undef RegisterClass

class WindowLocatorImpl {
	public:
		WindowLocatorImpl();
		~WindowLocatorImpl();

		void* FindByTitle(const char* title);
		void BringToFront();

	private:
		static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

	private:
		HWND m_hwnd;
		char m_title[255];
};

