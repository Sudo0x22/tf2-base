#include"source/source.hpp"

DWORD __stdcall MainThread(HMODULE hModule, LPVOID hBuffer)
{
	static bool m_bInitialize = false;
	while (!GetModuleHandleA("client.dll") || !GetModuleHandleA("engine.dll"))
		std::this_thread::sleep_for(std::chrono::milliseconds(420));

	while (!m_bInitialize)
	{		
		pOffsets.Initialize();
		init_interfaces::Initialize();
		init_hooks::Initialize();
		pFeatures.Initialize();
		MenuHooks::Initialize();
		m_bInitialize = true;
	}
	return TRUE;
}
BOOL __stdcall DllMain(HMODULE hModule, DWORD hReasons, LPVOID hBuffer)
{
	if (hReasons == DLL_PROCESS_ATTACH)
	{
		pApi->MyRtlDisableThreads(hModule);
		HANDLE hThread = pApi->MyRtlCreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
		if (hThread) { pApi->MyRtlCloseHandle(hThread); }
	}

	return TRUE;
}