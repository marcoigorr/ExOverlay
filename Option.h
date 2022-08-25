#pragma once

class Option
{
public:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	void GetDesktopResolution(int& horizontal, int& vertical);

	bool bMenu;	
	bool bGodMode;

	// Constructor
	Option() {
		this->bMenu =		true;
		this->bGodMode =	false;

		GetDesktopResolution(this->SCREEN_WIDTH, this->SCREEN_HEIGHT);
	}
};

extern Option* option;

