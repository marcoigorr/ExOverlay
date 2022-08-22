#include "framework.h"
#include "d3d.h"

void Direct3D9::initD3D(HWND hWnd)
{
	// Create Direct3D interface
	D3D9->d3d = Direct3DCreate9(D3D_SDK_VERSION);

	// Create a struct to hold various device info
	D3DPRESENT_PARAMETERS d3dpp;

	// Clear struct for use
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // Discard old frames
	d3dpp.hDeviceWindow = hWnd; // Window used by Direct3D
		
	// Create a device class using this information and information from the d3dpp stuct
	D3D9->d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&D3D9->d3ddev);

}

void Direct3D9::renderFrame(void)
{
	// Clear the window to a deep blue
	D3D9->d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.f, 0);

	// Begin d3d scene
	D3D9->d3ddev->BeginScene();

	// 3D rendering on the back buffer here

	// End d3d scene
	D3D9->d3ddev->EndScene();

	// Display created frame
	D3D9->d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Direct3D9::cleanD3D(void)
{
	D3D9->d3ddev->Release();
	D3D9->d3d->Release();
}

Direct3D9* D3D9 = new Direct3D9();
