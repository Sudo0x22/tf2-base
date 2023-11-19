#pragma once
#include"visuals/visuals.hpp"

namespace features
{
	bool unload = false;
	__declspec(dllexport) void __stdcall Initialize()
	{
		CBaseEntity* LocalEntity = GetLocalEntity();
		if (LocalEntity == NULL)
			return;

		while (!unload)
		{
			if (LocalEntity->m_bIsAlive())
			{

			}
		}
	}
}