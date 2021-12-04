/*
* Runtime Lua Injector 
* Author: NtKernelMC
* Version: 1.0 BETA
*/
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <thread>
#include "PebHider.h"
#include "Hooks.h"
DWORD WINAPI Load(LPVOID lpParam)
{
    static const char reverser[] = { "HUIBRIS TEAM POSHLI NAHUY!" };
    char tmp[50]; memset(tmp, 0, sizeof(tmp)); sprintf(tmp, "%s", reverser);
    Hooks::LogInFile(xorstr_("RLI.log"), xorstr_("[INTERNAL] Runtime Lua Injector by NtKernelMC loaded!\n"));
    Hooks::InstallHooks(); HMODULE hMDL = LI_FN(GetModuleHandleA)(xorstr_("RLI.dll"));
    PebHider::RemovePeHeader(hMDL); PebHider::UnlinkModule(xorstr_("RLI.dll"));
    return 0;
}
__forceinline void CaseByPass(HMODULE hModule){ LI_FN(CreateThread)(nullptr, 0, (LPTHREAD_START_ROUTINE)Load, nullptr, 0, nullptr); }
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) 
    {
    case DLL_PROCESS_ATTACH:
        LI_FN(DisableThreadLibraryCalls)(hModule); 
        CaseByPass(hModule);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
