#pragma once

class CEntity;
namespace globals
{
	inline CEntity* localPlayer = nullptr;
	
	inline int currentTab;

	// update the local player pointer
	void UpdateLocalPlayer() noexcept;
}