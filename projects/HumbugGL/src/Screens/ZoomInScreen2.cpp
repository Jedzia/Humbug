/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ZoomInScreen2.cpp class.
 * \file       ZoomInScreen2.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "ZoomInScreen2.h"
//
#include "../GUI/DebugOverlay.h"
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
#include <GuiLib/Filesystem/FileLoader.h>
#include <GuiLib/GUI/Components/EasingFunctors.h>
#include <GuiLib/GUI/Components/Image.h>
#include <GuiLib/GUI/Components/Rectangle.h>
#include <GuiLib/GUI/Components/Text.h>
#include <GuiLib/GUI/Components/TextAnimatorImpl.h>
#include <GuiLib/GUI/Components/TextScroller.h>
#include <GuiLib/GUI/Controls/Control.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Sprite/Sprite.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/GUI/Visual/EventHandler.h>
#include <cstdlib>
#include <GuiLib/Animation.h>
//
//#include <build/cmake/include/debug.h>

using namespace gui::components;
using namespace gui;

namespace humbug {

struct ZoomInScreen2::ZoomInScreen2Impl {
    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    ZoomInScreen2* m_host;
    int x;
    boost::scoped_ptr<CImage> m_pZoomingImage;
    Timing timing;
    boost::shared_ptr<AnimatedRectangle> animRect1;

    ZoomInScreen2Impl(ZoomInScreen2* host)
        : m_host(host), x(0), timing{host} {
        // *** initialize Animated Rectangle ***
        animRect1 = boost::make_shared<AnimatedRectangle>(
                CRectangle(50, 50, 50, 50), // starting shape
                CRectangle(400, 400, 300, 300), // final shape
                host, 2.0f, EaseOutBounce(2));
    }

    void draw(CCanvas* canvas, SDL_Color& fcol) {
        CRectangle screenrect = canvas->GetDimension();
        CPoint sp(220, 340);
        CColor textColor(fcol.r, fcol.g, fcol.b);
        CRectangle rect = screenrect + sp.Offset(fcol.r, 1 * (x + 10) + fcol.g);

        // *** Range mapper test ***

        //static EaseOutBounce ease;
        //static EaseOutQuart ease;
        static EaseOutElastic ease(2);
         
        float t1 = timing.RangeMappedSinceStart(0, screenrect.GetH(), 3.25f, boost::ref(ease));
        int zoomSize = t1;
        //int zoomSize = x * 16;
        CRectangle growRect(screenrect.GetW() / 2 - zoomSize / 2, screenrect.GetH() / 2 - zoomSize / 2, zoomSize, zoomSize);
        CPoint pt_dst = CPoint(50 + x, 50 + x);
        m_pZoomingImage->RenderPut(canvas, growRect);

        //canvas->RenderDrawRect(*animRect1, &textColor);

        x++;
    } // draw
};

ZoomInScreen2::ZoomInScreen2(FileLoader& loader, CCanvas* background) :
    pimpl_(new ZoomInScreen2Impl(this)),
    Screen(background),
    m_Loader(loader)
{
    dbgOut(__FUNCTION__ << " " << this);
}

ZoomInScreen2::~ZoomInScreen2(void) {
    dbgOut(__FUNCTION__ << " " << this);
}

bool ZoomInScreen2::OnInit(int argc, char* argv[]) {
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

    // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
    mcol = CColor::White();
    SDL_Surface* tmpfsurf = (m_Loader.FL_LOADIMG("Intro/TestScreenBg.png"));

    m_pBackground.reset(new CCanvas(tmpfsurf));

    m_Loader.FreeLast();

    pimpl_->m_pZoomingImage.reset(new CImage(new CCanvas(m_Loader.FL_LOADIMG("Images/Strange01.png")), true));

    CColor m_colText = CColor::White();
    std::ostringstream outstring;
    outstring << "Bla fasel:" << CApplication::ShownFrames();
    outstring << " ";

    return Screen::OnInit(argc, argv);

    //return true;
}   // OnInit

void ZoomInScreen2::OnIdle(int ticks) {
}

void ZoomInScreen2::OnDraw() {
    static int coldelta = 0;

    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    m_pMainCanvas->Lock();

    m_pBackground->RenderCopy();
    //CRectangle frect(700, 500, 185, 185);
    SDL_Color* wavemap = ColorData::Instance()->Wavemap();
    int index = (coldelta * 2 & 63);

    SDL_Color& fcol = wavemap[index];
    //CColor color = CColor(fcol.r, fcol.g, fcol.b);
    //m_pMainCanvas->RenderFillRect(frect, &color);

    CRectangle dstDims(0, 0, 200, 200);

    pimpl_->draw(m_pBackground.get(), fcol);

    coldelta++;

    if(coldelta > 64) {
        coldelta = 0;
    }

    //controls::CControl::Redraw();
    m_pMainCanvas->Unlock();
}   // OnDraw

void ZoomInScreen2::OnUpdate() {
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR(rand());
    mcol.SetG(rand());
    mcol.SetB(rand());
    //m_iUpdateTimes++;
}

void ZoomInScreen2::OnKeyDown(SDL_Keycode sym, Uint16) {
    switch(sym) {
    case SDLK_SPACE:
    {
        pimpl_->x = 0;
        pimpl_->timing.Reset();
        break;
    }
    case SDLK_a:
    {
        pimpl_->animRect1->Reset();
        break;
    }
    default:
        break;
    }     // switch
} // ZoomInScreen2::OnKeyDown
}
