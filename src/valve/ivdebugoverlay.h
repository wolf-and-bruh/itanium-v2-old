#pragma once

#include "cvector.h"
#include "cmatrix.h"
#include "ccolor.h"

class IVDebugOverlay
{
public:
	/*0*/	virtual void* AddEntityTextOverlay(int, int, float, int, int, int, int, char const*, ...) = 0;
	/*1*/	virtual void* AddBoxOverlay(Vector const&, Vector const&, Vector const&, Angle const&, int, int, int, int, float) = 0;
	/*2*/	virtual void* AddTriangleOverlay(Vector const&, Vector const&, Vector const&, int, int, int, int, bool, float) = 0;
	/*3*/	virtual void* AddLineOverlay(Vector const&, Vector const&, int, int, int, bool, float) = 0;
	/*4*/	virtual void* AddTextOverlay(Vector const&, float, char const*, ...) = 0;
	/*5*/	virtual void* AddTextOverlay(Vector const&, int, float, char const*, ...) = 0;
	/*6*/	virtual void* AddScreenTextOverlay(float, float, float, int, int, int, int, char const*) = 0;
	/*7*/	virtual void* AddSweptBoxOverlay(Vector const&, Vector const&, Vector const&, Vector const&, Angle const&, int, int, int, int, float) = 0;
	/*8*/	virtual void* AddGridOverlay(Vector const&) = 0;
	/*9*/	virtual bool ScreenPosition(CVector const& in, CVector& out) = 0;
	/*10*/	virtual bool ScreenPosition(float, float, Vector&) = 0;
	/*11*/	virtual void* GetFirst(void) = 0;
	/*12*/	virtual void* GetNext(void*) = 0;
	/*13*/	virtual void* ClearDeadOverlays(void) = 0;
	/*14*/	virtual void* ClearAllOverlays(void) = 0;
	/*15*/	virtual void* AddTextOverlayRGB(Vector const&, int, float, float, float, float, float, char const*, ...) = 0;
	/*16*/	virtual void* AddTextOverlayRGB(Vector const&, int, float, int, int, int, int, char const*, ...) = 0;
	/*17*/	virtual void* AddLineOverlayAlpha(Vector const&, Vector const&, int, int, int, int, bool, float) = 0;
	/*18*/	virtual void* AddBoxOverlay2(Vector const&, Vector const&, Vector const&, Angle const&, int const&, int const&, float) = 0;
};
