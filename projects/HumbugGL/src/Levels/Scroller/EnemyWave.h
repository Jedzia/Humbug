/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the EnemyWave.h class.
 * \file       EnemyWave.h
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

namespace humbug{
    class DebugOverlay;
}

namespace humbug {
namespace levels {
/** @class BaseEnemyWave:
 *  Detailed description.
 *  @param hitter TODO
 *  @param paintHitbox TODO
 *  @param id TODO
 *  @param tag TODO
 *  @param mdata TODO
 */
class BaseEnemyWave : public gui::HitHandler
{
    gui::components::CPoint m_iOffset;

public:

    gui::components::CPoint Offset() const
    {
        return m_iOffset;
    }

    void SetOffset(const gui::components::CPoint& offset)
    {
        m_iOffset = offset;
    }

    BaseEnemyWave(): m_iOffset(0)
    {
    }
};

namespace scroller_levela {
class EnemyWave1Mover;

/** @class EnemyWave:
 *  A one page static Page (Screen) with a selection menu.
 */
class EnemyWave : public BaseEnemyWave {
public:
    EnemyWave(FileLoader& loader, gui::components::CCanvas* canvas, gui::CSpriteManager* sprMgr, DebugOverlay* dbgOverlay);

    void HitBy(const gui::CSprite& hitter, const gui::components::CRectangle& paintHitbox, int id, const std::string& tag, gui::CSpriteModifierData& mdata) override;

    void HookIdle(int ticks, float speed);

    void Reset() const;

private:

    struct EnemyWaveImpl;
    boost::scoped_ptr<EnemyWaveImpl> pimpl_;

    gui::CSprite* m_pSprEnemy1Ship;
    gui::CSprite* m_pSprLaser;
    int m_iSprEnemy1ShipId;
    int m_iSprLaserId;
    gui::components::CRectangle sprPaintDimension;
    gui::components::CRectangle mainDimension;
    //boost::shared_ptr<EnemyShip1Mover> updfuncShip;
    gui::CSpriteManager* m_pSprMgr;
    gui::components::CCanvas* m_pCanvas;
    FileLoader& m_Loader;
    DebugOverlay* m_pOverlay;
    //boost::shared_ptr<EnemyShip> m_pEnemyShip;

};
}
}
}
