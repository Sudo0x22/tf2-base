#pragma once
#include"../../../includes/minhook/include/MinHook.h"
#include<cstdint>
#include<cassert>
#include<memory>

namespace hook
{
	class Table
	{
	private:
		unsigned int** m_pBase = 0u;
		unsigned int   m_pSize = 0u;
		std::unique_ptr<void* []> m_pOriginal = {};
	public:
		__inline bool Initialize(const void* pTable)
		{
			this->m_pBase = (unsigned int**)(pTable);
			while (reinterpret_cast<unsigned int*>(*this->m_pBase)[this->m_pSize])
				this->m_pSize += 1u;
			this->m_pOriginal = std::make_unique<void* []>(this->m_pSize);
			return (this->m_pBase && this->m_pSize);
		}
		__inline bool Hook(void* pDetour, const unsigned int pIndex)
		{
			if (this->m_pBase && this->m_pSize)
				return (MH_CreateHook((*reinterpret_cast<void***>(this->m_pBase))[pIndex], pDetour, &this->m_pOriginal[pIndex]) == MH_OK);
			return false;
		}
	public:
		template<typename HookFn>
		__inline HookFn Original(const unsigned int pIndex) const {
			return reinterpret_cast<HookFn>(this->m_pOriginal[pIndex]);
		}
	};

	class Function
	{
	private:
		void* n_pOriginal = nullptr;
	public:
		__inline bool Initialize(void* nTarget, void* nDetour) {
			return (MH_CreateHook(nTarget, nDetour, &n_pOriginal) == MH_OK);
		}
	public:
		template<typename HookFn>
		__inline HookFn Original() const {
			return reinterpret_cast<HookFn>(n_pOriginal);
		}
	};
}