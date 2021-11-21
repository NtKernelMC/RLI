/*
* Runtime Lua Injector 
* Author: NtKernelMC
* Version: 1.0 BETA
*/
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <thread>
//#include "xorstr.h"
#include "PebHider.h"
#include "Hooks.h"
DWORD WINAPI Load(LPVOID lpParam)
{
    //Hooks::LogInFile(xorstr_("RLI.log"), xorstr_("[INTERNAL] Runtime Lua Injector V1.0 BETA loaded!\n"));
    char *dllName = { xorstr_("RLI.dll") };
    ULONG len = (ULONG)strlen(dllName);
    Hooks::InstallHooks();
    PebHider::RemovePeHeader(GetModuleHandleA(dllName));
    PebHider::UnlinkModule(dllName);
    ZeroMemory(dllName, len);
    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) 
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Load, hModule, 0, NULL);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
