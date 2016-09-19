/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the KeyboardHandler.cpp class.
 * \folder     $(folder)
 * \file       KeyboardHandler.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"

//
#include "KeyboardHandler.h"

//#include <build/cmake/include/debug.h>
namespace gui {
/** KeyboardHandler, HandleKeyboardEvent:
 *  Run this continuosly in the event loop to update the keyboard map.
 *  @param event The event data provided by SDL.
 */
void KeyboardHandler::HandleKeyboardEvent(SDL_Event* event){
    if (event->type != SDL_KEYDOWN && event->type != SDL_KEYUP) {
        return;
    }

    // the state of the key; SDL_PRESSED or SDL_RELEASED
    keyState[event->key.keysym.sym] = event->key.state;
}
}
