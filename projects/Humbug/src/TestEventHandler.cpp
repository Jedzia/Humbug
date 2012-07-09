// TestEventHandler.cpp: implementation of the CTestEventHandler class.

//
//////////////////////////////////////////////////////////////////////
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Color.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Components/Image.h"
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
    m_pLastTicks2(0)
{}

//destructor
CTestEventHandler::~CTestEventHandler(){
    //destroy timer
    delete m_pTestTimer;

    //destroy thread
    delete m_pTestThread;
}

//initialization
bool CTestEventHandler::OnInit(int argc, char* argv[]){
    //initialize parent class
    CEventHandler::OnInit(argc, argv);

    //create display surface
    Uint32 video_flags;

    //video_flags = SDL_OPENGL;
    video_flags = SDL_ANYFORMAT;

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

    //char *file = "blue.png";
    // move this to a HUD class with Draw()
    FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");

    //fl.Load("testfile.txt");
    //fl.Load("libxml2_a_dll.lib");
    //m_pImgFooter = IMG_Load(file);
//    CCanvas footer( fl.LoadImg("footer.png") );
	//CRectangle blah(0,0,100,100);
	//CRectangle& blah = footer.GetDimension();
	//CRectangle kack((CRectangle&)footer.GetDimension());
	//CRectangle kack(footer.GetDimension());
//	std::cout << "The rect: |" << footer.GetDimension() << "|ends" << std::endl;
	//CImage footerImage( &footer , footer.GetDimension() , CPoint(0,0) ) ;
//	CImage footerImage( &footer ) ;
	//CImage footerImage( &footer , blah , CPoint(0,0) ) ;
    /*int imgh = footer.GetHeight( );
    int imgw = footer.GetWidth( );

    //m_pMainCanvas->Blit( CRectangle(0, m_pMainCanvas->GetHeight( ) - imgh, imgw,
    //              imgh), footer, footer.GetDimension() );
    CRectangle& dest( m_pMainCanvas->GetDimension( ) );
    dest.Offset( 0, m_pMainCanvas->GetHeight( ) - footer.GetHeight( ) );
    m_pMainCanvas->Blit( dest, footer, footer.GetDimension() );*/
	
//	footerImage.Put ( m_pMainCanvas , CPoint(0, m_pMainCanvas->GetHeight( ) - footer.GetHeight( )) ) ;

	Hud hud(fl, m_pMainCanvas);
	hud.Draw();
	
    SDL_Flip( m_pMainCanvas->GetSurface( ) );   //Refresh the screen
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
    m_pMainCanvas->Flip();

    //m_pMainCanvas->UpdateRects ( );
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
        SDL_Event quit;
        quit.type = SDL_QUIT;
        SDL_PushEvent(&quit);
        return(true);
    }
    //clear screen
    else if(MsgID==MSGID_ClearScreen) {
        //SDL_FreeSurface(m_pImgFooter);
        m_pMainCanvas->Clear( CColor(0, 0, 0) );

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

            //m_pMainCanvas->AddUpdateRect(CRectangle((Sint16)Parm1, (Sint16)Parm2,(Sint16)Parm1+1,
            // (Sint16)Parm2+1));
            //unlock
        }

        m_pMainCanvas->Unlock();

        //m_pMainCanvas->Flip();
        return(true);
    }
    //other message
    else {return( CEventHandler::OnMessage(MsgID, Parm1, Parm2, Parm3, Parm4) ); }} // OnMessage

//declare application variable
CTestEventHandler TheApp;
