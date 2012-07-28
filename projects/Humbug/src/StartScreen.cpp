#include "stdafx.h"
#include "StartScreen.h"

//#include <build/cmake/include/debug.h>
#include "boost/lambda/lambda.hpp"
#include "boost/function.hpp"
//
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Components/Text.h"
#include "GUI/Components/TextScroller.h"
#include "GUI/Data/ColorData.h"
#include "GUI/Sprite/Sprite.h"
#include "GUI/Sprite/SpriteManager.h"
#include "GUI/Visual/EventHandler.h"
#include <cstdlib>
StartScreen::StartScreen( FileLoader& loader, CCanvas* background) :
    Screen(background),
    m_Loader(loader),
    m_pArialfont(NULL),
    m_iUpdateTimes(0),
    m_pScrollText(NULL),
    m_pScroller(NULL),
    m_pSprMgr(new CSpriteManager),
    m_pSprEye(NULL),
    m_pSprWormler(NULL){
    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

StartScreen::~StartScreen(void){
    if (m_pArialfont) {
        TTF_CloseFont(m_pArialfont);
    }

    delete m_pScrollText;
    delete m_pScroller;
    delete m_pBackground;
    //delete m_pSprWormler;
    //delete m_pSprEye;
    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

const char * StartScreen::language(int x) const {
    return "AsciiDoc";
}
void Fresse(int x)
{

}

class EyeMover {
public:
    EyeMover() {}

    void operator()(CSprite* sprite, int frameNumber) {
        sprite->SetPos(CPoint(100 + ((frameNumber % 128) * 6), 460));
        sprite->SprOffset(frameNumber % 8);
    }

};


/*GroupId StartScreen::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/
bool StartScreen::OnInit( int argc, char* argv[] ){
    // Master()->GetMainCanvas();
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
    m_pArialfont = TTF_OpenFont("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/arial.ttf", 30);
    mcol = CColor::White();
    SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( m_Loader.LoadImg("Intro/Intro.png") );

    //SDL_SetColorKey(tmpfsurf, SDL_SRCCOLORKEY, 0xff00ff);
    //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_SRCCOLORKEY, 0xff00ff);
    //SDL_SetAlpha(tmpfsurf, SDL_SRCALPHA, 0);
    //SDL_SetAlpha(m_pMainCanvas->GetSurface(), SDL_SRCALPHA, 128);
    m_pBackground = new CCanvas( tmpfsurf );

    //CCanvas tmpCanvas( tmpfsurf );
    m_Loader.FreeLast();

    //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    //m_pBackground->Blit(m_pBackground->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    m_pMainCanvas->AddUpdateRect( m_pBackground->GetDimension() );

    //"\r\n"
    CColor m_colText = CColor::White();
    std::ostringstream outstring;
    outstring << "Bla fasel:" << CApplication::ShownFrames();
    outstring << " ";

    //std::string pstr;
    outstring <<
    "Error error C2248: 'boost::noncopyable_::noncopyable::noncopyable' : cannot access private member "
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

    //m_pScrollText.reset(new CCanvas(TTF_RenderText_Solid(m_pArialfont, outstring.str().c_str(),
    // m_colText)));
    //m_pScrollText = new CCanvas(TTF_RenderText_Solid(m_pArialfont, outstring.str().c_str(),
    // m_colText));
    m_pScrollText = new CText(m_pArialfont, outstring.str(), m_colText);
    m_pScroller = new CTextScroller(m_pMainCanvas, *m_pScrollText, CPoint(100, 600), 800);
	
	// ### Sprites ###
    //m_pSprEye.reset( new CSprite( m_Loader, "Sprites/eye.png", m_pMainCanvas,
    //    CRectangle(0, 0, 64, 64), CPoint(64, 0) ));
    m_pSprEye = new CSprite( m_Loader, "Sprites/eye.png", m_pMainCanvas,
        CRectangle(0, 0, 64, 64), CPoint(64, 0) );
    EyeMover k1;
    boost::function<void(CSprite*, int)> f3=
        k1;

    //f3(m_pSprEye, frameNumber);

    m_pSprMgr->AddSprite(m_pSprEye, k1);
    
    
    
    //m_pSprWormler.reset( new CSprite( m_Loader, "Sprites/wormtiles.png", m_pMainCanvas,
    //    CRectangle(0, 0, 256, 64), CPoint(0, 64) ));
    m_pSprWormler = new CSprite( m_Loader, "Sprites/wormtiles.png", m_pMainCanvas,
        CRectangle(0, 0, 256, 64), CPoint(0, 64) );
    m_pSprWormler->SetColorAndAlpha(0xff00ff, 128);
    m_pSprMgr->AddSprite(m_pSprWormler);

    using namespace boost::lambda;

    boost::function<void(int,int,int)> f=
        std::cout << boost::lambda::_1 << "*" << boost::lambda::_2 << "+" << boost::lambda::_3
        << "=" <<boost::lambda::_1*boost::lambda::_2+boost::lambda::_3 << "\n";

    boost::function<void(int)> f2=
        std::cout << boost::lambda::_1 << "\n";


   // boost::function<void(int)> f3=
     //   (m_pSprEye->SetPos(CPoint(100 + ((boost::lambda::_1 % 128) * 6), 460)));
    //boost::function<void(int)> f3=
    //    (m_pSprEye->SprOffset(boost::lambda::_1));
    //boost::function<void(CSprite&)> f3=
    //    bind(&CSprite::SprOffset, boost::lambda::_1, 4);

    //boost::function<void(int)> f3=
    //    boost::bind(&Fresse, boost::lambda::_1);

    //f(1,2,3);
    //f2(5);
    //int *test = new int(5);
    return Screen::OnInit(argc, argv);

    //return true;
} // OnInit

void StartScreen::OnIdle(int frameNumber){
    //x+= std::random()*5;
    //static int frameNumber = 0;
    m_pScroller->Scroll(4);

    //m_pSprEye->SetPos(CPoint(100 + ((frameNumber % 128) * 6), 460));
    //m_pSprEye->SprOffset(frameNumber % 8);
    int kack = frameNumber % 4;
    //boost::function<void(int)> f3=
    //    boost::bind(&CSprite::SprOffset,m_pSprEye, boost::lambda::_1 %= boost::lambda::constant(8) );
    //boost::function<void(int)> f3=
    //    boost::lambda::constant(boost::bind(&CSprite::SprOffset,m_pSprEye, (boost::lambda::_1 %= boost::lambda::constant(8)) ));
    //boost::function<void(int)> f3=
    //    boost::lambda::var(boost::bind(&CSprite::SprOffset,m_pSprEye, ( boost::lambda::_1 % boost::lambda::constant(8)) ));
    //int fm = 8;
    //boost::function<void(int)> f3=
    //    boost::bind(&CSprite::SprOffset,m_pSprEye, (boost::lambda::_1 % fm)(frameNumber));
    
    //f3(frameNumber);


    //m_pSprWormler->SetPos(CPoint(100 + ((frameNumber % 128) * 6), 420));
	//m_pSprWormler->SprOffset(frameNumber % 40);
    //frameNumber++;

    m_pSprMgr->OnIdle(frameNumber);
}

void StartScreen::OnDraw(){
    static int xdelta = 0;
    static int xdelta1 = 0;
    static int coldelta = 0;
    static std::string subtext("A");
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    m_pMainCanvas->Lock();
    m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension() );
    CRectangle frect(400, 300, 85, 85);
    SDL_Color* wavemap = ColorData::Instance()->Wavemap();
    int index = (coldelta * 2 & 63);

    //m_pMainCanvas->FillRect( frect, mcol );
    SDL_Color& fcol = wavemap[index];
    m_pMainCanvas->FillRect( frect, CColor(fcol.r, fcol.g, fcol.b) );
    m_pMainCanvas->AddUpdateRect(frect);

    //mcol.SetR(x);
    //mcol.SetG(x/2);
    //mcol.SetB(x);
    //CCanvas* background = CCanvas::CreateRGBCompatible(NULL, 1024 * 5, 768 - 320);
    int textwidth = 800;
    int textheigth = m_pScrollText->GetCanvas()->GetHeight();
    int textposX = 100;
    int textposY = 600;

    //int fontheigth = TTF_FontHeight(m_pArialfont);
    CColor m_colText = CColor::White();
    CColor m_colText2 = CColor::LightYellow();
    CColor m_colTextBg = CColor::Green();
    int xx = xdelta1 % 0xff;
    Uint32 col = 0x0000ff * xx + 0x00ff00 * xx + 0xff0000 * xx;
    double msin = sin( ( (double)xdelta1 - 600 ) / 50 ) + 0.5;

    //SDL_se
    //SDL_SetColorKey(m_pcnvText.GetSurface(), SDL_SRCCOLORKEY, col);
    //SDL_SetColorKey(m_pcnvText.GetSurface(), SDL_SRCCOLORKEY, 0x7F007F );
    //SDL_SetAlpha(m_pcnvText.GetSurface(), SDL_SRCALPHA, 0x3F- xdelta);
    //SDL_SetAlpha(m_pcnvText.GetSurface(), SDL_SRCALPHA, 0xfF * msin);
    //CRectangle textDims(m_pScrollText->GetDimension());
    //CRectangle textDims(xdelta1-xdelta,0, xdelta,textheigth);
    //CRectangle showline(0,textposY,1024,textheigth);
    //CRectangle dstRect( textposX,textposY, textwidth ,textheigth);
    //CRectangle dstDims( textposX + textwidth - xdelta,textposY, xdelta,textheigth);
    //textDims.SetW(500);
    //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), m_pcnvText, m_pcnvText.GetDimension());
    CPoint fpstextloc(150 + xdelta1, 600);

    //static CRectangle oldtextloc(dstDims);
    //m_pMainCanvas->Blit(dstDims , *m_pScrollText, textDims );
    //m_pMainCanvas->AddUpdateRect(textDims + CRectangle(0,0,0,0) + oldfpstextloc);
    //m_pMainCanvas->AddUpdateRect(textDims + CRectangle(0,0,0,0) + fpstextloc);
    //CRectangle updaRect(dstDims);
    //updaRect.SetW(m_pMainCanvas->GetWidth());
    //m_pMainCanvas->AddUpdateRect(dstDims);
    //m_pMainCanvas->AddUpdateRect(showline);
    xdelta1 += 4;

    if (xdelta1 >= 555) {
        xdelta1 = 0;
    }

    xdelta = xdelta1;

    if (xdelta > textwidth) {
        //xdelta1 +=2;
        xdelta = textwidth;
    }

    coldelta++;

    if (coldelta > 64) {
        coldelta = 0;
    }

    if (xdelta % 6 == 0) {
        //subtext += "B";
    }

    //oldtextloc = dstDims;
    m_iUpdateTimes = 0;

    //m_pScroller->Scroll(6);
    m_pScroller->Draw();
    //m_pSprEye->Draw();
    //m_pSprWormler->Draw();
    m_pSprMgr->OnDraw();

    m_pMainCanvas->Unlock();
} // OnDraw

void StartScreen::OnUpdate(){
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR( rand() );
    mcol.SetG( rand() );
    mcol.SetB( rand() );
    m_iUpdateTimes++;
}

