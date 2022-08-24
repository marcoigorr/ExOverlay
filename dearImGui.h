#pragma once

class dearImGUI
{
public:
	int width = 300;
	int height = 500;

	void initImGui(HWND hWnd, LPDIRECT3DDEVICE9 d3ddev);
	void render();
	void cleanImGui();
};

extern dearImGUI* dearImGui;

