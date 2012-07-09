#ifndef __TESTEVENTHANDLER_H__
#define __TESTEVENTHANDLER_H__

#include "GUI/Visual/EventHandler.h"
#include "GUI/Components/MainCanvas.h"
#include "TestTimer.h"
#include "TestThread.h"

class HUD;

/*
	==CTestEventHandler==
	CEventHandler component test.
*/
class CTestEventHandler : public CEventHandler
{
private:
	//main display surface
	CMainCanvas* m_pMainCanvas;
	Hud* m_pHud;
	//main display surface
	//SDL_Surface* m_pDisplaySurface;
	//test timer
	CTestTimer* m_pTestTimer;
	//test thread
	CTestThread* m_pTestThread;
    //last ticks
    Uint32 m_pLastTicks;
    Uint32 m_pLastTicks2;
protected:
    //idle behavior
	virtual void OnIdle();
    //update loop
	virtual void Update();
public:
	//constructor
	CTestEventHandler();
	//destructor
	virtual ~CTestEventHandler();
	//initialization
	bool OnInit(int argc,char* argv[]);
	//left button down
	void OnLButtonDown(Uint16 x,Uint16 y);
	//mouse move
	void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	//key press
	void OnKeyDown(SDLKey sym,SDLMod mod,Uint16 unicode);
	//message handler
	bool OnMessage(MSGID MsgID,MSGPARM Parm1,MSGPARM Parm2,MSGPARM Parm3,MSGPARM Parm4);
   	//event filtering
	bool FilterEvent(SDL_Event* pEvent);
	//message ids
	static MSGID MSGID_QuitApp;//no parms
	static MSGID MSGID_ClearScreen;//no parms
	static MSGID MSGID_DrawPixel;//parm1=x,parm2=y
};

#endif //#ifndef __TESTEVENTHANDLER_H__
