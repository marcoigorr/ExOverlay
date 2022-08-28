#pragma once

class Direct3D
{
public:
	LPDIRECT3D9 d3d; // the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev; // the pointer to the device class
	ID3DXFont* font;

	void initD3D(HWND hWnd);
	void renderFrame(void);
	void cleanD3D(void);

	void drawText(char* label, int x, int y, int a, int r, int g, int b);
};

extern Direct3D* d3d9;
