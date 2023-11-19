#pragma once
#include"../../hook/hook.hpp"
#include"../../interfaces/interfaces.hpp"

namespace engine_client
{
	inline hook::CTable table;
	namespace is_playing_time_demo
	{
		using HookFn = bool(__fastcall*)(void*, void*);
		constexpr uint32_t index = 78u;

		bool __fastcall Detour(void* ecx, void* edx)
		{
			return table.Original<HookFn>(index)(ecx, edx);
		}
	}

	void Initialize()
	{
		table.Initialize(interfaces::EngineClient);
		table.MakeHook(&is_playing_time_demo::Detour, is_playing_time_demo::index);
	}
}