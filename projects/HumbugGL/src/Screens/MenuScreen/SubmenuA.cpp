/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SubmenuA.cpp class.
 * \file       SubmenuA.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "SubmenuA.h"
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
//
//#include <build/cmake/include/debug.h>

using namespace gui::components;
using namespace gui;

namespace humbug {
struct SubmenuA::SubmenuAImpl {
    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    int x;
};

SubmenuA::SubmenuA( FileLoader& loader, CCanvas* background) :
    pimpl_(new SubmenuA::SubmenuAImpl ),
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

SubmenuA::~SubmenuA(void){
    //delete m_pScrollText;
    //delete m_pScroller;
    //delete m_pBackground;
    //delete m_pSprWormler;
    //delete m_pSprEye;
    dbgOut(__FUNCTION__ << " " << this);
}

/*GroupId SubmenuA::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/
bool SubmenuA::OnInit( int argc, char* argv[] ){
    // Master()->GetMainCanvas();
    //CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

    TTF_Font* m_pArialfont;
    m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
    mcol = CColor::White();
    
    SDL_Surface* tmpfsurf = ( m_Loader.FL_LOADIMG("Intro/MenuScreen/SubmenuABg.png") );
    m_pBackground.reset( new CCanvas( tmpfsurf ) );
    m_Loader.FreeLast();

    CColor m_colText = CColor::Black();
    std::ostringstream outstring;
    outstring << "Bla fasel:" << gui::CApplication::ShownFrames();
    outstring << " ";

    outstring <<
        "Error error C2248: 'boost::noncopyable_::noncopyable::noncopyable' : cannot access private member "
              <<
        "declared in class " <<
        "'boost::noncopyable_::noncopyable'" << "\t" <<
        "d:/e/projects/c++/humbug/projects/humbug/src/gui/visual/Hookable.h" <<
        "\t" << "48" << "\t" << "HumbugGL" << "\r\n" <<
        "\r\n" <<
        "Error" << "\t" << "3" << "\t" <<
        "error C2248: 'boost::scoped_ptr<T>::scoped_ptr' : cannot access private member declared in "
              <<
        "class " <<
        "'boost::scoped_ptr<T>'" << "\t" <<
        "d:/e/projects/c++/humbug/projects/humbug/src/gui/visual/Hookable.h" << "\t" << "48" << "\t" <<
        "HumbugGL" << "\r\n" <<
        "";

    m_pScrollText.reset( new CText(m_pArialfont, outstring.str(), m_colText) );
    m_pScroller.reset(new CTextScroller(m_pBackground.get(), *m_pScrollText, CPoint(100, 600), 800));

    return Screen::OnInit(argc, argv);

    //return true;
}   // OnInit

void SubmenuA::OnIdle(int ticks){
    m_pScroller->Scroll(4);
}

void SubmenuA::OnDraw(){
    static int coldelta = 0;

    m_pBackground->RenderCopy();
    SDL_Color* wavemap = ColorData::Instance()->Wavemap();
    int index = (coldelta * 2 & 63);

    SDL_Color& fcol = wavemap[index];
    CColor color = CColor(fcol.r, fcol.g, fcol.b);
    CRectangle frect(60, 180, 80, 80);
    m_pBackground->RenderFillRect( frect, &color );

    CRectangle dstDims( 0, 0, 200, 200);
    m_pScroller->Render();

    coldelta++;

    if (coldelta > 64) {
        coldelta = 0;
    }

    //m_pMainCanvas->Unlock();
}   // OnDraw

void SubmenuA::OnUpdate(){
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR( rand() );
    mcol.SetG( rand() );
    mcol.SetB( rand() );
    //m_iUpdateTimes++;
}
}
