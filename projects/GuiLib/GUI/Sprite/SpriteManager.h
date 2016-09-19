/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SpriteManager.h class.
 * \folder     $(folder)
 * \file       SpriteManager.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUGGL_GUI_SPRITE_SPRITEMANAGER_H
#define HUMBUGGL_GUI_SPRITE_SPRITEMANAGER_H

//
#include "Sprite.h"
#include <boost/ptr_container/ptr_vector.hpp>

//
namespace gui {
//
class CSpriteHook;
struct CSpriteModifierData
{
    /** contains the source rectangle. */
    components::CRectangle* srcRect;
    /** contains the destination rectangle. */
    components::CRectangle* dstRect;
    components::CPoint initialpos;
    bool isHandled;
    /** If set to true the TextAnimator will be removed and deleted from the execution queue.
       The TextAnimator::nextAnimator next animator is added and called on the next run of the
          queue. */
    bool markedForDeletion;
    int state;
    bool isHit;

    CSpriteModifierData(components::CRectangle* srcRect, components::CRectangle* dstRect)
        : srcRect(srcRect), dstRect(dstRect), isHandled(false), markedForDeletion(false), state(1), isHit(false)
    {}
};

/** @class HitHandler:
 *  Detailed description.
 */
class HitHandler {
public:

    virtual ~HitHandler()
    {}

    /** Brief description of HitHandler, HitBy
     *  Detailed description.
     *  @param hitter Sprite that hits.
     *  @param paintHitbox Position of the hit.
     *  @param id Identification number of the sprite. -1 if a real sprite or any positive number if a clone draw
     *  @param tag Tag of the hitting sprite.
     */
    virtual void HitBy(const CSprite& hitter, const components::CRectangle& paintHitbox, int id, const std::string& tag, CSpriteModifierData& mdata)
    {}
};

/** @class CSpriteManager:
 *  Detailed description.
 *  @param sprite TODO
 *  @param tag TODO
 *  @param updfunc TODO
 *  @param hitHandler TODO
 *  @param canCollideWithTags TODO
 *  @return TODO
 */
class CSpriteManager {
public:

    typedef boost::function<void (CSprite *, int, CSpriteModifierData& mdata)> CSpriteModifierFunc;
    typedef boost::function<void (CSprite *, CSpriteModifierData& mdata)> CSpriteRenderFunc;

    CSpriteManager(/*SDL_Surface* screen*/);
    ~CSpriteManager();
    int AddSprite(CSprite* sprite, const std::string& tag, const CSpriteModifierFunc& updfunc = NULL, HitHandler* hitHandler = NULL,
            const std::vector<std::string>& canCollideWithTags = std::vector<std::string>());

    /** Add clone of Sprite.
    *  Add a render instance of a sprite with the specified id.
    *  @param id TODO
    *  @param position TODO
    *  @param updfunc TODO
    *  @param canCollideWithTags TODO
    *  @param renderfunc TODO
    */
    void AddSpriteDraw(int id, const components::CPoint& position, const CSpriteModifierFunc& updfunc,
            const std::vector<std::string>& canCollideWithTags = std::vector<std::string>(),
            HitHandler* hitHandler = NULL,
            const CSpriteRenderFunc& renderfunc = NULL);

    void OnDraw();

    void OnIdle(int ticks);

    friend std::ostream& operator<<(std::ostream& o, const CSpriteManager& r);

    void Render();

    int UpdateTimeFunc() const { return m_iTicks; }
    
    /** Retrieve a Sprite instance by its id.
    *  @param id The identification number.
    *  @return the CSprite instance coupled with the specified id or Null if invalid.
    */
    CSprite* GetSpriteById(int id) const;

private:

    struct CSpriteManagerImpl;
    boost::scoped_ptr<CSpriteManagerImpl> pimpl_;
    int m_iTicks;
    bool m_bNotFirstRun;
    //typedef boost::ptr_vector<CSpriteHook> SprStorage;
    //SprStorage m_pvSprites;
};

std::ostream& operator<<(std::ostream& o, const CSpriteManager& r);
}
#endif // HUMBUGGL_GUI_SPRITE_SPRITEMANAGER_H guard
