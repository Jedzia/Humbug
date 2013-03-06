#ifndef HUMBUG___TESTEVENTHANDLER_H__
#define HUMBUG___TESTEVENTHANDLER_H__

#include "GUI/Visual/EventHandler.h"
#include "GUI/Components/MainCanvas.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include "boost/smart_ptr/scoped_ptr.hpp"

namespace gui { 
	class CSprite;
	class CTileEngine;
	class CTileSet;
	class Hookable;
	class Screen;
	class CConsole;

	namespace components {
	class CImage;
}
}

class HUD;
class CTestThread;
class CTestTimer;
class PlayerKeys;

namespace humbug {

	using gui::CTileEngine;	
/*
	==CTestEventHandler==
	CEventHandler component test.
*/
class CTestEventHandler : public gui::CEventHandler
{
private:
    boost::scoped_ptr<FileLoader> fl;
    //FileLoader* fl;
    //main display surface
    gui::CConsole* m_pConsole;

    CCanvas* m_pBackground;
    CCanvas* m_pDrawCanvas;
    CImage* m_pBlue;
	gui::CSprite* m_pSprite;
    gui::CSprite* m_pSprite2;
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

    gui::Screen* m_scrStart;
protected:
    //idle behavior
	virtual void OnIdle(int frameNumber);
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
	bool OnMessage(gui::MSGID MsgID,gui::MSGPARM Parm1,gui::MSGPARM Parm2,gui::MSGPARM Parm3,gui::MSGPARM Parm4);
   	//event filtering
	bool FilterEvent(SDL_Event* pEvent);
	//message ids
	static gui::MSGID MSGID_ClearScreen;//no parms
	static gui::MSGID MSGID_DrawPixel;//parm1=x,parm2=y
};
}
#endif //#ifndef HUMBUG___TESTEVENTHANDLER_H__
