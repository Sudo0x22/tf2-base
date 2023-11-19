#pragma once
#include"../../utils/capture/capture.hpp"
#include"baseentity/baseentity.hpp"
#include"endsence/endsence.hpp"
#include"../hl2_src/hl2_src.hpp"

namespace sigs
{

}

namespace interfaces
{
	inline BaseClient* IBaseClient = nullptr;
	inline IClientEntityList* ClientEntityList = nullptr;
	inline vgui::ISurface* VGuiSurface = nullptr;
	inline IDirect3DDevice9* DirectXDevice = nullptr;
	inline IVEngineClient* EngineClient = nullptr;


}

namespace init_interfaces
{
	__declspec(dllexport) bool initialize()
	{
		interfaces::IBaseClient = capture::pCapture.GetInterfaces<BaseClient>("client.dll", "VClient017");
		interfaces::ClientEntityList = capture::pCapture.GetInterfaces<IClientEntityList>("client.dll", "VClientEntityList003");
		interfaces::EngineClient = capture::pCapture.GetInterfaces<IVEngineClient>("engine.dll", "VEngineClient014");
		interfaces::VGuiSurface = capture::pCapture.GetInterfaces<vgui::ISurface>("vguimatsurface.dll", "VGUI_Surface030");

		return true;
	}
}

