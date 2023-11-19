#pragma once
#include"../../../utils/offsets/offsets.hpp"

int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

struct Matrix
{
	float matrix[16];
};

class Vector
{
public:
	float x, y, z;
};

class Vector2D
{
public:
	float x, y;
};

namespace Engine
{
	__inline Matrix GetViewMatrix()
	{
		uint32_t viewRender = *(uint32_t*)(offsets::client_dll + offsets::pOffsets.m_vViewRender);
		uint32_t viewMatrix = *(uint32_t*)(viewRender + offsets::pOffsets.m_vViewMatrix);
		return *(Matrix*)(viewMatrix);
	}
	__declspec(dllexport) float to_meters(float x)
	{
		return x / 39.62f;
	}
	__declspec(dllexport) bool __stdcall world_to_screen(Vector& in, Vector2D& out)
	{
		return true;
	}
}