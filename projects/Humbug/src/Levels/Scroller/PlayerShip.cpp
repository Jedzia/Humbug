/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the PlayerShip.cpp class.
 * \file       PlayerShip.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "PlayerShip.h"
//
#include "../../GUI/DebugOverlay.h"
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
#include <GUI/Components/Rectangle.h>
#include <GuiLib/Filesystem/FileLoader.h>
#include <GuiLib/Filesystem/FileLoader.h>
#include <GuiLib/GUI/Components/CanvasRendererImpl.h>
#include <GuiLib/GUI/Components/CoordSystem.h>
#include <GuiLib/GUI/Components/EasingFunctors.h>
#include <GuiLib/GUI/Components/Image.h>
#include <GuiLib/GUI/Components/Image.h>
#include <GuiLib/GUI/Components/SeamlessImage.h>
#include <GuiLib/GUI/Components/Shapes/Line.h>
#include <GuiLib/GUI/Components/Text.h>
#include <GuiLib/GUI/Components/Text.h>
#include <GuiLib/GUI/Components/TextScroller.h>
#include <GuiLib/GUI/Components/TextScroller.h>
#include <GuiLib/GUI/Controls/Button.h>
#include <GuiLib/GUI/Controls/Control.h>
#include <GuiLib/GUI/Controls/Label.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Sprite/Sprite.h>
#include <GuiLib/GUI/Sprite/Sprite.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/GUI/Visual/EventHandler.h>
#include <GuiLib/GUI/Visual/EventHandler.h>
#include <cstdlib>
//
//#include <build/cmake/include/debug.h>

using namespace gui;
using namespace components;

namespace humbug {
namespace levels {
namespace scroller_levela {

//CRectangle hitTestRect(200, 200, 300, 300);

//struct PlayerShip::PlayerShipImpl {
//    int x;
//};

/** @class ShipMover:
 *  Detailed description.
 *  @param sprite TODO
 *  @param ticks TODO
 *  @return TODO
 */
class ShipMover {
    int h_;
    bool toggle_;
    int deltaY_;
    uint32_t sproffs;
    //int rnd;
    CPoint lastSpritePos;
    DebugOverlay* m_pOverlay;
    PlayerKeys4* m_pKeyHandler;

public:

    ShipMover(PlayerKeys4* keyHandler, int deltaY = 0, uint32_t spriteoffset = 3) : h_(-1),
        toggle_(false), m_pKeyHandler(keyHandler),
        deltaY_(deltaY),
        sproffs(spriteoffset), m_pOverlay(nullptr) {
        dbgOut(__FUNCTION__ << " created:" << " (" << this << ")");
        int rnd = 180 - (rand() % 360);
        h_ = rnd;
    }

    ~ShipMover() {
        dbgOut(__FUNCTION__ << " " << this);
    }

    void SetDebugOverlay(DebugOverlay* m_p_overlay) {
        m_pOverlay = m_p_overlay;
    }

    /** $(fclass), operator ():
     *  Detailed description.
     *  @param sprite TODO
     * @param ticks TODO
     * @return TODO
     */
    void operator()(CSprite* sprite, int ticks, CSpriteModifierData& mdata) {
        double ss = std::sin(static_cast<double>(h_) / 3.14159 / 4.0);
        double sc = std::cos(static_cast<double>(h_) / 3.14159 / 4.0);
        int ssin = static_cast<int>(ss * 100);
        int scos = static_cast<int>(sc * 100);

        //sprite->SetPosition(CPoint(100 + ((ticks % 128) * 6), 460 + h_ + deltaY_ + ssin));
        //sprite->SetPosition(CPoint(130 + ssin, deltaY_ - scos));
        //sprite->SetPosition(CPoint(130 + ssin, deltaY_));
        sprite->SetPosition(m_pKeyHandler->Char());
        int delta = lastSpritePos.Distance(sprite->GetPosition());
        float angle = lastSpritePos.Angle(sprite->GetPosition());
        int sproffsAct = 0;
        if(delta > 0) {
            if(angle <= 0) {
                sproffsAct = 2;
            }
            else if(angle > 0) {
                sproffsAct = 1;
            }
        }

        if(mdata.isHit) {
            sproffsAct = ticks % sproffs;
        }

        //sprite->SetSpriteOffset(ticks % sproffs);
        sprite->SetSpriteOffset(sproffsAct % sproffs);

        lastSpritePos = sprite->GetPosition();

        //bool isHit = hitTestRect.Contains(sprite->PaintLocation());
        //bool isHit = sprite->PaintLocation().Contains(hitTestRect);
        //bool isHit = false;

        if(m_pOverlay) {
            std::ostringstream out6000;
            out6000 << "angle: (" << angle << ")";
            m_pOverlay->SetTextLabelText(6000, out6000.str());

            std::ostringstream out6001;
            out6001 << "delta: (" << delta << ")";
            m_pOverlay->SetTextLabelText(6001, out6001.str());

            //            std::ostringstream out6002;
            //            out6002 << "spritePos: (" << lastSpritePos << ")";
            //            out6002 << " hitRect: (" << hitTestRect << ")";
            //            out6002 << " PaintLoc: (" << sprite->PaintLocation() << ")";
            //            if (mdata.isHit)
            //            {
            //                out6002 << " HIT at pos: (" << hitTestRect << ")";
            //            }
            //
            //            m_pOverlay->SetTextLabelText(6002, out6002.str());
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
    }             // ()
};

struct PlayerShip::PlayerShipImpl {
private:

    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    int x;
    PlayerShip* host;

public:

//    boost::shared_ptr<hspriv::LaserMover> updfunc2;
//    boost::shared_ptr<hspriv::SaucerMover> updfunc3;
//    boost::shared_ptr<PlayerShip> m_pPlayerShip;
//    boost::shared_ptr<EnemyWave> m_pEnemyShip;

    explicit PlayerShipImpl(PlayerShip* host)
        : x(0), host{ host }
    {}

    void Draw() const {
        //auto aaaa = host->m_pBackground->GetDimension();
    }
};

PlayerShip::PlayerShip(FileLoader& loader,
        CCanvas* canvas,
        CSpriteManager* sprMgr, 
        DebugOverlay* dbgOverlay,
        seconds fireRate) : 
        pimpl_(new PlayerShipImpl(this)),
        m_pSprMgr(sprMgr), m_pCanvas(canvas), m_Loader(loader), m_pOverlay(dbgOverlay), m_fFireRate(fireRate),
    timing(boost::bind(&CSpriteManager::UpdateTimeFunc, boost::ref(*sprMgr))), m_bFired(false) {
    m_pSprShip =
        new CSprite(loader, "Sprites/Ship/ShipSprite02.png", canvas, CPoint(256, 256));
    m_pSprShip->SprImage()->DstRect() = m_pSprShip->SprImage()->DstRect() / 2;
    m_pSprShip->SetHitBox(m_pSprShip->SprImage()->DstRect());
    int mainCanvasMiddleX = canvas->GetWidth() / 2;
    int mainSprEyeMiddleX = m_pSprShip->SprImage()->DstRect().GetW() / 2;
    sprDimension = m_pSprShip->SpriteDimension();
    mainDimension = canvas->GetDimension();
    //CRectangle rect = CRectangle() mainDimension.Pad(sprPaintDimension);
    CRectangle rect = CRectangle(mainDimension.GetX(), mainDimension.GetY(),
            mainDimension.GetW() - sprDimension.GetW() / 2, mainDimension.GetH() - sprDimension.GetH() / 2);
    int delta_y = canvas->GetHeight() - m_pSprShip->SprImage()->DstRect().GetH() - 128;
    m_pKeyHandler.reset(new PlayerKeys4(rect.Pad(10), static_cast<float>(mainCanvasMiddleX - mainSprEyeMiddleX),
                    static_cast<float>(delta_y), false, false, 1.0f));
    updfuncShip = boost::make_shared<ShipMover>(m_pKeyHandler.get(), delta_y);
    updfuncShip->SetDebugOverlay(dbgOverlay);
    //sprMgr->AddSprite(m_pSprShip, "Ship", boost::ref(*updfuncShip.get()), this);
    sprMgr->AddSprite(m_pSprShip, "Ship", boost::ref(*updfuncShip.get()), this, { "Enemy", "Enemy1", "EnemyBullet" });
    //sprMgr->AddSprite(m_pSprShip, "Ship", boost::ref(*updfuncShip.get()), this, { "ALL" });

    //m_iSprLaserId = CreateLaserSprite();
    m_pSprLaser =
        new CSprite(loader, "Sprites/Ship/Laser/Laser01.png", canvas, CPoint(49, 480));
    CRectangle hitbox = CRectangle(m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::SW).Up(
                    -50), m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::NE).Up(50));
    m_pSprLaser->SetHitBox(hitbox.Pad(20, 0));
    CPoint pos = m_pSprShip->PaintLocation().Position(CRectangle::CompassRose::N) - m_pSprLaser->PaintDimension().Position(
            CRectangle::CompassRose::S).Up(-50);
    m_pSprLaser->SetPosition(pos);
    m_pSprLaser->SetVisibility(false);
    m_iSprLaserId = m_pSprMgr->AddSprite(m_pSprLaser, "Laser", 0, 0, { "Enemy", "Enemy1" });
}

void PlayerShip::LaserUpdfunc(CSprite* sprite, int ticks, CSpriteModifierData& mdata) {
    int ySpeed = -16;
    sprite->SetPosition(sprite->GetPosition().Move(0, ySpeed));
    CRectangle scr(0, 0, 1024, 768);
    if(!scr.Contains(sprite->GetPosition())) {
        mdata.markedForDeletion = true;
    }
}

void PlayerShip::LaserUpdfunc2(CSprite* sprite, int ticks, CSpriteModifierData& mdata) const {
    // Todo: test when not const .... say when modulating the alpha
    //int ySpeed = -16;
    int ySpeed = -4;
    sprite->SetPosition(sprite->GetPosition().Move(0, ySpeed));
    CRectangle scr(0, 0, 1024, 768);

    if(mdata.isHit) {
        sprite->SetSpriteOffset(ticks % 10);
    }
    else {
        sprite->SetSpriteOffset(0);
    }

    //CRectangle hitRect(0, 0, 100, 100);
    //bool isHit = hitRect.Contains(sprite->PaintLocation());
    CPoint pt = sprite->PaintLocation().Position(CRectangle::CompassRose::S);
    if(m_pOverlay) {
        std::ostringstream out6009;
        out6009 << "LaserUpdfunc2 sprite pos: (" << pt << ")";
        //            if (isHit)
        //            {
        //                out6009 << " HIT at pos: (" << hitRect << ")";
        //            }
        m_pOverlay->SetTextLabelText(6009, out6009.str());
    }

    if(!scr.Contains(pt)) {
        mdata.markedForDeletion = true;
    }
} // PlayerShip::LaserUpdfunc2

void PlayerShip::HitBy(const CSprite& hitter,
        const CRectangle& paintHitbox,
        int id,
        const std::string& tag,
        CSpriteModifierData& mdata) {
    std::ostringstream out6002;
    out6002 << "PlayerHit: (" << paintHitbox << ")";
    out6002 << " id:(" << id << ")";
    out6002 << " tag:(" << tag << ")";

    m_pOverlay->SetTextLabelText(6002, out6002.str());
}

void PlayerShip::Fire() {
    if(timing.IsAfter(m_fFireRate)) {
        m_bFired = false;
        timing.Reset(0);
    }

    //        if (m_bFired) {
    //            return;
    //        }

    m_bFired = true;

    //CSpriteManager::CSpriteModifierFunc fnc = boost::bind(&PlayerShip::LaserUpdfunc2,
    // boost::ref(*this), _1, _2, _3);
    //m_pSprMgr->AddSprite(m_pSprLaser, boost::bind(&PlayerShip::LaserUpdfunc2,
    // boost::ref(*this), _1, _2, _3));
    CPoint pos = m_pSprShip->PaintLocation().Position(CRectangle::CompassRose::N) - m_pSprLaser->PaintDimension().Position(
            CRectangle::CompassRose::S).Up(-50);
    m_pSprMgr->AddSpriteDraw(m_iSprLaserId, pos, boost::bind(&PlayerShip::LaserUpdfunc2, boost::ref(
                            *this), _1, _2, _3), { "Enemy", "Enemy1" });
} // PlayerShip::Fire

void PlayerShip::HookEventloop(SDL_Event* pEvent) {
    m_pKeyHandler->HookEventloop(pEvent);
    if(m_pKeyHandler->IsPressed(SDLK_SPACE)) {
        Fire();
    }

    //m_pKeyHandler->
    if(pEvent->type != SDL_KEYDOWN) {
        return;
    }

    switch(pEvent->key.keysym.sym) {
    case SDLK_SPACE:
    {
        //Fire();
        break;
    }
    case SDLK_a:
    {
        break;
    }
    default:
        break;
    }         // switch
} // PlayerShip::HookEventloop

void PlayerShip::HookIdle(int ticks, float speed) const {
    m_pKeyHandler->HookIdle(ticks, speed);
}
}
}
}
