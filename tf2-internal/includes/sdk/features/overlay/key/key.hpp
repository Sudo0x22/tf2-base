#pragma once
#include<Windows.h>

class CKeyInput {
public:
	__declspec(dllexport) int __stdcall key_input(int code)
	{
		return GetAsyncKeyState(code);
	}
}; CKeyInput pKeyInput;