// TestEventHandler.cpp: implementation of the CTestEventHandler class.

//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

//#include "windows.h"
//#include <build/cmake/include/debug.h>
//
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Color.h"
#include "GUI/Components/Image.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Controls/Button.h"
#include "GUI/Hud.h"
#include "GUI/Sprite/Sprite.h"
#include "GUI/TileEngine/TileEngine.h"
#include "GUI/Visual/Console.h"
#include "PlayerKeys.h"
#include "TestEventHandler.h"
#include "TestThread.h"
#include "TestTimer.h"
#include "StartScreen.h"
#include "GUI/Visual/HookableManager.h"
#include "TestScreen.h"

//#include "GUI/TileEngine/TileSet.h"
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
MSGID CTestEventHandler::MSGID_ClearScreen = CMessageHandler::GetNextMSGID(); //no parms
MSGID CTestEventHandler::MSGID_DrawPixel = CMessageHandler::GetNextMSGID(); //parm1=x,parm2=y
//constructor
CTestEventHandler::CTestEventHandler() :
    m_pConsole(NULL),
    //fl(new FileLoader("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data")),
    m_uiLastTicks(0),
    m_inActiveSprite(0),
    /*m_pTileSet(NULL),*/
    m_uiLastTicks2(0),
    m_uiNumFrames(0),
    m_pKeyHandler(NULL),
    m_pKeyHandler2(NULL),
    m_pSprite(NULL),
    m_pSprite2(NULL),
    m_pHud(NULL),
    m_inScreenDelta(0){
    //dbgOut(__FUNCTION__ << std::endl);
//	_CRT_DEBUG_BLOCK
}

//destructor
CTestEventHandler::~CTestEventHandler(){
    std::cout << "Killing the ~CTestEventHandler" << std::endl;

    //if(m_pHud) {
    //    delete m_pHud;
    //}
    //delete CControl::GetMainControl();
    //delete m_pMainCanvas;
    dbgOut(__FUNCTION__ << std::endl);

//    const char* explanation = "XXXXXX THIS IS TESTEVENTHANDLER.CPP";
//_RPT1( _CRT_WARN, "\n\n%s:\n**************************************
// //************************************\n", explanation );
//    _CrtDumpMemoryLeaks( );
}

//on cleanup
void CTestEventHandler::OnExit(){

    //destroy timer
    delete m_pTestTimer;

    //destroy thread
    delete m_pTestThread;



    //delete main canvas
    //delete m_pMainCanvas;

    //delete main control
    delete CControl::GetMainControl();
    delete m_pSprite;
    delete m_pSprite2;
    delete m_pBackground;
    delete m_pBlue;

    //delete m_pTileSet;
    delete m_pTileEngine;
    delete m_pKeyHandler;
    delete m_pKeyHandler2;
    delete m_pConsole;
    fl.reset();
    //destroy font
    //TTF_CloseFont( CButton::GetButtonFont() );
    //shut down font system
    TTF_Quit();
    CEventHandler::OnExit();
} // OnExit

//initialization
bool CTestEventHandler::OnInit(int argc, char* argv[]){
    //initialize parent class
    CEventHandler::OnInit(argc, argv);

    //create display surface
    Uint32 video_flags;

    //video_flags = SDL_OPENGL;
    //video_flags = SDL_ANYFORMAT | SDL_FULLSCREEN;
    //video_flags = SDL_ANYFORMAT;
    video_flags = SDL_HWSURFACE | SDL_DOUBLEBUF;

    //video_flags = SDL_HWSURFACE|SDL_DOUBLEBUF| SDL_FULLSCREEN;
    //SDL_EnableKeyRepeat(100, 1);
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL/2);
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY/10, SDL_DEFAULT_REPEAT_INTERVAL/3);
    //construct main canvas
    //m_pMainCanvas = new CMainCanvas(1024, 768, 0, video_flags);
    CMainCanvas* m_pMainCanvas = new CMainCanvas(1024, 768, 0, video_flags);
    SetMainCanvas( m_pMainCanvas );

    //m_pDrawCanvas = m_pMainCanvas;
    //CCanvas *testCanvas = CCanvas::CreateRGBCompatible(NULL, 1024 * 10, 768-320);
    //CCanvas::CreateRGBCompatible(NULL, 1024 * 10, 768-320);
    //CCanvas::CreateRGBCompatible(NULL, 1024 * 10, 768-320);
    //CCanvas::CreateRGBCompatible(NULL, 1024 * 10, 768-320);
    //CCanvas::CreateRGBCompatible(NULL, 1024 * 10, 768-320);
    // move this to the application class
    m_uiStartTime = SDL_GetTicks();

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

    //initialize sdl_ttf
    TTF_Init();


    //CControl mainControl(m_pMainCanvas);
    //char *file = "blue.png";
    //FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");
    //fl = new FileLoader("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");
    fl.reset(new FileLoader("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data"));

    //FileLoader fl2("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");
    CTileSet* tileSet = NULL;
    try
    {
        //load in button font. Todo: Error Checking
        //TTF_OpenFont(
          //  "D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/arial.ttf", 15)
        TTF_Font *arial = fl->LoadFont("Fonts/ARIAL.TTF", 15);
        CButton::SetButtonFont( arial );

        //m_pBackground->FillRect(m_pBackground->GetDimension(), CColor::LightRed());
        m_pHud = new Hud(*fl, mainControl, new HudBackground(*fl, "Hud/footer.png"), 0);

        //create a button
        new CButton(m_pHud, CRectangle(100, 100, 150, 25), 1, "Come on, Press me!");

        //new CButton(CControl::GetMainControl(),CRectangle(100,100,50,25),1,"Test");
        // m_pBackground = m_pMainCanvas->CreateRGBCompatible(NULL, 1024, 768- m_pHud->GetHeight());
        {
            SDL_Surface* loadsurf;
            SDL_Surface* tmpsurf;

            //tmpsurf = SDL_DisplayFormatAlpha( loadsurf = fl.LoadImg("Moo.png") );
            tmpsurf = SDL_DisplayFormatAlpha( loadsurf = fl->LoadImg("Moo.png") );

            // delete loadsurf;
            CCanvas tmpCanvas(tmpsurf);
            CCanvas* testCanvas = CCanvas::CreateRGBCompatible(NULL, 1024 * 5, 768 - 320);
            testCanvas->Blit( tmpCanvas.GetDimension(), tmpCanvas, tmpCanvas.GetDimension() );
            m_pBackground = testCanvas;

            //delete tmpsurf;
            //SDL_FreeSurface( loadsurf );
            fl->FreeLast();

            //SDL_FreeSurface( tmpsurf );
        }

        //m_pBackground = new CCanvas( SDL_DisplayFormatAlpha( tmpsurf ));
        //m_pBackground = m_pMainCanvas->CreateRGBCompatible(NULL, 1024, 768);
        //SDL_Surface* g_pBitmapSurface = fl.LoadImg("icons/blue.png");
        SDL_Surface* g_pBitmapSurface = SDL_DisplayFormatAlpha( fl->LoadImg("icons/blue.png") );
        fl->FreeLast();

        //SDL_FreeSurface( loadsurf );
        //SDL_SetAlpha(g_pBitmapSurface,SDL_SRCALPHA, 0);
        //SDL_SetAlpha(m_pBlue->GetCanvas()->GetSurface(), SDL_SRCALPHA, 255);
        m_pBlue = new CImage( new CCanvas( g_pBitmapSurface ), true );

        //m_pSprite = new CSprite(m_pMainCanvas, m_pBlue);
        {
            SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( fl->LoadImg("icons/red.png") );
            CCanvas* tmpCanvas = new CCanvas( tmpfsurf );
            fl->FreeLast();
            m_pSprite = new CSprite(m_pMainCanvas, new CImage( tmpCanvas,
                            true ), m_pBackground, true);
        }

        //CRectangle spr2Dim(0,0,32,32);
        //m_pSprite2 = new CSprite(m_pMainCanvas,
        //    new CImage( new CCanvas( SDL_DisplayFormatAlpha( fl.LoadImg("Voiture.bmp")) ), spr2Dim
        // ),
        //    m_pBackground, spr2Dim, CPoint(32,0));
        m_pSprite2 = new CSprite( *fl, "Sprites/Voiture.bmp", m_pMainCanvas,
                CRectangle(0, 0, 32, 32), CPoint(32, 0) );

        //m_pSprite2->m_pSprImage->SrcRect() = spr2Dim.Move(CPoint(32,0)*15);
        //SDL_Surface* ddd1 = fl2.LoadImg("icons/blue.png");
        //m_pHud = new Hud(fl, mainControl, new HudBackground(fl, "humbug.pdb"), 0);
        CTileImageSetup tilesetup;
        tilesetup.BitmapIdentifier = "Tiles1";
        tilesetup.TileWidth = 64;
        tilesetup.TileHeight = 64;
        tilesetup.TileCountX = 4;
        tilesetup.TileCountY = 1;
        tilesetup.TransparentX = 0;
        tilesetup.TransparentY = 0;
        tilesetup.Sequences = 0;
        tileSet = new CTileSet( m_pMainCanvas, new CTileImage(*fl, "Tiles1.bmp", tilesetup),
                m_pBackground, CRectangle(0, 0, 1024, 768 - 320) );

        // fl->Free("Tiles1.bmp");
    }
    catch (FileLoaderException ex)
    {
        std::cout << ex.what() << std::endl;

        //m_imp_ptr.reset();
    }
    m_pDrawCanvas = m_pBackground;

    //m_pTileSet->GetTileImage()->ShowTiles(m_pBackground);
    //CTile tile = m_pTileSet->CreateTile(1);
    //tile.Draw(m_pBackground, CPoint(200,300));
    m_pTileEngine = new CTileEngine(m_pMainCanvas, m_pBackground);
    m_pTileEngine->AddTileSet(tileSet);
    CTileEngine& eng = (*m_pTileEngine);
    (*m_pTileEngine)["Tiles1"]->GetTileImage()->ShowTiles(m_pBackground);
    CTile tile1 = eng["Tiles1"]->CreateTile(0);
    CTile tile2 = eng["Tiles1"]->CreateTile(1);
    CTile tile3 = eng["Tiles1"]->CreateTile(2);
    CTile tile4 = eng["Tiles1"]->CreateTile(3);

    for (int i = 0; i < 20; i += 4)
    {
        const int xdiff = 300;
        tile1.Draw( m_pBackground, CPoint(xdiff * i, 300) );
        tile2.Draw( m_pBackground, CPoint(xdiff * (i + 1), 300) );
        tile3.Draw( m_pBackground, CPoint(xdiff * (i + 2), 300) );
        tile4.Draw( m_pBackground, CPoint(xdiff * (i + 3), 300) );
    }
    //m_pBlue = new CCanvas( m_pLoader.LoadImg("blue.png") );
    //SDL_Surface* ddd =
    // IMG_Load("D:/E/Projects/C++/Humbug/projects/Humbug/Artwork/Clipboard01.png");
    //m_pBlue = new CImage( new CCanvas( ddd ) );
    //m_pBlue = new CImage( new CCanvas( ddd ) );
    // m_pHud = new Hud(fl, m_pMainCanvas);
    //m_pHud->Draw();
    //SDL_Flip( m_pMainCanvas->GetSurface( ) );   //Refresh the screen
    //success
    m_pKeyHandler = new PlayerKeys(200, 200);
    m_pKeyHandler2 = new PlayerKeys(400, 200);

    // Maybe we do not need the backing variables, since a Hookable is destroyed individually
    //m_Hooks = new Hookable(this);


    //new TestHookable();
    //new TestHookable();
    //m_scrStart = new StartScreen(*fl, m_pMainCanvas);
    //HookMgr()->AddHookable("StartScreen", m_scrStart, true);
    //HookMgr()->EnableHookable("StartScreen");
    //HookMgr()->AddHookable("Test1", new TestHookable());

    //Hookable *nn = HookCreator<StartScreen>::Create();
    //Hookable *nn = HookCreator<StartScreen>::Create();
    //StartScreenCreator<StartScreen> eee(*fl, m_pMainCanvas);
    //Hookable *nn = ScreenCreator<StartScreen>(*fl, m_pMainCanvas).Create();

    //boost::shared_ptr<HookCreator> nn(new ScreenCreator<StartScreen>(*fl, m_pMainCanvas));
    //HookMgr()->RegisterHookable("XXXX", nn);
    
    //HookMgr()->RegisterHookable("Test2", HookCreatorPtr(new DefaultHookCreator<TestHookable>()));
    HookMgr()->RegisterHookable("StartScreen", HookCreatorPtr(new ScreenCreator<StartScreen>(*fl, m_pMainCanvas)));
    HookMgr()->RegisterHookable("Test1", HookCreatorPtr(new ScreenCreator<TestScreen>(*fl, m_pMainCanvas)));
    HookMgr()->EnableHookable("StartScreen");
    //std::vector<boost::shared_ptr<HookCreator>> xx;
    //xx.push_back(nn);
    //std::map<std::string, boost::shared_ptr<HookCreator>> xx;
    //xx.insert(std::make_pair("XXXX", nn));

    //new TestHookable();
    //new TestHookable();

    m_pConsole =
        new CConsole( this, "D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/ConsoleFont.bmp",
                m_pMainCanvas, 100, CRectangle(0, 0, 0,
                        300) );
    return(true);
} // OnInit

void CTestEventHandler::PutBlue(){
    if(m_pHud /*!= NULL && m_pHud->HasMouseHover()*/) {

    }
} // PutBlue

//idle behavior - Draw the stuff
void CTestEventHandler::OnIdle(int frameNumber){
    CApplication::OnIdle(frameNumber); return;

    Uint32 now, diff;
    now = SDL_GetTicks();
    diff = now - m_uiLastTicks;

    if(diff > 20) {
        m_pKeyHandler->HookIdle();
        m_pKeyHandler2->HookIdle();

        //fprintf(stdout, "IDL-Ticks: '%d' (%d diff)\n", now, diff);
        m_uiLastTicks = now;
    }

    CMainCanvas* m_pMainCanvas = GetMainCanvas();
    //m_pMainCanvas->Lock();

    //update controls
    CRectangle screenrect = m_pMainCanvas->GetDimension();

    //m_pBackground->Blit(screenrect, m_pMainCanvas, screenrect);
    //m_pBackground->UpdateRects();
    //CRectangle& screenWithoutHud = m_pBackground->GetDimension().Intersect(
    // m_pHud->GetCanvas()->GetDimension());
    //CRectangle& screenWithoutHud = m_pBackground->GetDimension().Union(
    // m_pHud->GetCanvas()->GetDimension());
    CRectangle screenWithoutHud( 0, 0,
            m_pMainCanvas->GetDimension().GetW(), m_pMainCanvas->GetDimension().GetH() -
            m_pHud->GetCanvas()->GetDimension().GetH() );

    //CRectangle& screenWithoutHud = m_pMainCanvas->GetDimension().Move(hudsize);
    //m_pMainCanvas->Blit(screenrect, *m_pBackground, screenrect);
    static int scrdel = 0;
    scrdel += m_inScreenDelta;
    m_pMainCanvas->Blit( screenWithoutHud, *m_pBackground, screenWithoutHud + CPoint(scrdel, 0) );

    //m_pHud->Invalidate();
    CControl::Redraw();

    //m_pHud->Draw();
    //PutBlue();
    //for (int i = 0; i < 50 ; i++)
    {
        m_pSprite->Draw();
        m_pSprite2->Draw();
    }
    m_pConsole->Draw();

    //m_pHud->Draw();
    //m_pMainCanvas->Flip();
    // kucken fuer was 'screenrect' gebraucht wird und ob das stimmt.
    //m_pMainCanvas->ClearUpdateRects();
    if(m_inScreenDelta != 0) {
        m_pMainCanvas->AddUpdateRect( CRectangle( 0, 0, m_pMainCanvas->GetWidth(),
                        m_pMainCanvas->GetHeight() - m_pHud->GetHeight() ) );
    }

    //m_pMainCanvas->UpdateRects ( );
    
    //m_pMainCanvas->Unlock();


    static int spr2pic = 0;
    m_pSprite2->SprOffset(spr2pic);
    spr2pic++;

    if (spr2pic == 16) {
        spr2pic = 0;
    }

    // call base method.
    CApplication::OnIdle(frameNumber);
} // OnIdle

//update loop
void CTestEventHandler::Update(){
    Uint32 now, diff;
    now = SDL_GetTicks();
    diff = now - m_uiLastTicks2;
    /*if(diff > 100) {
        fprintf(stdout, "UPD-Ticks: '%d' (%d diff)\n", now, diff);
        m_pLastTicks2 = now;
       }*/
    m_pSprite->SetPos(m_pKeyHandler->Char() /* + CPoint(50,50)*/);
    m_pSprite2->SetPos( m_pKeyHandler2->Char() );

    // call base method.
    CApplication::Update();
}

//event handling
void CTestEventHandler::OnEvent(SDL_Event* pEvent){
    if( m_pConsole->OnEvent(pEvent) ) {
        //SendMessageQ(MSGID_ClearScreen);
        //OnIdle();
        return;
    }

    CEventHandler::OnEvent(pEvent);

    if (m_inActiveSprite == 0) {
        m_pKeyHandler->HookEventloop(pEvent);
    }
    else if (m_inActiveSprite == 1)   {
        m_pKeyHandler2->HookEventloop(pEvent);
    }
}

//#undef SendMessageQ(x,y,z)
//left button down
void CTestEventHandler::OnLButtonDown(Uint16 x, Uint16 y){
    //draw a pixel
    SendMessageQ(MSGID_DrawPixel, (MSGPARM)x, (MSGPARM)y);
}

//mouse move
void CTestEventHandler::OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft,
        bool bRight,
        bool bMiddle){
    //if left button is down
    if(bLeft) {
        //draw a pixel
        SendMessageQ(MSGID_DrawPixel, (MSGPARM)x, (MSGPARM)y);
    }
}

//key press
void CTestEventHandler::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){
    const int step = 6;
    CMainCanvas* m_pMainCanvas = GetMainCanvas();

    if( sym == SDLK_ESCAPE ) {
        //send clear screen message
        SendMessageQ(MSGID_QuitApp);
    }
    else if( sym == SDLK_LEFT )   {
        //
        CRectangle frect(100, 200, 45, 45);
        m_pMainCanvas->FillRect( frect, CColor::Green() );
        m_pMainCanvas->AddUpdateRect(frect);
    }
    else if( sym == SDLK_RIGHT )   {
        //
        CRectangle frect(100, 200, 45, 45);
        m_pMainCanvas->FillRect( frect, CColor::Blue() );
        m_pMainCanvas->AddUpdateRect(frect);
    }
    else if( sym == SDLK_UP )   {
        //
        CRectangle frect(100, 200, 45, 45);
        m_pMainCanvas->FillRect( frect, CColor(255, 255, 0) );
        m_pMainCanvas->AddUpdateRect(frect);
    }
    else if( sym == SDLK_DOWN )   {
        //
        CRectangle frect(100, 200, 45, 45);
        m_pMainCanvas->FillRect( frect, CColor(255, 255, 255) );
        m_pMainCanvas->AddUpdateRect(frect);
    }
    else if( sym == SDLK_b )   {
        //
        m_pBackground->Clear( CColor(0, 0, 0) );
        m_pMainCanvas->AddUpdateRect( m_pMainCanvas->GetDimension() );
    }
    else if( sym == SDLK_F1 )   {
        //
        m_inActiveSprite ^= 1;
    }
    else if( mod == KMOD_LCTRL && sym == SDLK_BACKQUOTE )   {
        // toggle console
        m_pConsole->Toggle();
    }
    else if( sym == SDLK_a )   {
        // toggle console
        m_inScreenDelta++;
    }
    else if( sym == SDLK_d )   {
        // toggle console
        m_inScreenDelta--;
    }
    else if( sym == SDLK_c )   {
        //send clear screen message
        SendMessageQ(MSGID_ClearScreen);
    }
    else if( sym == SDLK_1 )   {
        //
        //HookMgr()->Test1();
        //HookMgr()->DisableHookable("StartScreen");
        HookMgr()->EnableHookable("Test1");
    }
    else if( sym == SDLK_2 )   {
        //
        //HookMgr()->Test2();
        HookMgr()->EnableHookable("StartScreen");
    }

} // OnKeyDown

//message handler
bool CTestEventHandler::OnMessage(MSGID MsgID, MSGPARM Parm1, MSGPARM Parm2, MSGPARM Parm3,
        MSGPARM Parm4){
            CMainCanvas* m_pMainCanvas = GetMainCanvas();
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
            //m_pHud->Close();
            //m_pHud = NULL;
        }

        m_pMainCanvas->Clear( CColor(0, 0, 0) );

        if(m_pHud) {
            m_pHud->Invalidate();
            m_pHud->Draw();
        }

        m_pMainCanvas->AddUpdateRect( m_pMainCanvas->GetDimension() );

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
            //m_pDrawCanvas->SetPixel( (Sint16)Parm1, (Sint16)Parm2, CColor(255, 255, 255) );
            CRectangle frect( (Sint16)(int)Parm1, (Sint16)(int)Parm2, 1, 1 );

            //m_pMainCanvas->FillRect(frect, CColor::Red());
            //m_pDrawCanvas->AddUpdateRect(frect);
            m_pBlue->Put( m_pDrawCanvas, CPoint( (Sint16)(int)Parm1, (Sint16)(int)Parm2 ) );

            for (int i = 0; i < 50; i++) {
                m_pMainCanvas->AddUpdateRect( CRectangle( (Sint16)(int)Parm1, (Sint16)(int)Parm2,
                                m_pBlue->GetCanvas()->GetWidth(), m_pBlue->GetCanvas()->GetHeight() ) );
            }
//            m_pMainCanvas->AddUpdateRect(CRectangle((Sint16)Parm1, (Sint16)Parm2,(Sint16)Parm1+1,
//             (Sint16)Parm2+1));
            //unlock
            m_pMainCanvas->Unlock();
        }

        //m_pMainCanvas->Flip();
        return(true);
    }
    //other message
    else {return( CEventHandler::OnMessage(MsgID, Parm1, Parm2, Parm3, Parm4) );
    }
} // OnMessage

//event filtering
bool CTestEventHandler::FilterEvent(SDL_Event* pEvent){
    /*if(m_pConsole->OnEvent(pEvent))
       {
        return true;
       }*/
    return( CControl::FilterEvent(pEvent) );
}

//declare application variable
CTestEventHandler TheApp;
