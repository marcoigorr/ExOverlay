#pragma once

class wnd
{
public:
	HWND hWnd; // Handle for the window

	int SCREEN_WIDTH = 1920;
	int SCREEN_HEIGHT = 1080;

	void CreateWnd(HINSTANCE hInstance);
	void GetDesktopResolution(int& horizontal, int& vertical);

	wnd()
	{
		GetDesktopResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
};

extern wnd* window;
