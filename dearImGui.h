#pragma once

class dearImGUI
{
private:
	void AddCheckBox(const char* title, bool* var);
	bool AddButton(const char* title);
	template <typename T>
	void AddSlider(const char* label, T* value, T v_min, T v_max);

public:
	int width = 450;
	int height = 600;

	void initImGui(HWND hWnd, LPDIRECT3DDEVICE9 d3ddev);
	void render();
	void cleanImGui();
};

extern dearImGUI* dearImGui;

