#pragma once

class Option
{
public:
	bool exit = false;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	void GetDesktopResolution(int& horizontal, int& vertical);

	bool bMenu = true;	
	bool bGodMode = false, bSpeedHack = false, bBunnyJump = false;
	float vWalkSpeed = 750.f, vJumpForce = 90.f;

	// Constructor
	Option() {
		GetDesktopResolution(this->SCREEN_WIDTH, this->SCREEN_HEIGHT);
	}
};

extern Option* option;

