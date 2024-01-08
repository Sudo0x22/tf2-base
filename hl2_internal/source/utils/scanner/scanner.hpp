#pragma once
#include<cstdint>
#include<Windows.h>
#include<stdint.h>

#define INRANGE(x,a,b)	(x >= a && x <= b)
#define GET_BITS(x)		(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GET_BYTES(x)		(GET_BITS(x[0]) << 4 | GET_BITS(x[1]))

class Scanner
{
public:
	DWORD FindPattern(DWORD dwAddress, DWORD dwLength, LPCWSTR szSig)
	{
		auto szPat = szSig;
		DWORD dwFirstMatch = 0x0;

		for (auto pCur = dwAddress; pCur < dwLength; pCur++)
		{
			if (!*szPat)
			{
				return dwFirstMatch;
			}

			const auto pCurByte = *(BYTE*)pCur;
			const auto pBytePatt = *(BYTE*)szPat;

			if (pBytePatt == '\?' || pCurByte == GET_BYTES(szPat))
			{
				if (!dwFirstMatch)
				{
					dwFirstMatch = pCur;
				}

				//Found
				if (!szPat[2])
				{
					return dwFirstMatch;
				}

				szPat += (pBytePatt == '\?\?' || pBytePatt != '\?') ? 3 : 2;
			}
			else
			{
				szPat = szSig;
				dwFirstMatch = 0x0;
			}
		}

		//Failed to find, return NULL
		return 0x0;
	}

	DWORD LocatePattern(LPCWSTR ModuleName, LPCWSTR Sig)
	{
		if (const auto hModule = reinterpret_cast<DWORD>(GetModuleHandleW(ModuleName)))
		{
			if (const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(hModule + reinterpret_cast<PIMAGE_DOS_HEADER>(hModule)->e_lfanew))
			{
				return FindPattern(hModule + nt_headers->OptionalHeader.BaseOfCode, hModule + nt_headers->OptionalHeader.SizeOfCode, Sig);
			}
		}
	}

}; Scanner pScanner;