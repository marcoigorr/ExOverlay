#include "framework.h"
#include "addresses.h"

#include "proc.h"
#include "offsets.h"
#include "mem.h"

void Address::calcAddresses()
{
	addr->NextMovement = addr->unityPlayer + 0x017AB300;
	addr->Health = mem->FindDMAAddyEx(proc->hProcess, addr->NextMovement, offset->Health);
}

Address* addr = new Address();