#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <thread>
#include <iostream>

// expose our cheat to main.cpp
#include "core/hooks.h"
#include "core/d3d9hook.h"

const char* asciiart = R"(
██ ████████  █████  ███    ██ ██ ██    ██ ███    ███ 
██    ██    ██   ██ ████   ██ ██ ██    ██ ████  ████ 
██    ██    ███████ ██ ██  ██ ██ ██    ██ ██ ████ ██ 
██    ██    ██   ██ ██  ██ ██ ██ ██    ██ ██  ██  ██ 
██    ██    ██   ██ ██   ████ ██  ██████  ██      ██ 
)";

// for fast printing and typing
void print(const char* str)
{
	std::cout << str << std::endl;
}

// setup our cheat & unload it when exit key is pressed
DWORD WINAPI Setup(LPVOID lpParam)
{

	//memory::Setup();		// find signatures
	interfaces::Setup();    // capture interfaces
	netvars::Setup();		// dump latest offsets
	hooks::Setup();			// place hooks
	d3d9hook::Init();		// initialize d3d9 hook

	AllocConsole();
	freopen("CONOUT$", "w", stdout); // I've also tried CON and whatnot
	SetConsoleTitle("Itanium Logging Console");

	std::cout << asciiart << std::endl;
	std::cout << "" << std::endl;
	std::cout << "GlobalVars -> 0x" << std::hex << (DWORD)interfaces::globals << std::endl;
	std::cout << "ClientMode -> 0x" << std::hex << (DWORD)interfaces::clientMode << std::endl;
	std::cout << "Client -> 0x" << std::hex << (DWORD)interfaces::client << std::endl;
	std::cout << "Engine -> 0x" << std::hex << (DWORD)interfaces::engine << std::endl;
	std::cout << "EntityList -> 0x" << std::hex << (DWORD)interfaces::entityList << std::endl;
	std::cout << "StudioRender -> 0x" << std::hex << (DWORD)interfaces::studioRender << std::endl;
	std::cout << "ConVar -> 0x" << std::hex << (DWORD)interfaces::cvar << std::endl;
	std::cout << "LuaShared -> 0x" << std::hex << (DWORD)interfaces::luaShared << std::endl;

	// sleep our thread until unload key is pressed
	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	hooks::Destroy();		// restore hooks
	FreeConsole();
	kiero::shutdown();

	// unload library
	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	// dll is being loaded
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		// disable thread notifications
		DisableThreadLibraryCalls(hinstDLL);

		// create our "Setup" thread
		const HANDLE hThread = CreateThread(
			nullptr,
			NULL,
			Setup,
			hinstDLL,
			NULL,
			nullptr
		);

		// free thread handle because we have no use for it
		if (hThread)
			CloseHandle(hThread);
	}

	// successful DLL_PROCESS_ATTACH
	return TRUE;
}
