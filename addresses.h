#pragma once

class Address
{
public:
	uintptr_t moduleBase;
	uintptr_t unityPlayer;
	uintptr_t localPlayer;

	// NewMovement
	uintptr_t hp;
	uintptr_t walkSpeed;
	uintptr_t jumpForce;

	void calcAddresses();
};

extern Address* addr;
