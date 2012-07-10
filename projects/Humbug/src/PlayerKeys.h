#ifndef PROJECT_PLAYERKEYS_H
#define PROJECT_PLAYERKEYS_H

#include "SDL.h"

class PlayerKeys {
public:

    PlayerKeys(/*SDL_Surface* screen*/);
    ~PlayerKeys();

    void HookEventloop(SDL_Event* pEvent) ;
    void HookKeyDown(SDLKey sym) ;
    void HookKeyUp(SDLKey sym) ;

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
