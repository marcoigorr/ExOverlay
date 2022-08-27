
#include "framework.h"
#include "wnd.h" // window class
#include "d3d.h"
#include "dearImGui.h"

#include "Option.h"
#include "mem.h"
#include "proc.h"
#include "addresses.h"
#include "offsets.h"

#define procId proc->procId
#define hProcess proc->hProcess

// Forward declare message handler from imgui_impl_win32.cpp
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
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

// Entry point for any windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Get process Id of the target
	procId = proc->GetProcId(L"ULTRAKILL.exe");

	if (procId)
	{
		// Get Handle to target Process
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

		// Proc base address
		addr->moduleBase = (uintptr_t)proc->GetModuleBaseAddress64(procId);

		// UnityPlayer.dll base
 		addr->unityPlayer = (uintptr_t)proc->GetDllModule(L"UnityPlayer.dll", procId);
	}
	else
	{
		option->exit = true;
	}

	// Fullscreen transparent window creation
	if (!window->createWnd(hInstance))
		option->exit = true;

	// Display created window
	ShowWindow(window->hWnd, nCmdShow);

	// Set up and initialize Direct3D and ImGui
	D3D9->initD3D(window->hWnd);

	MSG msg;

	// Main loop
	while ((!(GetAsyncKeyState(VK_END))) && !option->exit)
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

		// Render Frame and ImGui
		D3D9->renderFrame();

		// -- Menu
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			option->bMenu = !option->bMenu;	
		}	

		// Calculate process memory addresses
		addr->calcAddresses();

		// -- GodMode
		if (option->bGodMode)
		{
			if (addr->hp)
				mem->writeMem<int>(hProcess, addr->hp, 420);
		}

		// -- SpeedHack
		if (option->bSpeedHack)
		{
			if (addr->walkSpeed)
				mem->writeMem<float>(hProcess, addr->walkSpeed, option->vWalkSpeed);
		}
		else
		{
			// set def speed
			if (addr->walkSpeed) 
				mem->writeMem<float>(hProcess, addr->walkSpeed, 750.f);
		}

		// -- Bunny Jump
		if (option->bBunnyJump)
		{
			if (addr->jumpForce)
				mem->writeMem<float>(hProcess, addr->jumpForce, option->vJumpForce);
		}
		else
		{
			// set def jumpforce
			if (addr->jumpForce)
				mem->writeMem<float>(hProcess, addr->jumpForce, 90.f);
		}

	}	

	// Close Handle
	CloseHandle(hProcess);

	// Clean ImGui
	dearImGui->cleanImGui();

	// Clean DirectX and COM
	D3D9->cleanD3D();

	// Return this part of the WM_QUIT message to Windows
	return msg.wParam;
}
