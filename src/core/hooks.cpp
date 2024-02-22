#include "hooks.h"
#include "d3d9hook.h"

// include minhook for epic hookage
#include "../../ext/minhook/minhook.h"
#include "../../ext/x86retspoof/x86RetSpoof.h"

#include "globals.h"
#include "config.h"

#include <intrin.h>
#include <thread>
#include <iostream>
#include <Windows.h>

#include "../hacks/misc.h"
#include "../hacks/aimbot.h"
#include "../hacks/esp.h"
#include "utils.h"

void hooks::Setup() noexcept
{
	MH_Initialize();

	// AllocKeyValuesMemory hook
	MH_CreateHook(
		memory::Get(interfaces::keyValuesSystem, 1),
		&AllocKeyValuesMemory,
		reinterpret_cast<void**>(&AllocKeyValuesMemoryOriginal)
	);

	// CreateMove hook
	MH_CreateHook(
		memory::Get(interfaces::clientMode, 21),
		&CreateMove,
		reinterpret_cast<void**>(&CreateMoveOriginal)
	);

	// DrawModelExecute hook
	//MH_CreateHook(
	//	memory::Get(interfaces::modelRender, 20),
	//	&DrawModelExecute,
	//	reinterpret_cast<void**>(&DrawModelExecuteOriginal)
	//);

	// PaintTraverse hook
	MH_CreateHook(
		memory::Get(interfaces::panel, 41),
		&PaintTraverse,
		reinterpret_cast<void**>(&PaintTraverseOriginal)
	);

	// RunStringEx hook
	MH_CreateHook(
		memory::Get(interfaces::luaShared, 111),
		&RunString,
		reinterpret_cast<void**>(&RunStringOriginal)
	);

	MH_EnableHook(0);
}

void hooks::Destroy() noexcept
{
	// restore hooks
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);

	// uninit minhook
	MH_Uninitialize();
}

void* __stdcall hooks::AllocKeyValuesMemory(const std::int32_t size) noexcept
{
	// if function is returning to speficied addresses, return nullptr to "bypass"
	if (const std::uint32_t address = reinterpret_cast<std::uint32_t>(_ReturnAddress());
		address == reinterpret_cast<std::uint32_t>(memory::allocKeyValuesEngine) ||
		address == reinterpret_cast<std::uint32_t>(memory::allocKeyValuesClient)) 
		return nullptr;

	// return original
	return AllocKeyValuesMemoryOriginal(interfaces::keyValuesSystem, size);
}

bool __stdcall hooks::CreateMove(float frameTime, CUserCmd* cmd) noexcept
{
	static const auto sequence = reinterpret_cast<std::uintptr_t>(memory::PatternScan("client.dll", "FF 23"));
	const auto result = x86RetSpoof::invokeStdcall<bool>((uintptr_t)hooks::CreateMoveOriginal, sequence, frameTime, cmd);

	// make sure this function is being called from CInput::CreateMove
	if (!cmd || !cmd->command_number)
		return result;

	// this would be done anyway by returning true
	if (CreateMoveOriginal(interfaces::clientMode, frameTime, cmd))
		interfaces::engine->SetViewAngles(cmd->viewangles);

	// get our local player here
	globals::UpdateLocalPlayer();

	if (globals::localPlayer && globals::localPlayer->GetHealth() > 0)
	{
		if (cmd->istyping)
			cmd->istyping = false;

		if (configuration::BHOP_Bhop)
			hacks::RunBunnyHop(cmd);
		if (configuration::AIMBOT_Aimbotting)
			hacks::RunAimbot(cmd);
		if (configuration::MISC_NoBobbing)
			hacks::RunNoShakeCamera(cmd);
	}

	return false;
}

void __fastcall hooks::DrawModelExecute(CModelRender* _this, void* edx, CModelRender* modelrender, const DrawModelState_t& dmstate, const ModelRenderInfo_t* mrinfo, CMatrix3x4* pCustomBoneToWorld) noexcept
{
	DrawModelExecuteOriginal(interfaces::modelRender, edx, modelrender, dmstate, mrinfo, pCustomBoneToWorld);
}

void __stdcall hooks::PaintTraverse(std::uintptr_t vguiPanel, bool forceRepaint, bool allowForce) noexcept
{
	// make sure we have the correct panel
	if (vguiPanel == interfaces::engineVGui->GetPanel(PANEL_CLIENTDLL))
	{
		// make sure local ply is valid && we are in-game
		if (globals::localPlayer && interfaces::engine->IsInGame())
		{
			if (configuration::VISUALS_2DBoxESP)
				for (int i = 1; i <= interfaces::globals->maxClients; ++i)
				{
					CEntity* player = interfaces::entityList->GetEntityFromIndex(i);

					// make sure player is valid
					if (!player) continue;
					if (!player->IsPlayer()) continue;
					if (player->GetHealth() == 0) continue;
					if (player == globals::localPlayer) continue;

					// player's bone matrix
					CMatrix3x4 bones[128];
					if (!player->SetupBones(bones, 128, 0x7FF00, interfaces::globals->currentTime))
						continue;

					// screen position of head
					CVector top;
					if (interfaces::debugOverlay->ScreenPosition(bones[8].Origin() + CVector{0.f, 0.f, 11.f}, top))
						continue;

					// screen pos of feet
					CVector bottom;
					if (interfaces::debugOverlay->ScreenPosition(player->GetAbsOrigin() - CVector{0.f, 0.f, 9.f}, bottom))
						continue;

					// height of box
					const float h = bottom.y - top.y;

					// use the height to determine a width
					const float w = h * 0.3f;

					const auto left = static_cast<int>(top.x - w);
					const auto right = static_cast<int>(top.x + w);

					// set draw color to white
					interfaces::surface->DrawSetColor(configuration::VISUALS_ESPColor[0] * 255, configuration::VISUALS_ESPColor[1] * 255, configuration::VISUALS_ESPColor[2] * 255, 255);

					// draw normal
					interfaces::surface->DrawOutlinedRect(left, top.y, right, bottom.y);
					interfaces::surface->DrawSetTextPos(100, 100);
					interfaces::surface->DrawPrintText(L"KKKKKKKKKKK", 12, EFontDrawType::FONT_DRAW_DEFAULT);
				}

			if (configuration::VISUALS_SnaplineESP)
				for (int i = 1; i <= interfaces::globals->maxClients; ++i)
				{
					CEntity* player = interfaces::entityList->GetEntityFromIndex(i);

					// make sure player is valid
					if (!player)
						continue;

					//if (!player->IsAlive())
					//	continue;

					// player's bone matrix
					CMatrix3x4 bones[128];
					if (!player->SetupBones(bones, 128, 0x7FF00, interfaces::globals->currentTime))
						continue;

					// screen pos of feet
					CVector screenpos;
					interfaces::debugOverlay->ScreenPosition(bones[8].Origin(), screenpos);
					interfaces::surface->DrawSetColor(configuration::VISUALS_ESPColor[0] * 255, configuration::VISUALS_ESPColor[1] * 255, configuration::VISUALS_ESPColor[2] * 255, 255);
					interfaces::surface->DrawOutlinedRect(1760 / 2, 990, screenpos.x, screenpos.y);
				}
		}
	}
	// call the og function
	PaintTraverseOriginal(interfaces::panel, vguiPanel, forceRepaint, allowForce);
}

bool __stdcall hooks::RunString(PVOID _this, const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns) noexcept
{
	MessageBoxA(NULL, "RunStringEx hook", "Itanium", MB_OK);
	std::string cvarName = utils::RandomString(10);
	std::string toRun = "CreateClientConVar(\"";
	toRun += cvarName;
	toRun += "\", \"\", true, false) :SetString(GetHostName() .. \" - \" ..game.GetIPAddress())";

	if (!strcmp(filename, "LuaCmd") || !strcmp(filename, "RunString(Ex)") || !strlen(filename))
		return RunStringOriginal(_this, filename, path, stringToRun, run, printErrors, dontPushErrors, noReturns);

	std::string lastFileName = std::string(filename);
	// To those not understanding what this is: this runs a lua script that sets a convar as "servername - serverip", and I just retrieve it and use it to save.
	RunStringOriginal(_this, filename, path, toRun.c_str(), run, printErrors, dontPushErrors, noReturns);
	// This is causing me problems in the x86 implementation...
	// For some reasons, calling it will simply make you crash... Tried fixing in a lots of ways, but just can't figure it out yet and i'm lazy to deeply search, so whoever fixes this, the cheat will work in X86 without any problems as it was first made to work with both.
	uintptr_t cvar = interfaces::cvar->FindVar(cvarName.c_str());
	
	if (!cvar)
		return RunStringOriginal(_this, filename, path, stringToRun, run, printErrors, dontPushErrors, noReturns);
	
	std::string ip = utils::CVarStr(cvar);
	
	utils::Fix(ip); // Fix = make it something "save'able", as some characters are blacklisted for file names.
	if (ip.find(" - loopback") != std::string::npos)
		return RunStringOriginal(_this, filename, path, stringToRun, run, printErrors, dontPushErrors, noReturns);

	std::string SavePath = "C:/GaztoofScriptHook/" + ip + "/" + std::string(filename);

	utils::Sanitize(SavePath);
	utils::StrToAscii(SavePath);
	std::string extension = utils::ToLower(utils::GetExtension(SavePath));
	if (extension == ".lua")
	{
		utils::CreateDirectoryRec((SavePath));
		std::ofstream outfile(SavePath);
		outfile << stringToRun << std::endl;
		std::cout << "Downloading file " + std::string(filename) << std::endl;
	}

	return RunStringOriginal(_this, filename, path, stringToRun, run, printErrors, dontPushErrors, noReturns);
}