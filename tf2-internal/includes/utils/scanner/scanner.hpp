#pragma once
#include<Windows.h>
#define INRANGE(x,a,b)	(x >= a && x <= b)
#define GET_BITS(x)		(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GET_BYTES(x)		(GET_BITS(x[0]) << 4 | GET_BITS(x[1]))

class CScanner
{
public:
	unsigned long FindPattern(unsigned long szAddress, unsigned long szBuffer, const wchar_t* pattern)
	{

	}
	unsigned long LocatePattern(const wchar_t* module, const wchar_t* pattern)
	{
		if (const auto hModule = reinterpret_cast<DWORD>(GetModuleHandleW(module)))
		{
			if (const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(hModule + reinterpret_cast<PIMAGE_DOS_HEADER>(hModule)->e_lfanew))
			{
				return FindPattern(hModule + nt_headers->OptionalHeader.BaseOfCode, hModule + nt_headers->OptionalHeader.SizeOfCode, pattern);
			}
		}
	}
};