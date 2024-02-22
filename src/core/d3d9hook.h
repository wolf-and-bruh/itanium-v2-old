#pragma once
#include "../../ext/kiero/kiero.h"
#include "../../ext/kiero/examples/imgui/imgui/examples/imgui_impl_dx9.h"
#include "../../ext/kiero/examples/imgui/imgui/examples/imgui_impl_win32.h"

#include "globals.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

namespace d3d9hook
{
	void Init() noexcept;
	LPDIRECT3DDEVICE9 GetRenderer() noexcept;
	
	namespace drawing
	{
		inline D3DCOLOR blue = D3DCOLOR_ARGB(255,0,0,255);

		void DrawRectangle(int x, int y, int w, int h, D3DCOLOR col) noexcept;
		void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR col) noexcept;
	}
}