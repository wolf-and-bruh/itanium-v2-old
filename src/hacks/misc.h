#pragma once
#include <Windows.h>
#include <string>

class CUserCmd;
namespace hacks
{
	void RunBunnyHop(CUserCmd* cmd) noexcept;
	void RunThirdperson() noexcept;
	void RunNoShakeCamera(CUserCmd* cmd) noexcept;
	void RunLuaScript(std::string string) noexcept;
}
