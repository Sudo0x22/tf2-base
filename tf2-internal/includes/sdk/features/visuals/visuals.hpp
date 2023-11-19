#pragma once
#include"../../functions/function.hpp"

class CVisuals
{
public:
	__declspec(dllexport) void Initialize()
	{
		for (int index = 1; index < 32; index++)
		{
			IEntity* entity = interfaces::ClientEntityList->GetClientEntity(index);
			if (entity->m_bIsAlive())
				printf("alive entity hooked\n");
		}
	}
};