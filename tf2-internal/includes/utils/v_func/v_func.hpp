#pragma once

class VFunc
{
private:
	void**& GetVTable(void* ecx, const unsigned int offset = 0u)
	{
		return *reinterpret_cast<void***>(reinterpret_cast<unsigned int>(ecx) + offset);
	}
	const void** GetVTable(const void* ecx, const unsigned int offset = 0u)
	{
		return *reinterpret_cast<const void***>(reinterpret_cast<unsigned int>(ecx) + offset);
	}
public:
	template<typename VFuncFn>
	__declspec(dllexport) VFuncFn GetVFunc(void* ecx, const unsigned int index, const unsigned int offset = 0u) {
		return reinterpret_cast<VFuncFn>(GetVTable(ecx, offset)[index]);
	}
};