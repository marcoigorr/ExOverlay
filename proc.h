#pragma once

class Proc
{
public:
	HANDLE hProcess = 0;
	DWORD procId;

	DWORD GetProcId(const wchar_t* procName);
	DWORD_PTR GetModuleBaseAddress64(DWORD processID);
	DWORD_PTR GetDllModule(const wchar_t* module, DWORD procId);
};

extern Proc* proc;