#pragma once
#include"surface/surface.hpp"
#include"engine_client/engine_client.hpp"

namespace init_hooks
{
	__declspec(dllexport) bool InitializeHooks()
	{
		if (MH_Initialize() != MH_STATUS::MH_OK)
			return false;

		engine_client::Initialize();
		surface::Initialize();

		if (MH_EnableHook(MH_ALL_HOOKS) != MH_STATUS::MH_OK)
			return false;

		return true;
	}

	__declspec(dllexport) void RemoveHooks(HMODULE hModule)
	{
		if (GetAsyncKeyState(VK_END) & 0x1)
		{
			MH_DisableHook(MH_ALL_HOOKS);
			MH_RemoveHook(MH_ALL_HOOKS);

			FreeLibraryAndExitThread(hModule, 1);
		}
	}
}