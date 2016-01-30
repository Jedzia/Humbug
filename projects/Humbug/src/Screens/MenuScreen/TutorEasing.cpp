/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TutorEasing.cpp class.
 * \file       TutorEasing.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "TutorEasing.h"
//
#include "../../GUI/DebugOverlay.h"
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
#include <GuiLib/Filesystem/FileLoader.h>
#include <GuiLib/GUI/Components/Rectangle.h>
#include <GuiLib/GUI/Components/Text.h>
#include <GuiLib/GUI/Components/TextScroller.h>
#include <GuiLib/GUI/Controls/Control.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Sprite/Sprite.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/GUI/Visual/EventHandler.h>
#include <cstdlib>
#include <GuiLib/GUI/Components/TextAnimatorImpl.h>
#include <GuiLib/GUI/Components/EasingFunctors.h>
//
//#include <build/cmake/include/debug.h>

using namespace gui::components;
using namespace gui;

namespace humbug {
struct TutorEasing::TutorEasingImpl {
    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    int x;
};

TutorEasing::TutorEasing( FileLoader& loader, CCanvas* background) :
    pimpl_(new TutorEasing::TutorEasingImpl ),
    Screen(background),
    m_Loader(loader),
    //m_iUpdateTimes(0),
    m_pScrollText(NULL),
    m_pScroller(NULL),
    m_pSprMgr(new CSpriteManager){
    //,m_pSprEye(NULL),
    //m_pSprWormler(NULL)
    dbgOut(__FUNCTION__ << " " << this);
}

TutorEasing::~TutorEasing(void){
    //delete m_pScrollText;
    //delete m_pScroller;
    //delete m_pBackground;
    //delete m_pSprWormler;
    //delete m_pSprEye;
    dbgOut(__FUNCTION__ << " " << this);
}

/*GroupId TutorEasing::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/
bool TutorEasing::OnInit( int argc, char* argv[] ){
    // Master()->GetMainCanvas();
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    //m_pOverlay.reset(new DebugOverlay(m_Loader, controls::CControl::GetMainControl(), 1,
    // "TutorEasing"));
    m_pOverlay.reset( new DebugOverlay(m_Loader, NULL, 1, "TutorEasing") );

    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
    // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
    TTF_Font* m_pArialfont;
    m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
    mcol = CColor::White();
    m_pBackground.reset(new CCanvas(m_Loader.FL_LOADIMG("Intro/MenuScreen/TutorA1Bg.png")));
    m_Loader.FreeLast();

    //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    //m_pBackground->Blit(m_pBackground->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    //m_pMainCanvas->AddUpdateRect( m_pBackground->GetDimension() );

    //"\r\n"
    CColor m_colText = CColor::Black();
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

    m_pScrollText.reset( new CText(m_pArialfont, outstring.str(), m_colText) );
    m_pScroller.reset(new CTextScroller(m_pBackground.get(), *m_pScrollText, CPoint(100, 600), 800));

    m_pEasingText.reset(new CText(m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24), "Ease In", CColor::DarkGreen(), CPoint(40, 400)));
    //m_pEasingText->MoveTo(CPoint(800, 400), this, 8.0f, 2, 2, EasingOperator::Func());
    
    //static EasingOperator eaop;
    //m_pEasingText->MoveTo(CPoint(800, 400), this, 8.0f, 2, 2, boost::ref(eaop));

    //m_pEasingText->MoveTo<EaseOutInQuad>(CPoint(800, 400), this, 8.0f, 2, 2, 2.0f);
    //m_pEasingText->MoveTo<EaseInOutElastic>(CPoint(800, 400), this, 4.0f, 2, 2, 8.0f, -4.0f);
    //m_pEasingText->MoveTo<EaseOutInElastic>(CPoint(800, 400), this, 4.0f, 2, 2, 4.0f, 2.0f);
    m_pEasingText->MoveTo<EaseInOutBounce>(CPoint(800, 400), this, 4.0f, 0.2, 4, 1.50f);

    return Screen::OnInit(argc, argv);

    //return true;
}   // OnInit

void TutorEasing::OnIdle(int ticks){
    m_pOverlay->IdleSetVars(ticks);
    m_pScroller->Scroll(4);
    //m_pSprMgr->OnIdle(ticks);
}

void TutorEasing::OnDraw(){
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
    m_pMainCanvas->RenderFillRect( frect, &color );
    //m_pMainCanvas->AddUpdateRect(frect);

    CRectangle dstDims( 0, 0, 200, 200);
    //m_pScrollText->RenderPut(m_pBackground.get(), dstDims, dstDims );
    //m_pMainCanvas->AddUpdateRect(dstDims);
    m_pScroller->Render();

    m_pEasingText->RenderPut(m_pBackground.get());

    coldelta++;

    if (coldelta > 64) {
        coldelta = 0;
    }

    //controls::CControl::Redraw();
    m_pOverlay->Draw();
    m_pMainCanvas->Unlock();
}   // OnDraw

void TutorEasing::OnUpdate(){
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR( rand() );
    mcol.SetG( rand() );
    mcol.SetB( rand() );
    //m_iUpdateTimes++;
}
}
