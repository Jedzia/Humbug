/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the MainCanvas.cpp class.
 * \folder     $(folder)
 * \file       MainCanvas.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../stdafx.h"
#include "MainCanvas.h"

namespace gui {
namespace components {
CMainCanvas::CMainCanvas(const char* title, int width, int height, Uint32 flags)
    : CCanvas( SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
                    height, flags) ) {
    SDL_Delay ( 10 );
}

CMainCanvas::~CMainCanvas() {
    // SDL_FreeSurface ( GetSurface ( ) );
    //SetWindow ( NULL );
    MainWindowClosing();
}

void CMainCanvas::SwapWindow()
{
    CanvasSwapWindow();
}
}   // namespace components
} // namespace gui
