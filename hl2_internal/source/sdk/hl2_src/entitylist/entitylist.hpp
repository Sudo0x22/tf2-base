#pragma once
#include <Windows.h>
#define abstract_class class

abstract_class IEntity
{
public:
	int m_iHealth() {
		return *(int*)(this + 0x00);
	}
	int m_bIsAlive() {
		return *(int*)(this + 0x00) != 0;
	}
};

abstract_class IClientEntityList
{
public:
	// Get IClientNetworkable interface for specified entity
	virtual void** GetClientNetworkable(int entnum) = 0;
	virtual void* GetClientNetworkableFromHandle(DWORD hEnt) = 0;
	virtual void* GetClientUnknownFromHandle(DWORD hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual IEntity* GetClientEntity(int entnum) = 0;
	virtual IEntity* GetClientEntityFromHandle(DWORD hEnt) = 0;

	// Returns number of entities currently in use
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	// Returns highest index actually used
	virtual int					GetHighestEntityIndex(void) = 0;

	// Sizes entity list to specified size
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
};

#define VCLIENTENTITYLIST_INTERFACE_VERSION	"VClientEntityList003"