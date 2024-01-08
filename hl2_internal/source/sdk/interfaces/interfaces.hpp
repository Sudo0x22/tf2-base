#pragma once
#include"../hl2_src/hl2_src.hpp"
#include"../../utils/capture/capture.hpp"
#include<d3d9.h>
namespace interfaces
{
	inline IBaseClient* BaseClient = nullptr;
	inline IClientEntityList* ClientEntityList = nullptr;
	inline vgui::ISurface* VGuiSurface = nullptr;
	inline IVEngineClient* EngineClient = nullptr;
	inline IDirect3DDevice9* DirectXDevice = nullptr;
	inline IMatSystemSurface* MatSystemSurface = nullptr;
}

namespace init_interfaces
{
	__declspec(dllexport) bool Initialize()
	{
		interfaces::BaseClient = pCapture.GetInterfaces<IBaseClient>("client.dll", "VClient017");
		interfaces::ClientEntityList = pCapture.GetInterfaces<IClientEntityList>("client.dll", "VClientEntityList003");
		
		interfaces::EngineClient = pCapture.GetInterfaces<IVEngineClient>("engine.dll", "VEngineClient014");
		interfaces::VGuiSurface = pCapture.GetInterfaces<vgui::ISurface>("vguimatsurface.dll", "VGUI_Surface030");
		
		interfaces::MatSystemSurface = pCapture.GetInterfaces<IMatSystemSurface>("vguimatsurface.dll", "VGUI_Surface030");

		return true;
	}
}