#include "Hooks.h"
Hooks::Hooks() {}
Hooks::~Hooks() {}
Hooks::t_LuaLoadBuffer Hooks::callLuaLoadBuffer = nullptr;
Hooks::ptrAddDebugHook Hooks::callAddDebugHook = nullptr;
Hooks::ptrDrawString Hooks::callDrawString = nullptr;
BYTE Hooks::prologue[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

typedef bool(__cdecl* f_SendChat)(const char* szCommand, const char* szArguments, bool bHandleRemotely, bool bHandled, bool bIsScriptedBind);

f_SendChat sendMTAChat = nullptr;

bool __cdecl Hooks::SendMTACommand(const char* szCommand, const char* szArguments)
{
	if (sendMTAChat == nullptr)
	{
		LogInFile(xorstr_("RLI.log"), xorstr_("[RLI] Attempt to call nullptr in SendMTACommand!\n"));
		return false;
	}

	return sendMTAChat(szCommand, szArguments, true, false, false);
}

void __stdcall Hooks::LogInFile(std::string log_name, const char* log, ...)
{
	char hack_dir[356]; memset(hack_dir, 0, sizeof(hack_dir));
	_getcwd(hack_dir, 356); char new_dir[500];
	memset(new_dir, 0, sizeof(new_dir));
	sprintf(new_dir, xorstr_("%s\\%s"), hack_dir, log_name.c_str());
	static bool once = false; if (!once)
	{
		FILE* hFile = fopen(new_dir, xorstr_("rb"));
		if (hFile) { fclose(hFile); LI_FN(DeleteFileA)(new_dir); }
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

bool __fastcall Hooks::AddDebugHook(void *ECX, void *EDX, int hookType, void* functionRef, void* allowedNameList)
{
	return true;
}

int __cdecl Hooks::hkLuaLoadBuffer(void* L, const char* buff, size_t sz, const char* name)
{
	HWBP::DeleteHWBP((DWORD)callLuaLoadBuffer);
	LogInFile(xorstr_("RLI.log"), xorstr_("[HOOK] Injected stub-code!\n"));
	//std::string code = xorstr_(R"STUB(outputChatBox('Runtime Lua Injector loaded, use F5 to inject lua code', 255, 0, 0) window = guiCreateWindow (650, 250, 600, 500, "Runtime Lua Injector for MTA", false) guiSetVisible (window, false) guiSetInputMode ("no_binds_when_editing") tabPanel = guiCreateTabPanel ( 9, 25, 590, 412, false, window ) LuaIjector = guiCreateTab ( "Runtime Lua Injector", tabPanel ) luaButton = guiCreateButton ( 10, 345, 120, 35, "Execute", false, LuaIjector ) guiSetFont ( luaButton, "default-bold-small" ) closeButton = guiCreateButton (476, 450, 105, 37, "Close", false, window) guiSetFont (closeButton, "default-bold-small") LuaIjectorLabel = guiCreateLabel ( 10, 10, 200, 25, "Enter the code for the injection", false, LuaIjector ) guiSetFont ( LuaIjectorLabel, "default-bold-small" ) LuaMemo = guiCreateMemo ( 10, 30, 565, 305, "", false, LuaIjector ) bindKey ( "F5", 'down', function ( ) guiSetVisible ( window, not guiGetVisible ( window ) ); showCursor ( guiGetVisible ( window ) ); end) addEventHandler ( 'onClientGUIClick', root, function ( btn, state ) if source == luaButton then local text = guiGetText ( LuaMemo ) if text ~= "" then local func, eror = loadstring ( text ) if eror then outputChatBox ( "Injection error "..eror, 255, 0, 0 ) return end local textfunc = pcall ( func ) if textfunc then outputChatBox ("The result of injection: "..tostring ( textfunc ), 0, 255, 0 ) end end end if source == closeButton then guiSetVisible (window, false) showCursor (false) end end))STUB");
	int result = callLuaLoadBuffer(L, buff, sz, name);
	callLuaLoadBuffer(L, code.c_str(), code.size(), xorstr_("RLI"));
	return result;
}
std::string Hooks::utf8_to_cp1251(const char* str) 
{
	std::string res;
	WCHAR* ures = NULL;
	char* cres = NULL;
	int result_u = MultiByteToWideChar(CP_UTF8, 0, str, -1, 0, 0);
	if (result_u != 0)
	{
		ures = new WCHAR[result_u];
		if (MultiByteToWideChar(CP_UTF8, 0, str, -1, ures, result_u))
		{
			int result_c = WideCharToMultiByte(1251, 0, ures, -1, 0, 0, 0, 0);
			if (result_c != 0)
			{
				cres = new char[result_c];
				if (WideCharToMultiByte(1251, 0, ures, -1, cres, result_c, 0, 0))
				{
					res = cres;
				}
			}
		}
	}
	delete[] ures, cres;
	return res;
}
bool Hooks::findStringIC(const std::string& strHaystack, const std::string& strNeedle)
{
	auto it = std::search(strHaystack.begin(), strHaystack.end(),
	strNeedle.begin(), strNeedle.end(),
	[](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); });
	return (it != strHaystack.end());
}
void __fastcall Hooks::DrawString(void* ECX, void* EDX, int uiLeft, int uiTop, int uiRight, int uiBottom,
unsigned long ulColor, const char* szText, float fScaleX, float fScaleY,
unsigned long ulFormat, void* pDXFont, bool bOutline)
{
	if (szText != nullptr)
	{
		//Администратор Dmitry_Soprano[72] для Austin_Torvalds[204]: Вы тут? Ответ в /b
		std::string txt = utf8_to_cp1251(szText); // Make anti-flood!!!!!!!!!
		if (findStringIC(txt.c_str(), xorstr_("Admin")) || findStringIC(txt.c_str(), xorstr_("Админ")))
		LogInFile(xorstr_("RLI.log"), xorstr_("[DrawString] %s\n"), txt.c_str());
	}
	callDrawString(ECX, uiLeft, uiTop, uiRight, uiBottom, ulColor, szText, fScaleX, fScaleY,
	ulFormat, pDXFont, bOutline);
}

bool Hooks::InstallHooks()
{
	code = (code + code2 + code3 + code4 + code5 + code6); MH_Initialize();
	SigScan scan; callDrawString = (ptrDrawString)scan.FindPattern(xorstr_("core.dll"),
	xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\xB4\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x53"),
	xorstr_("xxxxxx????xxxxxxxxxxxxxx????xxxxxx"));
	if (callDrawString != NULL) LogInFile(xorstr_("RLI.log"), xorstr_("[RLI] Found address from signature 0!\n"));
	MH_CreateHook(callDrawString, &DrawString, reinterpret_cast<LPVOID*>(&callDrawString));
	MH_EnableHook(MH_ALL_HOOKS);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (!LI_FN(GetModuleHandleA)(xorstr_("client.dll"))) LI_FN(Sleep)(10);
	LogInFile(xorstr_("RLI.log"), xorstr_("[INTERNAL] Found client.dll\n"));
	callLuaLoadBuffer = (t_LuaLoadBuffer)scan.FindPattern(xorstr_("client.dll"),
	xorstr_("\x55\x8B\xEC\x83\xEC\x08\x8B\x45\x0C\xFF"), xorstr_("xxxxxxxxxx"));
	if (callLuaLoadBuffer == nullptr) callLuaLoadBuffer = (t_LuaLoadBuffer)scan.FindPattern(xorstr_("lua5.1c.dll"),
	xorstr_("\x55\x8B\xEC\x83\xEC\x08\x8B\x45\x0C\xFF"), xorstr_("xxxxxxxxxx"));
	if (callLuaLoadBuffer != nullptr)
	{
		LogInFile(xorstr_("RLI.log"), xorstr_("[RLI] Found address from signature 1!\n"));
		//callAddDebugHook = (ptrAddDebugHook)scan.FindPattern(xorstr_("client.dll"),
		//xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\x98\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x53\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\x45"),
		//xorstr_("xxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxx"));
		//LogInFile(xorstr_("RLI.log"), xorstr_("[RLI] Found address from signature2!\n"));
		HWBP::InstallHWBP((DWORD)callLuaLoadBuffer, (DWORD)&hkLuaLoadBuffer);
		/*MH_CreateHook(callAddDebugHook, &AddDebugHook, reinterpret_cast<LPVOID*>(&callAddDebugHook));
		MH_EnableHook(MH_ALL_HOOKS);*/
		return true;
	}
	else LogInFile(xorstr_("RLI.log"), xorstr_("[ERROR] RLI can`t find a sig for injection.\n"));
	return false;
}