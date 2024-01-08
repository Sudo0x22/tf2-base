#pragma once
#include"../../../utils/offsets/offsets.hpp"
#include"../engine/engine.hpp"
class BaseEntity
{
public:
	__inline int m_iHealth() {}
	__inline int m_bIsAlive() {};
public:
	Vector m_vGetViewAngles()
	{
		return *(Vector*)(this + pOffsets.dwViewAngles);
	}
};
__inline BaseEntity* GetLocalPlayer()
{
	return *(BaseEntity**)(pOffsets.client_dll + pOffsets.local_player);
}
__inline BaseEntity* GetEntityFromList(uintptr_t index)
{
	return *(BaseEntity**)(pOffsets.client_dll + pOffsets.client_dll + (index << 5));
}