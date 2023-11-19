#pragma once
#include"imgui/imgui.h"
#include"imgui/imgui_impl_dx9.h"
#include"imgui/imgui_impl_win32.h"

#include<string>
#include<vector>

#include"dx9/dx9.hpp"
#include"key/key.hpp"

static HWND hWindow = 0;

class COverlayGlobals {
public:
	std::string window_title = "lmaobox.net";
	int width = 40;
	int height = 100;
public:
	bool close_button = false;
	unsigned long window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	bool init_imgui = false;
	bool call_overlay = false;
public:
	enum class menuTabs {
		Visuals,
		Misc,
		Config
	};
};

class COverlay : public COverlayGlobals {
public:
	__declspec(dllexport) void menu_tabs(menuTabs tabs) {
		switch (tabs) {
		case menuTabs::Visuals:
			break;
		case menuTabs::Misc:
			break;
		case menuTabs::Config:
			break;
		}
	}
public:
	__declspec(dllexport) void init_device(LPDIRECT3DDEVICE9 pDevice) {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplDX9_Init(pDevice);
		ImGui_ImplWin32_Init(hWindow);
	}
	__declspec(dllexport) void render_overlay(const char* wnd_title) {
		if (ImGui::Begin(wnd_title, &this->close_button, this->window_flags)) {
			ImGui::End();
		}
	}
}; COverlay pOverlay;