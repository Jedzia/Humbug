/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the PlayerShip.h class.
 * \file       PlayerShip.h
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
#include "../../Input/PlayerKeys4.h"
#include "boost/smart_ptr/scoped_ptr.hpp"
#include <GuiLib/GUI/Components/Rectangle.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/Timing.h>

namespace humbug {
class DebugOverlay;
namespace levels {
/** @class BasePlayerShip:
 *  Detailed description.
 *  @param hitter TODO
 *  @param paintHitbox TODO
 *  @param id TODO
 *  @param tag TODO
 *  @param mdata TODO
 */
class BasePlayerShip : public gui::HitHandler {};

namespace scroller_levela {
class ShipMover;
/** @class PlayerShip:
 *  Detailed description.
 *  @param pEvent TODO
 */
class PlayerShip : public BasePlayerShip {
public:

    PlayerShip(FileLoader& loader, gui::components::CCanvas* canvas, gui::CSpriteManager* sprMgr, DebugOverlay* dbgOverlay,
            gui::seconds fireRate);

    static void LaserUpdfunc(gui::CSprite* sprite, int ticks, gui::CSpriteModifierData& mdata);

    void LaserUpdfunc2(gui::CSprite* sprite, int ticks, gui::CSpriteModifierData& mdata) const;

    // LaserUpdfunc2

    void HitBy(const gui::CSprite& hitter, const gui::components::CRectangle& paintHitbox, int id, const std::string& tag,
            gui::CSpriteModifierData& mdata) override;

    void Fire();

    void HookEventloop(SDL_Event* pEvent);

    // HookEventloop

    void HookIdle(int ticks, float speed) const;
private:
    struct PlayerShipImpl;
    boost::scoped_ptr<PlayerShipImpl> pimpl_;

    gui::CSprite* m_pSprShip;
    gui::CSprite* m_pSprLaser;
    int m_iSprLaserId;
    gui::components::CRectangle sprDimension;
    gui::components::CRectangle mainDimension;
    boost::scoped_ptr<PlayerKeys4> m_pKeyHandler;
    boost::shared_ptr<ShipMover> updfuncShip;
    gui::CSpriteManager* m_pSprMgr;
    //CSpriteManager::CSpriteModifierFunc laserUpdfunc;
    gui::components::CCanvas* m_pCanvas;
    FileLoader& m_Loader;
    DebugOverlay* m_pOverlay;
    float m_fFireRate;
    gui::Timing timing;
    bool m_bFired;
};
}
}
}
