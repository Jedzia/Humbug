/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ZoomInScreen.cpp class.
 * \file       ZoomInScreen.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "ZoomInScreen.h"
//
#include "../GUI/DebugOverlay.h"
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
#include <GuiLib/Filesystem/FileLoader.h>
#include <GuiLib/GUI/Components/Image.h>
#include <GuiLib/GUI/Components/Rectangle.h>
#include <GuiLib/GUI/Components/Text.h>
#include <GuiLib/GUI/Components/TextScroller.h>
#include <GuiLib/GUI/Controls/Control.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Sprite/Sprite.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/GUI/Visual/EventHandler.h>
#include <cstdlib>
#include <GuiLib/GUI/Components/EasingFunctors.h>
#include <GuiLib/GUI/Components/TextAnimatorImpl.h>
//
//#include <build/cmake/include/debug.h>

using namespace gui::components;
using namespace gui;

namespace humbug {
    
    class AnimatedRectangle
    {
        CRectangle m_recStart;
        CRectangle m_recEnd;
        Timing m_Timing;
        vdouble m_duration;
        TimeEasingFunc m_easingFunc;

    public:
        AnimatedRectangle(const CRectangle& recStart, const CRectangle& recEnd, const Hookable* updater, vdouble duration, TimeEasingFunc easingfunc = NULL)
            : m_recStart{recStart},
              m_recEnd{recEnd},
              m_Timing(updater), m_duration(duration), m_easingFunc(easingfunc)
        {
        }

        void Reset() { m_Timing.Reset(); }

        // conversion
        operator CRectangle()
        {
            //static EaseNone ease;
            float x = m_Timing.RangeMappedSinceStart(m_recStart.GetX(), m_recEnd.GetX(), m_duration, m_easingFunc);
            float y = m_Timing.RangeMappedSinceStart(m_recStart.GetY(), m_recEnd.GetY(), m_duration, m_easingFunc);
            float w = m_Timing.RangeMappedSinceStart(m_recStart.GetW(), m_recEnd.GetW(), m_duration, m_easingFunc);
            float h = m_Timing.RangeMappedSinceStart(m_recStart.GetH(), m_recEnd.GetH(), m_duration, m_easingFunc);
            //float h = m_Timing.RangeMappedSinceStart(m_recStart.GetH(), m_recEnd.GetH(), m_duration, boost::ref(ease));
            return CRectangle(x, y, w, h);
        };

    private:

    };

struct ZoomInScreen::ZoomInScreenImpl {
    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    ZoomInScreen* m_host;
    int x;
    boost::scoped_ptr<gui::components::CImage> m_pZoomingImage;
    Timing timing;
    AnimatedRectangle animRect;
    boost::shared_ptr<AnimatedRectangle> animRect1;

    ZoomInScreenImpl(ZoomInScreen* host)
        : m_host(host), x(0), timing{ host }, animRect(CRectangle(50, 50, 50, 50), CRectangle(400, 400, 300, 300), m_host, 2.0f, EaseInOutElastic(2))
    {
        animRect1 = boost::make_shared<AnimatedRectangle>(CRectangle(50, 50, 50, 50), CRectangle(400, 400, 300, 300), m_host, 2.0f, EaseInOutElastic(2));
    }

    void draw(CCanvas* canvas, SDL_Color& fcol) {
        CRectangle screenrect = canvas->GetDimension();
        CPoint sp(220, 340);
        CColor textColor(fcol.r, fcol.g, fcol.b);
        CRectangle rect = screenrect + sp.Offset(fcol.r, 1 * (x + 10) + fcol.g);

        //static EaseOutBounce ease;
        //static EaseOutQuart ease;
        static EaseOutElastic ease(2);

        //float t1 = timing.RangeMappedSinceStart(0, 120, 0, 2.0f, 0, 120, boost::ref(ease));
        //float t1 = timing.RangeMappedSinceStart(0, screenrect.GetH(), 0, 2.0f, 0, screenrect.GetH() * 2, boost::ref(ease));
        float t1 = timing.RangeMappedSinceStart(0, screenrect.GetH(), 3.25f, boost::ref(ease));
        int zoomSize = t1;
        //int zoomSize = x * 16;
        CRectangle growRect(screenrect.GetW() / 2 - zoomSize / 2, screenrect.GetH() / 2 - zoomSize / 2, zoomSize, zoomSize);
        //CPoint c_point = m_pKeyHandler->Char();
        CPoint pt_dst = CPoint(50 + x, 50 + x);
        //m_pZoomingImage->RenderPut(canvas, pt_dst);
        m_pZoomingImage->RenderPut(canvas, growRect);

        // CRectangle rect2(screenrect.GetW() / 2 - zoomSize / 2, screenrect.GetH() / 2 - zoomSize / 2, zoomSize, zoomSize);
        const int drawSize = 200;
        CRectangle rect2(screenrect.GetW() / 2 - drawSize / 2, screenrect.GetH() / 2 - drawSize / 2, drawSize, drawSize);
        //AnimatedRectangle animRect(CRectangle(100, 100, 10, 10), rect2, m_host);
        //static EaseNone easeAnim;
        //static AnimatedRectangle animRect(CRectangle(50, 50, 50, 50), CRectangle(400, 400, 300, 300), m_host, 2.0f, boost::ref(easeAnim));
        //static AnimatedRectangle animRect(CRectangle(50, 50, 50, 50), CRectangle(400, 400, 300, 300), m_host, 2.0f, EaseInOutElastic(2));
        canvas->RenderDrawRect(animRect, &textColor);




        x++;
    }
};

ZoomInScreen::ZoomInScreen(FileLoader& loader, CCanvas* background) :
    pimpl_(new ZoomInScreen::ZoomInScreenImpl(this)),
    Screen(background),
    m_Loader(loader),
    //m_iUpdateTimes(0),
    m_pScrollText(NULL),
    m_pScroller(NULL),
    m_pSprMgr(new CSpriteManager) {
    //,m_pSprEye(NULL),
    //m_pSprWormler(NULL)
    dbgOut(__FUNCTION__ << " " << this);
}

ZoomInScreen::~ZoomInScreen(void) {
    //delete m_pScrollText;
    //delete m_pScroller;
    //delete m_pBackground;
    //delete m_pSprWormler;
    //delete m_pSprEye;
    dbgOut(__FUNCTION__ << " " << this);
}

/*GroupId ZoomInScreen::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/
bool ZoomInScreen::OnInit(int argc, char* argv[]) {
    // Master()->GetMainCanvas();
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    //m_pOverlay.reset(new DebugOverlay(m_Loader, controls::CControl::GetMainControl(), 1,
    // "ZoomInScreen"));
    m_pOverlay.reset(new DebugOverlay(m_Loader, NULL, 1, "ZoomInScreen"));

    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
    // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
    TTF_Font* m_pArialfont;
    m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
    mcol = CColor::White();
    SDL_Surface* tmpfsurf = (m_Loader.FL_LOADIMG("Intro/TestScreenBg.png"));

    //SDL_SetColorKey(tmpfsurf, SDL_SRCCOLORKEY, 0xff00ff);
    //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_SRCCOLORKEY, 0xff00ff);
    //SDL_SetAlpha(tmpfsurf, SDL_SRCALPHA, 0);
    //SDL_SetAlpha(m_pMainCanvas->GetSurface(), SDL_SRCALPHA, 128);
    m_pBackground.reset(new CCanvas(tmpfsurf));

    //CCanvas tmpCanvas( tmpfsurf );
    m_Loader.FreeLast();

    pimpl_->m_pZoomingImage.reset(new CImage(new CCanvas(m_Loader.FL_LOADIMG("Images/Strange01.png")), true));

    //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    //m_pBackground->Blit(m_pBackground->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    //m_pMainCanvas->AddUpdateRect( m_pBackground->GetDimension() );

    //"\r\n"
    CColor m_colText = CColor::White();
    std::ostringstream outstring;
    outstring << "Bla fasel:" << gui::CApplication::ShownFrames();
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

    m_pScrollText.reset(new CText(m_pArialfont, outstring.str(), m_colText));
    m_pScroller.reset(new CTextScroller(m_pBackground.get(), *m_pScrollText, CPoint(100, 600), 800));

    return Screen::OnInit(argc, argv);

    //return true;
}   // OnInit

void ZoomInScreen::OnIdle(int ticks) {
    m_pOverlay->IdleSetVars(ticks);
    //m_pScroller->Scroll(4);
    //m_pSprMgr->OnIdle(ticks);
}

void ZoomInScreen::OnDraw() {
    static int coldelta = 0;

    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    m_pMainCanvas->Lock();

    //m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pBackground,
    // m_pBackground->GetDimension() );
    m_pBackground->RenderCopy();
    CRectangle frect(700, 500, 185, 185);
    SDL_Color* wavemap = ColorData::Instance()->Wavemap();
    int index = (coldelta * 2 & 63);

    //m_pMainCanvas->FillRect( frect, mcol );
    SDL_Color& fcol = wavemap[index];
    CColor color = CColor(fcol.r, fcol.g, fcol.b);
    m_pMainCanvas->RenderFillRect(frect, &color);
    //m_pMainCanvas->AddUpdateRect(frect);

    CRectangle dstDims(0, 0, 200, 200);
    //m_pScrollText->RenderPut(m_pBackground.get(), dstDims, dstDims );
    //m_pMainCanvas->AddUpdateRect(dstDims);
    m_pScroller->Render();

    pimpl_->draw(m_pBackground.get(), fcol);

    coldelta++;

    if(coldelta > 64) {
        coldelta = 0;
    }

    //controls::CControl::Redraw();
    m_pOverlay->Draw();
    m_pMainCanvas->Unlock();
}   // OnDraw

void ZoomInScreen::OnUpdate() {
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR(rand());
    mcol.SetG(rand());
    mcol.SetB(rand());
    //m_iUpdateTimes++;
}

void ZoomInScreen::OnKeyDown(SDL_Keycode sym, Uint16) {
    switch(sym) {
    case SDLK_SPACE:
    {
        pimpl_->x = 0;
        pimpl_->timing.Reset();
        break;
    }
    case SDLK_a:
    {
        pimpl_->animRect.Reset();
        break;
    }
    default:
        break;
    }     // switch
}
}
