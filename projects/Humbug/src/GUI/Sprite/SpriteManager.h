#ifndef HUMBUG_GUI_SPRITE_SPRITEMANAGER_H
#define HUMBUG_GUI_SPRITE_SPRITEMANAGER_H

#include <boost/ptr_container/ptr_vector.hpp>
#include "Sprite.h"

class CSpriteHook;

class CSpriteManager {
public:

    CSpriteManager(/*SDL_Surface* screen*/);
    ~CSpriteManager();

    void AddSprite(CSprite *sprite, const boost::function<void(CSprite*, int)>& updfunc = NULL);
    void OnDraw();
    void OnIdle(int frameNumber);

    friend std::ostream& operator<<(std::ostream& o, const CSpriteManager& r);

private:
    typedef boost::ptr_vector<CSpriteHook> SprStorage;
    SprStorage m_pvSprites;
};

std::ostream& operator<<(std::ostream& o, const CSpriteManager& r);

#endif // HUMBUG_GUI_SPRITE_SPRITEMANAGER_H guard
