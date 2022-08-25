#pragma once

class MEM
{
public:
	uintptr_t FindDMAAddyIn(uintptr_t addr, std::vector<unsigned int> offsets);
	uintptr_t FindDMAAddyEx(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
};

extern MEM* mem;