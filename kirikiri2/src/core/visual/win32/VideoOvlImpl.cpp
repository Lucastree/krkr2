//---------------------------------------------------------------------------
/*
	TVP2 ( T Visual Presenter 2 )  A script authoring tool
	Copyright (C) 2000-2004  W.Dee <dee@kikyou.info>

	See details of license at "license.txt"
*/
//---------------------------------------------------------------------------
// Video Overlay support implementation
//---------------------------------------------------------------------------


#include "tjsCommHead.h"
#pragma hdrstop

#include "MsgIntf.h"
#include "VideoOvlImpl.h"
// Start:	Add:	T.Imoto
#include "LayerIntf.h"
#include "LayerBitmapIntf.h"
// End:		Add:	T.Imoto
#include "SysInitIntf.h"
#include "StorageImpl.h"
#include "krmovie.h"
#include <evcode.h>
#if 0
typedef void (__stdcall *tGetAPIVersion)(DWORD *version);
typedef const wchar_t*  (__stdcall *tGetVideoOverlayObject)(
	HWND callbackwin, IStream *stream, const wchar_t * streamname,
	const wchar_t *type, unsigned __int64 size, iTVPVideoOverlay **out);
#endif
//---------------------------------------------------------------------------
class tTVPVideoModule
{
	tTVPPluginHolder *Holder;
	HMODULE Handle;
	tGetAPIVersion procGetAPIVersion;
	tGetVideoOverlayObject procGetVideoOverlayObject;

public:
	tTVPVideoModule(const ttstr & name);
	~tTVPVideoModule();

	void GetAPIVersion(DWORD *version) { procGetAPIVersion(version); }
	const wchar_t * GetVideoOverlayObject(HWND callbackwin, IStream *stream,
		const wchar_t * streamname, const wchar_t *type, unsigned __int64 size,
		iTVPVideoOverlay **out)
	{
		return procGetVideoOverlayObject(callbackwin, stream, streamname, type, size, out);
	}
};
static tTVPVideoModule *TVPMovieVideoModule = NULL;
static tTVPVideoModule *TVPLayerMovieVideoModule = NULL;	// T.Imoto
static tTVPVideoModule *TVPFlashVideoModule = NULL;
static void TVPUnloadKrMovie();
//---------------------------------------------------------------------------
tTVPVideoModule::tTVPVideoModule(const ttstr &name)
{
	Holder = new tTVPPluginHolder(name);
	Handle = LoadLibrary(Holder->GetLocalName().AsAnsiString().c_str());
	if(!Handle)
	{
		delete Holder;
		TVPThrowExceptionMessage(TVPCannotLoadKrMovieDLL);
	}

	try
	{
		procGetVideoOverlayObject = (tGetVideoOverlayObject)
			GetProcAddress(Handle, "GetVideoOverlayObject");
		procGetAPIVersion = (tGetAPIVersion)
			GetProcAddress(Handle, "GetAPIVersion");
		if(!procGetVideoOverlayObject || !procGetAPIVersion)
			TVPThrowExceptionMessage(TVPInvalidKrMovieDLL);
		DWORD version;
		procGetAPIVersion(&version);
		if(version != TVP_KRMOVIE_VER)
			TVPThrowExceptionMessage(TVPInvalidKrMovieDLL);
	}
	catch(...)
	{
		FreeLibrary(Handle);
		delete Holder;
		throw;
	}
}
//---------------------------------------------------------------------------
tTVPVideoModule::~tTVPVideoModule()
{
	FreeLibrary(Handle);
	delete Holder;
}
//---------------------------------------------------------------------------
static tTVPVideoModule * TVPGetMovieVideoModule()
{
	if(TVPMovieVideoModule == NULL)
		TVPMovieVideoModule = new tTVPVideoModule("krmovie.dll");

	return TVPMovieVideoModule;
}
//---------------------------------------------------------------------------
// Start: Add: T.Imoto
static tTVPVideoModule * TVPGetLayerMovieVideoModule()
{
	if(TVPLayerMovieVideoModule == NULL)
		TVPLayerMovieVideoModule = new tTVPVideoModule("krlmovie.dll");

	return TVPLayerMovieVideoModule;
}
// End: Add: T.Imoto
//---------------------------------------------------------------------------
static tTVPVideoModule * TVPGetFlashVideoModule()
{
	if(TVPFlashVideoModule == NULL)
		TVPFlashVideoModule = new tTVPVideoModule("krflash.dll");

	return TVPFlashVideoModule;
}
//---------------------------------------------------------------------------
/*
//---------------------------------------------------------------------------
static void TVPLoadKrMovie(bool flash)
{
	if(TVPKrMovieHandle) TVPUnloadKrMovie();

	TVPFlashDllLoaded = flash;
	TVPKrMovieHolder = new tTVPPluginHolder(TJS_W("krmovie.dll"));
	TVPKrMovieHandle =
		LoadLibrary(TVPKrMovieHolder->GetLocalName().AsAnsiString().c_str());
	if(!TVPKrMovieHandle)
	{
		delete TVPKrMovieHolder;
		TVPKrMovieHolder = NULL;
		TVPThrowExceptionMessage(TVPCannotLoadKrMovieDLL);
	}

	try
	{
		TVPGetVideoOverlayObject = (tGetVideoOverlayObject)
			GetProcAddress(TVPKrMovieHandle, "GetVideoOverlayObject");
		TVPGetAPIVersion = (tGetAPIVersion)
			GetProcAddress(TVPKrMovieHandle, "GetAPIVersion");
		if(!TVPGetVideoOverlayObject || !TVPGetAPIVersion)
			TVPThrowExceptionMessage(TVPInvalidKrMovieDLL);
		DWORD version;
		TVPGetAPIVersion(&version);
		if(version != TVP_KRMOVIE_VER)
			TVPThrowExceptionMessage(TVPInvalidKrMovieDLL);
	}
	catch(...)
	{
		FreeLibrary(TVPKrMovieHandle), TVPKrMovieHandle = NULL;
		delete TVPKrMovieHolder;
		TVPKrMovieHolder = NULL;
		throw;
	}
}
//---------------------------------------------------------------------------
static void TVPUnloadKrMovie()
{
	if(!TVPKrMovieHandle) return;

	FreeLibrary(TVPKrMovieHandle);
	TVPKrMovieHandle = NULL;

	delete TVPKrMovieHolder;
	TVPKrMovieHolder = NULL;
}
*/
//---------------------------------------------------------------------------
static std::vector<tTJSNI_VideoOverlay *> TVPVideoOverlayVector;
//---------------------------------------------------------------------------
static void TVPAddVideOverlay(tTJSNI_VideoOverlay *ovl)
{
	TVPVideoOverlayVector.push_back(ovl);
}
//---------------------------------------------------------------------------
static void TVPRemoveVideoOverlay(tTJSNI_VideoOverlay *ovl)
{
	std::vector<tTJSNI_VideoOverlay*>::iterator i;
	i = std::find(TVPVideoOverlayVector.begin(), TVPVideoOverlayVector.end(), ovl);
	if(i != TVPVideoOverlayVector.end())
		TVPVideoOverlayVector.erase(i);
}
//---------------------------------------------------------------------------
static void TVPShutdownVideoOverlay()
{
	// shutdown all overlay object and release krmovie.dll / krflash.dll
	std::vector<tTJSNI_VideoOverlay*>::iterator i;
	for(i = TVPVideoOverlayVector.begin(); i != TVPVideoOverlayVector.end(); i++)
	{
		(*i)->Shutdown();
	}

	if(TVPMovieVideoModule) delete TVPMovieVideoModule, TVPMovieVideoModule = NULL;
	if(TVPLayerMovieVideoModule) delete TVPLayerMovieVideoModule, TVPLayerMovieVideoModule = NULL;	// T.Imoto
	if(TVPFlashVideoModule) delete TVPFlashVideoModule, TVPFlashVideoModule = NULL;
}
static tTVPAtExit TVPShutdownVideoOverlayAtExit
	(TVP_ATEXIT_PRI_PREPARE, TVPShutdownVideoOverlay);
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
// tTJSNI_VideoOverlay
//---------------------------------------------------------------------------
tTJSNI_VideoOverlay::tTJSNI_VideoOverlay()
{
	VideoOverlay = NULL;
	Rect.left = 0;
	Rect.top = 0;
	Rect.right = 320;
	Rect.bottom = 240;
	Visible = false;
	OwnerWindow = NULL;
	LocalTempStorageHolder = NULL;

	UtilWindow = AllocateHWnd(WndProc);

	Layer1 = NULL;
	Layer2 = NULL;
	Mode = vomOverlay;
//	Mode = vomLayer;
	Loop = false;
	IsPrepare = false;
	SegLoopStartFrame = -1;
	SegLoopEndFrame = -1;
	IsEventPast = false;
	EventFrame = -1;

	Bitmap[0] = Bitmap[1] = NULL;
	BmpBits[0] = BmpBits[1] = NULL;
}
//---------------------------------------------------------------------------
tjs_error TJS_INTF_METHOD
tTJSNI_VideoOverlay::Construct(tjs_int numparams, tTJSVariant **param,
		iTJSDispatch2 *tjs_obj)
{
	tjs_error hr = inherited::Construct(numparams, param, tjs_obj);
	if(TJS_FAILED(hr)) return hr;

	return TJS_S_OK;
}
//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTJSNI_VideoOverlay::Invalidate()
{
	inherited::Invalidate();

	Close();

	if(UtilWindow) DeallocateHWnd(UtilWindow);
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::Open(const ttstr &_name)
{
	// open

	// first, close
	Close();


	// check window
	if(!Window) TVPThrowExceptionMessage(TVPWindowAlreadyMissing);

	// open target storage
	ttstr name(_name);
	ttstr param;

	const tjs_char * param_pos;
	int param_pos_ind;
	param_pos = TJS_strchr(name.c_str(), TJS_W('?'));
	param_pos_ind = param_pos - name.c_str();
	if(param_pos != NULL)
	{
		param = param_pos;
		name = ttstr(name, param_pos_ind);
	}

	IStream *istream = NULL;
	long size;
	bool flash;
	ttstr ext = TVPExtractStorageExt(name).c_str();
	ext.ToLowerCase();

	tTVPVideoModule *mod = NULL;
	if(ext == TJS_W(".swf"))
	{
		// shockwave flash movie
		flash = true;

		// load krflash.dll
		mod = TVPGetFlashVideoModule();

		// prepare local storage
		if(LocalTempStorageHolder)
			delete LocalTempStorageHolder, LocalTempStorageHolder = NULL;

		// find local name
		ttstr placed = TVPSearchPlacedPath(name);

		// open and hold
		LocalTempStorageHolder =
			new tTVPLocalTempStorageHolder(placed);
	}
	else
	{
		flash = false;

		if( Mode == vomOverlay )
		{	// load krmovie.dll
			mod = TVPGetMovieVideoModule();
		}
		else
		{	// load krlmovie.dll
			mod = TVPGetLayerMovieVideoModule();
		}

		// prepate IStream
		tTJSBinaryStream *stream0 = NULL;
		try
		{
			stream0 = TVPCreateStream(name);
			size = (long)stream0->GetSize();
		}
		catch(...)
		{
			if(stream0) delete stream0;
			throw;
		}

		istream = new tTVPIStreamAdapter(stream0);
	}

	// 'istream' is an IStream instance at this point

	// create video overlay object
	try
	{
		const wchar_t *message;
		if(flash)
		{
			message = mod->GetVideoOverlayObject(UtilWindow,
				NULL, (LocalTempStorageHolder->GetLocalName() + param).c_str(),
				ext.c_str(), 0, &VideoOverlay);
		}
		else
		{
			message = mod->GetVideoOverlayObject(UtilWindow,
				istream, name.c_str(), ext.c_str(),
				size, &VideoOverlay);
		}
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);

		if( flash || (Mode == vomOverlay) )
		{
			// set Window handle
			tjs_int ofsx, ofsy;
			message = VideoOverlay->SetWindow(Window->GetWindowHandle(ofsx, ofsy));
			if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	
			VideoOverlay->SetMessageDrainWindow(Window->GetSurfaceWindowHandle());
			if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	
			// set Rectangle
			RECT r = {Rect.left + ofsx, Rect.top + ofsy,
				Rect.right + ofsx, Rect.bottom + ofsy};
			message = VideoOverlay->SetRect(&r);
			if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	
			// set Visible
			message = VideoOverlay->SetVisible(Visible);
			if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
		}
		else
		{	// set font and back buffer to layerVideo
			long	width, height;
			long			size;
			message = VideoOverlay->GetVideoSize( &width, &height );
			if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
			
			if( width <= 0 || height <= 0 )
				TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, L"Invalidate video size");

			size = width * height * 4;
			Bitmap[0] = new tTVPBaseBitmap( width, height, 32 );
			Bitmap[1] = new tTVPBaseBitmap( width, height, 32 );

			BmpBits[0] = static_cast<BYTE*>(Bitmap[0]->GetBitmap()->GetScanLine( Bitmap[0]->GetBitmap()->GetHeight()-1 ));
			BmpBits[1] = static_cast<BYTE*>(Bitmap[1]->GetBitmap()->GetScanLine( Bitmap[1]->GetBitmap()->GetHeight()-1 ));

			message = VideoOverlay->SetVideoBuffer( BmpBits[0], BmpBits[1], size );
			if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
		}
	}
	catch(...)
	{
		if(istream) istream->Release();
		Close();
		throw;
	}
	if(istream) istream->Release();

	// set Status
	ClearWndProcMessages();
	SetStatus(ssStop);
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::Close()
{
	// close
	// release VideoOverlay object
	if(VideoOverlay)
	{
		VideoOverlay->Release(), VideoOverlay = NULL;
		tjs_int ofsx, ofsy;
		::SetFocus(Window->GetWindowHandle(ofsx, ofsy));
	}
	if(LocalTempStorageHolder)
		delete LocalTempStorageHolder, LocalTempStorageHolder = NULL;
	ClearWndProcMessages();
	SetStatus(ssUnload);
//	TVPUnloadKrMovie();

	if( Bitmap[0] )
		delete Bitmap[0];
	if( Bitmap[1] )
		delete Bitmap[1];

	Bitmap[0] = Bitmap[1] = NULL;
	BmpBits[0] = BmpBits[1] = NULL;
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::Shutdown()
{
	// shutdown the system
	// this functions closes the overlay object, but must not fire any events.
	bool c = CanDeliverEvents;
	ClearWndProcMessages();
	SetStatus(ssUnload);
	try
	{
		if(VideoOverlay) VideoOverlay->Release(), VideoOverlay = NULL;
	}
	catch(...)
	{
		CanDeliverEvents = c;
		throw;
	}
	CanDeliverEvents = c;
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::Disconnect()
{
	// disconnect the object
	Shutdown();

	Window = NULL;
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::Play()
{
	// start playing
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->Play();
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
		ClearWndProcMessages();
		SetStatus(ssPlay);
	}
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::Stop()
{
	// stop playing
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->Stop();
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
		ClearWndProcMessages();
		SetStatus(ssStop);
	}
}
//---------------------------------------------------------------------------
// Start:	Add:	T.Imoto
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::Pause()
{
	// pause playing
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->Pause();
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
//		ClearWndProcMessages();
		SetStatus(ssPause);
	}
}
void tTJSNI_VideoOverlay::Rewind()
{
	// rewind playing
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->Rewind();
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
		ClearWndProcMessages();
	}
}
void tTJSNI_VideoOverlay::Prepare()
{	// prepare movie
	if( VideoOverlay && (Mode == vomLayer) )
	{
		Pause();
		const wchar_t *message;
		message = VideoOverlay->Rewind();
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
		ClearWndProcMessages();
		IsPrepare = true;

		Play();
	}
}
void tTJSNI_VideoOverlay::SetSegmentLoop( int comeFrame, int goFrame )
{
	SegLoopStartFrame = comeFrame;
	SegLoopEndFrame = goFrame;
}
void tTJSNI_VideoOverlay::SetPeriodEvent( int eventFrame )
{
	EventFrame = eventFrame;

	if( eventFrame <= GetFrame() )
		IsEventPast = true;
	else
		IsEventPast = false;
}
//---------------------------------------------------------------------------
// End:		Add:	T.Imoto
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetRectangleToVideoOverlay()
{
	// set Rectangle to video overlay
	if(VideoOverlay && OwnerWindow)
	{
		const wchar_t *message;
		RECT r = {Rect.left, Rect.top, Rect.right, Rect.bottom};
		message = VideoOverlay->SetRect(&r);
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	}
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetPosition(tjs_int left, tjs_int top)
{
	if( Mode == vomLayer )
	{
		if( Layer1 != NULL ) Layer1->SetPosition( left, top );
		if( Layer2 != NULL ) Layer2->SetPosition( left, top );
	}
	else
	{
		Rect.set_offsets(left, top);
		SetRectangleToVideoOverlay();
	}
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetSize(tjs_int width, tjs_int height)
{
	if( Mode == vomLayer ) return;

	Rect.set_size(width, height);
	SetRectangleToVideoOverlay();
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetBounds(const tTVPRect & rect)
{
	if( Mode == vomLayer ) return;

	Rect = rect;
	SetRectangleToVideoOverlay();
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetLeft(tjs_int l)
{
	if( Mode == vomLayer )
	{
		if( Layer1 != NULL ) Layer1->SetLeft( l );
		if( Layer2 != NULL ) Layer2->SetLeft( l );
	}
	else
	{
		Rect.set_offsets(l, Rect.top);
		SetRectangleToVideoOverlay();
	}
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetTop(tjs_int t)
{
	if( Mode == vomLayer )
	{
		if( Layer1 != NULL ) Layer1->SetTop( t );
		if( Layer2 != NULL ) Layer2->SetTop( t );
	}
	else
	{
		Rect.set_offsets(Rect.left, t);
		SetRectangleToVideoOverlay();
	}
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetWidth(tjs_int w)
{
	if( Mode == vomLayer ) return;

	Rect.right = Rect.left + w;
	SetRectangleToVideoOverlay();
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetHeight(tjs_int h)
{
	if( Mode == vomLayer ) return;

	Rect.bottom = Rect.top + h;
	SetRectangleToVideoOverlay();
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetVisible(bool b)
{
	Visible = b;
	if(VideoOverlay)
	{
		if( Mode == vomLayer )
		{
			if( Layer1 != NULL ) Layer1->SetVisible( Visible );
			if( Layer2 != NULL ) Layer2->SetVisible( Visible );
		}
		else
		{
			const wchar_t *message;
			message = VideoOverlay->SetVisible(Visible);
			if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
		}
	}
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetWindowHandle(HWND wnd)
{
	OwnerWindow = wnd;
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->SetWindow(wnd);
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	}
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetMessageDrainWindow(HWND wnd)
{
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->SetMessageDrainWindow(wnd);
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	}
}
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::SetRectOffset(tjs_int ofsx, tjs_int ofsy)
{
	if(VideoOverlay)
	{
		const wchar_t *message;
		RECT r = {Rect.left + ofsx, Rect.top + ofsy,
			Rect.right + ofsx, Rect.bottom + ofsy};
		message = VideoOverlay->SetRect(&r);
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	}
}
//---------------------------------------------------------------------------
void __fastcall tTJSNI_VideoOverlay::WndProc(Messages::TMessage &Msg)
{
	// UtilWindow's message procedure
	if(VideoOverlay)
	{
		if(Msg.Msg == WM_GRAPHNOTIFY)
		{
			long evcode, p1, p2;
			bool got;
			do {
				VideoOverlay->GetEvent(&evcode, &p1, &p2, &got);
				if( got == false)
					return;

				switch( evcode )
				{
					case EC_COMPLETE:
						if( Status == ssPlay )
						{
							if( Loop )
							{
								Rewind();
								SetStatus(ssPeriod); // All data has been rendered
								SetStatus(ssPlay); // All data has been rendered
							}
							else
								SetStatusAsync(ssStop); // All data has been rendered
						}
						break;
					case EC_UPDATE:
						if( Mode == vomLayer && Status == ssPlay )
						{
                    		const wchar_t *message;
                    		int		curFrame = p1;
							if( Layer1 == NULL && Layer2 == NULL )	// nothing to do.
								return;

							// get video image size
							long	width, height;
							message = VideoOverlay->GetVideoSize( &width, &height );
							if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);

							tTJSNI_BaseLayer	*l1 = Layer1;
							tTJSNI_BaseLayer	*l2 = Layer2;

							// Check layer image size
							if( l1 != NULL )
							{
#if 0
								if( l1->GetMainImage() == NULL )
								{
									l1->SetSize( width, height );
									l1->AllocateImage();
								}
#endif
								if( l1->GetImageWidth() != width || l1->GetImageHeight() != height )
									l1->SetImageSize( width, height );
								if( l1->GetWidth() != width || l1->GetHeight() != height )
									l1->SetSize( width, height );
							}
							if( l2 != NULL )
							{
#if 0
								if( l2->GetMainImage() == NULL )
								{
									l2->SetSize( width, height );
									l2->AllocateImage();
								}
#endif
								if( l2->GetImageWidth() != width || l2->GetImageHeight() != height )
									l2->SetImageSize( width, height );
								if( l2->GetWidth() != width || l2->GetHeight() != height )
									l2->SetSize( width, height );
							}
							BYTE *buff;
							VideoOverlay->GetFrontBuffer( &buff );
							if( buff == BmpBits[0] )
							{
								if( l1 ) l1->AssignMainImage( Bitmap[0] );
								if( l2 ) l2->AssignMainImage( Bitmap[0] );
							}
							else	// 0じゃなかったら、1とみなす。
							{
								if( l1 ) l1->AssignMainImage( Bitmap[1] );
								if( l2 ) l2->AssignMainImage( Bitmap[1] );
							}
							if( l1 )
							{
//								if( l1->GetVisible() == false )
//									l1->SetVisible( true );
								l1->Update();
							}
							if( l2 )
							{
//								if( l2->GetVisible() == false )
//									l2->SetVisible( true );
								l2->Update();
							}
							// Prepare mode ?
							if( IsPrepare )
							{
								SetStatus(ssPeriod);
								Pause();
//                                SetStatus(ssStop);
								Rewind();
								IsPrepare = false;
							}
							// Segment Loop ?
							if( SegLoopEndFrame >= 0 && curFrame >= SegLoopEndFrame )
							{
								SetFrame( SegLoopStartFrame );
							}
							// Send period event ?
							if( EventFrame >= 0 && !IsEventPast && curFrame >= EventFrame )
							{
								SetStatus(ssPeriod);
								SetStatus(ssPlay);
							}
                        }
						break;
				}
				VideoOverlay->FreeEventParams( evcode, p1, p2 );
			} while( got );
			return;
		}
		else if(Msg.Msg == WM_CALLBACKCMD)
		{
			// wparam : command
			// lparam : argument
			FireCallbackCommand((tjs_char*)Msg.WParam, (tjs_char*)Msg.LParam);
			return;
		}
	}

	Msg.Result =  DefWindowProc(UtilWindow, Msg.Msg, Msg.WParam, Msg.LParam);
}
//---------------------------------------------------------------------------
// Start:	Add:	T.Imoto
void tTJSNI_VideoOverlay::SetTimePosition( tjs_uint64 p )
{
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->SetPosition( p );
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	}
}
tjs_uint64 tTJSNI_VideoOverlay::GetTimePosition()
{
	tjs_uint64	result = 0;
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->GetPosition( &result );
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	}
	return result;
}
void tTJSNI_VideoOverlay::SetFrame( tjs_int f )
{
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->SetFrame( f );
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	}
}
tjs_int tTJSNI_VideoOverlay::GetFrame()
{
	tjs_int	result = 0;
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->GetFrame( &result );
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	}
	return result;
}
tjs_real tTJSNI_VideoOverlay::GetFPS()
{
	tjs_real	result = 0.0;
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->GetFPS( &result );
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	}
	return result;
}
tjs_int tTJSNI_VideoOverlay::GetNumberOfFrame()
{
	tjs_int	result = 0;
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->GetNumberOfFrame( &result );
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	}
	return result;
}
tjs_int64 tTJSNI_VideoOverlay::GetTotalTime()
{
	tjs_int64	result = 0;
	if(VideoOverlay)
	{
		const wchar_t *message;
		message = VideoOverlay->GetTotalTime( &result );
		if(message) TVPThrowExceptionMessage(TVPErrorInKrMovieDLL, message);
	}
	return result;
}
void tTJSNI_VideoOverlay::SetLoop( bool b )
{
	Loop = b;
}
void tTJSNI_VideoOverlay::SetLayer1( tTJSNI_BaseLayer *l )
{
	Layer1 = l;
}
void tTJSNI_VideoOverlay::SetLayer2( tTJSNI_BaseLayer *l )
{
	Layer2 = l;
}
void tTJSNI_VideoOverlay::SetMode( tTVPVideoOverlayMode m )
{
	Mode = m;
}
// End:		Add:	T.Imoto
//---------------------------------------------------------------------------
void tTJSNI_VideoOverlay::ClearWndProcMessages()
{
	// clear WndProc's message queue
	MSG msg;
	while(PeekMessage(&msg, UtilWindow, WM_GRAPHNOTIFY, WM_GRAPHNOTIFY+2, PM_REMOVE))
	{
		if(VideoOverlay)
		{
			long evcode, p1, p2;
			bool got;
			VideoOverlay->GetEvent(&evcode, &p1, &p2, &got); // dummy call
// Add: Start: T.Imoto
			if( got )
				VideoOverlay->FreeEventParams( evcode, p1, p2 );
// Add: End: T.Imoto
		}
	}
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
// tTJSNC_VideoOverlay::CreateNativeInstance : returns proper instance object
//---------------------------------------------------------------------------
tTJSNativeInstance *tTJSNC_VideoOverlay::CreateNativeInstance()
{
	return new tTJSNI_VideoOverlay();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// TVPCreateNativeClass_VideoOverlay
//---------------------------------------------------------------------------
tTJSNativeClass * TVPCreateNativeClass_VideoOverlay()
{
	return new tTJSNC_VideoOverlay();
}
//---------------------------------------------------------------------------

