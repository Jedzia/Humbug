/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the PlayerKeys.h class.
 * \folder     $(folder)
 * \file       PlayerKeys.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef PROJECT_PLAYERKEYS_H
#define PROJECT_PLAYERKEYS_H
#include "GUI\Components\Point.h"
#include "SDL.h"

// see http://content.gpwiki.org/index.php/SDL:Tutorials:Practical_Keyboard_Input
class PlayerKeys {
public:

    PlayerKeys(int x = 0, int y = 0);
    ~PlayerKeys();
    void HookEventloop(SDL_Event* pEvent);

    void HookKeyDown(SDLKey sym);

    void HookKeyUp(SDLKey sym);

    void HookIdle();

    CPoint Char() const { return CPoint(charx, chary); }

    int CharX() const { return charx; }

    void CharX(int val) { charx = val; }

    int CharY() const { return chary; }

    void CharY(int val) { chary = val; }

    friend std::ostream& operator<<(std::ostream& o, const PlayerKeys& r);

private:

    bool upup;             //Whether the up key is up.
    bool downup;           //Likewise for the down key.
    bool leftup;           //You get the drift.
    bool rightup;
    int charyvel;
    int charxvel;
    int done;
    int chary;
    int charx;
};
std::ostream& operator<<(std::ostream& o, const PlayerKeys& r);

#endif // PROJECT_PLAYERKEYS_H guard
