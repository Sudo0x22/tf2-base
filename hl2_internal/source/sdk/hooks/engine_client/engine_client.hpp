#pragma once
#include"../../../utils/hook/hook.hpp"
#include"../../interfaces/interfaces.hpp"
namespace hooks
{
	namespace engine_client
	{
		inline hook::Table pTable;
		namespace is_playing_time_demo
		{
			using HookFn = bool(__fastcall*)(void*, void*);
			constexpr uint32_t nIndex = 78u;
			bool __fastcall Detour(void* rcx, void* rbx) { return pTable.Original<HookFn>(nIndex)(rcx, rbx); }
		}

		__inline void Initialize()
		{
			pTable.Initialize(interfaces::EngineClient);
			pTable.Hook(&is_playing_time_demo::Detour, is_playing_time_demo::nIndex);
		}
	}
}