#pragma once
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <Windows.h>
#include <stdio.h>
#include <ctime>
#include <string>
#include <algorithm>
#include <direct.h>
#include <codecvt>
#include "sigscan.h"
#include "xorstr.h"
#include "BOT.h"
#include "HWBP.h"
#include "MinHook.h"
#include "lazy_import.h"
#pragma comment(lib, "libMinHook.x86.lib")
class Hooks
{
public:
	Hooks();
	~Hooks();
	static BYTE prologue[6];
	static std::string utf8_to_cp1251(const char* str);
	static bool findStringIC(const std::string& strHaystack, const std::string& strNeedle);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef void(__thiscall* ptrDrawString)(void *ECX, int uiLeft, int uiTop, int uiRight, int uiBottom, 
	unsigned long ulColor, const char* szText, float fScaleX, float fScaleY,
	unsigned long ulFormat, void* pDXFont, bool bOutline);
	static void __fastcall DrawString(void* ECX, void* EDX, int uiLeft, int uiTop, int uiRight, int uiBottom,
	unsigned long ulColor, const char* szText, float fScaleX, float fScaleY,
	unsigned long ulFormat, void* pDXFont, bool bOutline);
	static ptrDrawString callDrawString;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef bool (__thiscall* ptrAddDebugHook)(void *ECX, int hookType, void* functionRef, void* allowedNameList);
	static ptrAddDebugHook callAddDebugHook;
	static bool __fastcall AddDebugHook(void* ECX, void *EDX, int hookType, void* functionRef, void* allowedNameList);
	static DWORD MakeJump(DWORD jmp_address, DWORD hookAddr, BYTE* prologue, size_t prologue_size);
	static bool RestorePrologue(DWORD addr, BYTE* prologue, size_t prologue_size);
	static void __stdcall LogInFile(std::string log_name, const char* log, ...);
	typedef int(__cdecl* t_LuaLoadBuffer)(void* L, const char* buff, size_t sz, const char* name);
	static t_LuaLoadBuffer callLuaLoadBuffer;
	static int __cdecl hkLuaLoadBuffer(void* L, const char* buff, size_t sz, const char* name);
    static bool InstallHooks();
};