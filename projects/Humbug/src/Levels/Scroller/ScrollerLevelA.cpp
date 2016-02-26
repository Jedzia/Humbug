/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ScrollerLevelA.cpp class.
 * \folder     $(folder)
 * \file       ScrollerLevelA.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "ScrollerLevelA.h"
#include "stdafx.h"
//
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
#include <boost/foreach.hpp>
#include <cstdlib>
//
#include "PlayerShip.h"
#include "EnemyWave.h"
#include "GUI/DebugOverlay.h"
//#include "HumbugShared/GameObjects/Player.h"
#include <GUI/Components/Rectangle.h>
#include <GuiLib/Filesystem/FileLoader.h>
#include <GuiLib/GUI/Components/CanvasRendererImpl.h>
#include <GuiLib/GUI/Components/CoordSystem.h>
#include <GuiLib/GUI/Components/EasingFunctors.h>
#include <GuiLib/GUI/Components/Image.h>
#include <GuiLib/GUI/Components/SeamlessImage.h>
#include <GuiLib/GUI/Components/Shapes/Line.h>
#include <GuiLib/GUI/Components/Text.h>
#include <GuiLib/GUI/Components/TextScroller.h>
//#include <GuiLib/GUI/Controls/Button.h>
#include <GuiLib/GUI/Controls/Label.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Sprite/Sprite.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/GUI/Visual/EventHandler.h>
//#include <GuiLib/Timing.h>
//
//#include <build/cmake/include/debug.h>

namespace humbug {
namespace levels {
using namespace gui::components;
using namespace gui;
using namespace scroller_levela;

#include "ScrollerLevelATestStuff.h"
#include "MoverStuff.h"

/*GroupId ScrollerLevelA::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/

//using controls::CControl;

//gui::controls::CButton* testbutton;



struct ScrollerLevelA::ScrollerLevelAImpl {
private:

    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    int x;
    ScrollerLevelA* host;

public:

    boost::shared_ptr<hspriv::LaserMover> updfunc2;
    boost::shared_ptr<hspriv::SaucerMover> updfunc3;
    boost::shared_ptr<PlayerShip> m_pPlayerShip;
    boost::shared_ptr<EnemyWave> m_pEnemyWave;

    explicit ScrollerLevelAImpl(ScrollerLevelA* host)
        : x(0), host{host}
    {}

    void Draw() const {
        auto aaaa = host->m_pBackground->GetDimension();
    }
};

ScrollerLevelA::ScrollerLevelA(FileLoader& loader, CCanvas* background) :
    Screen(background, true),
    pimpl_(new ScrollerLevelAImpl(this)),
    m_Loader(loader),
    m_pArialfont(NULL),
    m_pScrollText(NULL),
    m_pScroller(NULL),
    m_pSprMgr(new CSpriteManager),
    m_pSeamlessImage(NULL){
    dbgOut(__FUNCTION__ << " " << this);
}

ScrollerLevelA::~ScrollerLevelA(void) {
    delete m_pSeamlessImage;
    dbgOut(__FUNCTION__ << " " << this);
}

/** $(class), OnInit:
 *  Detailed description.
 *  @param argc TODO
 * @param argv TODO
 * @return TODO
 */
bool ScrollerLevelA::OnInit(int argc, char* argv[]) {
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    mcol = CColor::White();
    m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 30);
    /*if (!controls::CLabel::GetLabelFont())
       {
       controls::CLabel::SetLabelFont(m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 16));
       }*/

    m_pOverlay.reset(new DebugOverlay(m_Loader, NULL, 1, "ScrollerLevelA"));
    m_pOverlay->AddTextLabel();
    m_pOverlay->AddTextLabel();
    m_pOverlay->AddTextLabel();
    m_pOverlay->AddTextLabel();
    m_pOverlay->AddTextLabel();

    SDL_Surface* tmpfsurf = (m_Loader.FL_LOADIMG("Intro/TestScreenBg.png"));
    m_pBackground.reset(new CCanvas(tmpfsurf));

    m_Loader.FreeLast();

    SDL_Surface* g_pBitmapSurface = (m_Loader.FL_LOADIMG("Images/SeamlessB.png"));
    m_pSeamlessImage = new CSeamlessImage(new CCanvas(g_pBitmapSurface), true);
    m_Loader.FreeLast();
    m_pSeamlessImage->SetLoader(&m_Loader);

    // m_pBlue = new CImage(new CCanvas(fl.FL_LOADIMG("icons/blue.png")), true);
    m_pBlue.reset(new CCanvas(m_Loader.FL_LOADIMG("icons/blue.png")));

    m_pBanding1.reset(new CImage(new CCanvas(m_Loader.FL_LOADIMG("Text/ColorBandedTextWhite01.png")), true));
    m_pBanding1->Scale(0.6f);
    CanvasStripeRendererA stripeModifier(m_Loader, 16, m_pArialfont, m_pOverlay.get());
    m_pBanding1->GetCanvas()->AddModifier(stripeModifier);

    m_pBanding2.reset(new CImage(new CCanvas(m_Loader.FL_LOADIMG("Text/ColorBandedTextWhite01.png")), true));
    m_pBanding2->GetCanvas()->AddModifier(stripeModifier);
    FadeInOutRenderer fadeRenderer(this, 3.0f, FadeInOutRenderer::FadeMode::FadeIn);
    m_pBanding2->GetCanvas()->AddModifier(fadeRenderer);

    CColor m_colText = CColor::White();
    std::ostringstream outstring;
    outstring << "Bla fasel:" << CApplication::ShownFrames();
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

    pimpl_->m_pPlayerShip = boost::make_shared<PlayerShip>(m_Loader, m_pMainCanvas, m_pSprMgr.get(), m_pOverlay.get(), 0.25f);
    pimpl_->m_pEnemyWave = boost::make_shared<EnemyWave>(m_Loader, m_pMainCanvas, m_pSprMgr.get(), m_pOverlay.get());

    /*CSprite* m_pSprLaser =
        new CSprite(m_Loader, "Sprites/Ship/Laser/Laser01.png", m_pMainCanvas, CPoint(49, 480));
       int offsetW = m_pMainCanvas->GetWidth() / 2 - m_pSprLaser->SprImage()->DstRect().GetW() / 2;
       pimpl_->updfunc2 = boost::make_shared<hspriv::LaserMover>(m_pBackground.get(), offsetW);
       pimpl_->updfunc2->SetDebugOverlay(m_pOverlay.get());
       m_pSprMgr->AddSprite(m_pSprLaser, "mytag", boost::ref(*pimpl_->updfunc2));*/

    CSprite* m_pSprSaucer = new CSprite(m_Loader, "Sprites/Ship/Saucer02.png", m_pMainCanvas, CPoint(256, 256));
    //m_pSprSaucer->SprImage()->Scale(0.5);
    int offsetW = m_pMainCanvas->GetWidth() / 2 - m_pSprSaucer->SprImage()->DstRect().GetW() / 2;
    offsetW += 300;
    pimpl_->updfunc3 = boost::make_shared<hspriv::SaucerMover>(m_pBackground.get(), offsetW, 90);
    pimpl_->updfunc3->SetDebugOverlay(m_pOverlay.get());
    m_pSprMgr->AddSprite(m_pSprSaucer, "Enemy1", boost::ref(*pimpl_->updfunc3), pimpl_->m_pEnemyWave.get());

    return Screen::OnInit(argc, argv);

    //return true;
}     // OnInit

/** $(class), OnIdle:
 *  Detailed description.
 *  @param ticks TODO
 * @return TODO
 */
void ScrollerLevelA::OnIdle(int ticks) {
    m_iTicks = ticks;
    m_pOverlay->IdleSetVars(ticks);
    //m_pKeyHandler->HookIdle(ticks, 1.0f);
    pimpl_->m_pEnemyWave->HookIdle(ticks, 1.0f);
    pimpl_->m_pPlayerShip->HookIdle(ticks, 1.0f);
    //m_pScroller->Scroll(4);
    m_pSprMgr->OnIdle(ticks);
}

/** $(class), OnDraw:
 *  Detailed description.
 *  @return TODO
 */
void ScrollerLevelA::OnDraw() {
    static int coldelta = 0;

    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    m_pMainCanvas->Lock();
    //m_pMainCanvas->MainRenderClear();

    // m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), *m_pBackground,
    // m_pBackground->GetDimension());
    m_pBackground->RenderCopy();
    CRectangle frect(700, 500, 185, 185);
    static SDL_Color* wavemap = ColorData::Instance()->Wavemap();
    int index = (coldelta * 2 & 63);

    //static CPoint sp(-480, 110);
    CPoint sp(0, m_iTicks);
    //m_pSprite->SetPosition(sp);
    //m_pSprite->Draw();
    //m_pSeamlessImage->RenderPut(m_pMainCanvas, sp);
    m_pSeamlessImage->RenderPut(m_pBackground.get(), sp);
    //m_pSeamlessImage->RenderPut(m_pBackground.get(), m_pKeyHandler->Char());

    /*if ( testbutton->IsPressed() ) {
        CPoint point(-3, 0);
        sp.Subtract(point);
       }
       else {
        CPoint point(3, 0);
        sp.Subtract(point);
       }*/

    //m_pMainCanvas->AddUpdateRect( m_pSprite->SprImage()->SrcRect() );
    //m_pMainCanvas->AddUpdateRect( m_pMainCanvas->GetDimension() );

    //m_pMainCanvas->FillRect( frect, mcol );
    SDL_Color& fcol = wavemap[index];
    CColor sdl_color = CColor(fcol.r, fcol.g, fcol.b, fcol.a);
    m_pMainCanvas->RenderFillRect(frect, &sdl_color);
    //m_pMainCanvas->AddUpdateRect(frect);

    //CColor hitTestRecColor = CColor::LightMagenta();
    //m_pMainCanvas->RenderDrawRect(hitTestRect, &hitTestRecColor);

    /*static int xxx = 0;
       CRectangle dstDims( 0 + xxx, 0 + xxx, 600, 200);
       CRectangle srcDims(0 + xxx, 0, 600, 200 - xxx);
       m_pScrollText->RenderPut(m_pMainCanvas, dstDims, srcDims );
       xxx++;

       if (xxx > 128) {
        xxx = 0;
       }*/

    //testbutton->Invalidate();
    //testbutton->Draw();

    m_pBlue->SetTextureColorMod(sdl_color);
    //m_pBlue->ClearColorKey();
    CRectangle sdl_rect = CRectangle(300, 300, 256, 256);
    //m_pBlue->RenderCopy(&sdl_rect, static_cast<CRectangle*>(nullptr));
//    m_pBlue->RenderCopy(&sdl_rect);
    //CPoint point = CPoint(300, 300);
    //m_pBlue->RenderCopy(point);

    /*CColor bannercolor(sdl_color);
       bannercolor.SetR(255 - coldelta);
       m_pBanding1->RenderPut( m_pMainCanvas, CPoint(40, 550) );
       m_pBanding2->RenderPut( m_pBackground.get(), CPoint(140, 250) );*/

    pimpl_->Draw();

    coldelta++;

    if(coldelta > 64) {
        coldelta = 0;
    }

    m_pOverlay->Draw();
    m_pOverlay->SetTextLabelText(6002, "Player Idle");
    m_pSprMgr->Render();
    //m_pSprMgr->OnDraw();
    m_pMainCanvas->Unlock();
}     // OnDraw

void ScrollerLevelA::OnUpdate() {
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR(rand());
    mcol.SetG(rand());
    mcol.SetB(rand());

    /*if (testbutton->IsPressed()) {
        m_pKeyHandler->Reset();
       }*/

    //m_iUpdateTimes++;
}

void ScrollerLevelA::OnEvent(SDL_Event* pEvent) {
    //m_pKeyHandler->HookEventloop(pEvent);
    pimpl_->m_pPlayerShip->HookEventloop(pEvent);

    Screen::OnEvent(pEvent);
}

void ScrollerLevelA::OnKeyDown(SDL_Keycode sym, Uint16) {
    switch(sym) {
    case SDLK_SPACE:
    {
        //pimpl_->x = 0;
        //pimpl_->timing.Reset();
        break;
    }
    case SDLK_KP_PLUS:
    {
        pimpl_->updfunc2->IncrementOffset();
        break;
    }
    case SDLK_KP_MINUS:
    {
        pimpl_->updfunc2->DecrementOffset();
        break;
    }
    default:
        break;
    }     // switch
} // ZoomInScreen::OnKeyDown
}
}
