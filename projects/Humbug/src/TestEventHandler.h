#ifndef __TESTEVENTHANDLER_H__
#define __TESTEVENTHANDLER_H__

#include "GUI/Visual/EventHandler.h"
#include "GUI/Components/MainCanvas.h"

class HUD;
class CConsole;
class CImage;
class CSprite;
class CTestThread;
class CTestTimer;
class PlayerKeys;
class CTileEngine;
class CTileSet;
/*
	==CTestEventHandler==
	CEventHandler component test.
*/
class CTestEventHandler : public CEventHandler
{
private:
    FileLoader* fl;
    //main display surface
    CConsole* m_pConsole;
	//main display surface
	CMainCanvas* m_pMainCanvas;
    CCanvas* m_pBackground;
    CCanvas* m_pDrawCanvas;
    CImage* m_pBlue;
    CSprite* m_pSprite;
    CSprite* m_pSprite2;
    CTileEngine* m_pTileEngine;
    //CTileSet* m_pTileSet;
	Hud* m_pHud;
	//main display surface
	//SDL_Surface* m_pDisplaySurface;
    // Player movement;
    PlayerKeys* m_pKeyHandler;
    PlayerKeys* m_pKeyHandler2;
	//test timer
	CTestTimer* m_pTestTimer;
	//test thread
	CTestThread* m_pTestThread;
    //last ticks
    Uint32 m_uiLastTicks;
    Uint32 m_uiLastTicks2;
    Uint32 m_uiStartTime;
    void PutBlue();
    unsigned int m_uiNumFrames; 
    int m_inActiveSprite;
    int m_inScreenDelta;
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
	//cleanup
	void OnExit();
    //event handling
    void OnEvent(SDL_Event* pEvent);
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
	static MSGID MSGID_ClearScreen;//no parms
	static MSGID MSGID_DrawPixel;//parm1=x,parm2=y
};

#endif //#ifndef __TESTEVENTHANDLER_H__
