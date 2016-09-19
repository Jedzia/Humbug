/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Screen.cpp class.
 * \folder     $(folder)
 * \file       Screen.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "GUI/Visual/Application.h"
#include "GUI/Visual/EventHandler.h"
#include "MainCanvas.h"
#include "Screen.h"
#include "boost/bind.hpp"
#include "boost/signals2.hpp"
//
//#include <build/cmake/include/debug.h>

namespace gui {
namespace components {
Screen::Screen(CCanvas* background, bool usesSDL2Render)
    : m_bUsesSDL2Render(usesSDL2Render), Hookable(true) { //, CMessageHandler()
    // , m_pMainScreen(mainScreen)
    dbgOut(__FUNCTION__ << " " << this);
}

Screen::~Screen(void) {
    dbgOut(__FUNCTION__ << " " << this);
}

/** $(class), GetGroupID:
 *  Detailed description.
 *  @return TODO
 */
GroupId Screen::GetGroupID() {
    static GroupId grpID = CreateNextGroupID();
    return grpID;

    //throw std::exception("The method or operation is not implemented.");
}

bool Screen::OnInit(int argc, char* argv[]) {
    //Screen *screen = static_cast<Screen *>(hook);
    bool result = Hookable::OnInit(argc, argv);
    //Master()->ConnectOnDraw(boost::bind(&Screen::OnDraw, boost::ref(*hook)));
    //Master()->ConnectOnDraw((const CApplication::slot_type_event&)boost::bind(&Screen::OnIdle,
    // boost::ref(*hook)));
    //Master()->ConnectOnDraw((const CApplication::slot_type_event&)boost::bind(&Screen::OnDraw,
    // boost::ref(*screen)));

    //m_conDraw = Master()->ConnectOnDraw(boost::bind(&Screen::OnDraw, boost::ref(*this)));
    //m_conUpdate = Master()->ConnectOnUpdate(boost::bind(&Screen::OnUpdate, boost::ref(*this)));
    return result;
}

/** $(class), OnUpdate:
 *  Detailed description.
 *  @return TODO
 */
void Screen::OnUpdate() {
    // Hookable::OnUpdate() runs SDL_UpdateTexture of the main texture with following
    // SDL_RenderCopy. Means GetSurface()->pixels to texture and then update render copy
    // later this should not need the surface any more
    if(!m_bUsesSDL2Render) {
        // render old SDL1 blit canvas stuff to the main window
        Master()->GetMainCanvas()->MainUpdateAndRenderCopy();
    }
}

/** $(class), OnIdle:
 *  Detailed description.
 *  @param ticks TODO
 * @return TODO
 */
void Screen::OnIdle(int ticks) {
    //throw std::exception("The method or operation is not implemented.");
}

/** $(class), OnEvent:
 *  Detailed description.
 *  @param pEvent TODO
 * @return TODO
 */
void Screen::OnEvent(SDL_Event* pEvent) {
    switch(pEvent->type)
    {
    case SDL_KEYDOWN:
        //key press
        OnKeyDown(pEvent->key.keysym.sym, pEvent->key.keysym.mod);
        break;
    default:
        break;
    }
}

//keyboard events
void Screen::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
    //do nothing
}

/** $(class), OnConnect:
 *  Detailed description.
 *  @return TODO
 */
void Screen::OnConnect() {
    //Hookable::Connect();
    m_conDraw = Master()->ConnectOnDraw(boost::bind(&Screen::OnDraw, boost::ref(*this)));
    m_conUpdate = Master()->ConnectOnUpdate(boost::bind(&Screen::OnUpdate, boost::ref(*this)));
    m_conEvt = Master()->ConnectOnEvent(boost::bind(&Screen::OnEvent, boost::ref(*this), _1));
    OnFocus();
}

/** $(class), OnDisconnect:
 *  Detailed description.
 *  @return TODO
 */
void Screen::OnDisconnect() {
    //Hookable::Disconnect();
    m_conDraw.disconnect();
    m_conUpdate.disconnect();
    m_conEvt.disconnect();
    OnLostFocus();
}

/*bool Screen::OnInit( int argc,char* argv[] )
   {
    return Hookable::OnInit(argc, argv);
    //throw std::exception("The method or operation is not implemented.");
    //return true;
   }*/
} // namespace components
} // namespace gui
