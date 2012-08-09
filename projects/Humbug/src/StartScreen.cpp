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

namespace prv
{
    class EyeMover {
        int h_;
        bool toggle_;
        int deltaY_;
        static int created;

    public:
        EyeMover(int deltaY = 0) : deltaY_(deltaY), h_(0), toggle_(false) 
        {
            dbgOut(__FUNCTION__ << " created:" << created << " (" << this << ")" << std::endl);
            //static int created = 0;
            created++;
        }

        ~EyeMover()
        {
            dbgOut(__FUNCTION__ << " " << this << std::endl);
        }

        void operator()(CSprite* sprite, int frameNumber) {
            double ss = std::sin(static_cast<double>(frameNumber) / 12);
            int ssin = static_cast<int>(ss * 155);

            sprite->SetPos(CPoint(100 + ((frameNumber % 128) * 6), 460 + h_ + deltaY_ + ssin));
            sprite->SprOffset(frameNumber % 8);

            if (h_ >= 100)
            {
                toggle_ = false;
            }
            else if (h_ <= 0)
            {
                toggle_ = true;
            }

            if (toggle_)
            {
                h_++;
            } 
            else
            {
                h_--;
            }
        }

    };

    int EyeMover::created = 0;

    class WormMover {
        int add_;
        static int created;
    public:
        WormMover() : add_(0) {
            dbgOut(__FUNCTION__ << " created:" << created << " (" << this << ")" << std::endl);
            created++;
        }
        ~WormMover()
        {
            dbgOut(__FUNCTION__ << " " << this << std::endl);
        }

        void operator()(CSprite* sprite, int frameNumber) {
            //sprite->SetPos(CPoint(100 + ((frameNumber % 32) * 16), 420));
            const int sprMaxFrames = 40;
            int frame = (frameNumber % sprMaxFrames);
            int div = (frameNumber % (sprMaxFrames*4)) / sprMaxFrames;
            //int movdelta = div * 40;
            int movdelta = 0;

            int deltaX = static_cast<int>( ((frameNumber % (sprMaxFrames*4))*4.3) );
            sprite->SetPos(CPoint(10 + deltaX + movdelta, 420));
            int sprframe;
            if (frame < (sprMaxFrames/2))
            {
                sprframe = frame;
            } 
            else
            {
                sprframe = sprMaxFrames - frame;
            }
            sprite->SprOffset(sprframe);
        }
    };

    int WormMover::created;



}


struct StartScreen::StartScreenImpl {
    prv::EyeMover eyemover;
    prv::WormMover wormmover;
};

StartScreen::StartScreen( FileLoader& loader, CCanvas* background) :
 pimpl_(new StartScreen::StartScreenImpl() ),
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

StartScreen::~StartScreen(void){
    if (m_pArialfont) {
        TTF_CloseFont(m_pArialfont);
    }

    //delete m_pScrollText;
    //delete m_pScroller;
    //delete m_pBackground;
    //delete m_pSprWormler;
    //delete m_pSprEye;
    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

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
    // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
    m_pArialfont = TTF_OpenFont("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/arial.ttf", 30);
    mcol = CColor::White();
    SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( m_Loader.LoadImg("Intro/Intro.png") );

    //SDL_SetColorKey(tmpfsurf, SDL_SRCCOLORKEY, 0xff00ff);
    //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_SRCCOLORKEY, 0xff00ff);
    //SDL_SetAlpha(tmpfsurf, SDL_SRCALPHA, 0);
    //SDL_SetAlpha(m_pMainCanvas->GetSurface(), SDL_SRCALPHA, 128);
    m_pBackground.reset(new CCanvas( tmpfsurf ));

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
    m_pScrollText.reset(new CText(m_pArialfont, outstring.str(), m_colText));
    m_pScroller.reset(new CTextScroller(m_pMainCanvas, *m_pScrollText, CPoint(100, 600), 800));
	
	// ### Sprites ###
    CSprite *m_pSprEye = new CSprite( m_Loader, "Sprites/eye.png", m_pMainCanvas,
        CRectangle(0, 0, 64, 64), CPoint(64, 0) );
    //EyeMover *eymover = new EyeMover;
    //prv::EyeMover eyemover;
    //m_pSprMgr->AddSprite(m_pSprEye, eyemover );
    m_pSprMgr->AddSprite(m_pSprEye, boost::ref( pimpl_->eyemover ) );

    /*CSprite *m_pSprEye2 = new CSprite( m_Loader, "Sprites/eye.png", m_pMainCanvas,
        CRectangle(0, 0, 64, 64), CPoint(64, 0) );
    EyeMover eymover2(55);
    m_pSprMgr->AddSprite(m_pSprEye2, eymover2 );*/

    CSprite *m_pSprWormler = new CSprite( m_Loader, "Sprites/wormtiles.png", m_pMainCanvas,
        CRectangle(0, 0, 256, 64), CPoint(0, 64) );
    //prv::WormMover wormmover;
    //WormMover *wormmover = new WormMover;
    m_pSprWormler->SetColorAndAlpha(0xff00ff, 128);
    m_pSprMgr->AddSprite(m_pSprWormler, boost::ref( pimpl_->wormmover ));


    return Screen::OnInit(argc, argv);

    //return true;
} // OnInit

void StartScreen::OnIdle(int frameNumber){
    m_pScroller->Scroll(4);
    m_pSprMgr->OnIdle(frameNumber);
}

void StartScreen::OnDraw(){
    static int coldelta = 0;

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

    coldelta++;

    if (coldelta > 64) {
        coldelta = 0;
    }

    m_pScroller->Draw();
    m_pSprMgr->OnDraw();

    m_pMainCanvas->Unlock();
} // OnDraw

void StartScreen::OnUpdate(){
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR( rand() );
    mcol.SetG( rand() );
    mcol.SetB( rand() );
    //m_iUpdateTimes++;
}

