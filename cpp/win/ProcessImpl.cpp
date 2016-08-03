#include "ProcessImpl.h"

ProcessImpl::ProcessImpl() {
	m_dwProcessId = 0;
}

ProcessImpl::~ProcessImpl() {
}

BOOL ProcessImpl::Open(const char* file, int wait) {
	m_dwProcessId = 0;

	SHELLEXECUTEINFO ShExecInfo;

	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = file;
	ShExecInfo.lpParameters = NULL;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOWNORMAL;
	ShExecInfo.hInstApp = NULL;

	if (::ShellExecuteEx(&ShExecInfo)) {
		::WaitForInputIdle(ShExecInfo.hProcess, INFINITE);
		m_dwProcessId = ::GetProcessId(ShExecInfo.hProcess);
        Sleep(wait);
		return (::GetLastError() == 0);
	}

	return FALSE;
}

BOOL ProcessImpl::Kill(int processId) {
    DWORD processToKill = processId;
    if (processToKill == 0) {
        processToKill = m_dwProcessId;
    }
    
    if (processToKill == 0) {
        return FALSE;
    }
    
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processToKill);
    BOOL result = TerminateProcess(processHandle, 0);
    CloseHandle(processHandle);
    if (processId == 0) {
        m_dwProcessId = 0;
    }
    return result;
}

DWORD ProcessImpl::GetProcessId() {
	return m_dwProcessId;
}
