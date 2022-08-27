#include "framework.h"
#include "dearImGUI.h"

#include "Option.h"
#include "mem.h"
#include "proc.h"
#include "addresses.h"


void dearImGUI::initImGui(HWND hWnd, LPDIRECT3DDEVICE9 d3ddev)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;
	io.WantSaveIniSettings = false;

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowMinSize = ImVec2(dearImGui->width, dearImGui->height);
	style.WindowTitleAlign = ImVec2(0.50f, 0.50f); // Title
	style.WindowPadding = ImVec2(20.0f, 20.0f);
	style.WindowRounding = 9.0f;
	style.FrameRounding = 12.0f;
	style.FramePadding = ImVec2(17.0f, 4.0f);
	style.TabRounding = 9.0f;
	style.GrabRounding = 10.0f;
	style.GrabMinSize = 15.0f;
	style.ScrollbarSize = 17.0f;
	style.ItemSpacing = ImVec2(13.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(10.0f, 8.0f);

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(d3ddev);
}

void dearImGUI::render()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Menu
	ImGui::Begin("ExOverlay");

	dearImGui->AddCheckBox("God Mode", &option->bGodMode);

	dearImGui->AddCheckBox("Speed Hack", &option->bSpeedHack);
	if (option->bSpeedHack)
	{
		dearImGui->AddSlider<float>("walkSpeed", &option->vWalkSpeed, 750.f, 1337.f);
	}

	dearImGui->AddCheckBox("Bunny Jump", &option->bBunnyJump);
	if (option->bBunnyJump)
	{
		dearImGui->AddSlider<float>("jumpForce", &option->vJumpForce, 90.f, 200.f);
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void dearImGUI::cleanImGui()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void dearImGUI::AddCheckBox(const char* title, bool* var)
{
	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 10, ImGui::GetCursorPos().y + 15));
	ImGui::Checkbox(title, var);
}

bool dearImGUI::AddButton(const char* title)
{
	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 10, ImGui::GetCursorPos().y + 15));
	return ImGui::Button(title, ImVec2(110.0f, 30.0f));
}

template <typename T>
void dearImGUI::AddSlider(const char* label, T* value, T v_min, T v_max)
{
	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 15, ImGui::GetCursorPosY() + 8));

	if constexpr (std::is_integral_v<T>)
	{
		ImGui::SliderInt(label, value, v_min, v_max);
	}

	if constexpr (std::is_floating_point_v<T>)
	{
		ImGui::SliderFloat(label, value, v_min, v_max);
	}
}


dearImGUI* dearImGui = new dearImGUI();
