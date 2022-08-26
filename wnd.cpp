#include "framework.h"
#include "wnd.h"

#include "Option.h"

#define wc window->wc


// forward declaration of WndProc in main.cpp
extern LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool Window::createWnd(HINSTANCE hInstance)
{
	// Clearing window class for use
	ZeroMemory(&wc, sizeof(wc));

	// Filling needed information
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.lpszMenuName = overlayTitle;
	wc.lpszClassName = overlayTitle;
	wc.hIconSm = 0;

	// Register window class
	RegisterClassExW(&wc);

	// Create the window and use the result as the handle
	window->hWnd = CreateWindowEx(
		WS_EX_LAYERED,
		window->overlayTitle,    // name of the window class
		window->overlayTitle,   // title of the window
		WS_POPUP | WS_EX_TOPMOST,    // window style
		0,    // x-position of the window
		0,    // y-position of the window
		option->SCREEN_WIDTH,    // width of the window
		option->SCREEN_HEIGHT,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	if (!window->hWnd)
		return FALSE;

	// Set the opacity and transparency color key
	SetLayeredWindowAttributes(window->hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

	return TRUE;
}

Window* window = new Window();