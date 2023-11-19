#pragma once
#include<Windows.h>
#include<cstdint>

namespace capture
{
	class CCapture {
	public:
		template<typename capture>
		__inline capture* GetInterfaces(const char* module_name, const char* interface_name);
	}; CCapture pCapture;

	template<typename capture>
	__inline capture* CCapture::GetInterfaces(const char* module_name, const char* interface_name)
	{
		const auto hModule = GetModuleHandleA(module_name);
		
		if (!hModule)
			return nullptr;

		const auto hFunction = GetProcAddress(hModule, "CreateInterface");

		if (!hFunction)
			return nullptr;

		using CreateInterfaceFn = capture * (*)(const char*, int*);
		const auto CreateInterface = reinterpret_cast<CreateInterfaceFn>(hFunction);

		return CreateInterface(interface_name, nullptr);
	}
}