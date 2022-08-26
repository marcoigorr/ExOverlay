#pragma once

class Proc
{
public:
	HANDLE hProcess;
	DWORD procId;

	DWORD GetProcId(const wchar_t* procName);
	DWORD_PTR GetModuleBaseAddress64(DWORD processID);
	DWORD_PTR GetDllModule(const wchar_t* module, DWORD procId);

	Proc() {
		this->hProcess = 0;
		this->procId = 0;
	}
};

extern Proc* proc;