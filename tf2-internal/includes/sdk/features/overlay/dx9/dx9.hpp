#pragma once
#include"../defines/defines.hpp"
#include"../../../hook/hook.hpp"

namespace dx9
{
	class Globals
	{
	public:
		HWND WindowHandle = 0;
		WNDCLASSEX WindowClass = {};
	};

	class CDX9 : public Globals
	{
	public:
		__declspec(dllexport) bool __stdcall init_window();
		__declspec(dllexport) bool __stdcall delete_window();
		__declspec(dllexport) bool __stdcall initialize();
	}; CDX9 pDX9;

	__declspec(dllexport) bool CDX9::init_window()
	{
		WindowClass.cbSize = sizeof(WNDCLASSEX);
		WindowClass.style = CS_HREDRAW | CS_VREDRAW;
		WindowClass.lpfnWndProc = DefWindowProc;
		WindowClass.cbClsExtra = 0;
		WindowClass.cbWndExtra = 0;
		WindowClass.hInstance = GetModuleHandleA(NULL);
		WindowClass.hIcon = NULL;
		WindowClass.hCursor = NULL;
		WindowClass.hbrBackground = NULL;
		WindowClass.lpszMenuName = NULL;
		WindowClass.lpszClassName = L"DX9";
		WindowClass.hIconSm = NULL;

		RegisterClassEx(&WindowClass);
		WindowHandle = CreateWindowW(WindowClass.lpszClassName, L"DX9 Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, WindowClass.hInstance, NULL);
		if (WindowHandle == NULL)
			return false;

		return true;
	}

	__declspec(dllexport) bool CDX9::delete_window()
	{
		UnregisterClassW(WindowClass.lpszClassName, WindowClass.hInstance);
		DestroyWindow(WindowHandle);
		if (WindowHandle != NULL)
			return false;
		return true;
	}

	__declspec(dllexport) bool CDX9::initialize()
	{
		HMODULE hModule = GetModuleHandleA("d3d9.dll");
		if (hModule == NULL) { delete_window(); }

		void* Direct3DCreate9;
		if ((Direct3DCreate9 = ::GetProcAddress(hModule, "Direct3DCreate9")) == NULL)
		{
			delete_window();
			return false;
		}

		LPDIRECT3D9 direct3D9;
		if ((direct3D9 = ((LPDIRECT3D9(__stdcall*)(uint32_t))(Direct3DCreate9))(D3D_SDK_VERSION)) == NULL)
		{
			delete_window();
			return false;
		}

		D3DPRESENT_PARAMETERS params;
		params.BackBufferWidth = 0;
		params.BackBufferHeight = 0;
		params.BackBufferFormat = D3DFMT_UNKNOWN;
		params.BackBufferCount = 0;
		params.MultiSampleType = D3DMULTISAMPLE_NONE;
		params.MultiSampleQuality = NULL;
		params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		params.hDeviceWindow = WindowHandle;
		params.Windowed = 1;
		params.EnableAutoDepthStencil = 0;
		params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
		params.Flags = NULL;
		params.FullScreen_RefreshRateInHz = 0;
		params.PresentationInterval = 0;

		LPDIRECT3DDEVICE9 device;
		if (direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, WindowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &device) < 0)
		{
			direct3D9->Release();
			delete_window();
			return false;
		}

		MethodsTable = (uint32_t*)::calloc(119, sizeof(uint32_t));
		memcpy(MethodsTable, *(uint32_t**)device, 119 * sizeof(uint32_t));

		MH_Initialize();

		device->Release();
		device = NULL;

		direct3D9->Release();
		direct3D9 = NULL;

		delete_window();

		return true;
	}
}