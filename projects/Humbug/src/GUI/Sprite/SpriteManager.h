#ifndef PROJECT_SPRITEMANAGER_H
#define PROJECT_SPRITEMANAGER_H

#include <boost/ptr_container/ptr_vector.hpp>
#include "Sprite.h"

class CSpriteHook;

class CSpriteManager {
public:

    CSpriteManager(/*SDL_Surface* screen*/);
    ~CSpriteManager();

    void AddSprite(CSprite *sprite, boost::function<void(CSprite*, int)> updfunc = NULL);
    void AddSpriteX(CSprite *sprite, boost::shared_ptr<boost::function<void(CSprite*, int)>> updfunc);
    void OnDraw();
    void OnIdle(int frameNumber);

    friend std::ostream& operator<<(std::ostream& o, const CSpriteManager& r);

private:
    typedef boost::ptr_vector<CSpriteHook> SprStorage;
    SprStorage m_pvSprites;
};

std::ostream& operator<<(std::ostream& o, const CSpriteManager& r);

#endif // PROJECT_SPRITEMANAGER_H guard
