#pragma once

class dearImGUI
{
public:
	void initImGui(HWND hWnd, LPDIRECT3DDEVICE9 d3ddev);
	void render();
	void cleanImGui();
};

extern dearImGUI* dearImGui;

