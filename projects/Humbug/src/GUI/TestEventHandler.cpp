// TestEventHandler.cpp: implementation of the CTestEventHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
#include "TestEventHandler.h"

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        // protected override void Draw(GameTime gameTime)

        /// <summary>
        /// Handles input for quitting the game.
        /// </summary>
        // private void HandleInput(GameTime gameTime)

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        //protected override void Update(GameTime gameTime)
        //{
        //    this.HandleInput(gameTime);
        //
        //    //this.pilleanim.Update(gameTime.ElapsedGameTime, Matrix.Identity);
        //    animationController.Update(gameTime.ElapsedGameTime, Matrix.Identity);
        //    // TODO: Add your update logic here
        //
        //    base.Update(gameTime);
        //}


//message ids
MSGID CTestEventHandler::MSGID_QuitApp=CMessageHandler::GetNextMSGID();//no parms
MSGID CTestEventHandler::MSGID_ClearScreen=CMessageHandler::GetNextMSGID();//no parms
MSGID CTestEventHandler::MSGID_DrawPixel=CMessageHandler::GetNextMSGID();//parm1=x,parm2=y

//constructor
CTestEventHandler::CTestEventHandler()
: m_pLastTicks(0), m_pLastTicks2(0)
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
    Uint32 video_flags;
    //video_flags = SDL_OPENGL;
    video_flags = SDL_ANYFORMAT;
    m_pDisplaySurface=SDL_SetVideoMode(1024,768,0,video_flags);
	if ( m_pDisplaySurface == NULL ) {
		fprintf(stderr, "Couldn't set GL mode: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

    //create timer
    m_pTestTimer=new CTestTimer(this);

    //create thread
    m_pTestThread=new CTestThread(this);

    //char *file = "blue.bmp";
    char *file = "D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/footer.png";
    //char *file = "blue.png";

    // move this to a HUD class with Draw()
    SDL_Surface *img;
    img = IMG_Load(file);
    if (!img) {
        fprintf(stderr, "Error: '%s' could not be opened: %s\n", file, IMG_GetError());
        // exitstate = false;
        // return NULL;
    } else {
        //DrawImage(img, 1024 - img->w, 768 - img->h, img->w, img->h, m_pDisplaySurface, 10, 10, 128);
        DrawImage(img, 0, 0, img->w, img->h, m_pDisplaySurface, 0, 768 - img->h, 128);
        SDL_Flip(m_pDisplaySurface); //Refresh the screen
    }

    //success
    return(true);
}

//idle behavior
void CTestEventHandler::OnIdle()
{
   	Uint32 now, diff;
    now = SDL_GetTicks();
    diff = now - m_pLastTicks;
    if(diff > 10)
    {
        fprintf(stdout, "IDL-Ticks: '%d' (%d diff)\n", now, diff);
        m_pLastTicks = now;
    }

	// call base method.
    CApplication::OnIdle();
}

//update loop
void CTestEventHandler::Update()
{
   	Uint32 now, diff;
    now = SDL_GetTicks();
    diff = now - m_pLastTicks2;
    if(diff > 100)
    {
        fprintf(stdout, "UPD-Ticks: '%d' (%d diff)\n", now, diff);
        m_pLastTicks2 = now;
    }

	// call base method.
    CApplication::OnIdle();
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
    if( sym == SDLK_ESCAPE )
    {
	    //send clear screen message
	    SendMessage(MSGID_QuitApp);
    }
    else        
    {
	    //send clear screen message
	    SendMessage(MSGID_ClearScreen);
    }
}

//message handler
bool CTestEventHandler::OnMessage(MSGID MsgID,MSGPARM Parm1,MSGPARM Parm2,MSGPARM Parm3,MSGPARM Parm4)
{
	// quit application
	if(MsgID==MSGID_QuitApp)
	{
        SDL_Event quit;
        quit.type = SDL_QUIT;
        SDL_PushEvent(&quit);
		return(true);
    }
	//clear screen
	else if(MsgID==MSGID_ClearScreen)
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
