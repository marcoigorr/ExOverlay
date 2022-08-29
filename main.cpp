#include "framework.h"

#include "wnd.h"
#include "d3d.h"
#include "dearImGui.h"

#include "options.h"

#include "mem.h"
#include "proc.h"
#include "offsets.h"
#include "addresses.h"

#define hProcess proc->hProcess

// Forward declare message handler from imgui_impl_win32.cpp
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    } break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

// Entry point for any windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Get target process Id
    proc->procId = proc->GetProcId(L"ULTRAKILL.exe");

    if (proc->procId)
    {
        // Get handle to process
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, proc->procId);

        /* Get Modules base address */

        addr->moduleBase = proc->GetModuleBase(L"ULTRAKILL.exe", proc->procId);

        addr->unityPlayer = proc->GetModuleBase(L"UnityPlayer.dll", proc->procId);
    }

    // Fullscreen transparent window creation
    window->CreateWnd(hInstance);

    // Display created window
    ShowWindow(window->hWnd, nCmdShow);

    // Set up and initialize Direct3D and ImGui
    d3d9->initD3D(window->hWnd);

    MSG msg;

    // Main loop
    while (!(GetAsyncKeyState(VK_END)))
    {
        // Check to see if any messages are waiting in the queue
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
            break;

        // Render frame and ImGui
        d3d9->renderFrame();

        // -- Menu
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            option->bMenu = !option->bMenu;
        }

        // Calculate target addresses
        addr->calcAddresses();

        // -- God Mode
        if (option->bGodMode)
        {
            if (addr->hp) 
                mem->writeMem<int>(hProcess, addr->hp, 420);
        }
    }

    // Clean ImGui
    dearImGui->cleanImGui();

    // Clean DirectX and COM
    d3d9->cleanD3D();

    // Return this part of the WM_QUIT message to Windows
    return msg.wParam;
}
