#pragma once
#include"../../../includes/imgui/imgui.h"
#include"../../../includes/imgui/imgui_impl_dx9.h"
#include"../../../includes/imgui/imgui_impl_win32.h"
#include"../../../includes/kiero/kiero.h"
#include<d3dx9.h>
typedef BOOL(__stdcall* _RtlKeyPress)(int);
BOOL __stdcall MyRtlKeyPress(int code)
{
	auto hModule = GetModuleHandleA("user32.dll");
	_RtlKeyPress RtlKeyPress = (_RtlKeyPress)
		GetProcAddress(hModule, "GetAsyncKeyState");
	return RtlKeyPress(code);
}
typedef long(__stdcall* EndSceneFn)(LPDIRECT3DDEVICE9);
typedef HRESULT(__stdcall* ResetBufferFn)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
typedef LRESULT(__stdcall* WndProcFn)(HWND, UINT, WPARAM, LPARAM);
typedef BOOL(__stdcall* oCursorFn)(bool);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

EndSceneFn oEndScene = 0;
WndProcFn oWndProc = 0;
ResetBufferFn oResetBuffer = 0;
oCursorFn oCursor = 0;
static HWND hWindow = 0;

ImVec4 Hex(int hexValue, float alpha)
{
	float r = (hexValue >> 16) & 0xFF;
	float g = (hexValue >> 8) & 0xFF;
	float b = hexValue & 0xFF;
	return ImVec4(r / 255, g / 255, b / 255, alpha);
}

class Snow
{
public:

};

class Menu
{
private:
	std::string menu_title = "settings";
	int width = 450;
	int height = 450;
	ImFont* VerdanaSmall = nullptr;
	ImFont* TitleFont = nullptr;
public:
	bool m_bInitImGui = false;
public:
	bool m_bRenderMenu = false;
	bool m_bCloseButton = false;
	bool m_bCaptureCursor = false;
	bool m_bRenderCursor = false;
public:
	unsigned long window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
public:
	__inline void InitImGui(LPDIRECT3DDEVICE9 pDevice)
	{
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(hWindow);
		ImGui::StyleColorsDark();
		ImGui_ImplDX9_Init(pDevice);
	}
	__inline void Initialize()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::StyleColorsDark();

		style.WindowRounding = 4;
		style.ChildRounding = 4;
		style.FrameRounding = 3;
		style.PopupRounding = 3;
		style.GrabRounding = 3;
		style.TabRounding = 3;
		style.ScrollbarRounding = 3;
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.WindowTitleAlign = { 0.5f, 0.5f };
		style.FramePadding = { 6.0f, 6.0f };
		style.ItemSpacing = { 9.0f, 9.0f };
		style.WindowPadding = { 9.0f, 9.0f };
		style.ItemInnerSpacing = { 8.0f, 4.0f };
		style.WindowBorderSize = 1;
		style.FrameBorderSize = 1;
		style.ScrollbarSize = 12.f;
		style.GrabMinSize = 8.f;
		//style.WindowShadowSize = 0.f;

		//style.Colors[ImGuiCol_WindowShadow] = Hex(0xDB4141, 1.0f); // 0x5E61BA

		style.Colors[ImGuiCol_WindowBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_ChildBg] = Hex(0x151515, 1.0f);
		style.Colors[ImGuiCol_MenuBarBg] = Hex(0x191919, 1.0f);

		style.Colors[ImGuiCol_TitleBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = Hex(0x111111, 1.0f);

		style.Colors[ImGuiCol_Border] = Hex(0x00FFFF, 1.0f);
		style.Colors[ImGuiCol_Separator] = Hex(0x00FFFF, 1.0f);

		style.Colors[ImGuiCol_SliderGrab] = Hex(0x9b58ff, 1.0f);
		style.Colors[ImGuiCol_SliderGrabActive] = Hex(0x9b58ff, 0.8f);

		style.Colors[ImGuiCol_CheckMark] = Hex(0xE8E8E8, 1.0f);
		style.Colors[ImGuiCol_Text] = Hex(0xE8E8E8, 1.0f);
		style.Colors[ImGuiCol_TextDisabled] = Hex(0x616161, 1.0f);

		style.Colors[ImGuiCol_Header] = Hex(0x212121, 1.0f);
		style.Colors[ImGuiCol_HeaderHovered] = Hex(0x444444, 1.0f);
		style.Colors[ImGuiCol_HeaderActive] = Hex(0x363636, 1.0f);

		style.Colors[ImGuiCol_FrameBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = Hex(0x111111, 0.9f);
		style.Colors[ImGuiCol_FrameBgActive] = Hex(0x111111, 0.8f);

		style.Colors[ImGuiCol_Button] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_ButtonHovered] = Hex(0x00FFFF, 0.8f);
		style.Colors[ImGuiCol_ButtonActive] = Hex(0x00FFFF, 0.6f);

		style.Colors[ImGuiCol_Tab] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_TabHovered] = Hex(0x00FFFF, 0.8f);
		style.Colors[ImGuiCol_TabActive] = Hex(0x00FFFF, 0.6f);

		style.Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(0, 0, 0, 0);

		{
			const auto& io = ImGui::GetIO();
			auto FontConfig = ImFontConfig();
			FontConfig.OversampleH = 2;
			constexpr ImWchar FontRange[] = { 0x0020, 0x00FF,0x0400,0x044F,0 };
			this->VerdanaSmall = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 12.0f, &FontConfig, FontRange);
			this->TitleFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 20.0f, &FontConfig, FontRange);
			io.Fonts->Build();
		}
	}
	__inline void Tabs()
	{
		//ImGui::PushFont(this->VerdanaSmall);

		ImGui::BeginTabBar("##features");
		
		if (ImGui::BeginTabItem("Aimbot")) { ImGui::EndTabItem(); }
		if (ImGui::BeginTabItem("Visuals")) { ImGui::EndTabItem(); }
		if (ImGui::BeginTabItem("Misc")) { ImGui::EndTabItem(); }
		if (ImGui::BeginTabItem("Configs")) {ImGui::EndTabItem(); }
		
		ImGui::EndTabBar();

		//ImGui::PopFont();
	}
	__inline void Render()
	{
		ImGui::Begin(this->menu_title.c_str(), &this->m_bCloseButton, this->window_flags);
		ImGui::SetWindowSize(ImVec2(this->width, this->height));
		this->Tabs();
		ImGui::End();
	}
}; Menu pMenu;