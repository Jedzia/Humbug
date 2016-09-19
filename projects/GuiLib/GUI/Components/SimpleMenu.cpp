/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SimpleMenu.cpp class.
 * \folder     $(folder)
 * \file       SimpleMenu.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../stdafx.h"
#include "SimpleMenu.h"

namespace gui {
namespace components {
CSimpleMenu::CSimpleMenu(const char* title, int width, int height, Uint32 flags)
    : CCanvas( SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
                    height, flags) ) {
    SDL_Delay ( 10 );
}

CSimpleMenu::~CSimpleMenu() {
    // SDL_FreeSurface ( GetSurface ( ) );
    //SetWindow ( NULL );
}
}   // namespace components
} // namespace gui
