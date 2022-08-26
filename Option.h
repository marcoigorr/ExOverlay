#pragma once

class Option
{
public:
	bool exit = false;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	void GetDesktopResolution(int& horizontal, int& vertical);

	bool bMenu = true;	
	bool bGodMode = false;

	// Constructor
	Option() {
		GetDesktopResolution(this->SCREEN_WIDTH, this->SCREEN_HEIGHT);
	}
};

extern Option* option;

