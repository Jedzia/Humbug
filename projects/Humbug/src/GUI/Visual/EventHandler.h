#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include "Application.h"
#include "boost/signals.hpp"
class Hookable;


class double_slot {
public:
    void operator()(int& i) const {
        i*=2;
    }
};

class plus_slot {
public:
    void operator()(int& i) const {
        i+=3;
    }
};

/*
	==CEventHandler==
	Event dispatching application class
*/
class CEventHandler : public CApplication  
{
public:
    typedef boost::signal<void (int, char**)> signal_type_init;
    typedef boost::signal<bool (int&)> signal_type_init2;
    typedef signal_type_init::slot_type slot_type_init;


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
	virtual void OnKeyDown(SDLKey sym,SDLMod mod,Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym,SDLMod mod,Uint16 unicode);
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

    void ConnectOnInit(const slot_type_init& s) {
        m_sigOnInit.connect( s );
    }
    //boost::signals::connection ConnectOnInit(const slot_type_init& s) {
    //        return m_sigOnInit.connect(s);
    //}
    //void ConnectOnInit(const Hookable& s) {
        //return m_sigOnInit.connect(s);
    //}

    virtual bool OnInit( int argc,char* argv[] );

protected:
    bool OnPreInit( int argc,char* argv[] );
    bool AfterInit( int argc,char* argv[] );

    Hookable* m_Hooks;

private:
    signal_type_init m_sigOnInit;
    //slot_type_init m_slotOnInit;

};

#endif //#ifndef __EVENTHANDLER_H__
