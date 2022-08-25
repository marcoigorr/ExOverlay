#pragma once

class Address
{
public:
	uintptr_t moduleBase;
	uintptr_t unityPlayer;

	uintptr_t NextMovement;
	uintptr_t Health;

	void calcAddresses();
};

extern Address* addr;
