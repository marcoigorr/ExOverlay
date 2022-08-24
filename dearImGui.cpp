#include "framework.h"
#include "dearImGUI.h"


void dearImGUI::initImGui(HWND hWnd, LPDIRECT3DDEVICE9 d3ddev)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(d3ddev);
}

void dearImGUI::render()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowSize({ 300,  500 });

	// Menu
	ImGui::Begin("ExOverlay");
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

dearImGUI* dearImGui = new dearImGUI();
