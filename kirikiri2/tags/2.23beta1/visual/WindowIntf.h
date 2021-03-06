//---------------------------------------------------------------------------
/*
	TVP2 ( T Visual Presenter 2 )  A script authoring tool
	Copyright (C) 2000-2004  W.Dee <dee@kikyou.info>

	See details of license at "license.txt"
*/
//---------------------------------------------------------------------------
// "Window" TJS Class implementation
//---------------------------------------------------------------------------
#ifndef WindowIntfH
#define WindowIntfH

#include "tjsNative.h"
#include "drawable.h"
#include "ComplexRect.h"
#include "tvpinputdefs.h"
#include "EventIntf.h"





//---------------------------------------------------------------------------
// Window List Management
//---------------------------------------------------------------------------
extern void TVPClearAllWindowInputEvents();
//---------------------------------------------------------------------------




/*[*/
//---------------------------------------------------------------------------
// Window related constants
//---------------------------------------------------------------------------
enum tTVPUpdateType
{
	utNormal, // only needed region
	utEntire // entire of window
};
//---------------------------------------------------------------------------
enum tTVPBorderStyle
{
	bsNone=0,  bsSingle=1,  bsSizeable=2,  bsDialog=3,  bsToolWindow=4,
	bsSizeToolWin =5
};
//---------------------------------------------------------------------------
enum tTVPMouseCursorState
{
	mcsVisible, // the mouse cursor is visible
	mcsTempHidden, // the mouse cursor is temporarily hidden
	mcsHidden // the mouse cursor is invisible
};
//---------------------------------------------------------------------------
/*]*/




//---------------------------------------------------------------------------
// tTJSNI_BaseWindow
//---------------------------------------------------------------------------
class tTVPBaseBitmap;
class tTJSNI_BaseLayer;
class tTJSNI_BaseVideoOverlay;
class tTVPLayerManager;
class tTJSNI_BaseWindow : public tTJSNativeInstance, public tTVPDrawable
{
	typedef tTJSNativeInstance inherited;

private:
	std::vector<tTJSVariantClosure> ObjectVector;
	bool ObjectVectorLocked;

protected:
	iTJSDispatch2 *Owner;
public:
	iTJSDispatch2 * GetOwnerNoAddRef() const { return Owner; }

public:
	tTJSNI_BaseWindow();
	~tTJSNI_BaseWindow();
	tjs_error TJS_INTF_METHOD
	Construct(tjs_int numparams, tTJSVariant **param,
		iTJSDispatch2 *tjs_obj);
	void TJS_INTF_METHOD Invalidate();

	bool IsMainWindow() const;

	//----- event dispatching
public:
	virtual bool CanDeliverEvents() const = 0; // implement this in each platform


public:
	virtual void PostInputEvent(const ttstr &name, iTJSDispatch2 * params) = 0;

public:

	void OnClose();
	void OnClick(tjs_int x, tjs_int y);
	void OnDoubleClick(tjs_int x, tjs_int y);
	void OnMouseDown(tjs_int x, tjs_int y, tTVPMouseButton mb, tjs_uint32 flags);
	void OnMouseUp(tjs_int x, tjs_int y, tTVPMouseButton mb, tjs_uint32 flags);
	void OnMouseMove(tjs_int x, tjs_int y, tjs_uint32 flags);
	void OnReleaseCapture();
	void OnMouseForceLeave();
	void OnMouseEnter();
	void OnMouseLeave();
	void OnKeyDown(tjs_uint key, tjs_uint32 shift);
	void OnKeyUp(tjs_uint key, tjs_uint32 shift);
	void OnKeyPress(tjs_char key);
	void OnFileDrop(const tTJSVariant &array);
	void OnMouseWheel(tjs_uint32 shift, tjs_int delta, tjs_int x, tjs_int y);

	void ClearInputEvents();

	void PostReleaseCaptureEvent();

	//----- layer managermant
protected:
	tTVPRect WindowExposedRegion;
	tTVPBaseBitmap * DrawBuffer;
	// methods from tTVPDrawable
	tTVPBaseBitmap * GetDrawTargetBitmap(const tTVPRect &rect,
		tTVPRect &cliprect);
	bool GetDrawTargetHasAlpha() { return false; }
//	void DrawCompleted();
		// DrawCompleted is implemented in each platform to
		// transfer the image to the display
	tTVPLayerManager * LayerManager;

	bool WindowUpdating; // window is in updating

public:
	tTVPLayerManager * GetLayerManager() const { return LayerManager; }

	void NotifyWindowExposureToLayer(const tTVPRect &cliprect);

public:
	tTVPDrawable * GetDrawable() { return (tTVPDrawable *)this; } ;
	void NotifyUpdateRegionFixed(const tTVPComplexRect &updaterects); // is called by layer manager
	void UpdateContent(); // is called from event dispatcher
	virtual void BeginUpdate(const tTVPComplexRect & rects);
	virtual void EndUpdate();
	virtual void NotifyWindowInvalidation(); // is called from primary layer
	virtual void NotifyLayerResize(); // is called from primary layer
	virtual void SetDefaultMouseCursor() = 0; // set window mouse cursor to default
	virtual void SetMouseCursor(tjs_int cursor) = 0; // set window mouse cursor
	virtual void GetCursorPos(tjs_int &x, tjs_int &y) = 0;
		// get mouse cursor position in primary layer's coordinates
	virtual void SetCursorPos(tjs_int x, tjs_int y) = 0;
		// set mosue cursor position
	virtual void SetHintText(const ttstr & text) = 0; // set hint
	virtual void SetAttentionPoint(tTJSNI_BaseLayer *layer,
		tjs_int l, tjs_int t) = 0;
	virtual void DisableAttentionPoint() = 0;
	virtual void SetImeMode(tTVPImeMode mode) = 0;
	virtual void SetDefaultImeMode(tTVPImeMode mode) = 0;
	virtual tTVPImeMode GetDefaultImeMode() const = 0;
	virtual void ResetImeMode() = 0;

	void DumpPrimaryLayerStructure();

	//----- methods
	void Add(tTJSVariantClosure clo);
	void Remove(tTJSVariantClosure clo);

	//----- interface to menu object
private:
	iTJSDispatch2 * MenuItemObject;
public:
	iTJSDispatch2 * GetMenuItemObjectNoAddRef();

	//----- interface to video overlay object
protected:
	tTJSNI_BaseVideoOverlay * VideoOverlay;

public:
	void RegisterVideoOverlayObject(tTJSNI_BaseVideoOverlay *ovl);
	void UnregisterVideoOverlayObject(tTJSNI_BaseVideoOverlay *ovl);

};
//---------------------------------------------------------------------------

#include "WindowImpl.h" // must define tTJSNI_Window class

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
// Window List
//---------------------------------------------------------------------------
class tTJSNI_Window;
extern tTJSNI_Window * TVPGetWindowListAt(tjs_int idx);
extern tjs_int TVPGetWindowCount();
extern tTJSNI_Window * TVPMainWindow; //  = NULL; // main window

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// tTJSNC_Window : TJS Window class
//---------------------------------------------------------------------------
class tTJSNC_Window : public tTJSNativeClass
{
public:
	tTJSNC_Window();
	static tjs_uint32 ClassID;

protected:
	tTJSNativeInstance *CreateNativeInstance();
	/*
		implement this in each platform.
		this must return a proper instance of tTJSNI_Window.
	*/
};
//---------------------------------------------------------------------------
extern tTJSNativeClass * TVPCreateNativeClass_Window();
	/*
		implement this in each platform.
		this must return a proper instance of tTJSNI_Window.
		usually simple returns: new tTJSNC_Window();
	*/
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
// Input Events
//---------------------------------------------------------------------------
class tTVPOnCloseInputEvent : public tTVPBaseInputEvent
{
public:
	tTVPOnCloseInputEvent(tTJSNI_BaseWindow *win) :
		tTVPBaseInputEvent(win) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnClose(); }
};
//---------------------------------------------------------------------------
class tTVPOnClickInputEvent : public tTVPBaseInputEvent
{
	tjs_int X;
	tjs_int Y;
public:
	tTVPOnClickInputEvent(tTJSNI_BaseWindow *win, tjs_int x, tjs_int y) :
		tTVPBaseInputEvent(win), X(x), Y(y) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnClick(X, Y); }
};
//---------------------------------------------------------------------------
class tTVPOnDoubleClickInputEvent : public tTVPBaseInputEvent
{
	tjs_int X;
	tjs_int Y;
public:
	tTVPOnDoubleClickInputEvent(tTJSNI_BaseWindow *win, tjs_int x, tjs_int y) :
		tTVPBaseInputEvent(win), X(x), Y(y) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnDoubleClick(X, Y); }
};
//---------------------------------------------------------------------------
class tTVPOnMouseDownInputEvent : public tTVPBaseInputEvent
{
	tjs_int X;
	tjs_int Y;
	tTVPMouseButton Buttons;
	tjs_uint32 Flags;
public:
	tTVPOnMouseDownInputEvent(tTJSNI_BaseWindow *win, tjs_int x, tjs_int y,
		tTVPMouseButton buttons, tjs_uint32 flags) :
		tTVPBaseInputEvent(win), X(x), Y(y), Buttons(buttons), Flags(flags) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnMouseDown(X, Y, Buttons, Flags); }
};
//---------------------------------------------------------------------------
class tTVPOnMouseUpInputEvent : public tTVPBaseInputEvent
{
	tjs_int X;
	tjs_int Y;
	tTVPMouseButton Buttons;
	tjs_uint32 Flags;
public:
	tTVPOnMouseUpInputEvent(tTJSNI_BaseWindow *win, tjs_int x, tjs_int y,
		tTVPMouseButton buttons, tjs_uint32 flags) :
		tTVPBaseInputEvent(win), X(x), Y(y), Buttons(buttons), Flags(flags) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnMouseUp(X, Y, Buttons, Flags); }
};
//---------------------------------------------------------------------------
class tTVPOnMouseMoveInputEvent : public tTVPBaseInputEvent
{
	tjs_int X;
	tjs_int Y;
	tjs_uint32 Flags;
public:
	tTVPOnMouseMoveInputEvent(tTJSNI_BaseWindow *win, tjs_int x, tjs_int y,
		tjs_uint32 flags) :
		tTVPBaseInputEvent(win), X(x), Y(y), Flags(flags) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnMouseMove(X, Y, Flags); }
};
//---------------------------------------------------------------------------
class tTVPOnReleaseCaptureInputEvent : public tTVPBaseInputEvent
{
public:
	tTVPOnReleaseCaptureInputEvent(tTJSNI_BaseWindow *win) :
		tTVPBaseInputEvent(win) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnReleaseCapture(); }
};
//---------------------------------------------------------------------------
class tTVPOnMouseForceLeaveInputEvent : public tTVPBaseInputEvent
{
public:
	tTVPOnMouseForceLeaveInputEvent(tTJSNI_BaseWindow *win) :
		tTVPBaseInputEvent(win) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnMouseForceLeave(); }
};
//---------------------------------------------------------------------------
class tTVPOnMouseEnterInputEvent : public tTVPBaseInputEvent
{
public:
	tTVPOnMouseEnterInputEvent(tTJSNI_BaseWindow *win) :
		tTVPBaseInputEvent(win) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnMouseEnter(); }
};
//---------------------------------------------------------------------------
class tTVPOnMouseLeaveInputEvent : public tTVPBaseInputEvent
{
public:
	tTVPOnMouseLeaveInputEvent(tTJSNI_BaseWindow *win) :
		tTVPBaseInputEvent(win) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnMouseLeave(); }
};
//---------------------------------------------------------------------------
class tTVPOnKeyDownInputEvent : public tTVPBaseInputEvent
{
	tjs_uint Key;
	tjs_uint32 Shift;
public:
	tTVPOnKeyDownInputEvent(tTJSNI_BaseWindow *win, tjs_uint key, tjs_uint32 shift) :
		tTVPBaseInputEvent(win), Key(key), Shift(shift) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnKeyDown(Key, Shift); }
};
//---------------------------------------------------------------------------
class tTVPOnKeyUpInputEvent : public tTVPBaseInputEvent
{
	tjs_uint Key;
	tjs_uint32 Shift;
public:
	tTVPOnKeyUpInputEvent(tTJSNI_BaseWindow *win, tjs_uint key, tjs_uint32 shift) :
		tTVPBaseInputEvent(win), Key(key), Shift(shift) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnKeyUp(Key, Shift); }
};
//---------------------------------------------------------------------------
class tTVPOnKeyPressInputEvent : public tTVPBaseInputEvent
{
	tjs_char Key;
public:
	tTVPOnKeyPressInputEvent(tTJSNI_BaseWindow *win, tjs_char key) :
		tTVPBaseInputEvent(win), Key(key) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnKeyPress(Key); }
};
//---------------------------------------------------------------------------
class tTVPOnFileDropInputEvent : public tTVPBaseInputEvent
{
	tTJSVariant Array;
public:
	tTVPOnFileDropInputEvent(tTJSNI_BaseWindow *win, const tTJSVariant & val) :
		tTVPBaseInputEvent(win), Array(val) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnFileDrop(Array); }
};
//---------------------------------------------------------------------------
class tTVPOnMouseWheelInputEvent : public tTVPBaseInputEvent
{
	tjs_uint32 Shift;
	tjs_int WheelDelta;
	tjs_int X;
	tjs_int Y;
public:
	tTVPOnMouseWheelInputEvent(tTJSNI_BaseWindow *win, tjs_uint32 shift,
		tjs_int wheeldelta, tjs_int x, tjs_int y) :
		tTVPBaseInputEvent(win), Shift(shift), WheelDelta(wheeldelta),
		X(x), Y(y) {};
	void Deliver() const
	{ ((tTJSNI_BaseWindow*)GetSource())->OnMouseWheel(Shift, WheelDelta, X, Y); }
};
//---------------------------------------------------------------------------



#endif
