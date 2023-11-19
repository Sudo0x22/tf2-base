#pragma once
#include"../../features/overlay/overlay.hpp"
#include"../../interfaces/interfaces.hpp"

namespace surface
{
	inline hook::CTable table;

	namespace screen_change
	{
		using HookFn = void(__fastcall*)(void*, void*, int, int);
		constexpr uint32_t index = 111u;

		void __fastcall Detour(void* ecx, void* edx, int oldWidth, int oldHeight)
		{
			table.Original<HookFn>(index)(ecx, edx, oldWidth, oldHeight);
		}
	}

	namespace lock_cursor
	{
		using HookFn = void(__fastcall*)(void*, void*);
		constexpr uint32_t index = 62u;

		void __fastcall Detour(void* ecx, void* edx)
		{
			pOverlay.call_overlay ? interfaces::VGuiSurface->UnlockCursor() : table.Original<HookFn>(index)(ecx, edx);
		}
	}

	void Initialize()
	{
		table.Initialize(interfaces::VGuiSurface);
		table.MakeHook(&screen_change::Detour, screen_change::index);
		table.MakeHook(&lock_cursor::Detour, lock_cursor::index);
	}
}