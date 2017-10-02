// TestEventHandler.cpp: implementation of the CTestEventHandler class.

//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

//#include "windows.h"
//
#include "HumbugFileLoader.h"
//#include "Filesystem/FileLoader.h"
#include "GUI/Components/Color.h"
#include "GUI/Components/Image.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Controls/Button.h"
//#include "GUI/Hud.h"
//#include "GUI/Sprite/Sprite.h"
#include "GUI/Visual/Console.h"
#include "Input/PlayerKeys.h"
#include "TestEventHandler.h"
#include "TestThread.h"
#include "TestTimer.h"
#include "Screens/StartScreen.h"
#include "GUI/Visual/HookableManager.h"
#include "Screens/TestScreen.h"
#include "Screens/HighscoreScreen.h"
#include "Screens/BlaScreen.h"
#include "Screens/LuaScreen.h"
#include "Screens/HopperScreen.h"
#include "Screens/MenuScreen.h"
#include "Levels/TestLevel.h"
#include "Levels/LevelA.h"
#include "HumbugLib/src/HumbugLib/AppGB.h"
#include "Screens/TileScreen.h"
#include "GUI/Components/MainCanvas.h"
#include "GUI/Components/Text.h"
#include "Screens/SimpleScreen.h"
#include "Screens/ZoomInScreen.h"
#include "Screens/ZoomInScreen2.h"
#include "Screens/MenuScreen/SubmenuA.h"
#include "Screens/MenuScreen/TutorEasing.h"
#include "Levels/Scroller/ScrollerLevelA.h"
//
#include <SDL_opengl.h>
#include <GL\GLU.h>
//
//#include <build/cmake/include/debug.h>

namespace humbug {

	using namespace gui;
	using namespace gui::controls;
	using namespace gui::components;
	using namespace humbug::screens;
	using humbug::levels::TestLevel;
	using humbug::levels::LevelA;

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
    //fl(new FileLoader("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data")),
    m_uiLastTicks(0),
    /*m_pTileSet(NULL),*/
    m_uiLastTicks2(0),
    m_uiNumFrames(0)
{
    //dbgOut(__FUNCTION__ << std::endl);
//	_CRT_DEBUG_BLOCK
}

//destructor
CTestEventHandler::~CTestEventHandler(){
    LOGSTREAM << "Killing the ~CTestEventHandler";

    //if(m_pHud) {
    //    delete m_pHud;
    //}
    //delete CControl::GetMainControl();
    //delete m_pMainCanvas;
    dbgOut(__FUNCTION__);
	//std::cout << "Killing the ~CTestEventHandler " << __FUNCTION__ << std::endl;

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
    delete gui::controls::CControl::GetMainControl();
    delete m_pBlue;

    //delete m_pTileSet;
    fl.reset();

	// FileLoader frees the surface of m_pBackground,
	// so this is a workaround.
	//m_pBackground->SetSurface(NULL);
	delete m_pBackground;
	
	//destroy font
    //TTF_CloseFont( CButton::GetButtonFont() );
    //shut down font system
    TTF_Quit();
    CEventHandler::OnExit();
} // OnExit

CText *fickText;

//initialization
bool CTestEventHandler::OnInit(int argc, char* argv[]){
    //initialize parent class
    CEventHandler::OnInit(argc, argv);


    Uint32 video_flags;

    //video_flags = SDL_OPENGL;
    //video_flags = SDL_ANYFORMAT | SDL_FULLSCREEN;
    //video_flags = SDL_ANYFORMAT;
    //video_flags = SDL_WINDOW_BORDERLESS;
    //video_flags = SDL_WINDOW_SHOWN;
    video_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    //video_flags = SDL_HWSURFACE|SDL_DOUBLEBUF| SDL_FULLSCREEN;
    //SDL_EnableKeyRepeat(100, 1);
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL/2);
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY/10, SDL_DEFAULT_REPEAT_INTERVAL/3);
    //construct main canvas
    //m_pMainCanvas = new CMainCanvas(1024, 768, 0, video_flags);
    CMainCanvas* m_pMainCanvas = new CMainCanvas("Humbug, the Game", 1024, 768, video_flags);
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
    //fl.reset(new FileLoader("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data"));
	//fl.reset(new FileLoader("E:/Projects/C++/Humbug/build/Humbug/src/Debug/base_data"));

	std::string appDir = AppGB::Instance().AppDir();
	fl.reset(new HumbugFileLoader(appDir + "base_data"));
    //return true;
    //FileLoader fl2("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");
    try
    {
        //load in button font. Todo: Error Checking
        //TTF_OpenFont(
          //  "D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/arial.ttf", 15)
        TTF_Font *arial = fl->FL_LOADFONT("Fonts/ARIAL.TTF", 15);
        CButton::SetButtonFont( arial );

        //m_pBackground->FillRect(m_pBackground->GetDimension(), CColor::LightRed());
        //m_pHud = new Hud(*fl, mainControl, new HudBackground(*fl, "Hud/footer.png"), 0);

        //create a button
        //new CButton(m_pHud, CRectangle(100, 100, 150, 25), 1, "Come on, Press me!");

        //new CButton(CControl::GetMainControl(),CRectangle(100,100,50,25),1,"Test");
        // m_pBackground = m_pMainCanvas->CreateRGBCompatible(NULL, 1024, 768- m_pHud->GetHeight());
        {

			
			/*// Todo: make a copy, or painting to the súrface is like writíng on Moo.png.
			m_pBackground = new CCanvas( fl->FL_LOADIMG("Moo.png") );
			m_pBackground->Invalidate();
			CRectangle screenrect = m_pMainCanvas->GetDimension();
			m_pMainCanvas->Blit(screenrect, *m_pBackground, screenrect);
			//m_pMainCanvas->Invalidate();*/


			SDL_Surface* loadsurf;
			SDL_Surface* tmpsurf;
            
			// delete loadsurf;
			//m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024 * 5, 768 - 320);
            //tmpsurf = (loadsurf = fl->FL_LOADIMG("Moo.png"));
            tmpsurf = loadsurf = fl->FL_LOADIMG("Moo.png");
            CCanvas tmpCanvas(tmpsurf);
            //CCanvas* testCanvas = CCanvas::CreateRGBCompatible(NULL, 1024 * 5, 768 - 320);
			CCanvas* testCanvas = CCanvas::CreateRGBCompatible(NULL, 1024 * 5, 768);
            testCanvas->Blit( tmpCanvas.GetDimension(), tmpCanvas, tmpCanvas.GetDimension() );
            m_pBackground = testCanvas;
			CRectangle screenrect = m_pMainCanvas->GetDimension();
            m_pMainCanvas->Blit(screenrect, *m_pBackground, screenrect);
            //m_pMainCanvas->Render(m_pBackground, screenrect, screenrect);

			//m_pBackground->Invalidate();
            //delete tmpsurf;
            //SDL_FreeSurface( loadsurf );
            fl->FreeLast();

            int fontsize = 48;
			CPoint sp(120, 140);
			TTF_Font *iarial = fl->FL_LOADFONT("Fonts/ARIAL.TTF", fontsize);

			const char *lines[] = { 
                //"Press '1' for: StartScreen",
                "Press '1' for: current devel Screen",
				"Press '2' for: Highscores",
                //"Press '3' for: TestLevel",
                "Press '3' for: ScrollerLevelA",
				"Press '4' for: BlaScreen",
				"Press '5' for: TileScreen",
				"Press '6' for: LuaScreen",
				"Press '7' for: HopperScreen",
				"Press '8' for: LevelA",
                "Press '9' for: SimpleScreen",
                "Press '0' for: MenuScreen"
            };

            for (int i = 0; i < sizeof(lines) / sizeof(const char *); i++)
			{
				const char *cur = lines[i];
				CText infoText(iarial, cur, CColor::Black());
				infoText.Put(m_pMainCanvas, screenrect + sp.Offset(0, ( i * (fontsize + 10))));
			}

			/*std::ostringstream outstring;
			outstring << "Press '1' for: StartScreen";
			CText infoText(iarial, outstring.str(), CColor::Red());
			infoText.Put(m_pMainCanvas, screenrect + sp);

			outstring.str(std::string());
			outstring << "Press '2' for: TestScreen";
			CText infoText2(iarial, outstring.str(), CColor::Red());
			infoText2.Put(m_pMainCanvas, screenrect + sp.Offset(0, ( 1 * (fontsize + 10))));*/
			//infoText2.Put(m_pMainCanvas, screenrect + CPoint(100, 200));
			//SDL_FreeSurface( tmpsurf );
        }

        //m_pBackground = new CCanvas( ( tmpsurf ));
        //m_pBackground = m_pMainCanvas->CreateRGBCompatible(NULL, 1024, 768);
        //SDL_Surface* g_pBitmapSurface = fl.LoadImg("icons/blue.png");
        //SDL_Surface* g_pBitmapSurface = (fl->FL_LOADIMG("icons/blue.png"));
        SDL_Surface* g_pBitmapSurface = (fl->FL_LOADIMG("icons/blue.png"));
        fl->FreeLast();

        //SDL_FreeSurface( loadsurf );
        m_pBlue = new CImage( new CCanvas( g_pBitmapSurface ), true );

		//SDL_Surface* ddd1 = fl2.LoadImg("Icons/blue.png");
        //m_pHud = new Hud(fl, mainControl, new HudBackground(fl, "humbug.pdb"), 0);

        // fl->Free("Tiles1.bmp");
        m_pMainCanvas->MainUpdateAndRenderCopy();
    }
    catch (FileLoaderException ex)
    {
        LOGSTREAM << ex.what();

        //m_imp_ptr.reset();
    }
    m_pDrawCanvas = m_pBackground;

	//m_pBlue = new CCanvas( m_pLoader.LoadImg("blue.png") );
    //SDL_Surface* ddd =
    // IMG_Load("D:/E/Projects/C++/Humbug/projects/Humbug/Artwork/Clipboard01.png");
    //m_pBlue = new CImage( new CCanvas( ddd ) );
    //m_pBlue = new CImage( new CCanvas( ddd ) );
    // m_pHud = new Hud(fl, m_pMainCanvas);
    //m_pHud->Draw();
    //SDL_Flip( m_pMainCanvas->GetSurface( ) );   //Refresh the screen
    //success

    // Maybe we do not need the backing variables, since a Hookable is destroyed individually
    //m_Hooks = new Hookable(this);


    //new TestHookable();
    //new TestHookable();
    //m_scrStart = new StartScreen(*fl, m_pMainCanvas);
    //HookMgr()->AddHookable("StartScreen", m_scrStart, true);
    //HookMgr()->EnableHookable("StartScreen");
    //HookMgr()->AddHookable("TestScreen", new TestHookable());

    //Hookable *nn = HookCreator<StartScreen>::Create();
    //Hookable *nn = HookCreator<StartScreen>::Create();
    //StartScreenCreator<StartScreen> eee(*fl, m_pMainCanvas);
    //Hookable *nn = ScreenCreator<StartScreen>(*fl, m_pMainCanvas).Create();

    //boost::shared_ptr<HookCreator> nn(new ScreenCreator<StartScreen>(*fl, m_pMainCanvas));
    //HookMgr()->RegisterHookable("XXXX", nn);
    
    //HookMgr()->RegisterHookable("Test2", HookCreatorPtr(new DefaultHookCreator<TestHookable>()));
    //HookMgr()->RegisterHookable("StartScreen", HookCreatorPtr(new ScreenCreator<StartScreen>(*fl, m_pMainCanvas)));
    HookMgr()->RegisterHookable("StartScreen", HookCreatorPtr(new ScreenCreator<ZoomInScreen2>(*fl, m_pMainCanvas)));
	HookMgr()->RegisterHookable("TestScreen", HookCreatorPtr(new ScreenCreator<TestScreen>(*fl, m_pMainCanvas)));
    //HookMgr()->RegisterHookable("TestLevel", HookCreatorPtr(new ScreenCreator<TestLevel>(*fl, m_pMainCanvas)));
    HookMgr()->RegisterHookable("TestLevel", HookCreatorPtr(new ScreenCreator<levels::ScrollerLevelA>(*fl, m_pMainCanvas)));
    HookMgr()->RegisterHookable("Highscores", HookCreatorPtr(new ScreenCreator<HighscoreScreen>(*fl, m_pMainCanvas)));
    //HookMgr()->RegisterHookable("Highscores", HookCreatorPtr(new ScreenCreator < SubmenuA> (*fl, m_pMainCanvas)));
	HookMgr()->RegisterHookable("Bla", HookCreatorPtr(new ScreenCreator<BlaScreen>(*fl, m_pMainCanvas)));
	HookMgr()->RegisterHookable("Tiles", HookCreatorPtr(new ScreenCreator<TileScreen>(*fl, m_pMainCanvas)));
	HookMgr()->RegisterHookable("Lua", HookCreatorPtr(new ScreenCreator<LuaScreen>(*fl, m_pMainCanvas)));
	HookMgr()->RegisterHookable("Hopper", HookCreatorPtr(new ScreenCreator<HopperScreen>(*fl, m_pMainCanvas)));
    HookMgr()->RegisterHookable("LevelA", HookCreatorPtr(new ScreenCreator<LevelA>(*fl, m_pMainCanvas)));
    HookMgr()->RegisterHookable("Simple", HookCreatorPtr(new ScreenCreator<SimpleScreen>(*fl, m_pMainCanvas)));
    HookMgr()->RegisterHookable("Menu", HookCreatorPtr(new ScreenCreator<MenuScreen>(*fl, m_pMainCanvas)));
    //HookMgr()->EnableHookable("StartScreen");
	//HookMgr()->EnableHookable("TestScreen");
    //std::vector<boost::shared_ptr<HookCreator>> xx;
    //xx.push_back(nn);
    //std::map<std::string, boost::shared_ptr<HookCreator>> xx;
    //xx.insert(std::make_pair("XXXX", nn));

    //new TestHookable();
    //new TestHookable();

    m_pConsole =
        new gui::CConsole( this, fl->FL_LOADIMG("Fonts/ConsoleFont.bmp"),
                m_pMainCanvas, 100, CRectangle(0, 0, 0,
                        300) );

    //int *failmemcheck = new int(666);
    return(true);
} // OnInit

void CTestEventHandler::PutBlue(){
    //if(m_pHud /*!= NULL && m_pHud->HasMouseHover()*/) {
	//
    //}
} // PutBlue

//idle behavior - Draw the stuff
void CTestEventHandler::OnIdle(int ticks){
    //CApplication::OnIdle(ticks); 
	//return;


    CMainCanvas* m_pMainCanvas = GetMainCanvas();
    //m_pMainCanvas->Lock();

//    glColor3f(1, 1, 1);
//    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//    oglplus::Context::Clear().ColorBuffer().DepthBuffer();
    m_pMainCanvas->MainRenderClear();

	//CRectangle screenrect = m_pMainCanvas->GetDimension();
	//m_pMainCanvas->Blit(screenrect, *m_pBackground, screenrect);
	//m_pMainCanvas->Invalidate();

    //update controls
    //CRectangle screenrect = m_pMainCanvas->GetDimension();
	//m_pMainCanvas->Blit(screenrect, *m_pBackground, screenrect);
	//m_pMainCanvas->Invalidate();
	//m_pBackground->Blit(screenrect, m_pMainCanvas, screenrect);
    //m_pBackground->UpdateRects();
    //CRectangle& screenWithoutHud = m_pBackground->GetDimension().Intersect(
    // m_pHud->GetCanvas()->GetDimension());
    //CRectangle& screenWithoutHud = m_pBackground->GetDimension().Union(
    // m_pHud->GetCanvas()->GetDimension());
    CRectangle screenWithoutHud( 0, 0,
            m_pMainCanvas->GetDimension().GetW(), m_pMainCanvas->GetDimension().GetH() -
            //m_pHud->GetCanvas()->GetDimension().GetH() );
	200 );

    //m_pHud->Invalidate();
//    CControl::Redraw();

    //m_pHud->Draw();
    //PutBlue();
    //for (int i = 0; i < 50 ; i++)

    //m_pConsole->Draw();

    //m_pHud->Draw();
    //m_pMainCanvas->Flip();
    // kucken fuer was 'screenrect' gebraucht wird und ob das stimmt.
    //m_pMainCanvas->ClearUpdateRects();

    //fickText->Put(m_pMainCanvas, CRectangle(ticks % 200, ticks % 200, 0, 0));
    //fickText->RenderPut(m_pMainCanvas, CRectangle(ticks % 200, ticks % 200, 0, 0));
    //m_pMainCanvas->MainUpdateAndRenderCopy();

    //m_pMainCanvas->UpdateRects ( );
    //m_pMainCanvas->Render(m_pDrawCanvas, m_pMainCanvas->GetDimension(), m_pMainCanvas->GetDimension());
	//m_pMainCanvas->Invalidate();
    // call base method.





    //Render flag
    bool gRenderQuad = true;




    //Clear color buffer
    //glClear(GL_COLOR_BUFFER_BIT);

    float mod = (ticks % 60) / 60.0f;

    /*
    //Render quad
    if (gRenderQuad)
    {
        glBegin(GL_QUADS);
        glVertex2f(-0.5f*mod, -0.5f);
        glVertex2f(0.5f, -0.5f*mod);
        glVertex2f(0.5f*mod, 0.5f);
        glVertex2f(-0.5f, 0.5f*mod);
        glEnd();
    }*/

    //m_pMainCanvas->MainUpdateAndRenderCopy();
    //m_pMainCanvas->SwapWindow();

    //SDL_GL_SwapWindow(gWindow);

    // calls RaiseOnIdle, RaiseOnDraw, m_pMainCanvas->UpdateRects and m_pMainCanvas->MainRenderFinal 
    CApplication::OnIdle(ticks);

    m_pMainCanvas->MainRenderFinal();

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
void CTestEventHandler::OnKeyDown(SDL_Keycode sym, Uint16 mod){
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
    /*else if( sym == SDLK_F1 )   {
        //
        m_inActiveSprite ^= 1;
    }*/
    //else if (mod == KMOD_LCTRL && sym == SDLK_BACKQUOTE)   {
    else if (sym == SDLK_CARET)   {
        // toggle console
        m_pConsole->Toggle();
    }
    else if( sym == SDLK_c )   {
        //send clear screen message
        SendMessageQ(MSGID_ClearScreen);
    }
    else if( sym == SDLK_1 )   {
        //
        //HookMgr()->Test1();
        //HookMgr()->DisableHookable("StartScreen");
        HookMgr()->EnableHookable("StartScreen");
    }
    else if( sym == SDLK_2 )   {
        //
        //HookMgr()->Test2();
        //HookMgr()->EnableHookable("TestScreen");
        HookMgr()->EnableHookable("Highscores");
    }
    else if( sym == SDLK_3 )   {
        //
        HookMgr()->EnableHookable("TestLevel");
    }
	else if( sym == SDLK_4 )   {
		//
		HookMgr()->EnableHookable("Bla");
	}
	else if( sym == SDLK_5 )   {
		//
		HookMgr()->EnableHookable("Tiles");
	}
	else if( sym == SDLK_6 )   {
		// 
		HookMgr()->EnableHookable("Lua");
	}
	else if( sym == SDLK_7 )   {
		//
		HookMgr()->EnableHookable("Hopper");
	}
	else if( sym == SDLK_8 )   {
		//
		HookMgr()->EnableHookable("LevelA");
	}
    else if (sym == SDLK_9)   {
        //
        HookMgr()->EnableHookable("Simple");
    }
    else if (sym == SDLK_0)   {
        //
        HookMgr()->EnableHookable("Menu");
    }
    else if (sym == SDLK_F1)   {
        //
        m_pMainCanvas->ToggleOpenGL();
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
        /*if(m_pHud) {
            //m_pHud->Close();
            //m_pHud = NULL;
        }*/

        m_pMainCanvas->Clear( CColor(0, 0, 0) );

        /*if(m_pHud) {
            m_pHud->Invalidate();
            m_pHud->Draw();
        }*/

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
            CRectangle frect( (Sint16)(long)Parm1, (Sint16)(long)Parm2, 1, 1 );
            
            //m_pMainCanvas->FillRect(frect, CColor::Red());
            //m_pDrawCanvas->AddUpdateRect(frect);
            m_pBlue->Put( m_pDrawCanvas, CPoint( (Sint16)(long)Parm1, (Sint16)(long)Parm2 ) );

            for (int i = 0; i < 50; i++) {
                m_pMainCanvas->AddUpdateRect( CRectangle( (Sint16)(long)Parm1, (Sint16)(long)Parm2,
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

}
