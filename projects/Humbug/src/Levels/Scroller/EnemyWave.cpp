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
#include <boost/foreach.hpp>
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
#include <GUI/Components/Rectangle.h>
//#include <GuiLib/Filesystem/FileLoader.h>
//#include <GuiLib/GUI/Components/CanvasRendererImpl.h>
//#include <GuiLib/GUI/Components/CoordSystem.h>
//#include <GuiLib/GUI/Components/EasingFunctors.h>
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

using namespace gui;
using namespace components;

namespace humbug {
namespace levels {
namespace scroller_levela {


struct EnemyWave::EnemyWaveImpl {
    int x;
};


    EnemyWave::EnemyWave(FileLoader& loader, gui::components::CCanvas* canvas, gui::CSpriteManager* sprMgr, DebugOverlay* dbgOverlay): m_pSprMgr(sprMgr), m_pCanvas(canvas), m_Loader(loader), m_pOverlay(dbgOverlay)
    {
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
        //        updfuncShip = boost::make_shared<EnemyShip1Mover>(canvas, 120);
        //        updfuncShip->SetDebugOverlay(dbgOverlay);
        //        m_iSprEnemy1ShipId = sprMgr->AddSprite(m_pSprEnemy1Ship, "Enemy",
        // boost::ref(*updfuncShip.get()), this);
        m_iSprEnemy1ShipId = sprMgr->AddSprite(m_pSprEnemy1Ship, "Enemy", NULL, this);
        m_pSprEnemy1Ship->SetPosition(CPoint(200, 200));
        //        //CPoint pos = m_pSprEnemy1Ship->PaintLocation().Position(CRectangle::CompassRose::N) -
        // m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::S).Up(-50);
        //        //CPoint pos =
        // m_pSprEnemy1Ship->PaintLocation().Position(CRectangle::CompassRose::N).Up(-64);
        //        CPoint pos(128, 128);
        //        //m_pSprMgr->AddSpriteDraw(m_iSprLaserId, pos, boost::bind(&PlayerShip::LaserUpdfunc2,
        // boost::ref(*this), _1, _2, _3), { "Enemy", "Test" });
        //        m_pSprMgr->AddSpriteDraw(m_iSprEnemy1ShipId, pos, boost::ref(*updfuncShip.get()), {
        // "Laser", "Ship" });
        m_pSprEnemy1Ship->SetVisibility(false);

        //m_iSprLaserId = CreateLaserSprite();
        m_pSprLaser =
            new CSprite(loader, "Sprites/Ship/Laser/Bullet01.png", canvas, CPoint(32, 32));
        CRectangle hitbox = CRectangle(m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::SW).Up(
                                           -50), m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::NE).Up(50));
        m_pSprLaser->SetHitBox(hitbox.Pad(20, 0));
        //        CPoint posLas = m_pSprEnemy1Ship->PaintLocation().Position(CRectangle::CompassRose::N) -
        // m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::S).Up(-50);
        //        m_pSprLaser->SetPosition(posLas);
        m_pSprLaser->SetVisibility(false);
        m_iSprLaserId = m_pSprMgr->AddSprite(m_pSprLaser, "EnemyBullet");

        const int rows = 4;
        const int columns = 16;
        //        const int rows = 2;
        //        const int columns = 2;
        //const int startPosX = 32;

        int screenXMiddle = canvas->GetDimension().GetW() / 2;
        int spriteShipWidth = sprPaintDimension.GetW();
        int spriteShipHeight = sprPaintDimension.GetH();
        int spriteShipHeightDouble = spriteShipHeight * 2;
        int spriteShipWidthHalf = spriteShipWidth / 2;
        int spriteShipWidthDouble = spriteShipWidth * 2;
        int spritesXMiddle = (spriteShipWidth * columns) / 2;
        
        int startPosX = screenXMiddle - spritesXMiddle;
        const int startPosY = 32;

        //m_pEnemyShip = boost::make_shared<EnemyShip>(m_pSprEnemy1Ship, m_iSprEnemy1ShipId,
        // m_pSprLaser, m_iSprLaserId, canvas, sprMgr, dbgOverlay);
        for (size_t row = 0; row < rows; row++)
        {
            int rowNotEven = row % 1;
            CPoint pos = CPoint(startPosX + rowNotEven * spriteShipWidthHalf, startPosY + row * spriteShipHeightDouble);
            for (size_t column = 0; column < columns; column++)
            {
                m_pEnemyShips.push_back(new EnemyShip(sprMgr, pos, m_iSprEnemy1ShipId, m_iSprLaserId, canvas,
                                                      dbgOverlay));
                pos.Move(spriteShipWidth, 0);
            }
        }
    }

    void EnemyWave::HitBy(const gui::CSprite& hitter, const gui::components::CRectangle& paintHitbox, int id, const std::string& tag, gui::CSpriteModifierData& mdata)
    {
    }

    void EnemyWave::HookIdle(int ticks, float speed)
    {
        return;
        //m_pKeyHandler->HookIdle(ticks, speed);
        BOOST_FOREACH(boost::ptr_vector<EnemyShip>::reference ship, m_pEnemyShips)
        {
            ship.SetOffset(ship.Offset() + 1);
        }
    }
}
}
}
