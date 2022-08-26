#include "framework.h"
#include "proc.h"

DWORD Proc::GetProcId(const wchar_t* procName)
{
	DWORD procId = 0;

	// Get Process snapshot
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		// Struct that contains process information
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(PROCESSENTRY32);

		if (!Process32First(hSnap, &procEntry))
		{
			return procId;
		}

		while (Process32Next(hSnap, &procEntry))
		{
			if (!_wcsicmp(procEntry.szExeFile, procName))
			{
				procId = procEntry.th32ProcessID;
				break;
			}
		}
	}
	CloseHandle(hSnap);
	return procId;
}

DWORD_PTR Proc::GetModuleBaseAddress64(DWORD processID)
{
	DWORD_PTR   baseAddress = 0;
	HANDLE      hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	HMODULE*	moduleArray;
	LPBYTE      moduleArrayBytes;
	DWORD       bytesRequired;

	if (hProc)
	{
		if (EnumProcessModules(hProc, NULL, 0, &bytesRequired))
		{
			if (bytesRequired)
			{
				moduleArrayBytes = (LPBYTE)LocalAlloc(LPTR, bytesRequired);

				if (moduleArrayBytes)
				{
					unsigned int moduleCount;

					moduleCount = bytesRequired / sizeof(HMODULE);
					moduleArray = (HMODULE*)moduleArrayBytes;

					if (EnumProcessModules(hProc, moduleArray, bytesRequired, &bytesRequired))
					{
						baseAddress = (DWORD_PTR)moduleArray[0];
					}

					LocalFree(moduleArrayBytes);
				}
			}
		}

		CloseHandle(hProc);
	}

	return baseAddress;
}

DWORD Proc::GetDllModule(const wchar_t* module, DWORD procId)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procId);

	if (hSnap == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	MODULEENTRY32 modEntry;
	modEntry.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(hSnap, &modEntry))
	{	
		return 0;
	}

	if (!_wcsicmp(modEntry.szModule, module))
		return (DWORD)modEntry.modBaseAddr;

	while (Module32Next(hSnap, &modEntry))
	{
		if (!_wcsicmp(modEntry.szModule, module))
			return (DWORD)modEntry.modBaseAddr;
	}

}

Proc* proc = new Proc();