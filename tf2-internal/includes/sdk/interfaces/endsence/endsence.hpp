#pragma once
#include"../wnd_proc/wnd_proc.hpp"

namespace endsence
{
	LRESULT __stdcall EndSceneHk(LPDIRECT3DDEVICE9 pDevice)
	{
		if (!pOverlay.init_imgui) 
		{
			ImGui::CreateContext();
			oWndProc = (oWndProcFn)SetWindowLongPtrA(hWindow, GWL_WNDPROC, (LONG_PTR)wnd_proc::WndProc);
			ImGui::GetIO().ImeWindowHandle = hWindow;
			pOverlay.init_device(pDevice);
			pOverlay.init_imgui = true;
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (pKeyInput.key_input(VK_HOME) & 0x1) { pOverlay.call_overlay = !pOverlay.call_overlay; }

		if (pOverlay.call_overlay) { pOverlay.render_overlay(pOverlay.window_title.c_str()); }

		ImGui::EndFrame();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		return oEndScene(pDevice);
	}
}
