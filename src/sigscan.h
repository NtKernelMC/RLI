#pragma once
#include <Windows.h>
#include <Psapi.h>
#include "lazy_import.h"
#pragma comment (lib, "Psapi.lib")
class SigScan
{
public:
	MODULEINFO GetModuleInfo(const char* szModule)
	{
		MODULEINFO modinfo = { 0 };
		HMODULE hModule = LI_FN(GetModuleHandleA)(szModule);
		if (hModule == 0) return modinfo;
		LI_FN(K32GetModuleInformation)(LI_FN(GetCurrentProcess)(), hModule, &modinfo, sizeof(MODULEINFO));
		return modinfo;
	}
	DWORD FindPattern(const char* module, const char* pattern, const char* mask)
	{
		MODULEINFO mInfo = GetModuleInfo(module);
		DWORD base = (DWORD)mInfo.lpBaseOfDll;
		DWORD size = (DWORD)mInfo.SizeOfImage;
		DWORD patternLength = (DWORD)strlen(mask);
		for (DWORD i = 0; i < size - patternLength; i++)
		{
			bool found = true;
			for (DWORD j = 0; j < patternLength; j++)
			{
				found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
			}
			if (found)
			{
				return base + i;
			}
		}
		return NULL;
	}
};