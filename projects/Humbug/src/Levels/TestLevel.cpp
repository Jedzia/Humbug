#include "stdafx.h"
#include "TestLevel.h"

//#include <build/cmake/include/debug.h>
#include <cstdlib>
#include "boost/lambda/lambda.hpp"
#include "boost/function.hpp"
//
#include "../Filesystem/FileLoader.h"
#include "../GUI/Components/Image.h"
#include "../GUI/Components/Rectangle.h"
#include "../GUI/Components/Text.h"
#include "../GUI/Components/TextScroller.h"
#include "../GUI/Data/ColorData.h"
#include "../GUI/Sprite/Sprite.h"
#include "../GUI/Sprite/SpriteManager.h"
#include "../GUI/Visual/EventHandler.h"

struct TestLevel::TestLevelImpl {
    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    int x;
};

TestLevel::TestLevel( FileLoader& loader, CCanvas* background) :
 pimpl_(new TestLevel::TestLevelImpl ),
    Screen(background),
    m_Loader(loader),
    m_pArialfont(NULL),
    //m_iUpdateTimes(0),
    m_pScrollText(NULL),
    m_pScroller(NULL),
    m_pSprMgr(new CSpriteManager)
    //,m_pSprEye(NULL),
    //m_pSprWormler(NULL)
    {
    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

TestLevel::~TestLevel(void){
    //if (m_pArialfont) {
    //    TTF_CloseFont(m_pArialfont);
    //}

    //delete m_pScrollText;
    //delete m_pScroller;
    //delete m_pBackground;
    //delete m_pSprWormler;
    //delete m_pSprEye;
    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

/*GroupId TestLevel::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/



bool TestLevel::OnInit( int argc, char* argv[] ){
    // Master()->GetMainCanvas();
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
    // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
    //m_pArialfont = TTF_OpenFont("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/arial.ttf", 30);
	m_pArialfont = m_Loader.LoadFont("Fonts/ARIAL.TTF", 30);
    mcol = CColor::White();
    SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( m_Loader.LoadImg("Intro/TestScreenBg.png") );

    //SDL_SetColorKey(tmpfsurf, SDL_SRCCOLORKEY, 0xff00ff);
    //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_SRCCOLORKEY, 0xff00ff);
    //SDL_SetAlpha(tmpfsurf, SDL_SRCALPHA, 0);
    //SDL_SetAlpha(m_pMainCanvas->GetSurface(), SDL_SRCALPHA, 128);
    m_pBackground.reset(new CCanvas( tmpfsurf ));

    //CCanvas tmpCanvas( tmpfsurf );
    m_Loader.FreeLast();

	//m_pSprite = new CSprite(m_Loader, "Sprites/kmail.png", m_pBackground.get()/*, CRectangle(0,0,64,64)*/);
	m_pSprite = new CSprite(m_Loader, "Images/Sky01.png", m_pBackground.get()/*, CRectangle(0,0,64,64)*/);

	//m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    //m_pBackground->Blit(m_pBackground->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    m_pMainCanvas->AddUpdateRect( m_pBackground->GetDimension() );

    //"\r\n"
    CColor m_colText = CColor::White();
    std::ostringstream outstring;
	outstring << "Bla fasel:" << gui::CApplication::ShownFrames();
    outstring << " ";

    //std::string pstr;
    outstring <<
    "The Test Level! \n"
              <<
    "declared in class " <<
    "'boost::noncopyable_::noncopyable'" << "\t" <<
    "d:/e/projects/c++/humbug/projects/humbug/src/gui/visual/Hookable.h" <<
    "\t" << "48" << "\t" << "Humbug" << "\r\n" <<
    "\r\n" <<
    "Error" << "\t" << "3" << "\t" <<
    "error C2248: 'boost::scoped_ptr<T>::scoped_ptr' : cannot access private member declared in "
            <<
    "class " <<
    "'boost::scoped_ptr<T>'" << "\t" <<
    "d:/e/projects/c++/humbug/projects/humbug/src/gui/visual/Hookable.h" << "\t" << "48" << "\t" <<
    "Humbug" << "\r\n" <<
    "";

    m_pScrollText.reset(new CText(m_pArialfont, outstring.str(), m_colText));


    return Screen::OnInit(argc, argv);

    //return true;
} // OnInit

void TestLevel::OnIdle(int frameNumber){
    //m_pScroller->Scroll(4);
    //m_pSprMgr->OnIdle(frameNumber);
}

void TestLevel::OnDraw(){
    static int coldelta = 0;

    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    m_pMainCanvas->Lock();

    m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension() );
    CRectangle frect(700, 500, 185, 185);
    SDL_Color* wavemap = ColorData::Instance()->Wavemap();
    int index = (coldelta * 2 & 63);
	
	static CPoint sp(0,0);
	m_pSprite->SetPos(sp);
	m_pSprite->Draw();
	sp.Subtract(CPoint(6,0));

	//m_pMainCanvas->AddUpdateRect( m_pSprite->SprImage()->SrcRect() );
	m_pMainCanvas->AddUpdateRect( m_pMainCanvas->GetDimension() );

    //m_pMainCanvas->FillRect( frect, mcol );
    SDL_Color& fcol = wavemap[index];
    m_pMainCanvas->FillRect( frect, CColor(fcol.r, fcol.g, fcol.b) );
    m_pMainCanvas->AddUpdateRect(frect);

    CRectangle dstDims( 0, 0, 600, 200);
    m_pScrollText->Put(m_pBackground.get(),dstDims, dstDims );
    m_pMainCanvas->AddUpdateRect(dstDims);

    coldelta++;

    if (coldelta > 64) {
        coldelta = 0;
    }


    m_pMainCanvas->Unlock();
} // OnDraw

void TestLevel::OnUpdate(){
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR( rand() );
    mcol.SetG( rand() );
    mcol.SetB( rand() );
    //m_iUpdateTimes++;
}

