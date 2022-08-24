#pragma once

class dearImGUI
{
public:
	int width = 300, height = 500;

	void initImGui(HWND hWnd, LPDIRECT3DDEVICE9 d3ddev);
	void render();
	void cleanImGui();
};

extern dearImGUI* dearImGui;

