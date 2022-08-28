#include "framework.h"
#include "addresses.h"

#include "proc.h"
#include "offsets.h"
#include "mem.h"

void Address::calcAddresses()
{
	localPlayer = unityPlayer + 0x017AB300;
	Health = mem->FindDMAAddyEx(proc->hProcess, localPlayer, offset->Health);
}

Address* addr = new Address();