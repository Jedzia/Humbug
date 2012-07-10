#include "stdafx.h"
#include "PlayerKeys.h"

//#include <build/cmake/include/debug.h>


PlayerKeys::PlayerKeys(/*SDL_Surface* screen*/)
: charxvel(0), charyvel(0), done(0)
{
         dbgOut(__FUNCTION__ << std::endl);
}

PlayerKeys::~PlayerKeys(void)
{
         dbgOut(__FUNCTION__ << std::endl);
}

void PlayerKeys::HookKeyDown(SDLKey sym) 
{
    switch(sym) {
        case SDLK_LEFT:
            leftup = false;
            charxvel = -1;
            break;
        case SDLK_RIGHT:
            rightup = false;
            charxvel = 1;
            break;
        case SDLK_UP:
            upup = false;
            charyvel = -1;
            break;
        case SDLK_DOWN:
            downup = false;
            charyvel = 1;
            break;
        default:
            done = 1;
            break;
    } // switch
}

void PlayerKeys::HookKeyUp( SDLKey sym ) 
{
    switch(sym) {
        case SDLK_LEFT:
            leftup = true;
            charxvel = 0;
            break;
        case SDLK_RIGHT:
            rightup = true;
            charxvel = 0;
            break;
        case SDLK_UP:
            upup = true;
            charyvel = 0;
            break;
        case SDLK_DOWN:
            downup = true;
            charyvel = 0;
            break;
        default:
            break;
    } // switch

}

void PlayerKeys::HookEventloop( SDL_Event* keyevent )
{
    upup = true;           //Initialize all the key booleans to true.
    downup = true;
    leftup = true;
    rightup = true;

    if (keyevent->type == SDL_KEYDOWN)
    {
        HookKeyDown(keyevent->key.keysym.sym);
    }
    if (keyevent->type == SDL_KEYUP)
    {
        HookKeyUp(keyevent->key.keysym.sym);
    }

    //These continue to accelerate the character if the user is holding
    // down a button.
    if (!upup) {
        charyvel -= 1;         
    }

    if (!downup) {charyvel += 1; }

    if (!rightup) {charxvel += 1; }

    if (!leftup) {charxvel -= 1; }

    charx += charxvel;
    chary += charyvel;

}


std::ostream& operator<<(std::ostream& o, const PlayerKeys& r) {
    return o << "PlayerKeys[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
        << ", W=" << r.GetW() << ", H=" << r.GetH()
        <<*/ " ]";
}

