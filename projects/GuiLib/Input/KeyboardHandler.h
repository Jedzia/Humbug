/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the KeyboardHandler.h class.
 * \folder     $(folder)
 * \file       KeyboardHandler.h
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef __HUMBUG_GUI_KEYBOARDHANDLER_H
#define __HUMBUG_GUI_KEYBOARDHANDLER_H
#include "SDL.h"

namespace gui {
/** @class KeyboardHandler:
 *  Helper to detect if multiple keys are pressed down.
 */
class KeyboardHandler {
public:

    /** KeyboardHandler, HandleKeyboardEvent:
     *  Run this continuosly in the event loop to update the keyboard map.
     *  @param event The event data provided by SDL.
     */
    void HandleKeyboardEvent(SDL_Event* event);

    /** KeyboardHandler, IsPressed:
     *  Determines if the given key is pressed down.
     *  @param keyCode The key to check.
     * @return True if the specified key in @paramref keyCode was pressed.
     */
    bool IsPressed(SDL_Keycode keyCode) {
        return (keyState[keyCode] == SDL_PRESSED);
    }
    /** KeyboardHandler, IsReleased:
     *  Determines if the given key is in released state.
     *  @param keyCode The key to check.
     * @return True if the specified key in @paramref keyCode is not pressed down.
     */
    bool IsReleased(SDL_Keycode keyCode) {
        return (keyState[keyCode] == SDL_RELEASED);
    }
private:

    //int keyState[200];
    std::map<int, int> keyState;
};
}
#endif // __HUMBUG_GUI_KEYBOARDHANDLER_H guard
