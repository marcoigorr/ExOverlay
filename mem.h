#pragma once

class MEM
{
public:
	uintptr_t FindDMAAddyIn(uintptr_t addr, std::vector<unsigned int> offsets);
	uintptr_t FindDMAAddyEx(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);

	template <class T>
	T readMem(HANDLE hProcess, uintptr_t address)
	{
		T x;
		ReadProcessMemory(hProcess, (BYTE*)address, &x, sizeof(x), nullptr);
		return x;
	}

	template <class T>
	T writeMem(HANDLE hProcess, uintptr_t address, T value)
	{
		WriteProcessMemory(hProcess, (BYTE*)address, &value, sizeof(value), nullptr);
		return value;
	}
};

extern MEM* mem;