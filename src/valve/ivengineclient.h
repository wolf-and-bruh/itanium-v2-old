#pragma once
#include "../util/memory.h"

#include "cvector.h"
#include "cmatrix.h"
#include "ispatialquery.h"
#include <Windows.h>

typedef struct player_info_s
{
	char name[128];
	int userID; // local server user ID, unique while server is running <- THIS IS NOT STEAMID
	char guid[33]; // that is Steamid
	unsigned int friendsid;
	char friendsname[128];
	bool fakeplayer; // true, if player is a bot controlled by game.dll
	bool ishltv;
	unsigned int customfiles[4]; // custom files CRC for this player
	unsigned char filesdownloaded; // this counter increases each time the server downloaded a new file
} player_info_t;

template<typename Func> Func getvfunc(PVOID Base, DWORD Index)
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];
	return (Func)(dwAddress);
}

class IVEngineClient
{
public:
	constexpr void GetScreenSize(std::int32_t& width, std::int32_t& height) noexcept
	{
		memory::Call<void>(this, 5, std::ref(width), std::ref(height));
	}

	// returns index of local player
	constexpr std::int32_t GetLocalPlayerIndex() noexcept 
	{
		return memory::Call<std::int32_t>(this, 12);
	}

	constexpr void SetViewAngles(const CVector& viewAngles) noexcept 
	{
		memory::Call<void, const CVector&>(this, 20, viewAngles);
	}

	// returns true if in-game
	constexpr bool IsInGame() noexcept 
	{
		return memory::Call<bool>(this, 26);
	}

	constexpr const CMatrix4x4& WorldToScreenMatrix() noexcept
	{
		return memory::Call<const CMatrix4x4&>(this, 36);
	}

	constexpr ISpacialQuery* GetBSPTreeQuery() noexcept
	{
		return memory::Call<ISpacialQuery*>(this, 42);
	}

	constexpr void GetViewAngles(const CVector& viewAngles) noexcept
	{
		memory::Call<void, const CVector&>(this, 19, viewAngles);
	}

	player_info_t GetPlayerInfo(int idx) {
		player_info_t p_info;

		typedef bool(__thiscall* OriginalFn)(void*, int entityIndex, player_info_t& playerInfo);
		getvfunc<OriginalFn>(this, 8)(this, idx, p_info);

		return p_info;
	}
};
