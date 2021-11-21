#include "Hooks.h"
Hooks::Hooks() {}
Hooks::~Hooks() {}
Hooks::t_LuaLoadBuffer Hooks::callLuaLoadBuffer = nullptr;
Hooks::ptrAddDebugHook Hooks::callAddDebugHook = nullptr;
BYTE Hooks::prologue[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
void __stdcall Hooks::LogInFile(std::string log_name, const char* log, ...)
{
	char hack_dir[356]; memset(hack_dir, 0, sizeof(hack_dir));
	_getcwd(hack_dir, 356); char new_dir[500];
	memset(new_dir, 0, sizeof(new_dir));
	sprintf(new_dir, xorstr_("%s\\%s"), hack_dir, log_name.c_str());
	static bool once = false; if (!once)
	{
		FILE* hFile = fopen(new_dir, xorstr_("rb"));
		if (hFile) { fclose(hFile); DeleteFileA(new_dir); }
		once = true;
	}
	FILE* hFile = fopen(new_dir, xorstr_("a+"));
	if (hFile)
	{
		time_t t = std::time(0); tm* now = std::localtime(&t);
		char tmp_stamp[500]; memset(tmp_stamp, 0, sizeof(tmp_stamp));
		sprintf(tmp_stamp, xorstr_("[%d:%d:%d]"), now->tm_hour, now->tm_min, now->tm_sec);
		strcat(tmp_stamp, std::string(" " + std::string(log)).c_str());
		va_list arglist; va_start(arglist, log); vfprintf(hFile, tmp_stamp, arglist);
		va_end(arglist); fclose(hFile);
	}
}
DWORD Hooks::MakeJump(DWORD jmp_address, DWORD hookAddr, BYTE* prologue, size_t prologue_size)
{
	DWORD old_prot = 0x0;
	if (prologue == nullptr) return 0x0;
	VirtualProtect((void*)jmp_address, prologue_size, PAGE_EXECUTE_READWRITE, &old_prot);
	memcpy(prologue, (void*)jmp_address, prologue_size);
	BYTE addrToBytes[5] = { 0xE9, 0x90, 0x90, 0x90, 0x90 };
	DWORD JMPBytes = (hookAddr - jmp_address - 5);
	memcpy(&addrToBytes[1], &JMPBytes, 4);
	memcpy((void*)jmp_address, addrToBytes, 5);
	PVOID Trampoline = VirtualAlloc(0, (5 + (prologue_size - 5)), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	BYTE TrampolineBytes[5] = { 0xE9, 0x90, 0x90, 0x90, 0x90 };
	if (prologue_size > 5)
	{
		BYTE nop[] = { 0x90 };
		for (BYTE x = 0; x < (prologue_size - 5); x++) memcpy((void*)(jmp_address + 0x5 + x), nop, 1);
		memcpy(Trampoline, &prologue[3], (prologue_size - 3));
		DWORD Delta = (jmp_address + prologue_size) - (((DWORD)Trampoline + (prologue_size - 3)) + 5);
		memcpy(&TrampolineBytes[1], &Delta, 4);
		memcpy((void*)((DWORD)Trampoline + (prologue_size - 3)), TrampolineBytes, 5);
	}
	else
	{
		DWORD Delta = (jmp_address + prologue_size) - ((DWORD)Trampoline + 5);
		memcpy(&TrampolineBytes[1], &Delta, 4);
		memcpy(Trampoline, TrampolineBytes, 5);
	}
	VirtualProtect((void*)jmp_address, prologue_size, old_prot, 0);
	return (DWORD)Trampoline;
}
bool Hooks::RestorePrologue(DWORD addr, BYTE* prologue, size_t prologue_size)
{
	if (prologue == nullptr) return false;
	DWORD old_prot = 0;
	VirtualProtect((void*)addr, prologue_size, PAGE_EXECUTE_READWRITE, &old_prot);
	memcpy((void*)addr, prologue, prologue_size);
	VirtualProtect((void*)addr, prologue_size, old_prot, &old_prot);
	return true;
}
bool __fastcall Hooks::AddDebugHook(void *ECX, void *EDX, int hookType, void* functionRef, void* allowedNameList)
{
	return true;
}
int __cdecl Hooks::hkLuaLoadBuffer(void* L, const char* buff, size_t sz, const char* name)
{
	HWBP::DeleteHWBP((DWORD)callLuaLoadBuffer);
	//LogInFile("RLI.log", "[HOOK] Injected stub-code!\n");
	//std::string code = R"STUB(outputChatBox('Runtime Lua Injector loaded, use F5 to inject lua code', 255, 0, 0) window = guiCreateWindow (650, 250, 600, 500, "Runtime Lua Injector for MTA", false) guiSetVisible (window, false) guiSetInputMode ("no_binds_when_editing") tabPanel = guiCreateTabPanel ( 9, 25, 590, 412, false, window ) LuaIjector = guiCreateTab ( "Runtime Lua Injector", tabPanel ) luaButton = guiCreateButton ( 10, 345, 120, 35, "Execute", false, LuaIjector ) guiSetFont ( luaButton, "default-bold-small" ) closeButton = guiCreateButton (476, 450, 105, 37, "Close", false, window) guiSetFont (closeButton, "default-bold-small") LuaIjectorLabel = guiCreateLabel ( 10, 10, 200, 25, "Enter the code for the injection", false, LuaIjector ) guiSetFont ( LuaIjectorLabel, "default-bold-small" ) LuaMemo = guiCreateMemo ( 10, 30, 565, 305, "", false, LuaIjector ) bindKey ( "F5", 'down', function ( ) guiSetVisible ( window, not guiGetVisible ( window ) ); showCursor ( guiGetVisible ( window ) ); end) addEventHandler ( 'onClientGUIClick', root, function ( btn, state ) if source == luaButton then local text = guiGetText ( LuaMemo ) if text ~= "" then local func, eror = loadstring ( text ) if eror then outputChatBox ( "Injection error "..eror, 255, 0, 0 ) return end local textfunc = pcall ( func ) if textfunc then outputChatBox ("The result of injection: "..tostring ( textfunc ), 0, 255, 0 ) end end end if source == closeButton then guiSetVisible (window, false) showCursor (false) end end))STUB";
	int result = callLuaLoadBuffer(L, buff, sz, name);
	callLuaLoadBuffer(L, code.c_str(), code.size(), xorstr_("RLI"));
	return result;
}
bool Hooks::InstallHooks()
{
	code = (code + code2 + code3 + code4 + code5 + code6 + code7 + code8 + code9 + code10 + code11 + code12);
	//code = (code + code2 + code3);
	SigScan scan; while (!GetModuleHandleA(xorstr_("client.dll"))) Sleep(10);
	//LogInFile(xorstr_("RLI.log"), xorstr_("[INTERNAL] Found client.dll\n"));
	callLuaLoadBuffer = (t_LuaLoadBuffer)scan.FindPattern(xorstr_("client.dll"),
	xorstr_("\x55\x8B\xEC\x83\xEC\x08\x8B\x45\x0C\xFF"), xorstr_("xxxxxxxxxx"));
	if (callLuaLoadBuffer == nullptr) callLuaLoadBuffer = (t_LuaLoadBuffer)scan.FindPattern(xorstr_("lua5.1c.dll"),
	xorstr_("\x55\x8B\xEC\x83\xEC\x08\x8B\x45\x0C\xFF"), xorstr_("xxxxxxxxxx"));
	if (callLuaLoadBuffer != nullptr)
	{
		//LogInFile(xorstr_("RLI.log"), xorstr_("[RLI] Found address from sig1: 0x%X\n"), (DWORD)callLuaLoadBuffer);
		callAddDebugHook = (ptrAddDebugHook)scan.FindPattern(xorstr_("client.dll"),
		xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\x98\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x53\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\x45"),
		xorstr_("xxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxx"));
		//LogInFile(xorstr_("RLI.log", "[RLI] Found address from sig2: 0x%X\n"), (DWORD)callAddDebugHook);
		HWBP::InstallHWBP((DWORD)callLuaLoadBuffer, (DWORD)&hkLuaLoadBuffer);
		//MH_Initialize();
		//MH_CreateHook(callAddDebugHook, &AddDebugHook, reinterpret_cast<LPVOID*>(&callAddDebugHook));
		//MH_EnableHook(MH_ALL_HOOKS);
		return true;
	}
	//else LogInFile(xorstr_("RLI.log"), xorstr_("[ERROR] RLI can`t find a sig for injection.\n"));
	return false;
}