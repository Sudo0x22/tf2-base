#pragma once
#include"../../hook/hook.hpp"
#include"../vguisystem/vguisystem.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

namespace wnd_proc
{
	LRESULT WINAPI WndProc(HWND hWnd, UINT uInt, WPARAM wParam, LPARAM lParam)
	{
		if (pOverlay.call_overlay) {
			ImGui_ImplWin32_WndProcHandler(hWnd, uInt, wParam, lParam);
			return TRUE;
		}
		return CallWindowProcA(oWndProc, hWnd, uInt, wParam, lParam);
	}
}