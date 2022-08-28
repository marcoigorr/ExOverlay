#pragma once

class Address
{
public:
	uintptr_t moduleBase;
	uintptr_t unityPlayer;
	uintptr_t localPlayer;

	uintptr_t Health;

	void calcAddresses();
};

extern Address* addr;
