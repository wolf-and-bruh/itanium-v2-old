#pragma once
#include <string>
#include <vector>

enum LuaInterfaceType
{
	LUAINTERFACE_CLIENT = 0,
	LUAINTERFACE_SERVER = 1,
	LUAINTERFACE_MENU = 2
};

class CLuaShared
{
public:
    constexpr uintptr_t GetLuaInterface(LuaInterfaceType type) noexcept
    {
        return memory::Call<uintptr_t>(this, 6, type);
    }
};
