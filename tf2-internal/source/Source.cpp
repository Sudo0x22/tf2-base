#include"../includes/includes.hpp"

void __stdcall MainThread(HMODULE hModule, LPVOID Buffer)
{
	while (!GetModuleHandleA("client.dll") || !GetModuleHandleA("engine.dll"))
		std::this_thread::sleep_for(std::chrono::milliseconds(420));

	init_interfaces::initialize();
	
	offsets::pOffsets.Initialize();
	offsets::pNetVars.Initialize();
	
	init_hooks::InitializeHooks();
	features::Initialize();
}

void __stdcall OverlayThread(LPVOID Buffer)
{

}

bool __stdcall DllMain(HMODULE hModule, DWORD Reasons, LPVOID Buffer)
{
	if (Reasons != DLL_PROCESS_ATTACH)
		return false;

	void* hCreateThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
	if (hCreateThread)
		CloseHandle(hCreateThread);

	/*void* hCreateOverlayThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)OverlayThread, 0, 0, 0);
	if (hCreateOverlayThread)
		CloseHandle(hCreateOverlayThread);*/

	return true;
}