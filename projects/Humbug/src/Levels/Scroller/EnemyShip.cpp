/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the EnemyShip.cpp class.
 * \file       EnemyShip.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "EnemyShip.h"
//
#include "../../GUI/DebugOverlay.h"
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

using namespace gui::components;
using namespace gui;

namespace humbug {
namespace levels {
namespace scroller_levela {
/** @class EnemyShip1Mover:
 *  Detailed description.
 *  @param m_p_overlay TODO
 */
class EnemyShip1Mover {
    int h_;
    bool toggle_;
    int deltaX_;
    uint32_t sproffs;
    uint32_t sproffsAct;
    //int rnd;
    CPoint lastSpritePos;
    DebugOverlay* m_pOverlay;
    CCanvas* m_pBackground;
    CPoint pos;
    EnemyShip* m_pShip;
    Timing timing;
    float m_waitTime;

public:

    EnemyShip1Mover(EnemyShip* ship, CCanvas* background, int deltaY = 0, uint32_t spriteoffset = 29) : m_pShip(ship), h_(-1),
        toggle_(false),
        deltaX_(deltaY),
        sproffs(spriteoffset), sproffsAct(0), m_pOverlay(nullptr), m_pBackground(background) {
        dbgOut(__FUNCTION__ << " created:" << " (" << this << ")");
        int rnd = 180 - (rand() % 360);
        h_ = rnd;
        m_waitTime = CalcWaitTime(0);
    }

    ~EnemyShip1Mover() {
        dbgOut(__FUNCTION__ << " " << this);
    }

    void SetDebugOverlay(DebugOverlay* m_p_overlay) {
        m_pOverlay = m_p_overlay;
    }

    void IncrementOffset() { sproffsAct++; }

    void DecrementOffset() { sproffsAct--; }

    static float CalcWaitTime(float minTime = 4.5f) {
        //float minTime = 4.5f;
        float rndTime = (rand() % 24500) / 1000.0f;
        float wtime = minTime + rndTime;

        return wtime;
    }

    /** $(fclass), operator ():
     *  Detailed description.
     *  @param sprite TODO
     * @param ticks TODO
     * @return TODO
     */
    void operator()(CSprite* sprite, int ticks, CSpriteModifierData& mdata) {
        timing.UpdateIdle();
        double ss = std::sin(static_cast<double>(h_) / 3.14159 / 12.0);
        double sc = std::cos(static_cast<double>(h_) / 3.14159 / 12.0);
        int ssin = static_cast<int>(ss * 8);
        int scos = static_cast<int>(sc * 8);

        sprite->SetPosition(CPoint(mdata.initialpos.GetX() + deltaX_ + scos, mdata.initialpos.GetY() + ssin) + m_pShip->Offset());
        int delta = lastSpritePos.Distance(sprite->GetPosition());
        float angle = lastSpritePos.Angle(sprite->GetPosition());

        //uint32_t offset = sproffsAct % sproffs;
        uint32_t offset = h_ / 4 % sproffs;
        sprite->SetSpriteOffset(offset);

        CRectangle sdl_rect = sprite->SprImage()->DstRect();
        //m_pBackground->RenderDrawRect(sdl_rect, &sprColor);
        CColor sprColor = CColor::White();
        //m_pBackground->RenderFillRect(CRectangle(100, 100, 200, 200), &sprColor);

        if(timing.IsAfter(m_waitTime)) {
            //m_pShip->Fire(*sprite);
            m_waitTime = CalcWaitTime();
            timing.Reset();
        }

        if(false && m_pOverlay) {
            std::ostringstream out6003;
            out6003 << "sproffs: (" << offset << ")";
            m_pOverlay->SetTextLabelText(6003, out6003.str());

            std::ostringstream out6004;
            out6004 << "delta: (" << delta << ")";
            m_pOverlay->SetTextLabelText(6004, out6004.str());
        }

        if(h_ >= 180) {
            toggle_ = false;
        }
        else if(h_ <= -180) {
            toggle_ = true;
        }

        if(toggle_) {
            h_++;
        }
        else {
            h_--;
        }

        lastSpritePos = sprite->GetPosition();
    }                 // ()
};

struct EnemyShip::EnemyShipImpl {
    int x;
};

EnemyShip::EnemyShip(CSpriteManager* sprMgr, const CPoint& pos,
        int sprShipId,
        int sprLaserId,
        CCanvas* canvas,
        DebugOverlay* dbgOverlay) : m_iSprShipId(sprShipId), m_iSprLaserId(sprLaserId),
        pimpl_(new EnemyShipImpl),
    m_pSprMgr(sprMgr), m_pCanvas(canvas), m_pOverlay(dbgOverlay), m_pos(pos),
    timing(boost::bind(&CSpriteManager::UpdateTimeFunc, boost::ref(*sprMgr))), m_bFired(false) {
    m_pEnemy1Ship = sprMgr->GetSpriteById(sprShipId);
    m_pSprLaser = sprMgr->GetSpriteById(sprLaserId);

    updfuncShip = boost::make_shared<EnemyShip1Mover>(this, canvas, 120);
    //    updfuncShip->SetDebugOverlay(dbgOverlay);

    m_pSprMgr->AddSpriteDraw(m_iSprShipId, pos, boost::ref(*updfuncShip.get()), { "Laser", "Ship" }, this);

    //m_iSprLaserId = CreateLaserSprite();
    /*m_pSprLaser =
       new CSprite(loader, "Sprites/Ship/Laser/Bullet01.png", canvas, CPoint(49, 480));
       CRectangle hitbox =
       CRectangle(m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::SW).Up(-50),
       m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::NE).Up(50));
       m_pSprLaser->SetHitBox(hitbox.Pad(20, 0));*/
    CPoint posLas = m_pEnemy1Ship->PaintLocation().Position(CRectangle::CompassRose::N) - m_pSprLaser->PaintDimension().Position(
            CRectangle::CompassRose::S).Up(-50);
    //m_pSprLaser->SetPosition(posLas);
    //m_pSprLaser->SetVisibility(false);
    //m_iSprLaserId = m_pSprMgr->AddSprite(m_pSprLaser, "EnemyLaser");
}

void EnemyShip::HitBy(const gui::CSprite& hitter,
        const gui::components::CRectangle& paintHitbox,
        int id,
        const std::string& tag,
        gui::CSpriteModifierData& mdata) {
    Fire(hitter);
    // delete laser when enemy is hit.
    //        if (tag == "Laser" && id > 1023)
    //        {
    //            mdata.markedForDeletion = true;
    //        }
}

void EnemyShip::LaserUpdfunc2(gui::CSprite* sprite, int ticks, gui::CSpriteModifierData& mdata) const {
    // Todo: test when not const .... say when modulating the alpha
    //int ySpeed = -16;
    int ySpeed = 4;
    sprite->SetPosition(sprite->GetPosition().Move(0, ySpeed));
    gui::components::CRectangle scr(0, 0, 1024, 768);

    if(mdata.isHit) {
        sprite->SetSpriteOffset(1 + ticks % 1);
    }
    else {
        sprite->SetSpriteOffset(0);
    }

    gui::components::CPoint pt = sprite->PaintLocation().Position(gui::components::CRectangle::CompassRose::S);
    if(!scr.Contains(pt)) {
        mdata.markedForDeletion = true;
    }
} // EnemyShip::LaserUpdfunc2

void EnemyShip::Fire(const gui::CSprite& hitter) {
    //return;

    if(timing.IsAfter(4.0f)) {
        m_bFired = false;
        timing.Reset(0);
    }

    if(m_bFired) {
        return;
    }

    m_bFired = true;
    //CSpriteManager::CSpriteModifierFunc fnc = boost::bind(&PlayerShip::LaserUpdfunc2,
    // boost::ref(*this), _1, _2, _3);
    //m_pSprMgr->AddSprite(m_pSprLaser, boost::bind(&PlayerShip::LaserUpdfunc2,
    // boost::ref(*this), _1, _2, _3));
    //CPoint pos = m_pEnemy1Ship->PaintLocation().Position(CRectangle::CompassRose::N) -
    // m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::S).Up(-50);
    //CPoint pos = m_pos -
    // m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::S).Up(-50);
    //CPoint pos = m_pos;
    //CPoint pos = m_pos + m_pEnemy1Ship->PaintLocation();
    gui::components::CPoint pos = hitter.PaintLocation();
    m_pSprMgr->AddSpriteDraw(m_iSprLaserId, pos, boost::bind(&EnemyShip::LaserUpdfunc2, boost::ref(*this), _1, _2, _3), { "Ship" });
} // EnemyShip::Fire
}
}
}
