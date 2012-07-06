// TestEventHandler.cpp: implementation of the CTestEventHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
#include "TestEventHandler.h"

//message ids
MSGID CTestEventHandler::MSGID_ClearScreen=CMessageHandler::GetNextMSGID();//no parms
MSGID CTestEventHandler::MSGID_DrawPixel=CMessageHandler::GetNextMSGID();//parm1=x,parm2=y

//constructor
CTestEventHandler::CTestEventHandler()
{
}

//destructor
CTestEventHandler::~CTestEventHandler()
{
	//destroy timer
	delete m_pTestTimer;

	//destroy thread
	delete m_pTestThread;
}

void DrawImage(SDL_Surface *srcimg, int sx, int sy, int sw, int sh, SDL_Surface *dstimg, int dx, int dy, int alpha = 255) {

 if ((srcimg == NULL) || (alpha == 0)) return; //If theres no image, or its 100% transparent.
 SDL_Rect src, dst;
 
 src.x = sx;  src.y = sy;  src.w = sw;  src.h = sh;
 dst.x = dx;  dst.y = dy;  dst.w = src.w;  dst.h = src.h;
 if (alpha != 255) SDL_SetAlpha(srcimg, SDL_SRCALPHA, alpha);
 SDL_BlitSurface(srcimg, &src, dstimg, &dst);

}

//initialization
bool CTestEventHandler::OnInit(int argc,char* argv[])
{
	//initialize parent class
	CEventHandler::OnInit(argc,argv);

	//create display surface
	m_pDisplaySurface=SDL_SetVideoMode(1024,768,0,SDL_ANYFORMAT);

	//create timer
	m_pTestTimer=new CTestTimer(this);

	//create thread
	m_pTestThread=new CTestThread(this);

	SDL_Surface *tux;
	tux = SDL_LoadBMP("blue.bmp");
	DrawImage(tux, 0,0, tux->w, tux->h, m_pDisplaySurface, 10, 10, 128);
	SDL_Flip(m_pDisplaySurface); //Refresh the screen
	
	//success
	return(true);
}

//left button down
void CTestEventHandler::OnLButtonDown(Uint16 x,Uint16 y)
{
	//draw a pixel
	SendMessage(MSGID_DrawPixel,(MSGPARM)x,(MSGPARM)y);
}

//mouse move
void CTestEventHandler::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
	//if left button is down
	if(bLeft)
	{
		//draw a pixel
		SendMessage(MSGID_DrawPixel,(MSGPARM)x,(MSGPARM)y);
	}
}

//key press
void CTestEventHandler::OnKeyDown(SDLKey sym,SDLMod mod,Uint16 unicode)
{
	//send clear screen message
	SendMessage(MSGID_ClearScreen);
}

//message handler
bool CTestEventHandler::OnMessage(MSGID MsgID,MSGPARM Parm1,MSGPARM Parm2,MSGPARM Parm3,MSGPARM Parm4)
{
	//clear screen
	if(MsgID==MSGID_ClearScreen)
	{
		//set up rectangle
		SDL_Rect rcFill;
		rcFill.x=rcFill.y=0;
		rcFill.w=m_pDisplaySurface->w;
		rcFill.h=m_pDisplaySurface->h;
		//fill the rectangle black
		SDL_FillRect(m_pDisplaySurface,&rcFill,0);
		//update the screen
		SDL_UpdateRect(m_pDisplaySurface,0,0,0,0);
		//success
		return(true);
	}
	//draw pixel
	else if(MsgID==MSGID_DrawPixel)
	{
		//set up rectangle
		SDL_Rect rcFill;
		rcFill.x=(Sint16)Parm1;
		rcFill.y=(Sint16)Parm2;
		rcFill.w=1;
		rcFill.h=1;
		//fill the rectangle black
		SDL_FillRect(m_pDisplaySurface,&rcFill,SDL_MapRGB(m_pDisplaySurface->format,255,255,255));
		//update the screen
		SDL_UpdateRect(m_pDisplaySurface,0,0,0,0);
		//success
		return(true);
	}
	//other message
	else return(CEventHandler::OnMessage(MsgID,Parm1,Parm2,Parm3,Parm4));
}

//declare application variable
CTestEventHandler TheApp;
