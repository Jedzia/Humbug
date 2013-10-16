#ifndef HUMBUG_GUI_VISUAL_EVENTHANDLER_H_
#define HUMBUG_GUI_VISUAL_EVENTHANDLER_H_

#include "Application.h"
#include "boost/smart_ptr/scoped_ptr.hpp"

namespace gui {

class HookableManager;
#if !SDL_GUILIB_ENABLED
//#define SDLKey int;
//#define SDLMod int;
//enum SDLKey;
//enum SDLMod;
#endif


/*
	==CEventHandler==
	Event dispatching application class
*/
class CEventHandler : public CApplication
{
public:
	// signal types

	// bool OnInit(int argc,char* argv[])
	// void OnKeyDown(SDLKey sym,SDLMod mod,Uint16 unicode);
#if SDL_GUILIB_ENABLED
		typedef boost::signal<void (SDLKey sym, SDLMod mod, Uint16 unicode)> signal_type_keydown;
		typedef signal_type_keydown::slot_type slot_type_keydown;
#endif

    static MSGID MSGID_QuitApp;//no parms

    //constructor
	CEventHandler();
	//destructor
	virtual ~CEventHandler();
	//event handling
	virtual void OnEvent(SDL_Event* pEvent);
	//event filtering
	virtual bool FilterEvent(SDL_Event* pEvent);
//active events
	//keyboard(input)
	virtual void OnInputFocus();
	virtual void OnInputBlur();
	//mouse
	virtual void OnMouseFocus();
	virtual void OnMouseBlur();
	//application active
	virtual void OnMinimize();
	virtual void OnRestore();
//keyboard events
#if SDL_GUILIB_ENABLED
		virtual void OnKeyDfown(SDLKey sym,SDLMod mod,Uint16 unicode);
		virtual void OnKeyUp(SDLKey sym,SDLMod mod,Uint16 unicode);
#endif
//mouse events
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
//joystick events
	virtual void OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value);
	virtual void OnJoyButtonDown(Uint8 which,Uint8 button);
	virtual void OnJoyButtonUp(Uint8 which,Uint8 button);
	virtual void OnJoyHat(Uint8 which,Uint8 hat,Uint8 value);
	virtual void OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel);
//resize event
	virtual void OnResize(int w,int h);
//expose event
	virtual void OnExpose();
//user event
	virtual void OnUser(Uint8 type,int code,void* data1,void* data2);

    virtual void OnExiting();

#if SDL_GUILIB_ENABLED
	    boost::signals::connection ConnectOnInit(const slot_type_init& s) {
	         return m_sigOnInit.connect( s );
	    }
		boost::signals::connection ConnectOnKeyDown(const slot_type_keydown& s) {
			return m_sigOnKeyDown.connect( s );
		}
#endif

    //boost::signals::connection ConnectOnInit(const slot_type_init& s) {
    //        return m_sigOnInit.connect(s);
    //}
    //void ConnectOnInit(const Hookable& s) {
        //return m_sigOnInit.connect(s);
    //}

protected:
    bool OnPreInit( int argc,char* argv[] );
    bool OnPostInit( int argc,char* argv[] );
//    HookableManager* HookMgr() const { return m_HookMgr.get(); }

    //Hookable* m_Hooks;
private:
//    boost::scoped_ptr<HookableManager> m_HookMgr;
#if SDL_GUILIB_ENABLED
		signal_type_init m_sigOnInit;
		signal_type_keydown m_sigOnKeyDown;
#endif
    //slot_type_init m_slotOnInit;

};

} // namespace gui

#endif //#ifndef HUMBUG_GUI_VISUAL_EVENTHANDLER_H_
