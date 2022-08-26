#pragma once

class Window
{
public:
	WCHAR overlayTitle[50] = L"ExOverlay"; // Window Title 
	HWND hWnd;		// Handle for the window
	WNDCLASSEX wc;	// Struct that holds info for the window class

	bool createWnd(HINSTANCE hInstance);
};

extern Window* window;
