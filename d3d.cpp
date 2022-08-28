#include "framework.h"
#include "d3d.h"

#include "wnd.h"
#include "dearImGui.h"

#include "options.h"

void Direct3D::initD3D(HWND hWnd)
{
    // Create Direct3D interface
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    // Create a struct to hold various device info
    D3DPRESENT_PARAMETERS d3dpp;

    // Clear struct for use
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;       // discard old frames
    d3dpp.hDeviceWindow = hWnd;                     // set the window to be used by Direct3D
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;       // set the back buffer format to 32-bit
    d3dpp.BackBufferWidth = window->SCREEN_WIDTH;   // set the width of the buffer
    d3dpp.BackBufferHeight = window->SCREEN_HEIGHT; // set the height of the buffer


    // Create a device class using this information and information from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3ddev);

    // Font creation
    D3DXCreateFont(d3ddev, 20, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Comic Sans", &font);

    // Setup ImGui
    dearImGui->initImGui();
}

void Direct3D::renderFrame(void)
{
    // Clear the window to black
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.f, 0);

    // Begin d3d scene
    d3ddev->BeginScene();

    /* 3D rendering on the back buffer here */

    drawText((char*)"ExOverlay - marcoigorr", 110, window->SCREEN_HEIGHT - 100, 255, 255, 255, 255);

    // End d3d scene
    d3ddev->EndScene();

    // Dear ImGUI frame
    if (option->bMenu)
        dearImGui->renderImGui();

    // Display created frame
    d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Direct3D::cleanD3D(void)
{
    d3ddev->Release();
    d3d->Release();
}

void Direct3D::drawText(char* label, int x, int y, int a, int r, int g, int b)
{
    RECT rect;
    rect.top = y;
    rect.left = x;
    font->DrawTextA(0, label, strlen(label), &rect, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
}

Direct3D* d3d9 = new Direct3D();
