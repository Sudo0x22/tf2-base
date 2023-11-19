#pragma once
#include"../engine/engine.hpp"

class CBaseEntity
{
public:
	int m_iTeamNum() {
		return *(int*)(this + offsets::pNetVars.m_iTeamNum);
	}

	int m_bIsAlive() {
		return *(int*)(this + offsets::pNetVars.m_iHealth) != 0;
	}
};

CBaseEntity* GetLocalEntity() {
	return *(CBaseEntity**)(offsets::client_dll + offsets::pOffsets.m_dwLocalEntity);
}

CBaseEntity* GetEntityList(uintptr_t index) {
	return *(CBaseEntity**)(offsets::client_dll + offsets::pOffsets.m_dwEntityList + (index << 5));
}