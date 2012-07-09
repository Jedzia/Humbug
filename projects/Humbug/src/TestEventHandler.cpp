// TestEventHandler.cpp: implementation of the CTestEventHandler class.

//
//////////////////////////////////////////////////////////////////////
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Color.h"
#include "GUI/Components/Image.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Hud.h"
#include "TestEventHandler.h"
#include "stdafx.h"

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
MSGID CTestEventHandler::MSGID_QuitApp = CMessageHandler::GetNextMSGID(); //no parms
MSGID CTestEventHandler::MSGID_ClearScreen = CMessageHandler::GetNextMSGID(); //no parms
MSGID CTestEventHandler::MSGID_DrawPixel = CMessageHandler::GetNextMSGID(); //parm1=x,parm2=y
//constructor
CTestEventHandler::CTestEventHandler() :
    m_pLastTicks(0),
    m_pLastTicks2(0),
    m_pHud(NULL){
    //dbgOut(__FUNCTION__ << std::endl);
}

//destructor
CTestEventHandler::~CTestEventHandler(){
    if(m_pHud) {
        delete m_pHud;
    }

    delete CControl::GetMainControl();

    //destroy timer
    delete m_pTestTimer;

    //destroy thread
    delete m_pTestThread;
    dbgOut(__FUNCTION__ << std::endl);
}

//initialization
bool CTestEventHandler::OnInit(int argc, char* argv[]){
    //initialize parent class
    CEventHandler::OnInit(argc, argv);

    //create display surface
    Uint32 video_flags;

    //video_flags = SDL_OPENGL;
    //video_flags = SDL_ANYFORMAT | SDL_FULLSCREEN;
    video_flags = SDL_ANYFORMAT ;

    //construct main canvas
    m_pMainCanvas = new CMainCanvas(1024, 768, 0, video_flags);

    //m_pDisplaySurface=m_pMainCanvas->GetSurface ( );
    //m_pDisplaySurface=SDL_SetVideoMode(1024,768,0,video_flags);
    /*if ( m_pDisplaySurface == NULL ) {
        fprintf(stderr, "Couldn't set GL mode: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
       }*/

    //create timer
    m_pTestTimer = new CTestTimer(this);

    //create thread
    m_pTestThread = new CTestThread(this);

    //char *file = "blue.bmp";
//    char* file = "D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/footer.png";
    //create main control
    CControl* mainControl = new CControl(m_pMainCanvas);

    //CControl mainControl(m_pMainCanvas);
    //char *file = "blue.png";
    FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");
    try
    {
        m_pHud = new Hud(fl, mainControl, new HudBackground(fl, "footer.png"), 0);
        //m_pHud = new Hud(fl, mainControl, new HudBackground(fl, "humbug.pdb"), 0);
    }
    catch (FileLoaderException ex)
    {
        std::cout << ex.what() << std::endl;

        //m_imp_ptr.reset();
    }

    // m_pHud = new Hud(fl, m_pMainCanvas);
    //m_pHud->Draw();
    //SDL_Flip( m_pMainCanvas->GetSurface( ) );   //Refresh the screen
    //success
    return(true);
} // OnInit

//idle behavior
void CTestEventHandler::OnIdle(){
    Uint32 now, diff;
    now = SDL_GetTicks();
    diff = now - m_pLastTicks;
    /*if(diff > 100) {
        fprintf(stdout, "IDL-Ticks: '%d' (%d diff)\n", now, diff);
        m_pLastTicks = now;
       }*/

    //update controls
    CControl::Redraw();
    if(m_pHud /*!= NULL && m_pHud->HasMouseHover()*/)
    {
        int zz = 3;
        zz = 5;
        // CRectangle rmf(m_pHud->GetLeft(), m_pHud->GetTop(),m_pHud->GetRight(),m_pHud->GetBottom());
        //CRectangle rmf(m_pHud->GetLeft(), m_pHud->GetTop(),m_pHud->GetRight(),m_pHud->GetBottom());
        CRectangle rmfull(0,0,1024,768);
        CRectangle rmf(0,0,1024,768 - m_pHud->GetHeight());
        //m_pMainCanvas->AddUpdateRect(rmfull);
    }


    static int x = 0;
    static int y = 25;
    if(x<768)
    {
        CRectangle frect(x,x,y,y);
        //m_pMainCanvas->FillRect(frect, CColor::Red());
        //m_pMainCanvas->AddUpdateRect(frect);
    }
    else
    {
        x = 0;
        y += 25;
    }
    x++;
    //m_pHud->Draw();
    //m_pMainCanvas->Flip();

    m_pMainCanvas->UpdateRects ( );
    // call base method.
    CApplication::OnIdle();
}

//update loop
void CTestEventHandler::Update(){
    Uint32 now, diff;
    now = SDL_GetTicks();
    diff = now - m_pLastTicks2;
    /*if(diff > 100) {
        fprintf(stdout, "UPD-Ticks: '%d' (%d diff)\n", now, diff);
        m_pLastTicks2 = now;
       }*/

    // call base method.
    CApplication::Update();
}

//left button down
void CTestEventHandler::OnLButtonDown(Uint16 x, Uint16 y){
    //draw a pixel
    SendMessage(MSGID_DrawPixel, (MSGPARM)x, (MSGPARM)y);
}

//mouse move
void CTestEventHandler::OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft,
        bool bRight,
        bool bMiddle){
    //if left button is down
    if(bLeft) {
        //draw a pixel
        SendMessage(MSGID_DrawPixel, (MSGPARM)x, (MSGPARM)y);
    }
}

//key press
void CTestEventHandler::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){
    if( sym == SDLK_ESCAPE ) {
        //send clear screen message
        SendMessage(MSGID_QuitApp);
    }
    else {
        //send clear screen message
        SendMessage(MSGID_ClearScreen);
    }
}

//message handler
bool CTestEventHandler::OnMessage(MSGID MsgID, MSGPARM Parm1, MSGPARM Parm2, MSGPARM Parm3,
        MSGPARM Parm4){
    // quit application
    if(MsgID==MSGID_QuitApp) {
        //m_pHud->Close();
        //m_pHud->Update();
        SDL_Event quit;
        quit.type = SDL_QUIT;
        SDL_PushEvent(&quit);
        return(true);
    }
    //clear screen
    else if(MsgID==MSGID_ClearScreen) {
        //SDL_FreeSurface(m_pImgFooter);
        if(m_pHud) {
            m_pHud->Close();
            m_pHud = NULL;
        }

        m_pMainCanvas->Clear( CColor(0, 0, 0) );
        m_pMainCanvas->AddUpdateRect(m_pMainCanvas->GetDimension());

        //update the screen
        //m_pMainCanvas->Flip();
        return(true);
    }
    //draw pixel
    else if(MsgID==MSGID_DrawPixel) {
        /*//set up rectangle
           SDL_Rect rcFill;
           rcFill.x=(Sint16)Parm1;
           rcFill.y=(Sint16)Parm2;
           rcFill.w=1;
           rcFill.h=1;
           //fill the rectangle black
           SDL_FillRect(m_pMainCanvas->GetSurface( ),&rcFill,SDL_MapRGB(m_pMainCanvas->GetSurface(
              )->format,255,255,255));
           //update the screen
           SDL_UpdateRect(m_pMainCanvas->GetSurface( ),0,0,0,0);
           //success*/
        if( m_pMainCanvas->Lock() ) {
            //successful lock
            //set pixel
            m_pMainCanvas->SetPixel( (Sint16)Parm1, (Sint16)Parm2, CColor(255, 255, 255) );
            CRectangle frect((Sint16)Parm1,(Sint16)Parm2,1,1);
            //m_pMainCanvas->FillRect(frect, CColor::Red());
            m_pMainCanvas->AddUpdateRect(frect);

            //m_pMainCanvas->AddUpdateRect(CRectangle((Sint16)Parm1, (Sint16)Parm2,(Sint16)Parm1+1,
            // (Sint16)Parm2+1));
            //unlock
        }

        m_pMainCanvas->Unlock();

        //m_pMainCanvas->Flip();
        return(true);
    }
    //other message
    else {return( CEventHandler::OnMessage(MsgID, Parm1, Parm2, Parm3, Parm4) ); 
    }
} // OnMessage

//event filtering
bool CTestEventHandler::FilterEvent(SDL_Event* pEvent)
{
	return(CControl::FilterEvent(pEvent));
}


//declare application variable
CTestEventHandler TheApp;
