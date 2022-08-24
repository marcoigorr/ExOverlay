#include "framework.h"
#include "dearImGUI.h"


void dearImGUI::initImGui(HWND hWnd, LPDIRECT3DDEVICE9 d3ddev)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
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
