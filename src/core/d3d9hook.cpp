#include "d3d9hook.h"
#include "config.h"
#include "../valve/cvector.h"
#include "interfaces.h"
#include <iostream>
#include "../hacks/misc.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define WINDOW_NAME "Dear ImGui DirectX9 Example"

typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

LPDIRECT3DDEVICE9 renderer;
EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	style.GrabRounding = style.FrameRounding = 2.3f;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 20.0f);
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
}

void DrawMenu()
{
	ImGui::Begin("Itanium V2 / MoGamer's Powers", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	// tabs
	if (ImGui::Button("Movement", ImVec2{ 0,25 }))
	{
		globals::currentTab = 1;
	}
	ImGui::SameLine(0.0f, 2.0f);
	if (ImGui::Button("Visuals", ImVec2{ 0,25 }))
	{
		globals::currentTab = 2;
	}
	ImGui::SameLine(0.0f, 2.0f);
	if (ImGui::Button("Aim", ImVec2{ 0,25 }))
	{
		globals::currentTab = 3;
	}
	ImGui::SameLine(0.0f, 2.0f);
	if (ImGui::Button("Fun & Lua", ImVec2{ 0,25 }))
	{
		globals::currentTab = 4;
	}
	ImGui::SameLine(0.0f, 2.0f);
	if (ImGui::Button("Credits", ImVec2{ 0,25 }))
	{
		globals::currentTab = 5;
	}


	// tabs content
	if (globals::currentTab == 1)
	{
		ImGui::Checkbox("Bhop", &configuration::BHOP_Bhop);
		ImGui::Checkbox("Autostrafe", &configuration::BHOP_AutoStrafe);
		ImGui::SliderFloat("Silent Move", &configuration::BHOP_Silence, 0.0f, 100.0f);
		ImGui::SliderFloat("Speed", &configuration::BHOP_Speed, 0.0f, 1000.0f);
	}
	if (globals::currentTab == 2)
	{
		ImGui::Checkbox("Thirdperson", &configuration::VISUALS_Thirdperson);
		ImGui::SameLine();
		ImGui::ColorPicker3("ESP Color", configuration::VISUALS_ESPColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs);
		ImGui::Checkbox("2D Box ESP", &configuration::VISUALS_2DBoxESP);
		ImGui::Checkbox("Snapline ESP", &configuration::VISUALS_SnaplineESP);
	}
	if (globals::currentTab == 3)
	{
		ImGui::Checkbox("Aimbot", &configuration::AIMBOT_Aimbotting);
		ImGui::Checkbox("Auto shoot", &configuration::AIMBOT_Autoshoot);
		ImGui::SliderFloat("Smoothness", &configuration::AIMBOT_Smoothness, 0.0f, 1.0f);
		ImGui::SliderFloat("Best FOV", &configuration::AIMBOT_BestFOV, 0.0f, 360.0f);
	}
	if (globals::currentTab == 4)
	{
		ImGui::Checkbox("No Bobbing", &configuration::MISC_NoBobbing);
		ImGui::Checkbox("Lagger", &configuration::MISC_Lagger);
		ImGui::InputText("IP with port (XXX.XXX.XXX.XXX:XXXXX)", configuration::MISC_LaggerIP, sizeof(configuration::MISC_LaggerIP));

		ImGui::Text("Lua Execution");
		ImGui::SameLine();

		ImGui::InputTextMultiline("Lua Script", configuration::LUA_FilePath, sizeof(configuration::LUA_FilePath));
		if (ImGui::Button("Execute"))
		{
			uintptr_t var = interfaces::cvar->FindVar("sv_cheats");
			std::cout << (int)var << std::endl;
		}
	}
	if (globals::currentTab == 5)
	{
		ImGui::Text("thanks to cazz for based");
		ImGui::Text("thanks to artplay for features");
		ImGui::Text("thanks to kolesobelaza for help");
		ImGui::Text("thanks to gmod-sdk src for some code");
	}

	ImGui::End();
}

bool init = false;
bool show = false;
long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!init)
	{
		InitImGui(pDevice);
		renderer = pDevice;
		init = true;
	}

	DWORD colorwrite, srgbwrite;
	pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
	pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &srgbwrite);

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

	IDirect3DVertexDeclaration9* vertexDeclaration;
	IDirect3DVertexShader9* vertexShader;
	pDevice->GetVertexDeclaration(&vertexDeclaration);
	pDevice->GetVertexShader(&vertexShader);

	if (GetKeyState(VK_HOME)) {
		show = !show;
	}

	if (show)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		DrawMenu();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
	return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	if (window != handle)
	{
		GetWindowThreadProcessId(handle, &wndProcId);
		if (GetCurrentProcessId() != wndProcId)
			return TRUE; // skip to next window
		window = handle;
		return FALSE; // window found abort search
	}
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

void d3d9hook::Init() noexcept
{
	bool attached = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)&oEndScene, hkEndScene);
			do
				window = GetProcessWindow();
			while (window == NULL);
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
			attached = true;
		}
	} while (!attached);
}

LPDIRECT3DDEVICE9 d3d9hook::GetRenderer() noexcept
{
	return renderer;
}

void d3d9hook::drawing::DrawRectangle(int x, int y, int w, int h, D3DCOLOR col) noexcept
{
	D3DRECT BarRect = { x, y, x + w, y + h };
	d3d9hook::GetRenderer()->Clear(1, &BarRect, D3DCLEAR_TARGET, col, 0, 0);
}

void d3d9hook::drawing::DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR col) noexcept
{
	ID3DXLine* LineL;
	D3DXCreateLine(d3d9hook::GetRenderer(), &LineL);
	D3DXVECTOR2 Line[2];
	LineL->SetWidth(thickness);
	LineL->Draw(Line, 2, col);
	LineL->Release();
}