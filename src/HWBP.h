#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <map>
#include "xorstr.h"
#include "lazy_import.h"
static std::map<DWORD_PTR, DWORD_PTR> hooks; 
class HWBP
{
protected:
	static LONG __stdcall hwbpHandler(PEXCEPTION_POINTERS ExceptionInfo)
	{
		if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP ||
		ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT)
		{
			for (const auto& it : hooks)
			{
#ifdef _WIN64
				if (it.first == ExceptionInfo->ContextRecord->Rip)
#else
				if (it.first == ExceptionInfo->ContextRecord->Eip)
#endif
				{
#ifdef _WIN64
					ExceptionInfo->ContextRecord->Rip = it.second;
#else
					ExceptionInfo->ContextRecord->Eip = it.second;
#endif
					return EXCEPTION_CONTINUE_EXECUTION;
				}
			}
		}
		return EXCEPTION_CONTINUE_SEARCH;
	}
public:
	static int GetFreeIndex(size_t regValue)
	{
		if (!(regValue & 1)) return 0;
		else if (!(regValue & 4)) return 1;
		else if (!(regValue & 16)) return 2;
		else if (!(regValue & 64)) return 3;
		return -1;
	}
private:
	typedef struct
	{
		DWORD_PTR target;
		DWORD_PTR interceptor;
	} PRM_THREAD, *PPRM_THREAD;
	static bool installHWBP(PPRM_THREAD prm)
	{
		typedef PVOID(__stdcall* ptrAddVectoredExceptionHandler)(ULONG first, PVECTORED_EXCEPTION_HANDLER handler);
		ptrAddVectoredExceptionHandler callAddVectoredExceptionHandler = (ptrAddVectoredExceptionHandler)
		LI_FN(GetProcAddress)(LI_FN(GetModuleHandleA)(xorstr_("kernel32.dll")), xorstr_("AddVectoredExceptionHandler"));
		callAddVectoredExceptionHandler(0x1, hwbpHandler);
		hooks.insert(hooks.begin(), std::pair<DWORD_PTR, DWORD_PTR>(prm->target, prm->interceptor));
		THREADENTRY32 th32; HANDLE hSnapshot = NULL; th32.dwSize = sizeof(THREADENTRY32);
		hSnapshot = LI_FN(CreateToolhelp32Snapshot)(TH32CS_SNAPTHREAD, 0);
		if (LI_FN(Thread32First)(hSnapshot, &th32))
		{
			do
			{
				if (th32.th32OwnerProcessID == LI_FN(GetCurrentProcessId)() && th32.th32ThreadID != LI_FN(GetCurrentThreadId)())
				{
					HANDLE pThread = LI_FN(OpenThread)(THREAD_ALL_ACCESS, FALSE, th32.th32ThreadID);
					if (pThread)
					{
						LI_FN(SuspendThread)(pThread); CONTEXT context = { 0 };
						context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
						LI_FN(GetThreadContext)(pThread, &context);
						auto index = GetFreeIndex(context.Dr7);
						if (index < 0) continue;
						context.Dr7 |= 1 << (2 * index) | 0x100;
						if (context.Dr0 == NULL) *((DWORD_PTR*)&context.Dr0 + index) = prm->target;
						else
						{
							if (context.Dr1 == NULL) *((DWORD_PTR*)&context.Dr1 + index) = prm->target;
							else
							{
								if (context.Dr2 == NULL) *((DWORD_PTR*)&context.Dr2 + index) = prm->target;
								else
								{
									if (context.Dr3 == NULL) *((DWORD_PTR*)&context.Dr3 + index) = prm->target;
								}
							}
						}
						LI_FN(SetThreadContext)(pThread, &context);
						LI_FN(ResumeThread)(pThread); 
						LI_FN(CloseHandle)(pThread);
					}
				}
			} while (LI_FN(Thread32Next)(hSnapshot, &th32));
		}
		return true;
	}
public:
	static bool InstallHWBP(DWORD_PTR target, DWORD_PTR interceptor)
	{
		if (target == 0x0 || interceptor == 0x0) return false;
		if (hooks.find(target) != hooks.end()) return false;
		if (hooks.size() == 4) return false;
		static PRM_THREAD prm; prm.target = target; prm.interceptor = interceptor;
		HANDLE hThread = LI_FN(CreateThread)(nullptr, 0, (LPTHREAD_START_ROUTINE)installHWBP, &prm, 0, nullptr);
		LI_FN(WaitForSingleObject)(hThread, INFINITE);
		return true;
	}
private:
	CRITICAL_SECTION CriticalSection;
	static bool deleteHWBP(PPRM_THREAD prm)
	{
		auto it = hooks.find(prm->target);
		if (it == hooks.end()) return false;
		typedef ULONG(__stdcall* ptrRemoveVectoredExceptionHandler)(PVOID Handle);
		ptrRemoveVectoredExceptionHandler callRemoveVectoredExceptionHandler = (ptrRemoveVectoredExceptionHandler)
		LI_FN(GetProcAddress)(LI_FN(GetModuleHandleA)(xorstr_("kernel32.dll")), xorstr_("RemoveVectoredExceptionHandler"));
		hooks.erase(it); callRemoveVectoredExceptionHandler(hwbpHandler);
		THREADENTRY32 th32; HANDLE hSnapshot = NULL; th32.dwSize = sizeof(THREADENTRY32);
		hSnapshot = LI_FN(CreateToolhelp32Snapshot)(TH32CS_SNAPTHREAD, 0);
		if (LI_FN(Thread32First)(hSnapshot, &th32))
		{
			do
			{
				if (th32.th32OwnerProcessID == LI_FN(GetCurrentProcessId)() && th32.th32ThreadID != LI_FN(GetCurrentThreadId)())
				{
					HANDLE pThread = LI_FN(OpenThread)(THREAD_ALL_ACCESS, FALSE, th32.th32ThreadID);
					if (pThread)
					{
						LI_FN(SuspendThread)(pThread); CONTEXT context = { 0 };
						context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
						LI_FN(GetThreadContext)(pThread, &context);
						context.Dr7 = 0x0;
						*(DWORD_PTR*)&context.Dr0 = 0x0;
						*(DWORD_PTR*)&context.Dr1 = 0x0;
						*(DWORD_PTR*)&context.Dr2 = 0x0;
						*(DWORD_PTR*)&context.Dr3 = 0x0;
						LI_FN(SetThreadContext)(pThread, &context);
						LI_FN(ResumeThread)(pThread); 
						LI_FN(CloseHandle)(pThread);
					}
				}
			} while (LI_FN(Thread32Next)(hSnapshot, &th32));
		}
		return true;
	}
public:
	static bool DeleteHWBP(DWORD_PTR target)
	{
		if (target == 0x0 || hooks.empty()) return false;
		static PRM_THREAD prm; prm.target = target;
		HANDLE hThread = LI_FN(CreateThread)(nullptr, 0, (LPTHREAD_START_ROUTINE)deleteHWBP, &prm, 0, nullptr);
		LI_FN(WaitForSingleObject)(hThread, INFINITE);
		return true;
	}
};