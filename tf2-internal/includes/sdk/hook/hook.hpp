#pragma once
#include<cassert>
#include <cstdint>
#include"minhook/include/MinHook.h"

static uint32_t* MethodsTable = nullptr;

namespace hook
{
	class CHook {
	public:
		__declspec(dllexport) bool __stdcall make_hook(unsigned short nIndex, void* nDetour, void** nOriginal)
		{
			assert(_index >= 0 && _detour != NULL && _original != NULL);
			void* nTarget = (void*)MethodsTable[nIndex];
			if (MH_CreateHook(nTarget, nDetour, nOriginal) != MH_OK)
				return false;
			if (MH_EnableHook(nTarget) != MH_OK)
				return false;
			return true;
		}
		__declspec(dllexport) void __stdcall remove_hook(unsigned short nIndex) 
		{
			assert(nIndex >= 0);
			MH_DisableHook((void*)MethodsTable[nIndex]);
			MH_RemoveHook((void*)MethodsTable[nIndex]);
		}
	};

	class CFunction {
	private:
		void* nOriginal = nullptr;
	public:
		__declspec(dllexport) bool Initialize(void* nTarget, void* nDetour) {
			return (MH_CreateHook(nTarget, nDetour, &nOriginal) == MH_STATUS::MH_OK);
		}
	public:
		template<typename HookFn>
		__declspec(dllexport) HookFn Original() const {
			return reinterpret_cast<HookFn>(nOriginal);
		}
	};

	class CTable {
	private:
		unsigned int** m_pBase = 0u;
		unsigned int   m_nSize = 0u;
		std::unique_ptr<void* []> m_nOriginal = {};
	public:
		__declspec(dllexport) bool Initialize(const void* nTable)
		{
			m_pBase = (unsigned int**)(nTable);
			while (reinterpret_cast<unsigned int*>(*m_pBase)[m_nSize])
				m_nSize += 1u;
			m_nOriginal = std::make_unique<void* []>(m_nSize);
			return (m_pBase && m_nSize);
		}
		__declspec(dllexport) bool MakeHook(void* nDetour, const unsigned int nIndex)
		{
			if (m_pBase && m_nSize)
				return (MH_CreateHook((*reinterpret_cast<void***>(m_pBase))[nIndex], nDetour, &m_nOriginal[nIndex]) == MH_STATUS::MH_OK);
			return false;
		}
	public:
		template<typename HookFn>
		__declspec(dllexport) HookFn Original(const unsigned int nIndex) const
		{
			return reinterpret_cast<HookFn>(m_nOriginal[nIndex]);
		}
	};
}