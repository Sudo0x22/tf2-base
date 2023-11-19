#pragma once
#include"../netvars/netvar_dumper.hpp"

namespace offsets
{
	uintptr_t client_dll = (uintptr_t)GetModuleHandleA("client.dll");
	uintptr_t engine_dll = (uintptr_t)GetModuleHandleA("engine.dll");

	class COffsets {
	public:
		uintptr_t m_dwEntityList = 0x00;
		uintptr_t m_dwLocalEntity = 0x00;
		uintptr_t m_vViewRender = 0x00;
		uintptr_t m_vViewMatrix = 0x00;
		uintptr_t m_dwIsInGame = 0x00;
		uintptr_t m_dwIsInConnected = 0x00;
		uintptr_t m_dwViewAngles = 0x00;
	public:
		__declspec(dllexport) bool Initialize();
	}; COffsets pOffsets;

	class CNetVars {
	public:
		uintptr_t m_iHealth = 0x00;
		uintptr_t m_iTeamNum = 0x00;
	public:
		__declspec(dllexport) bool Initialize();
	}; CNetVars pNetVars;

	__declspec(dllexport) bool COffsets::Initialize() {

		this->m_dwLocalEntity = 0xC495F0;
		this->m_dwEntityList = 0xC57574;

		this->m_dwIsInGame = 0x465B88;
		this->m_dwIsInConnected = 0x59A94A;

		this->m_dwViewAngles = 0x46A5DC;

		return true;
	}

	__declspec(dllexport) bool CNetVars::Initialize() {


		return true;
	}
}