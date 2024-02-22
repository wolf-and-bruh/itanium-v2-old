#pragma once
#include "interfaces.h"
#include <Windows.h>

namespace hooks
{
	// call once to emplace all hooks
	void Setup() noexcept;

	// call once to restore all hooks
	void Destroy() noexcept;

	// bypass return address checks (thx osiris)
	using AllocKeyValuesMemoryFn = void* (__thiscall*)(void*, const std::int32_t) noexcept;
	inline AllocKeyValuesMemoryFn AllocKeyValuesMemoryOriginal;
	void* __stdcall AllocKeyValuesMemory(const std::int32_t size) noexcept;

	// example CreateMove hook
	using CreateMoveFn = bool(__thiscall*)(IClientModeShared*, float, CUserCmd*) noexcept;
	inline CreateMoveFn CreateMoveOriginal = nullptr;
	bool __stdcall CreateMove(float frameTime, CUserCmd* cmd) noexcept;

	// DrawModelExecute hook
	using DrawModelExecuteFn = void(__thiscall*)(CModelRender*, void*, CModelRender*, const DrawModelState_t&, const ModelRenderInfo_t*, CMatrix3x4*) noexcept;
	inline DrawModelExecuteFn DrawModelExecuteOriginal = nullptr;
	void __fastcall DrawModelExecute(CModelRender* _this, void* edx, CModelRender* modelrender, const DrawModelState_t& dmstate, const ModelRenderInfo_t* mrinfo, CMatrix3x4* pCustomBoneToWorld = NULL) noexcept;

	// PaintTraverse hook
	using PaintTraverseFn = void(__thiscall*)(IVPanel*, std::uintptr_t, bool, bool) noexcept;
	inline PaintTraverseFn PaintTraverseOriginal = nullptr;
	void __stdcall PaintTraverse(std::uintptr_t vguiPanel, bool forceRepaint, bool allowForce) noexcept;

	// RunStringEx hook
	using RunStringFn = bool(__thiscall*)(PVOID, const char*, const char*, const char*, bool, bool, bool, bool) noexcept;
	inline RunStringFn RunStringOriginal = nullptr;
	bool __stdcall RunString(PVOID _this, const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns) noexcept;
}
