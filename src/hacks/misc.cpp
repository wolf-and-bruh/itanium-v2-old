#include "misc.h"

// access global variables
#include "../core/globals.h"

// access interfaces
#include "../core/interfaces.h"
#include "../core/config.h"
#include <iostream>
#include "../valve/ccvar.h"

// code

void hacks::RunBunnyHop(CUserCmd* cmd) noexcept
{
	float r = 1000 * 0.1;
	if (!(globals::localPlayer->GetFlags() & CEntity::FL_ONGROUND))
		cmd->buttons &= ~CUserCmd::IN_JUMP;
		if (configuration::BHOP_AutoStrafe && GetAsyncKeyState(VK_SPACE))
			cmd->forwardmove = configuration::BHOP_Speed * 0.015f;
			cmd->sidemove += (float)(((cmd->tick_count % 2) * 2) - 1) * r;
};

void hacks::RunThirdperson() noexcept
{
	if (configuration::VISUALS_Thirdperson == true)
	{
		
	}
	else if (configuration::VISUALS_Thirdperson == false)
	{

	}
}

void hacks::RunNoShakeCamera(CUserCmd* cmd) noexcept
{
	CVector aimPunch = globals::localPlayer->GetAimPunch();
	std::cout << aimPunch.x << aimPunch.y << aimPunch.z << std::endl;
	aimPunch = cmd->viewangles;
}

void hacks::RunLuaScript(std::string string) noexcept
{

}