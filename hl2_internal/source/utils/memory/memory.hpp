#pragma once
#include<vector>
#include<Windows.h>
class Memory
{
public:
	template<typename type>
	__inline type ReadProcMem(type offset);
public:
	template<typename type>
	__inline type WriteProcMem(type offset, type value);
};