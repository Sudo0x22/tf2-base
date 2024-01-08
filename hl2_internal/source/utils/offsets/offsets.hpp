#pragma once
#include<cstdint>
#include<Windows.h>
class Offsets
{
public:
	uintptr_t client_dll = 0x00;
	uintptr_t engine_dll = 0x00;

	uintptr_t local_player = 0x00;
	uintptr_t cl_entitylist = 0x00;
	uintptr_t dwDuck = 0x00;
	uintptr_t dwLeft = 0x00;
	uintptr_t dwRight = 0x00;

	uintptr_t dwMoveLeft = 0x00;
	uintptr_t dwMoveRight  = 0x00;
	uintptr_t dwMoveForwards = 0x00;
	uintptr_t dwMoveBackwards = 0x00;

	uintptr_t dwJump = 0x00;
	uintptr_t dwAttack = 0x00;
	uintptr_t dwAttack2 = 0x00;

	uintptr_t dwGetMaxClients = 0x00;
	uintptr_t dwIsInGame = 0x00;
	uintptr_t dwIsInConnected = 0x00;
	uintptr_t dwGlowObjectManager = 0x00;

	uintptr_t dwViewAngles = 0x00;
public:
	__inline bool Initialize()
	{
		this->client_dll = (uintptr_t)GetModuleHandleA("client.dll");
		this->engine_dll = (uintptr_t)GetModuleHandleA("engine.dll");

		this->local_player = 0xC49670;
		this->cl_entitylist = 0xC575F4;
		return true;
	}
}; Offsets pOffsets;