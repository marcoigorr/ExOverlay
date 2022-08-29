#pragma once

class Address
{
public:
	uintptr_t moduleBase;
	uintptr_t unityPlayer;
	uintptr_t localPlayer;

	uintptr_t hp;

	void calcAddresses();
};

extern Address* addr;
