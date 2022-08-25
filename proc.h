#pragma once

class Proc
{
public:
	HANDLE hProcess;
	DWORD procId;

	DWORD GetProcId(const wchar_t* procName);
	DWORD_PTR GetModuleBaseAddress64(DWORD processID);
	DWORD getDllModule(LPSTR lpDllName);

	Proc() {
		this->hProcess = 0;
		this->procId = 0;
	}
};

extern Proc* proc;