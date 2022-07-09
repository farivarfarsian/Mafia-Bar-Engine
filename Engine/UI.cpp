#include "UI.h"

MafiaBar::Engine::UI::UI() 
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
}

MafiaBar::Engine::UI::~UI()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void MafiaBar::Engine::UI::Initialize(HWND Handle, ID3D11Device* Device, ID3D11DeviceContext* Context, bool LightMode)
{
#if IS_DEBUG
	assert(Device != nullptr);
	assert(Context != nullptr);
#endif

	//Enabling Docking And Keyboard and Gamepad Controls
	ImGuiIO& IO = ImGui::GetIO();
	IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	IO.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	if (LightMode == true)
	{
		ImGui::StyleColorsLight();
	}
	else
	{
		ImGui::StyleColorsDark();
	}

	//Setting the Custom Style for UI
	ImGuiStyle& Style = ImGui::GetStyle();
	Style.WindowRounding = 10.0f;
	Style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	Style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	Style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	Style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

	ImGui_ImplWin32_Init(Handle);
	ImGui_ImplDX11_Init(Device, Context);

	//Setting the default Font
	//ImGui::GetIO().Fonts->AddFontFromFileTTF("Engine Content/Fonts/Roboto-Regular.ttf", 14.0f);
}

void MafiaBar::Engine::UI::NewFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void MafiaBar::Engine::UI::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
