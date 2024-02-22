#pragma once
#include "../util/memory.h"

class IVPanel;

enum EFontDrawType : std::int32_t
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE
};

enum EFontFlag
{
	FONT_FLAG_NONE,
	FONT_FLAG_ITALIC = 0x001,
	FONT_FLAG_UNDERLINE = 0x002,
	FONT_FLAG_STRIKEOUT = 0x004,
	FONT_FLAG_SYMBOL = 0x008,
	FONT_FLAG_ANTIALIAS = 0x010,
	FONT_FLAG_GAUSSIANBLUR = 0x020,
	FONT_FLAG_ROTARY = 0x040,
	FONT_FLAG_DROPSHADOW = 0x080,
	FONT_FLAG_ADDITIVE = 0x100,
	FONT_FLAG_OUTLINE = 0x200,
	FONT_FLAG_CUSTOM = 0x400,
	FONT_FLAG_BITMAP = 0x800,
};

class IAppSystem
{
public:
	virtual bool Connect(void* factory) = 0;
	virtual void Disconnect() = 0;
	virtual void* QueryInterface(const char* pInterfaceName) = 0;
	virtual void Init() = 0;
	virtual void Shutdown() = 0;
};

class ISurface : IAppSystem
{
	virtual void unkn01() = 0;
	virtual void unkn02() = 0;
	virtual void unkn03() = 0;
	virtual void unkn04() = 0;
public:
	virtual void Shutdown() = 0;
	virtual void RunFrame() = 0;
	virtual void GetEmbeddedPanel() = 0;
	virtual void SetEmbeddedPanel(IVPanel pPanel) = 0;
	virtual void PushMakeCurrent(IVPanel panel, bool useInsets) = 0;
	virtual void PopMakeCurrent(IVPanel panel) = 0;
	virtual void DrawSetColor(int r, int g, int b, int a) = 0;
	virtual void DrawSetColor(int col) = 0;
	virtual void DrawFilledRect(int x0, int y0, int x1, int y1) = 0;
	virtual void DrawFilledRectArray(void* pRects, int numRects) = 0;
	virtual void DrawOutlinedRect(int x0, int y0, int x1, int y1) = 0;
	virtual void DrawLine(int x0, int y0, int x1, int y1) = 0;
	virtual void DrawPolyLine(int* px, int* py, int numPoints) = 0;
	virtual void DrawSetTextFont(int font) = 0;
	virtual void DrawSetTextColor(int r, int g, int b, int a) = 0;
	virtual void DrawSetTextColor(int col) = 0;
	virtual void DrawSetTextPos(int x, int y) = 0;
	virtual void DrawGetTextPos(int& x, int& y) = 0;
	virtual void DrawPrintText(const wchar_t* text, int textLen, int drawType = 0) = 0;
	virtual void DrawUnicodeChar(wchar_t wch, int drawType = 0) = 0;
	virtual void DrawFlushText() = 0;
	virtual void* CreateHTMLWindow(void* events, IVPanel context) = 0;
	virtual void PaintHTMLWindow(void* htmlwin) = 0;
	virtual void DeleteHTMLWindow(void* htmlwin) = 0;
	virtual int	 DrawGetTextureId(char const* filename) = 0;
	virtual bool DrawGetTextureFile(int id, char* filename, int maxlen) = 0;
	virtual void DrawSetTextureFile(int id, const char* filename, int hardwareFilter, bool forceReload) = 0;
	virtual void DrawSetTextureRGBA(int id, const unsigned char* rgba, int wide, int tall, int hardwareFilter, bool forceReload) = 0;
	virtual void DrawSetTexture(int id) = 0;
	virtual void DrawGetTextureSize(int id, int& wide, int& tall) = 0;
	virtual void DrawTexturedRect(int x0, int y0, int x1, int y1) = 0;
	virtual bool IsTextureIDValid(int id) = 0;
	virtual int CreateNewTextureID(bool procedural = false) = 0;
	virtual void GetScreenSize(int& wide, int& tall) = 0;
	virtual void SetAsTopMost(IVPanel panel, bool state) = 0;
	virtual void BringToFront(IVPanel panel) = 0;
	virtual void SetForegroundWindow(IVPanel panel) = 0;
	virtual void SetPanelVisible(IVPanel panel, bool state) = 0;
	virtual void SetMinimized(IVPanel panel, bool state) = 0;
	virtual bool IsMinimized(IVPanel panel) = 0;
	virtual void FlashWindow(IVPanel panel, bool state) = 0;
	virtual void SetTitle(IVPanel panel, const wchar_t* title) = 0;
	virtual void SetAsToolBar(IVPanel panel, bool state) = 0;
	virtual void CreatePopup(IVPanel panel, bool minimised, bool showTaskbarIcon = true, bool disabled = false, bool mouseInput = true, bool kbInput = true) = 0;
	virtual void SwapBuffers(IVPanel panel) = 0;
	virtual void Invalidate(IVPanel panel) = 0;
	virtual void SetCursor(int cursor) = 0;
	virtual bool IsCursorVisible() = 0;
	virtual void ApplyChanges() = 0;
	virtual bool IsWithin(int x, int y) = 0;
	virtual bool HasFocus() = 0;
	virtual bool SupportsFeature(int feature) = 0;
	virtual void RestrictPaintToSinglePanel(IVPanel panel) = 0;
	virtual void SetModalPanel(IVPanel) = 0;
	virtual IVPanel GetModalPanel() = 0;
	virtual void UnlockCursor() = 0;
	virtual void LockCursor() = 0;
	virtual void SetTranslateExtendedKeys(bool state) = 0;
	virtual IVPanel GetTopmostPopup() = 0;
	virtual void SetTopLevelFocus(IVPanel panel) = 0;
	virtual int CreateFont() = 0;
	virtual bool SetFontGlyphSet(int font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags) = 0;
	virtual bool AddCustomFontFile(const char* fontName, const char* fontFileName) = 0;
	virtual int GetFontTall(int font) = 0;
	virtual int GetFontAscent(int font, wchar_t wch) = 0;
	virtual bool IsFontAdditive(int font) = 0;
	virtual void GetCharABCwide(int font, int ch, int& a, int& b, int& c) = 0;
	virtual int GetCharacterWidth(int font, int ch) = 0;
	virtual void GetTextSize(int font, const wchar_t* text, int& wide, int& tall) = 0;
	virtual IVPanel GetNotifyPanel() = 0;
	virtual void SetNotifyIcon(IVPanel context, int icon, IVPanel panelToReceiveMessages, const char* text) = 0;
	virtual void PlaySound(const char* fileName) = 0;
	virtual int GetPopupCount() = 0;
	virtual IVPanel GetPopup(int index) = 0;
	virtual bool ShouldPaintChildPanel(IVPanel childPanel) = 0;
	virtual bool RecreateContext(IVPanel panel) = 0;
	virtual void AddPanel(IVPanel panel) = 0;
	virtual void ReleasePanel(IVPanel panel) = 0;
	virtual void MovePopupToFront(IVPanel panel) = 0;
	virtual void MovePopupToBack(IVPanel panel) = 0;
	virtual void SolveTraverse(IVPanel panel, bool forceApplySchemeSettings = false) = 0;
	virtual void PaintTraverse(IVPanel panel) = 0;
	virtual void EnableMouseCapture(IVPanel panel, bool state) = 0;
	virtual void GetWorkspaceBounds(int& x, int& y, int& wide, int& tall) = 0;
	virtual void GetAbsoluteWindowBounds(int& x, int& y, int& wide, int& tall) = 0;
	virtual void GetProportionalBase(int& width, int& height) = 0;
	virtual void CalculateMouseVisible() = 0;
	virtual bool NeedKBInput() = 0;
	virtual bool HasCursorPosFunctions() = 0;
	virtual void SurfaceGetCursorPos(int& x, int& y) = 0;
	virtual void SurfaceSetCursorPos(int x, int y) = 0;
	virtual void DrawTexturedLine(const int& a, const int& b) = 0;
	virtual void DrawOutlinedCircle(int x, int y, int radius, int segments) = 0;
	virtual void DrawTexturedPolyLine(const void* p, int n) = 0;
	virtual void DrawTexturedSubRect(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1) = 0;
	virtual void DrawTexturedPolygon(int n, void* pVertices) = 0;
	virtual const wchar_t* GetTitle(IVPanel panel) = 0;
	virtual bool IsCursorLocked(void) const = 0;
	virtual void SetWorkspaceInsets(int left, int top, int right, int bottom) = 0;
	virtual bool DrawGetUnicodeCharRenderInfo(wchar_t ch, int& info) = 0;
	virtual void DrawRenderCharFromInfo(const int& info) = 0;
	virtual void DrawSetAlphaMultiplier(float alpha) = 0;
	virtual float DrawGetAlphaMultiplier() = 0;
	virtual void SetAllowHTMLJavaScript(bool state) = 0;
	virtual void OnScreenSizeChanged(int nOldWidth, int nOldHeight) = 0;
	virtual void* DrawGetTextureMatInfoFactory(int id) = 0;
	virtual void PaintTraverseEx(IVPanel panel, bool paintPopups = false) = 0;
	virtual float GetZPos() const = 0;
	virtual void SetPanelForInput(IVPanel IVPanel) = 0;
	virtual void DrawFilledRectFade(int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool bHorizontal) = 0;
	virtual void DrawSetTextureRGBAEx(int id, const unsigned char* rgba, int wide, int tall, int imageFormat) = 0;
	virtual void DrawSetTextScale(float sx, float sy) = 0;
	virtual bool SetBitmapFontGlyphSet(int font, const char* windowsFontName, float scalex, float scaley, int flags) = 0;
	virtual bool AddBitmapFontFile(const char* fontFileName) = 0;
	virtual void SetBitmapFontName(const char* pName, const char* pFontFilename) = 0;
	virtual const char* GetBitmapFontName(const char* pName) = 0;
	virtual void* GetIconImageForFullPath(char const* pFullPath) = 0;
	virtual void DrawUnicodeString(const wchar_t* pwString, int drawType = 0) = 0;

	void StartDrawing();
	void FinishDrawing();
};