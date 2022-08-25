#include "framework.h"
#include "mem.h"

uintptr_t MEM::FindDMAAddyIn(uintptr_t addr, std::vector<unsigned int> offsets)
{
	uintptr_t cAddr = addr;
	for (unsigned int i = 0; i < offsets.size(); i++)
	{
		cAddr = *(uintptr_t*)cAddr;

		// Check if memory is writable (not ?? in cheatengine)
		if (IsBadReadPtr((uintptr_t*)cAddr, sizeof(cAddr)))
			return 0;

		cAddr += offsets[i];
	}
	return cAddr;
}

uintptr_t MEM::FindDMAAddyEx(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}

MEM* mem = new MEM();