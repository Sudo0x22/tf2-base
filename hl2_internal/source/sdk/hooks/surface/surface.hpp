#pragma once
#include"../../interfaces/interfaces.hpp"
#include"../../../utils/hook/hook.hpp"
#include"../../../features/features.hpp"

namespace hooks
{
	namespace surface
	{
		inline hook::Table pTable;
		namespace screen_change
		{
			using HookFn = void(__fastcall*)(void*, void*, int, int);
			constexpr uint32_t nIndex = 111u;
			void __fastcall Detour(void* rcx, void* rbx, int width, int height) {
				pTable.Original<HookFn>(nIndex)(rcx, rbx, width, height);
			}
		}

		namespace lock_cursor
		{
			using HookFn = void(__fastcall*)(void*, void*);
			constexpr uint32_t nIndex = 62u;
			void __fastcall Detour(void* rcx, void* rbx) {
				pMenu.m_bRenderMenu ? interfaces::VGuiSurface->UnlockCursor() : pTable.Original<HookFn>(nIndex)(rcx, rbx);
			}
		}

		void Initialize()
		{
			pTable.Initialize(interfaces::VGuiSurface);
			pTable.Hook(&screen_change::Detour, screen_change::nIndex);
			pTable.Hook(&lock_cursor::Detour, lock_cursor::nIndex);
		}
	}
}