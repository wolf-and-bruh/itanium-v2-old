#include "aimbot.h"

// access global variables
#include "../core/globals.h"

// access interfaces
#include "../core/interfaces.h"
#include "../core/config.h"
#include <iostream>

void hacks::RunAimbot(CUserCmd* cmd) noexcept
{
	CVector bestAngle{};
	CTrace trace;
	float bestFov{ configuration::AIMBOT_BestFOV };

	for (int i = 1; i <= interfaces::globals->maxClients; i++)
	{
		CEntity* player = interfaces::entityList->GetEntityFromIndex(i);

		if (!player) continue;
		//if (player->IsDormant()) continue;
		if (player->GetHealth() <= 0) continue;
		if (player == globals::localPlayer) continue;

		// player's bone matrix
		CMatrix3x4 bones[128];
		if (!player->SetupBones(bones, 128, 256, interfaces::globals->currentTime))
			continue;

		// our eye pos
		CVector localEyePosition = globals::localPlayer->GetAbsOrigin();
		localEyePosition.z += 60;

		// our aim punch
		CVector aimPunch = globals::localPlayer->GetAimPunch();
		
		interfaces::engineTrace->TraceRay(
			CRay{ localEyePosition, bones[8].Origin()},
			MASK_SHOT,
			CTraceFilter{globals::localPlayer},
			trace
		);

		if (trace.fraction < 0.97f)
			return;

		CVector enemyAngle
		{
			(bones[8].Origin() - localEyePosition).ToAngle() - cmd->viewangles
		};

		if (const float fov = std::hypot(enemyAngle.x, enemyAngle.z))
		{
			bestFov = fov;
			bestAngle = enemyAngle;
		};
	}
	cmd->viewangles = cmd->viewangles + bestAngle.Scale(configuration::AIMBOT_Smoothness);
	if (trace.hitbox == HITBOX_HEAD && configuration::AIMBOT_Autoshoot == true) {
		cmd->buttons &= ~CUserCmd::ButtonFlags::IN_ATTACK;
	}
	else
	{
		cmd->buttons |= CUserCmd::ButtonFlags::IN_ATTACK;
	}
}