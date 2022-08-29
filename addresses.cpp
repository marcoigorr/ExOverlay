#include "framework.h"
#include "addresses.h"

#include "proc.h"
#include "offsets.h"
#include "mem.h"

void Address::calcAddresses()
{
	localPlayer = unityPlayer + 0x017AB300;
	hp = mem->FindDMAAddyEx(proc->hProcess, localPlayer, offset->hp);
}

Address* addr = new Address();