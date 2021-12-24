#include "Hooks.h"
Hooks::Hooks() {}
Hooks::~Hooks() {}
Hooks::t_LuaLoadBuffer Hooks::callLuaLoadBuffer = nullptr;
Hooks::ptrAddDebugHook Hooks::callAddDebugHook = nullptr;
Hooks::ptrDrawString Hooks::callDrawString = nullptr;
/*
* [province_bank] triggerServerEvent(args: 3) : { "bank:TakeMoneyBankAccount", elem:resource00001CA0, 123 }
Снять со счета
[province_bank] triggerServerEvent(args: 3) : { "bank:AddMoneyBankAccount", elem:resource00001CA0, 123 }
Внести на счет
[province_bank] triggerServerEvent(args: 4) : { "bank:SendToAnotherAccount", elem:resource00001CA0, 123, "920102" }
Перевести на счет
*/
BYTE Hooks::prologue[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

typedef bool(__cdecl* f_SendChat)(const char* szCommand, const char* szArguments, bool bHandleRemotely, bool bHandled, bool bIsScriptedBind);

f_SendChat sendMTAChat = nullptr;

bool __cdecl Hooks::SendMTACommand(const char* szCommand, const char* szArguments, bool bHandleRemotely, bool bHandled, bool bIsScriptedBind)
{
	LogInFile(xorstr_("RLI.log"), xorstr_("[SendMTACommand] %s\n"), szArguments);
	return sendMTAChat(szCommand, szArguments, bHandleRemotely, bHandled, bIsScriptedBind);
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
void* Hooks::LuaVM = nullptr;
int __cdecl Hooks::hkLuaLoadBuffer(void* L, const char* buff, size_t sz, const char* name)
{
	HWBP::DeleteHWBP((DWORD)callLuaLoadBuffer);
	LogInFile(xorstr_("RLI.log"), xorstr_("[HOOK] Injected stub-code!\n"));
	std::string code = xorstr_(R"STUB(outputChatBox('Runtime Lua Injector loaded, use F5 to inject lua code', 255, 0, 0) window = guiCreateWindow (650, 250, 600, 500, "Runtime Lua Injector for MTA", false) guiSetVisible (window, false) guiSetInputMode ("no_binds_when_editing") tabPanel = guiCreateTabPanel ( 9, 25, 590, 412, false, window ) LuaIjector = guiCreateTab ( "Runtime Lua Injector", tabPanel ) luaButton = guiCreateButton ( 10, 345, 120, 35, "Execute", false, LuaIjector ) guiSetFont ( luaButton, "default-bold-small" ) closeButton = guiCreateButton (476, 450, 105, 37, "Close", false, window) guiSetFont (closeButton, "default-bold-small") LuaIjectorLabel = guiCreateLabel ( 10, 10, 200, 25, "Enter the code for the injection", false, LuaIjector ) guiSetFont ( LuaIjectorLabel, "default-bold-small" ) LuaMemo = guiCreateMemo ( 10, 30, 565, 305, "", false, LuaIjector ) bindKey ( "F5", 'down', function ( ) guiSetVisible ( window, not guiGetVisible ( window ) ); showCursor ( guiGetVisible ( window ) ); end) addEventHandler ( 'onClientGUIClick', root, function ( btn, state ) if source == luaButton then local text = guiGetText ( LuaMemo ) if text ~= "" then local func, eror = loadstring ( text ) if eror then outputChatBox ( "Injection error "..eror, 255, 0, 0 ) return end local textfunc = pcall ( func ) if textfunc then outputChatBox ("The result of injection: "..tostring ( textfunc ), 0, 255, 0 ) end end end if source == closeButton then guiSetVisible (window, false) showCursor (false) end end))STUB");
	int result = callLuaLoadBuffer(L, buff, sz, name);
	callLuaLoadBuffer(L, code.c_str(), code.size(), xorstr_("RLI"));
	LuaVM = L;
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
std::string Hooks::cp1251_to_utf8(const char* str)
{
	std::string res;
	WCHAR* ures = NULL;
	char* cres = NULL;
	int result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
	if (result_u != 0)
	{
		ures = new WCHAR[result_u];
		if (MultiByteToWideChar(1251, 0, str, -1, ures, result_u))
		{
			int result_c = WideCharToMultiByte(CP_UTF8, 0, ures, -1, 0, 0, 0, 0);
			if (result_c != 0)
			{
				cres = new char[result_c];
				if (WideCharToMultiByte(CP_UTF8, 0, ures, -1, cres, result_c, 0, 0))
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
std::map<std::string, std::tuple<bool, Hooks::AWarnings>> Hooks::AntiFlood;
void Hooks::AddMessageToList(std::string message, AWarnings type)
{
	time_t t = std::time(0); tm* now = std::localtime(&t);
	char tmp_stamp[500]; memset(tmp_stamp, 0, sizeof(tmp_stamp));
	sprintf(tmp_stamp, xorstr_("[%d:%d]"), now->tm_hour, now->tm_min);
	strcat(tmp_stamp, std::string(" " + std::string(message)).c_str());
	if (AntiFlood.count(tmp_stamp) == 0)
	{
		LogInFile(xorstr_("RLI.log"), xorstr_("[RLI] %s\n"), tmp_stamp);
		AntiFlood.insert(AntiFlood.begin(), std::pair(tmp_stamp, std::make_tuple(false, type)));
	}
}
void __stdcall Hooks::AntiAFK()
{
	while (true)
	{
		Sleep(10000);
		POINT p; GetCursorPos(&p); SetCursorPos(p.x + 1, p.y);
	}
}
void __stdcall Hooks::CyclicAnswer(HMODULE mdl)
{
	while (true)
	{
		Sleep(1000);
		for (decltype(auto) it : AntiFlood)
		{
			if (!std::get<0>(it.second))
			{
				std::get<0>(it.second) = true;
				Sleep(rand() % 2000);
				sendMTAChat(xorstr_("start_ai"), cp1251_to_utf8(xorstr_("")).c_str(), true, false, false);
				Sleep(2500 + (rand() % 6000));
				PlaySoundA(MAKEINTRESOURCE(IDR_WAVE1), mdl, SND_RESOURCE | SND_ASYNC);
				int rnd = rand() % 5 + 1;
				if (rnd == 6) rnd = 1;
				if (std::get<1>(it.second) == AWarnings::WARN_NRP_CHAT_TASK)
				{
					//if (rnd == 1) sendMTAChat(xorstr_("b"), cp1251_to_utf8(xorstr_("Тут я")).c_str(), true, false, false);
					//else if (rnd == 2) sendMTAChat(xorstr_("b"), cp1251_to_utf8(xorstr_("Я тут")).c_str(), true, false, false);
					//else if (rnd == 3) sendMTAChat(xorstr_("b"), cp1251_to_utf8(xorstr_("Здесь а что?")).c_str(), true, false, false);
					//else if (rnd == 4) sendMTAChat(xorstr_("b"), cp1251_to_utf8(xorstr_("здесь, здесь")).c_str(), true, false, false);
					//else if (rnd == 5) sendMTAChat(xorstr_("b"), cp1251_to_utf8(xorstr_("Тут, тут...")).c_str(), true, false, false);
				}
				else
				{
					//if (rnd == 1) sendMTAChat(xorstr_("say"), cp1251_to_utf8(xorstr_("Тут я")).c_str(), true, false, false);
					//else if (rnd == 2) sendMTAChat(xorstr_("say"), cp1251_to_utf8(xorstr_("Я тут")).c_str(), true, false, false);
					//else if (rnd == 3) sendMTAChat(xorstr_("say"), cp1251_to_utf8(xorstr_("Здесь а что?")).c_str(), true, false, false);
					//else if (rnd == 4) sendMTAChat(xorstr_("say"), cp1251_to_utf8(xorstr_("здесь, здесь")).c_str(), true, false, false);
					//else if (rnd == 5) sendMTAChat(xorstr_("say"), cp1251_to_utf8(xorstr_("Тут, тут...")).c_str(), true, false, false);
				}
				Sleep(1000 + (rand() % 2000));
				sendMTAChat(xorstr_("start_ai"), cp1251_to_utf8(xorstr_("")).c_str(), true, false, false);
			}
		}
	}
}
bool Hooks::IsMathContains(std::string msg)
{
	if (msg.find('+') != std::string::npos || msg.find('-') != std::string::npos || msg.find('*') != std::string::npos
		|| msg.find('/') != std::string::npos || findStringIC(msg, xorstr_("плюс")) || findStringIC(msg, xorstr_("минус"))
		|| findStringIC(msg, xorstr_("умножить")) || findStringIC(msg, xorstr_("разделить"))) return true;
	return false;
}
std::string MathResolver(std::string msg)
{
	std::string resolved = "";
	return resolved;
}
void __fastcall Hooks::DrawString(void* ECX, void* EDX, int uiLeft, int uiTop, int uiRight, int uiBottom,
unsigned long ulColor, char* szText, float fScaleX, float fScaleY,
unsigned long ulFormat, void* pDXFont, bool bOutline)
{
	if (szText != nullptr)
	{
		std::string txt = utf8_to_cp1251(szText); 
		if (findStringIC(txt.c_str(), xorstr_("телепортированы")))
		{
			for (int x = 0; x < strlen(szText); x++)
			{
				szText[x] = ' ';
			}
			sendMTAChat(xorstr_("start_ai"), cp1251_to_utf8(xorstr_("")).c_str(), true, false, false);
			PlaySoundA(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandleA("RLI.dll"), SND_RESOURCE | SND_ASYNC);
		}
		if (findStringIC(txt.c_str(), xorstr_("Admin")) || findStringIC(txt.c_str(), xorstr_("Админ")))
		{
			if (sendMTAChat)
			{
				if (!IsMathContains(txt) && 
				(findStringIC(txt.c_str(), xorstr_("тут")) || findStringIC(txt.c_str(), xorstr_("здесь"))))
				{
					for (int x = 0; x < strlen(szText); x++)
					{
						szText[x] = ' ';
					}
					if (findStringIC(txt.c_str(), xorstr_("/b"))) AddMessageToList(txt, AWarnings::WARN_NRP_CHAT_TASK);
					else AddMessageToList(txt, AWarnings::WARN_CHAT_TASK);
				}
				else
				{
					// unhandled warning (only once per game session!)
					static bool once = false;
					if (!once)
					{
						AddMessageToList(txt, AWarnings::UNHANDLED_WARNING);
						once = true;
					}
				}
			}
		}
	}
	callDrawString(ECX, uiLeft, uiTop, uiRight, uiBottom, ulColor, szText, fScaleX, fScaleY,
	ulFormat, pDXFont, bOutline);
}
void FuckArthemidaIntegrity() // Обход Артемиды (Ебет в очко проверку памяти античита)
{
	MODULEINFO modinfo = { 0 }; typedef NTSTATUS(__stdcall* pfnNtQueryInformationThread)(
		HANDLE ThreadHandle,
		THREAD_INFORMATION_CLASS ThreadInformationClass,
		PVOID ThreadInformation,
		ULONG ThreadInformationLength,
		PULONG ReturnLength
		);
	pfnNtQueryInformationThread fnNtQueryInformationThread = (pfnNtQueryInformationThread)
		GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationThread");
	K32GetModuleInformation(GetCurrentProcess(), GetModuleHandleA("core.dll"), &modinfo, sizeof(MODULEINFO));
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (h != INVALID_HANDLE_VALUE)
	{
		THREADENTRY32 te{ 0 }; te.dwSize = sizeof(te);
		if (Thread32First(h, &te))
		{
			do
			{
				if (te.th32OwnerProcessID == GetCurrentProcessId())
				{
					HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te.th32ThreadID);
					if (hThread)
					{
						DWORD tempBase = NULL; fnNtQueryInformationThread(hThread,
							(THREAD_INFORMATION_CLASS)9, &tempBase, sizeof(DWORD), 0);
						if (tempBase >= (DWORD)modinfo.lpBaseOfDll &&
							tempBase <= ((DWORD)modinfo.lpBaseOfDll + modinfo.SizeOfImage)) SuspendThread(hThread);
						CloseHandle(hThread);
					}
				}
				te.dwSize = sizeof(te);
			} while (Thread32Next(h, &te));
		}
		CloseHandle(h);
	}
}
/*
	LuaLoadBuffer
	\x55\x8B\xEC\x83\xEC\x38\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xFC\x8B\x45\x14\x53\x8B
	xxxxxxx????xxxxxxxxxx
	luaL_loadbuffer
	\x55\x8B\xEC\x83\xEC\x08\x56\x8B\x75\x0C\x57\xFF
	xxxxxxxxxxxx
*/
bool Hooks::InstallHooks(HMODULE mdl)
{
	MH_Initialize(); while (!LI_FN(GetModuleHandleA)(xorstr_("client.dll"))) LI_FN(Sleep)(10);
	FuckArthemidaIntegrity();
	SigScan scan; callDrawString = (ptrDrawString)scan.FindPattern(xorstr_("core.dll"),
	xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\xB4\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x53"),
	xorstr_("xxxxxx????xxxxxxxxxxxxxx????xxxxxx"));
	if (callDrawString != NULL) LogInFile(xorstr_("RLI.log"), xorstr_("[RLI] Found address from signature 0!\n"));
	MH_CreateHook(callDrawString, &DrawString, reinterpret_cast<LPVOID*>(&callDrawString));
	MH_EnableHook(MH_ALL_HOOKS);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	LogInFile(xorstr_("RLI.log"), xorstr_("[INTERNAL] Found client.dll\n"));
	callLuaLoadBuffer = (t_LuaLoadBuffer)scan.FindPattern(xorstr_("client.dll"),
	xorstr_("\x55\x8B\xEC\x83\xEC\x08\x56\x8B\x75\x0C\x57\xFF"), xorstr_("xxxxxxxxxxxx"));
	if (callLuaLoadBuffer != nullptr)
	{
		LogInFile(xorstr_("RLI.log"), xorstr_("[RLI] Found address from signature 1! 0x%X\n"), (DWORD)callLuaLoadBuffer);
		sendMTAChat = (f_SendChat)scan.FindPattern(xorstr_("client.dll"),
		xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x80\x7D\x14\x00\x8B\x75\x0C\x8B\x7D\x08\x89\xB5\x00\x00\x00\x00\x0F\x85\x00\x00\x00\x00\x80\x7D\x10\x00\x75\x1A\x68\x00\x00\x00\x00\x57\xE8\x00\x00\x00\x00\x83\xC4\x08"),
		xorstr_("xxxxxx????xx????xxx????x????xxxxxxxxxxxxx????xxxxxxxxxxxx????xx????xxxxxxx????xx????xxx"));
		if (sendMTAChat)
		{
			LogInFile(xorstr_("RLI.log"), xorstr_("[RLI] Found address from signature 3!\n"));
			//MH_CreateHook(sendMTAChat, &SendMTACommand, reinterpret_cast<LPVOID*>(&sendMTAChat));
			//MH_EnableHook(MH_ALL_HOOKS);
		}
		//callAddDebugHook = (ptrAddDebugHook)scan.FindPattern(xorstr_("client.dll"),
		//xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\x98\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x53\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\x45"),
		//xorstr_("xxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxx"));
		//LogInFile(xorstr_("RLI.log"), xorstr_("[RLI] Found address from signature2!\n"));
		//HWBP::InstallHWBP((DWORD)callLuaLoadBuffer, (DWORD)&hkLuaLoadBuffer);
		/*MH_CreateHook(callAddDebugHook, &AddDebugHook, reinterpret_cast<LPVOID*>(&callAddDebugHook));
		MH_EnableHook(MH_ALL_HOOKS);*/
		//LI_FN(CreateThread)(nullptr, 0, (LPTHREAD_START_ROUTINE)CyclicAnswer, mdl, 0, nullptr);
		//LI_FN(CreateThread)(nullptr, 0, (LPTHREAD_START_ROUTINE)AntiAFK, nullptr, 0, nullptr);
		return true;
	}
	else LogInFile(xorstr_("RLI.log"), xorstr_("[ERROR] RLI can`t find a sig for injection.\n"));
	return false;
}