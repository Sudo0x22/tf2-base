#pragma once
#include<Windows.h>
#include<cstdint>
class Capture
{
public:
	template<typename capture>
	__inline capture* GetInterfaces(const char* module_name, const char* interface_name)
	{
		auto hModule = GetModuleHandleA(module_name);
		const auto hFunction = GetProcAddress(hModule, "CreateInterface");
		using CreateInterfaceFn = capture * (*)(const char*, int*);
		const auto CreateInterface = reinterpret_cast<CreateInterfaceFn>(hFunction);
		return CreateInterface(interface_name, nullptr);
	}
}; Capture pCapture;