/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the MenuScreen.cpp class.
 * \file       MenuScreen.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "MenuScreen.h"
//
#include "../GUI/DebugOverlay.h"
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
#include "MenuScreen/SubmenuA.h"
//
//#include <build/cmake/include/debug.h>

using namespace gui::components;
using namespace gui;

namespace humbug {
struct MenuScreen::MenuScreenImpl {
    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    int x;
};

    gui::components::CMainCanvas* MenuScreen::GetMainCanvas() const
    {
        return Master()->GetMainCanvas();
    }

    MenuScreen::MenuScreen( FileLoader& loader, CCanvas* background) :
    pimpl_(new MenuScreenImpl ),
    Screen(background),
    m_Loader(loader),
    //m_iUpdateTimes(0),
    m_pScrollText(NULL),
    m_pScroller(NULL),
    m_HookMgr(new HookableManager(this)),
    //m_HookMgr(new HookableManager(NULL)),
    m_pSprMgr(new CSpriteManager){
    dbgOut(__FUNCTION__ << " " << this);
}

MenuScreen::~MenuScreen(void){
    m_pLineMenu->disconnect(m_connection);
    dbgOut(__FUNCTION__ << " " << this);
}

bool MenuScreen::OnInit( int argc, char* argv[] ){
    m_pLineMenu.reset(new LineMenu(m_Loader, NULL, 1, "MenuScreen", Master()->GetMainCanvas()->GetDimension(), CRectangle(100, 100, 100, 100)));
    //m_pLineMenu.reset(new LineMenu(m_Loader, NULL, 1, "MenuScreen", CRectangle(0, 0, 200, 100)));
    label1 = m_pLineMenu->AddTextLabel();
    label2 = m_pLineMenu->AddTextLabel();
    label3 = m_pLineMenu->AddTextLabel();
    label4 = m_pLineMenu->AddTextLabel();

    m_connection = m_pLineMenu->connect(boost::bind(&MenuScreen::MenuSelectionChanged, this, _1));

    TTF_Font* m_pArialfont;
    m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
    mcol = CColor::White();
    
    SDL_Surface* tmpfsurf = ( m_Loader.FL_LOADIMG("Intro/MenuScreenBg.png") );
    m_pBackground.reset( new CCanvas( tmpfsurf ) );
    m_Loader.FreeLast();

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

    m_pScrollText.reset( new CText(m_pArialfont, outstring.str(), m_colText) );

    HookMgr()->RegisterHookable("6000", HookCreatorPtr(new ScreenCreator < SubmenuA>(m_Loader, m_pBackground.get())));


    return Screen::OnInit(argc, argv);

    //return true;
}   // OnInit

void MenuScreen::OnIdle(int ticks){
    m_pLineMenu->IdleSetVars(ticks);
    //m_pScroller->Scroll(4);
    //m_pSprMgr->OnIdle(ticks);
}

void MenuScreen::OnDraw(){
    if (HookMgr()->IsHookActive())
    {
        RaiseOnDraw();
        return;
    }

    static int coldelta = 0;

    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    m_pMainCanvas->Lock();

    m_pBackground->RenderCopy();
    CRectangle frect(700, 500, 185, 185);
    SDL_Color* wavemap = ColorData::Instance()->Wavemap();
    int index = (coldelta * 2 & 63);

    SDL_Color& fcol = wavemap[index];
    CColor color = CColor(fcol.r, fcol.g, fcol.b);
    m_pMainCanvas->RenderFillRect( frect, &color );

    CRectangle dstDims( 0, 0, 200, 200);
    //m_pScrollText->RenderPut(m_pBackground.get(), dstDims, dstDims );
    //m_pMainCanvas->AddUpdateRect(dstDims);

    coldelta++;

    if (coldelta > 64) {
        coldelta = 0;
    }

    m_pLineMenu->Draw();
    m_pMainCanvas->Unlock();

}   // OnDraw

void MenuScreen::OnUpdate(){
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR( rand() );
    mcol.SetG( rand() );
    mcol.SetB( rand() );
    //m_iUpdateTimes++;
}

void MenuScreen::OnEvent(SDL_Event* pEvent)
{
    m_pLineMenu->HookEventloop(pEvent);
}

void MenuScreen::MenuSelectionChanged(int selectedLabel) const
{
    if (selectedLabel == -1)
    {
        HookMgr()->DisableHookable();
    }
    else if (selectedLabel == 6000)
    {
        HookMgr()->EnableHookable("6000");
    }
    else if (selectedLabel == 6000)
    {
        HookMgr()->EnableHookable("6001");
    }

    dbgOut(__FUNCTION__ << "SelectedLabel: " << selectedLabel << " (" << this << ").");
}
}
