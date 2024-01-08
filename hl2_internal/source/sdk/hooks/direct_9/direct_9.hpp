#pragma once
#include"../../../utils/hook/hook.hpp"
#include"../../interfaces/interfaces.hpp"

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	hWindow = handle;
	return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
	hWindow = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return hWindow;
}

namespace WndProc
{
	LRESULT __stdcall Detour(const HWND hWindow, UINT uInt, WPARAM wParam, LPARAM lParam)
	{
		if (pMenu.m_bRenderMenu)
		{
			ImGui_ImplWin32_WndProcHandler(hWindow, uInt, wParam, lParam);
			return true;
		}
		return CallWindowProcW(oWndProc, hWindow, uInt, wParam, lParam);
	}
}

namespace CursorHook
{
	BOOL __stdcall Detour(bool show)
	{
		if (pMenu.m_bRenderMenu)
			return FALSE;
		return oCursor(show);
	}

	bool __stdcall InitHook(LPVOID nFunc, LPVOID nDet, LPVOID* nOrig)
	{
		if (MH_CreateHook(nFunc, nDet, nOrig) != MH_OK)
			return false;
		if (MH_EnableHook(nFunc) != MH_OK)
			return false;
		return true;
	}
	void __stdcall KillHook(LPVOID nFunc)
	{
		MH_DisableHook(nFunc);
		MH_RemoveHook(nFunc);
	}
}

namespace MenuHooks
{
	inline hook::Table pTable;
	namespace end_scene
	{
		long __stdcall Detour(LPDIRECT3DDEVICE9 pDevice)
		{
			if (!pMenu.m_bInitImGui) { pMenu.InitImGui(pDevice); pMenu.Initialize(); pMenu.m_bInitImGui = true; }
			
			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGui::GetIO().MouseDrawCursor = pMenu.m_bRenderMenu;
			ImGui::GetIO().WantCaptureMouse = pMenu.m_bRenderMenu;

			pMenu.m_bCaptureCursor = ImGui::GetIO().WantCaptureMouse;
			pMenu.m_bRenderCursor = ImGui::GetIO().MouseDrawCursor;

			if (MyRtlKeyPress(VK_INSERT) &0x1)
			{
				pMenu.m_bRenderMenu = !pMenu.m_bRenderMenu;
			}
			if (pMenu.m_bRenderMenu)
			{
				pMenu.Render();
			}

			if (pMenu.m_bCaptureCursor && pMenu.m_bRenderCursor)
			{
				CursorHook::InitHook(&SetCursorPos, CursorHook::Detour,
					reinterpret_cast<LPVOID*>(&oCursor));
			}
			else
			{
				CursorHook::KillHook(&SetCursorPos);
			}


			ImGui::EndFrame();
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

			return oEndScene(pDevice);
		}
	}

	namespace reset_buffer 
	{
		using HookFn = HRESULT(__fastcall*)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
		constexpr uint16_t nIndex = 16;
		HRESULT __fastcall Detour(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pParams)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			ImGui_ImplDX9_CreateDeviceObjects();
			return oResetBuffer(pDevice, pParams);
		}
	}

	bool __stdcall Initialize() {
		static bool m_bInitialized = false;
		while (!m_bInitialized) 
		{
			if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
			{
				kiero::bind(42, (void**)&oEndScene, end_scene::Detour);
				kiero::bind(reset_buffer::nIndex, (void**)&oResetBuffer, reset_buffer::Detour);
				do
					hWindow = GetProcessWindow();
				while (hWindow == NULL);
				oWndProc = (WndProcFn)SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)WndProc::Detour);
				m_bInitialized = true;
			}
		}
		return true;
	}
}