#pragma once

class Direct3D9
{
public:
	// global declarations
	LPDIRECT3D9 d3d;			// the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;   // the pointer to the device class

	// function prototypes
	void initD3D(HWND hWnd);    // sets up and initializes Direct3D
	void renderFrame(void);		// renders a single frame
	void cleanD3D(void);		// closes Direct3D and releases memory
};

extern Direct3D9* D3D9;


