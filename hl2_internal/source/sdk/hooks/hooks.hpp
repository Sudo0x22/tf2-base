#pragma once
#include"surface/surface.hpp"
#include"engine_client/engine_client.hpp"
#include"direct_9/direct_9.hpp"

namespace init_hooks
{
	__inline bool Initialize()
	{
		if (MH_Initialize() != MH_OK)
			return false;

		hooks::engine_client::Initialize();
		hooks::surface::Initialize();

		if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
			return false;
		return true;
	}
}