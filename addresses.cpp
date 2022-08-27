#include "framework.h"
#include "addresses.h"

#include "proc.h"
#include "offsets.h"
#include "mem.h"

void Address::calcAddresses()
{
	addr->localPlayer = addr->unityPlayer + 0x017AB300;

	// NewMovement
	addr->hp =			mem->FindDMAAddyEx(proc->hProcess, addr->localPlayer, offset->hp);
	addr->walkSpeed =	mem->FindDMAAddyEx(proc->hProcess, addr->localPlayer, offset->walkSpeed);
	addr->jumpForce =	mem->FindDMAAddyEx(proc->hProcess, addr->localPlayer, offset->jumpForce);
}

Address* addr = new Address();