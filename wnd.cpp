#include "framework.h"
#include "wnd.h"

// Forward declaration of WndProc in main.cpp
extern LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void wnd::CreateWnd(HINSTANCE hInstance)
{
    WNDCLASSEX wc;

    // Clearing window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // Filling needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wc.lpszClassName = L"WindowClass";

    // Register window class
    RegisterClassEx(&wc);

    // Create the window and use the result as the handle
    window->hWnd = CreateWindowEx(
        WS_EX_LAYERED,
        L"WindowClass",
        L"ExOverlay",
        WS_POPUP | WS_EX_TOPMOST,    // fullscreen values
        0, 0,    // the starting x and y positions should be 0
        window->SCREEN_WIDTH, window->SCREEN_HEIGHT,    // set the window to 640 x 480
        NULL,
        NULL,
        hInstance,
        NULL);

    // Set the opacity and transparency color key
    SetLayeredWindowAttributes(window->hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
}

void wnd::GetDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
}

wnd* window = new wnd();
