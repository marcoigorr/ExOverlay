#pragma once

class DIG
{
private:
	// ImGui Menu creation
	void AddCheckBox(const char* title, bool* var);
	bool AddButton(const char* title);
	template <typename T>
	void AddSlider(const char* label, T* value, T v_min, T v_max);

public:
	// ImGui Settings
	int width = 400;
	int height = 600;

	void initImGui();
	void renderImGui();
	void cleanImGui();
};

extern DIG* dearImGui;

