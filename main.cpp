
#include "framework.h"
#include "d3d.h"
#include "Option.h"
#include "dearImGui.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Entry point for any windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Title
	WCHAR overlayTitle[50] = L"ExOverlay";

	// Handle for the window
	HWND hWnd;
	// Struct that holds info for the window class
	WNDCLASSEX wc;

	// Clearing window class for use
	ZeroMemory(&wc, sizeof(wc));

	// Filling needed information
	wc.cbSize =			sizeof(wc);
	wc.style =			CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc =	WndProc;
	wc.cbClsExtra =		0;
	wc.cbWndExtra =		0;
	wc.hInstance =		hInstance;
	wc.hIcon =			0;
	wc.hCursor =		LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground =	CreateSolidBrush(RGB(0,0,0));
	wc.lpszMenuName =	overlayTitle;
	wc.lpszClassName =	overlayTitle;
	wc.hIconSm =		0;

	// Register window class
	RegisterClassExW(&wc);

	// Create the window and use the result as the handle
	hWnd = CreateWindowEx(
		WS_EX_LAYERED,
		overlayTitle,    // name of the window class
		overlayTitle,   // title of the window
		WS_POPUP | WS_EX_TOPMOST,    // window style
		0,    // x-position of the window
		0,    // y-position of the window
		SCREEN_WIDTH,    // width of the window
		SCREEN_HEIGHT,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	if (!hWnd) 
		return FALSE;

	// Set the opacity and transparency color key
	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

	// Display window
	ShowWindow(hWnd, nCmdShow);

	// Set up and initialize Direct3D
	D3D9->initD3D(hWnd);

	MSG msg;

	// Infinite loop
	while (!(GetAsyncKeyState(VK_END)))
	{
		// Check to see if any messages are waiting in the queue
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		// If the message is WM_QUIT, exit the while loop
		if (msg.message == WM_QUIT)
			break;

		// Render Frame
		D3D9->renderFrame();

		// -- Menu
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			option->bMenu = !option->bMenu;	
		}		
	}	

	// Clean ImGui
	dearImGui->cleanImGui();

	// Clean DirectX and COM
	D3D9->cleanD3D();

	// Return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

// Forward declare message handler from imgui_impl_win32.cpp
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
// Main message handler
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
		case WM_DESTROY:
		{
			// Close the application, send WM_QUIT (0) 
			PostQuitMessage(0);
			return 0;
		} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
