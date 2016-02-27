/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the EnemyWave.cpp class.
 * \file       EnemyWave.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "EnemyWave.h"
//
#include "../../GUI/DebugOverlay.h"
#include "EnemyWaveSTM.h"
#include <boost/foreach.hpp>
#include <iostream>

//#include "boost/function.hpp"
//#include "boost/lambda/lambda.hpp"
//#include <GuiLib/Filesystem/FileLoader.h>
//#include <GuiLib/GUI/Components/Text.h>
//#include <GuiLib/GUI/Components/TextScroller.h>
#include <GuiLib/GUI/Controls/Control.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Sprite/Sprite.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
//#include <GuiLib/GUI/Visual/EventHandler.h>
//#include <cstdlib>
#include <GuiLib/Animation.h>
#include <GuiLib/GUI/Components/Rectangle.h>
//#include <GuiLib/Filesystem/FileLoader.h>
//#include <GuiLib/GUI/Components/CanvasRendererImpl.h>
//#include <GuiLib/GUI/Components/CoordSystem.h>
//#include <GuiLib/GUI/Components/EasingFunctors.h>
#include <GuiLib/GUI/Components/EasingFunctors.h>
#include <GuiLib/GUI/Components/Image.h>
//#include <GuiLib/GUI/Components/Image.h>
//#include <GuiLib/GUI/Components/SeamlessImage.h>
//#include <GuiLib/GUI/Components/Shapes/Line.h>
//#include <GuiLib/GUI/Components/Text.h>
//#include <GuiLib/GUI/Components/TextScroller.h>
//#include <GuiLib/GUI/Controls/Button.h>
//#include <GuiLib/GUI/Controls/Label.h>
//#include <GuiLib/GUI/Data/ColorData.h>
//#include <GuiLib/GUI/Sprite/Sprite.h>
//#include <GuiLib/GUI/Sprite/SpriteManager.h>
//#include <GuiLib/GUI/Visual/EventHandler.h>
//
//#include <build/cmake/include/debug.h>

using namespace gui::components;
using namespace gui;

namespace humbug {
namespace levels {
namespace scroller_levela {
struct EnemyWave::EnemyWaveImpl {
    int x;
    boost::shared_ptr<AnimatedRectangle> animRect1;
};

EnemyWave::EnemyWave(FileLoader& loader, CCanvas* canvas, CSpriteManager* sprMgr,
        DebugOverlay* dbgOverlay) : pimpl_(new EnemyWaveImpl), m_pSprMgr(sprMgr), m_pCanvas(canvas), m_Loader(loader),
    m_pOverlay(dbgOverlay) {
    m_pSprEnemy1Ship =
        new CSprite(loader, "Sprites/Ship/Enemy01a.png", canvas, CPoint(64, 64));
    m_pSprEnemy1Ship->SprImage()->DstRect() = m_pSprEnemy1Ship->SprImage()->DstRect() / 2;
    m_pSprEnemy1Ship->SetHitBox(m_pSprEnemy1Ship->SprImage()->DstRect());
    int mainCanvasMiddleX = canvas->GetWidth() / 2;
    int mainSprEyeMiddleX = m_pSprEnemy1Ship->SprImage()->DstRect().GetW() / 2;
    sprPaintDimension = m_pSprEnemy1Ship->PaintDimension();
    mainDimension = canvas->GetDimension();
    //CRectangle rect = CRectangle() mainDimension.Pad(sprPaintDimension);
    CRectangle rect = CRectangle(mainDimension.GetX(), mainDimension.GetY(),
            mainDimension.GetW() - sprPaintDimension.GetW() / 2, mainDimension.GetH() - sprPaintDimension.GetH() / 2);
    int delta_y = canvas->GetHeight() - m_pSprEnemy1Ship->SprImage()->DstRect().GetH() - 128;
    m_iSprEnemy1ShipId = sprMgr->AddSprite(m_pSprEnemy1Ship, "Enemy", NULL, this);
    m_pSprEnemy1Ship->SetPosition(CPoint(200, 200));
    m_pSprEnemy1Ship->SetVisibility(false);

    //m_iSprLaserId = CreateLaserSprite();
    m_pSprLaser =
        new CSprite(loader, "Sprites/Ship/Laser/Bullet01.png", canvas, CPoint(32, 32));
    CRectangle hitbox = CRectangle(m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::SW).Up(
                    -50), m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::NE).Up(50));
    m_pSprLaser->SetHitBox(hitbox.Pad(20, 0));
    m_pSprLaser->SetVisibility(false);
    m_iSprLaserId = m_pSprMgr->AddSprite(m_pSprLaser, "EnemyBullet");

    const int rows = 4;
    const int columns = 8;
    //        const int rows = 2;
    //        const int columns = 2;
    //const int startPosX = 32;

    int screenXMiddle = canvas->GetDimension().GetW() / 2;
    int spriteShipWidth = sprPaintDimension.GetW();
    int spriteShipHeight = sprPaintDimension.GetH();
    int spriteShipHeightDouble = spriteShipHeight * 2;
    int spriteShipWidthHalf = spriteShipWidth / 2;
    int spriteShipWidthDouble = spriteShipWidth * 2;

    // setup what dimensions to use
    int spriteShipHorizontalUse = spriteShipWidthDouble;
    int spriteShipVerticalUse = spriteShipHeightDouble;
    // end setup

    int spritesXMiddle = (spriteShipHorizontalUse * columns) / 2;
    int spritesYHeight = (spriteShipVerticalUse * rows);

    int startPosX = screenXMiddle - spritesXMiddle;
    const int startPosY = 32 * 4;
    CPoint initialpos = CPoint(startPosX, startPosY);

    //m_pEnemyShip = boost::make_shared<EnemyShip>(m_pSprEnemy1Ship, m_iSprEnemy1ShipId,
    // m_pSprLaser, m_iSprLaserId, canvas, sprMgr, dbgOverlay);
    for(size_t row = 0; row < rows; row++)
    {
        int rowNotEven = row % 1;
        CPoint pos = CPoint(startPosX + rowNotEven * spriteShipWidthHalf, startPosY + row * spriteShipVerticalUse);

        for(size_t column = 0; column < columns; column++)
        {
            m_pEnemyShips.push_back(new EnemyShip(sprMgr, pos, m_iSprEnemy1ShipId, m_iSprLaserId, canvas,
                            dbgOverlay));
            pos.Move(spriteShipHorizontalUse, 0);
        }
    }
    pimpl_->animRect1 = boost::make_shared<AnimatedRectangle>(
            CRectangle(0, -2 * spritesYHeight, 0, 0),     // starting shape, over the top
            CRectangle(),                                 // final shape, zero
            //boost::bind(&CSpriteManager::UpdateTimeFunc, boost::ref(*sprMgr)), 8.0f,
            // EaseOutElastic(2));
            AnimatedRectangleBindAdapter(sprMgr), 8.0f, EaseOutElastic(1.5f));

    //mainX();
}

void EnemyWave::HitBy(const CSprite& hitter,
        const CRectangle& paintHitbox,
        int id,
        const std::string& tag,
        CSpriteModifierData& mdata) {
}

struct ModulateSinus {
    explicit ModulateSinus(const vdouble amplitude = static_cast<vdouble>(1.0f),
            const vdouble period = static_cast<vdouble>(1.0f)) : m_amplitude(amplitude), m_period(period)
    { }

    // 0.0 to 1.0 maps to 0 to 360 degrees.
    vdouble operator()(vdouble t) const {
        double result = sin(t * 360.0f * vdouble(M_PI) / 180.0f);
        return result;
    }

private:

    vdouble m_amplitude;
    vdouble m_period;
};

struct ModulateCosinus {
    explicit ModulateCosinus()
    { }

    // 0.0 to 1.0 maps to 0 to 360 degrees.
    vdouble operator()(vdouble t) const {
        double result = cos(t * 360.0f * vdouble(M_PI) / 180.0f);
        return result;
    }
};

void EnemyWave::HookIdle(int ticks, float speed) {
    CPoint movement = CPoint(1, 1);
    if(ticks % 300 > 150) {
        movement = CPoint(-1, -1);
    }

    static Modulo ring(2.0f);
    static ModulateSinus modSinus;
    static ModulateCosinus modCosinus;

    //int ring0 = ring.Timed(ticks);
    int ring1 = ring(ticks);
    int mod_sinus = static_cast<int>(modSinus(ring.NormTimed(ticks)) * 100);
    int mod_cosinus = static_cast<int>(modCosinus(ring.NormTimed(ticks)) * 100);
    //dbgOut("Ring:" << ring.NormTimed(ticks) << ", i:" << ring1 << ", modSin:" << modSinus(ring.NormTimed(ticks)));
    //dbgOut("Ring:" << ring1);
    //return;
    //m_pKeyHandler->HookIdle(ticks, speed);
//        BOOST_FOREACH(boost::ptr_vector<EnemyShip>::reference ship, m_pEnemyShips)
//        {
//            ship.SetOffset(ship.Offset() + movement);
//        }

    boost::ptr_vector<EnemyShip>::iterator sprIt = m_pEnemyShips.begin();

    while(sprIt != m_pEnemyShips.end()) {
        boost::ptr_vector<EnemyShip>::reference ship = (*sprIt);
        unsigned int id = ship.Id();
        if(ship.IsDisposed()) {
            // if markedForDeletion, remove it
            sprIt = m_pEnemyShips.erase(sprIt);
        }
        else {
            //ship.SetOffset(ship.Offset() + movement);
            ship.SetOffset(pimpl_->animRect1->Rect() + CPoint(mod_sinus, mod_cosinus));
            ++sprIt;
        }
    }
} // EnemyWave::HookIdle

void EnemyWave::Reset() const {
    pimpl_->animRect1->Reset();
}
}
}
}
