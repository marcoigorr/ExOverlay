#pragma once

class Proc
{
public:
	HANDLE hProcess = 0;
	DWORD procId;

	DWORD GetProcId(const wchar_t* procName);
	DWORD_PTR GetModuleBaseAddress64(DWORD procId);
	DWORD_PTR GetModuleBase(const wchar_t* module, DWORD procId);
};

extern Proc* proc;