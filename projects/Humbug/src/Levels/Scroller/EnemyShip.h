/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the EnemyShip.h class.
 * \file       EnemyShip.h
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
#include "boost/smart_ptr/scoped_ptr.hpp"
#include <GuiLib/GUI/Components/Rectangle.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/Timing.h>

namespace humbug {
class DebugOverlay;
namespace levels {
/** @class BaseEnemyShip:
 *  Detailed description.
 *  @param hitter TODO
 *  @param paintHitbox TODO
 *  @param id TODO
 *  @param tag TODO
 *  @param mdata TODO
 */
class BaseEnemyShip : public gui::HitHandler, public gui::Disposable {
    unsigned int m_iId;
    static unsigned int CurrentID;
    
    static unsigned int GetNewId();
public:

    /** Brief description of BaseEnemyShip, Offset
     *  Detailed description.
     *  @return TODO
     */
    unsigned int Id() const {
        return m_iId;
    }

    BaseEnemyShip();
};

namespace scroller_levela {
/** @class EnemyShip1Mover:
 *  Detailed description.
 *  @param hitter TODO
 *  @param paintHitbox TODO
 *  @param id TODO
 *  @param tag TODO
 *  @param mdata TODO
 */
class EnemyShip1Mover;

/** @class EnemyShip:
 *  A one page static Page (Screen) with a selection menu.
 */
class EnemyShip : public BaseEnemyShip {
public:

    EnemyShip(gui::CSpriteManager* sprMgr, const gui::components::CPoint& pos,
            int sprShipId,
            int sprLaserId,
            gui::components::CCanvas* canvas,
            DebugOverlay* dbgOverlay);

    void HitBy(const gui::CSprite& hitter, const gui::components::CRectangle& paintHitbox, int id, const std::string& tag,
            gui::CSpriteModifierData& mdata) override;

    void LaserUpdfunc2(gui::CSprite* sprite, int ticks, gui::CSpriteModifierData& mdata) const;

    void Fire(const gui::CSprite& hitter, const gui::components::CRectangle& paintHitbox);
    void Explode() const;

    /** Brief description of BaseEnemyShip, Offset
        *  Detailed description.
        *  @return TODO
        */
    gui::components::CPoint Offset() const;

    /** Brief description of BaseEnemyShip, SetOffset
        *  Detailed description.
        *  @param offset TODO
        */
    void SetOffset(const gui::components::CPoint& offset) const;

private:

    struct EnemyShipImpl;
    boost::scoped_ptr<EnemyShipImpl> pimpl_;

    gui::CSprite* m_pEnemy1Ship;
    gui::CSprite* m_pSprLaser;
    int m_iSprShipId;
    int m_iSprLaserId;
    gui::components::CRectangle sprDimension;
    gui::components::CRectangle mainDimension;
    boost::shared_ptr<EnemyShip1Mover> updfuncShip;
    gui::CSpriteManager* m_pSprMgr;
    gui::components::CCanvas* m_pCanvas;
    DebugOverlay* m_pOverlay;
    gui::components::CPoint m_pos;
    gui::Timing timing;
    bool m_bFired;

    //boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;
    //boost::scoped_ptr<DebugOverlay> m_pOverlay;
};
}
}
}
