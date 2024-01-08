#pragma once
#include"menu/menu.hpp"
#include"../sdk/external_src/src.hpp"
class Features
{
public:
	__inline void Initialize() 
	{ 
		BaseEntity* pLocal = GetLocalPlayer();
		if (pLocal)
			return;

		for (int index = 0; index < 32; index++)
		{
			BaseEntity* pEntity = GetEntityFromList(index);
			
			if (!pEntity || pEntity == pLocal)
				continue;
			
			//printf("Entity: 0x%p\n", pEntity);
		}
	}
}; Features pFeatures;