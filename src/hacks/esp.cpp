#include "esp.h"

// access global variables
#include "../core/globals.h"
#include "../core/config.h"

// access interfaces
#include "../core/interfaces.h"
#include "../core/d3d9hook.h"
#include <iostream>

void hacks::Run2DBoxESP() noexcept
{
	for (int i = 1; i <= 64; i++)
	{
		CEntity* player = interfaces::entityList->GetEntityFromIndex(i);

		if (!player) continue;
		if (!player->IsPlayer()) continue;
		if (player->GetHealth() == 0) continue;
		if (player == globals::localPlayer) continue;

		CVector screenpos;
		interfaces::surface->DrawFilledRect(100, 100, 100, 100);
		if (!interfaces::debugOverlay->ScreenPosition(player->GetAbsOrigin(), screenpos))
			std::cout << "dfgsdgd";
	}
}