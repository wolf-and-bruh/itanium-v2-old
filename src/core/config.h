#pragma once
namespace configuration
{
	inline bool VISUALS_Thirdperson;
	inline bool VISUALS_2DBoxESP;
	inline bool VISUALS_SnaplineESP;
	inline float VISUALS_ESPColor[3] = { 255,255,255 };

	inline bool BHOP_Bhop;
	inline bool BHOP_AutoStrafe;
	inline float BHOP_Silence;
	inline float BHOP_Speed;
	
	inline bool MISC_Lagger;
	inline bool MISC_NoBobbing;
	inline char MISC_LaggerIP[256];
	inline char LUA_FilePath[256];

	inline bool AIMBOT_Aimbotting;
	inline bool AIMBOT_Autoshoot;
	inline float AIMBOT_Smoothness;
	inline float AIMBOT_BestFOV;

	void Save() noexcept;
}