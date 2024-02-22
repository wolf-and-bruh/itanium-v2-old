#pragma once
#include "../util/memory.h"
#include "../core/netvars.h"

#include "cclientclass.h"
#include "cvector.h"
#include "cmatrix.h"

class CEntity;
class IClientUnknown
{
public:
	constexpr CEntity* GetBaseEntity() noexcept
	{
		return memory::Call<CEntity*>(this, 7);
	}
};

class IClientRenderable
{
public:
	constexpr IClientUnknown* GetIClientUnknown() noexcept
	{
		return memory::Call<IClientUnknown*>(this, 0);
	}
};

class CModel;
class CEntity
{
public:
	enum EFlags : std::int32_t
	{
		FL_ONGROUND = (1 << 0),
		FL_DUCKING = (1 << 1),
		FL_ANIMDUCKING = (1 << 2),
		FL_WATERJUMP = (1 << 3),
		FL_ONTRAIN = (1 << 4),
		FL_INRAIN = (1 << 5),
		FL_FROZEN = (1 << 6),
		FL_ATCONTROLS = (1 << 7),
		FL_CLIENT = (1 << 8),
		FL_FAKECLIENT = (1 << 9),
		FL_INWATER = (1 << 10),
		FL_FLY = (1 << 11),
		FL_SWIM = (1 << 12),
		FL_CONVEYOR = (1 << 13),
		FL_NPC = (1 << 14),
		FL_GODMODE = (1 << 15),
		FL_NOTARGET = (1 << 16),
		FL_AIMTARGET = (1 << 17),
		FL_PARTIALGROUND = (1 << 18),
		FL_STATICPROP = (1 << 19),
		FL_GRAPHED = (1 << 20),
		FL_GRENADE = (1 << 21),
		FL_STEPMOVEMENT = (1 << 22),
		FL_DONTTOUCH = (1 << 23),
		FL_BASEVELOCITY = (1 << 24),
		FL_WORLDBRUSH = (1 << 25),
		FL_OBJECT = (1 << 26),
		FL_KILLME = (1 << 27),
		FL_ONFIRE = (1 << 28),
		FL_DISSOLVING = (1 << 29),
		FL_TRANSRAGDOLL = (1 << 30),
		FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
	};

	enum EWeaponType : int
	{
		WEAPONTYPE_KNIFE = 0,
		WEAPONTYPE_PISTOL = 1,
		WEAPONTYPE_SUBMACHINEGUN = 2,
		WEAPONTYPE_RIFLE = 3,
		WEAPONTYPE_SHOTGUN = 4,
		WEAPONTYPE_SNIPER = 5,
		WEAPONTYPE_MACHINEGUN = 6,
		WEAPONTYPE_C4 = 7,
		WEAPONTYPE_PLACEHOLDER = 8,
		WEAPONTYPE_GRENADE = 9,
		WEAPONTYPE_HEALTHSHOT = 11,
		WEAPONTYPE_FISTS = 12,
		WEAPONTYPE_BREACHCHARGE = 13,
		WEAPONTYPE_BUMPMINE = 14,
		WEAPONTYPE_TABLET = 15,
		WEAPONTYPE_MELEE = 16
	};

public: // netvars
	NETVAR(GetFlags, "CBasePlayer->m_fFlags", std::int32_t);
	NETVAR(GetClip, "CBaseCombatWeapon->m_iClip1", int)

public: // renderable virtual functions (+0x4)
	constexpr CModel* GetModel() noexcept
	{
		return memory::Call<CModel*>(this + 0x4, 9);
	}

	constexpr bool SetupBones(CMatrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) noexcept
	{
		return memory::Call<bool>(this + 0x4, 16, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}

public: // networkable virtual functions (+0x8)
	constexpr CClientClass* GetClientClass() noexcept
	{
		return memory::Call<CClientClass*>(this + 0x8, 2);
	}

	constexpr std::int32_t GetIndex() noexcept
	{
		return memory::Call<std::int32_t>(this + 0x8, 10);
	}

public: // entity virtual functions
	constexpr const CVector& GetAbsOrigin() noexcept
	{
		return memory::Call<const CVector&>(this, 9);
	}

	const bool IsDormant() noexcept
	{
		return *reinterpret_cast<bool*>(std::uintptr_t(this) + 0x17E);
	}

	constexpr std::int32_t GetTeam() noexcept
	{
		return memory::Call<std::int32_t>(this, 118);
	}

	const int& GetHealth() noexcept
	{
		return *reinterpret_cast<int*>(std::uintptr_t(this) + 0x90);
	}

	constexpr bool IsAlive() noexcept
	{
		//if (this->GetHealth() > 0)
			//return true;
		//else
			return false;
	}

	constexpr bool IsPlayer() noexcept
	{
		return memory::Call<bool>(this, 182);
	}

	constexpr bool IsWeapon() noexcept
	{
		return memory::Call<bool>(this, 166);
	}

	constexpr CEntity* GetActiveWeapon() noexcept
	{
		return memory::Call<CEntity*>(this, 268);
	}

	constexpr CVector GetEyePosition() noexcept
	{
		return memory::Call<CVector>(this, 191);
	}

	constexpr CEntity* GetObserverTarget() noexcept
	{
		return memory::Call<CEntity*>(this, 295);
	}

	const CVector& GetAimPunch() noexcept
	{
		return *reinterpret_cast<CVector*>(std::uintptr_t(this) + 0x24D0);
	}

	constexpr int GetWeaponType() noexcept
	{
		return memory::Call<int>(this, 455);
	}

	const CVector& GetVelocity() noexcept
	{
		return *reinterpret_cast<CVector*>(std::uintptr_t(this) + 0xF4);
	}
};
