#pragma once
#include<Windows.h>
#include<cstdint>
#include<thread>
#include<chrono>
typedef HANDLE(__stdcall* _RtlCreateThread)(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
typedef BOOL(__stdcall* _RtlCloseHandle)(HANDLE);
typedef BOOL(__stdcall* _RtlDisableThreads)(HMODULE);
typedef BOOL(__stdcall* _RtlAsyncKeyState)(int);
class Api
{
public:
	__inline HANDLE __stdcall MyRtlCreateThread(LPSECURITY_ATTRIBUTES attr, SIZE_T size, LPTHREAD_START_ROUTINE entry, LPVOID lpvoid,
		DWORD flags, LPDWORD thread)
	{
		auto hModule = GetModuleHandleA("kernel32.dll");
		_RtlCreateThread RtlCreateThread = (_RtlCreateThread)
			GetProcAddress(hModule, "CreateThread");
		return RtlCreateThread(attr, size, entry, lpvoid, flags, thread);
	}
	__inline BOOL __stdcall MyRtlCloseHandle(HANDLE handle)
	{
		auto hModule = GetModuleHandleA("kernel32.dll");
		_RtlCloseHandle RtlCloseHandle = (_RtlCloseHandle)
			GetProcAddress(hModule, "CloseHandle");
		return RtlCloseHandle(handle);
	}
	__inline BOOL __stdcall MyRtlDisableThreads(HMODULE Module)
	{
		auto hModule = GetModuleHandleA("kernel32.dll");
		_RtlDisableThreads RtlDisableThreads = (_RtlDisableThreads)
			GetProcAddress(hModule, "DisableThreadLibraryCalls");
		return RtlDisableThreads(Module);
	}
	__inline BOOL __stdcall MyRtlAsyncKeyState(int code)
	{
		auto hModule = GetModuleHandleA("user32.dll");
		_RtlAsyncKeyState RtlAsyncKeyState = (_RtlAsyncKeyState)
			GetProcAddress(hModule, "GetAsyncKeyState");
		return RtlAsyncKeyState(code);
	}
}; Api* pApi = new Api();