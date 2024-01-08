#pragma once
#include"api/api.hpp"
#include"memory/memory.hpp"
#include"offsets/offsets.hpp"
#include"scanner/scanner.hpp"

namespace Utils
{
	inline uintptr_t GetVFuncPtr(void* pBaseClass, unsigned int nIndex)
	{
		return static_cast<uintptr_t>((*static_cast<int**>(pBaseClass))[nIndex]);
	}

}