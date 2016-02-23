/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ScrollerLevelA.cpp class.
 * \folder     $(folder)
 * \file       ScrollerLevelA.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "ScrollerLevelA.h"
#include "stdafx.h"

//#include <build/cmake/include/debug.h>
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
#include <cstdlib>
//
#include "../../Input/PlayerKeys4.h"
#include "GUI/DebugOverlay.h"
#include "HumbugShared/GameObjects/Player.h"
#include <GUI/Components/Rectangle.h>
#include <GuiLib/Filesystem/FileLoader.h>
#include <GuiLib/GUI/Components/CanvasRendererImpl.h>
#include <GuiLib/GUI/Components/CoordSystem.h>
#include <GuiLib/GUI/Components/EasingFunctors.h>
#include <GuiLib/GUI/Components/Image.h>
#include <GuiLib/GUI/Components/Image.h>
#include <GuiLib/GUI/Components/SeamlessImage.h>
#include <GuiLib/GUI/Components/Shapes/Line.h>
#include <GuiLib/GUI/Components/Text.h>
#include <GuiLib/GUI/Components/TextScroller.h>
#include <GuiLib/GUI/Controls/Button.h>
#include <GuiLib/GUI/Controls/Label.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Sprite/Sprite.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/GUI/Visual/EventHandler.h>
#include <GuiLib/Timing.h>

namespace humbug {
namespace levels {
using namespace gui::components;
using namespace gui;

/** @class CanvasStripeRendererOld:
 *  Detailed description.
 *  @param source TODO
 *  @param target TODO
 *  @param mdata TODO
 *  @return TODO
 */
class CanvasStripeRendererAOld {
    int m_iBoatcols;
    int m_iFrames;
    int m_iSteps;
    SDL_Color cmap[256];

public:

    // this little bastard should render colored stripes when ready.
    explicit CanvasStripeRendererAOld(int steps = 16) : m_iBoatcols(0), m_iFrames(0), m_iSteps(steps)
    {}

    void operator()(const CCanvas* target, CCanvas* source,
            CCanvasRenderModifierData& mdata) {
        m_iFrames++;

        if(!mdata.dstRect) {
            return;
        }

        CRectangle dstRect(*mdata.dstRect);

        if(m_iFrames % 3 == 0) {
            // jitter arround
            dstRect.X() += m_iSteps / 2 - rand() % m_iSteps;
            //dstRect.X() += m_iTicks % 5;
            dstRect.Y() += m_iSteps / 2 - rand() % m_iSteps;
            //dstRect.Y() += m_iTicks % 5;
        }

        if(rand() % 12 > 9) {
            // flicker
            CColor bannercolor = CColor::White();
            source->SetTextureColorMod(bannercolor);
        }

        target->FinalRenderCopy(source->GetTexture(), &dstRect, mdata.srcRect);
        //target->RenderCopy(source->GetTexture(), mdata.srcRect, dstRect);

        // prevent rendering the target canvas again.
        mdata.isHandled = true;
    } // ()
};

/** @class CanvasStripeRendererA:
 *  Detailed description.
 *  @param source TODO
 *  @param target TODO
 *  @param dstRect TODO
 *  @param srcRect TODO
 *  @param color TODO
 */
class CanvasStripeRendererA {
    int m_iBoatcols;
    int m_iFrames;
    int m_iSteps;
    SDL_Color cmap[256];
    TTF_Font* m_pDebugFont;
    DebugOverlay* m_pDovl;
    boost::shared_ptr<controls::CLabel> label1;
    int label2;
    int label3;
    int label4;
    int label5;
    int label6;
    CCoordSystem cs;
    static int renderNum;

public:

    // this little bastard should render colored stripes when ready.
    explicit CanvasStripeRendererA(FileLoader& loader, int steps = 16, TTF_Font* debugFont = NULL, DebugOverlay* debug_overlay = NULL)
        : m_iBoatcols(0), m_iFrames(0), m_iSteps(steps), m_pDebugFont(debugFont), m_pDovl(debug_overlay),
        label1(nullptr), label2(0), label3(0), label4(0), cs("Coords", 400, 400, CPoint(100, 100)) {
        renderNum++;
        if(debug_overlay && debugFont) {
            /*if (!controls::CLabel::GetLabelFont())
               {
                controls::CLabel::SetLabelFont(debugFont);
               }*/
            cs.SetLoader(&loader);

            // manual label creation
            label1.reset(new controls::CLabel(debug_overlay, CRectangle(0, 0, -1, -1), 123, "Label 1", debugFont,
                            true, CColor::Black(), CColor::White()));
            Uint16 height = label1->GetHeight();
            label1->SetPosition(CPoint(600, height / 2));
            m_pDovl->AddChild(label1.get());

            // automatic labels
            label2 = m_pDovl->AddTextLabel();
            label3 = m_pDovl->AddTextLabel();
            label4 = m_pDovl->AddTextLabel();
            label5 = m_pDovl->AddTextLabel();
            label6 = m_pDovl->AddTextLabel();
        }
    }

    ~CanvasStripeRendererA() {
    }

    static void Render(CCanvas* source, const CCanvas* target,
            const CRectangle& dstRect, const CRectangle& srcRect, const CColor& color) {
        source->SetTextureColorMod(color);
        target->FinalRenderCopy(source->GetTexture(), &dstRect, &srcRect);
    }

    template<typename T>
    void PrintLabel(const int& id, const char* title, const T& degrees) const {
        if(id) {
            std::ostringstream labelText;
            labelText << "{" << renderNum << "}" << title << "(" << degrees << ")";
            m_pDovl->SetTextLabelText(id, labelText.str());
        }
    }

    float norm(float ceiling, float floor, float max, float min, float input) {
        return 1.0f;
    }

    void operator()(const CCanvas* target, CCanvas* source,
            CCanvasRenderModifierData& mdata) {
        m_iFrames++;

        if(!mdata.dstRect) {
            return;
        }

        CRectangle dstRect(*mdata.dstRect);
        CRectangle srcRect(source->GetDimension());

        CColor color1 = CColor::White();
        //CColor color1 = CColor::Red();
        CColor color2 = CColor::Green();

        /*if (m_iTicks % 16 > 8)
           {
            color1 = CColor::Green();
            color2 = CColor::Red();
           }*/

        const int stepsize = 16;
        const int colorstep = 256 / stepsize;
        srcRect.H() /= stepsize;
        dstRect.H() /= stepsize;

        int rdegrees = (m_iFrames % 360);
        int degrees = (m_iFrames * 8 % 360);
        const float PI = 3.14159265f;
        float radians = degrees * PI / 180.0f;
        float clock = degrees / PI;
        int corrector = static_cast<int>(64 + sin(radians) * 64);
        int stepcheck = static_cast<int>(stepsize + sin(((m_iFrames * 2 % 180) + 180) * PI / 180.0f) * stepsize);

        /*if (m_pDebugFont)
           {
            std::ostringstream labelText;
            //labelText << "deg(" << diffx << ", " << diffy << ")";
            labelText << "deg(" << degrees << ")";
            CText label(m_pDebugFont, (labelText.str()), CColor::DarkRed());
            label.RenderPut(source, CRectangle(20,100,0,0));
           }*/

        if(label1) {
            std::ostringstream labelText;
            labelText << "rad(" << radians << ")";
            label1->SetCaption(labelText.str());
        }

        PrintLabel(label2, "rad", radians);
        PrintLabel(label3, "deg", degrees);
        PrintLabel(label4, "clock", clock);

        // CCoordSystem ?
        target->SetRenderDrawBlendMode(BLENDMODE_NONE);
        CColor color = CColor::LightGreen();
        //target->RenderDrawLine(CPoint(20, 100 + degrees), CPoint(220, 100 + degrees), &color);
        SLine::RenderDrawLine(target, CPoint(20, 100 + degrees), CPoint(220, 100 + degrees), &color);
        target->SetRenderDrawBlendMode(BLENDMODE_MOD);
        CRectangle rect = CRectangle(20, 100 + degrees, 100, 20);
        target->RenderFillRect(rect, &color);
        target->SetRenderDrawBlendMode(BLENDMODE_NONE);

        if(rdegrees == 0) {
            //cs.Reset();
        }

        for(int i = 0; i < stepsize; i++)
        {
            //int newColor = (colorstep * ((i * 8 + -m_iTicks / colorstep) % stepsize)) % 255;
            int newColorStep = (colorstep / 2 * i) + 1;
            int newColor = corrector + newColorStep;
            newColor = newColor > 255 ? 255 : newColor;
            newColor = newColor < 0 ? 0 : newColor;

            int newGreen = 25;

            //if ((m_iTicks % (i + 1)) > stepsize / 2)
            if(stepcheck == i) {
                newGreen ^= m_iFrames;
            }

            color2 = CColor(newColor, newGreen, 25);

            //CRectangle src_rect(*mdata.srcRect);
            Render(source, target, dstRect, srcRect, color2);
            srcRect.Y() += srcRect.H();
            dstRect.Y() += dstRect.H();
        }
        cs.AddDatapoint(CPoint(degrees, corrector));
        PrintLabel(label5, "Datapoints", cs.NumDatapoints());

        //cs.AddDatapoint(CPoint(rdegrees, rdegrees));
        //cs.AddDatapoint(CPoint(degrees, stepcheck));
        cs.RenderPut(target);

        //srcRect.Y() += srcRect.H();
        //dstRect.Y() += dstRect.H();
        //Render(source, target, dstRect, srcRect, color2);

        // prevent rendering the target canvas again.
        mdata.isHandled = true;
    } // ()
};

int CanvasStripeRendererA::renderNum = 0;

/*GroupId ScrollerLevelA::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/

using controls::CControl;

//gui::controls::CButton* testbutton;
CRectangle hitTestRect(200, 200, 300, 300);

namespace hspriv {
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
    }     // ()
};

/** @class LaserMover:
 *  Detailed description.
 *  @param m_p_overlay TODO
 */
class LaserMover {
    int h_;
    bool toggle_;
    int deltaX_;
    uint32_t sproffs;
    uint32_t sproffsAct;
    //int rnd;
    CPoint lastSpritePos;
    DebugOverlay* m_pOverlay;
    CCanvas* m_pBackground;

public:

    LaserMover(CCanvas* background, int deltaY = 0, uint32_t spriteoffset = 11) : h_(-1),
        toggle_(false),
        deltaX_(deltaY),
        sproffs(spriteoffset), sproffsAct(0), m_pOverlay(nullptr), m_pBackground(background) {
        dbgOut(__FUNCTION__ << " created:" << " (" << this << ")");
        int rnd = 180 - (rand() % 360);
        h_ = rnd;
    }

    ~LaserMover() {
        dbgOut(__FUNCTION__ << " " << this);
    }

    void SetDebugOverlay(DebugOverlay* m_p_overlay) {
        m_pOverlay = m_p_overlay;
    }

    void IncrementOffset() { sproffsAct++; }

    void DecrementOffset() { sproffsAct--; }

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

        //sprite->SetPosition(CPoint(100 + ((ticks % 128) * 6), 460 + h_ + deltaX_ + ssin));
        //sprite->SetPosition(CPoint(130 + ssin, deltaX_ - scos));
        sprite->SetPosition(CPoint(deltaX_, 130 + ssin));
        //sprite->SetPosition(CPoint(deltaX_, 130));
        int delta = lastSpritePos.Distance(sprite->GetPosition());
        float angle = lastSpritePos.Angle(sprite->GetPosition());
        //sproffsAct = 2;
        /*if (delta > 4) {
            if (angle <= 0) {
                sproffsAct = 2;
            }
            else if (angle > 0) {
                sproffsAct = 1;
            }
           }*/

        //sprite->SetSpriteOffset(ticks % sproffs);
        uint32_t offset = sproffsAct % sproffs;
        sprite->SetSpriteOffset(offset);

        CRectangle sdl_rect = sprite->SprImage()->DstRect();
        //m_pBackground->RenderDrawRect(sdl_rect, &sprColor);
        CColor sprColor = CColor::White();
        m_pBackground->RenderFillRect(CRectangle(100, 100, 200, 200), &sprColor);

        if(m_pOverlay) {
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
    }     // ()
};

/** @class SaucerMover:
 *  Detailed description.
 *  @return TODO
 */
class SaucerMover {
    int deltaX_;
    uint32_t sproffs;
    CPoint lastSpritePos;
    int m_iTicks;
    Timing timing;
    DebugOverlay* m_pOverlay;
    CCanvas* m_pBackground;

    int MITicks() const { return m_iTicks; }

public:

    SaucerMover(CCanvas* background, int deltaY = 0, uint32_t spriteoffset = 70) :
        deltaX_(deltaY), sproffs(spriteoffset),
        timing(boost::bind(&SaucerMover::MITicks, boost::ref(*this))), m_pOverlay(nullptr), m_pBackground(background) {
        dbgOut(__FUNCTION__ << " created:" << " (" << this << ")");
    }

    ~SaucerMover() {
        dbgOut(__FUNCTION__ << " " << this);
    }

    void SetDebugOverlay(DebugOverlay* m_p_overlay) {
        m_pOverlay = m_p_overlay;
    }

    void operator()(CSprite* sprite, int ticks, CSpriteModifierData& mdata) {
        m_iTicks = ticks;

        sprite->SetPosition(CPoint(deltaX_, 130));
        int delta = lastSpritePos.Distance(sprite->GetPosition());
        float angle = lastSpritePos.Angle(sprite->GetPosition());

        static EaseNone easeNone(2);
        static RingBounce easeRingBounce(2);
        static EaseInOutBounce easeInOutBounce(1);
        static EaseInOutQuad easeInOutQuad;
        static EaseInOutQuart easeInOutQuart;
        //static Ring ring(FRAMESPERSECOND * 32);
        static Ring ring(8.0f);

        //int ring0 = ring.Timed(ticks);
        int ring1 = ring(ticks);

        // -static_cast<int>(sproffs),

//        // ring mod via functor and loop parameter.
//        float t1 =
//            Timing::RangeMappedSinceStart(ticks / static_cast<float>(gui::FRAMESPERSECOND), 0,
// sproffs, 3.25f, boost::ref(
//                            easeRingBounce), true);

//        // stops at sproffs, no looping.
//        float t1 = Timing::RangeMappedSinceStart(ticks / static_cast<float>(gui::FRAMESPERSECOND),
// 0, sproffs,
//                ring.RingSeconds(), boost::ref(easeNone), false);

//        // ring via operator() -> int.
//        float t1 = Timing::RangeMappedSinceStart(ring(ticks) /
// static_cast<float>(gui::FRAMESPERSECOND), 0, sproffs,
//                ring.RingSeconds(), boost::ref(easeNone));

        // ring via Timed() -> seconds. added easing.
        //float t1 = Timing::RangeMappedSinceStart(ring.Timed(ticks), 0, sproffs,
        // ring.RingSeconds(), boost::ref(easeInOutQuart));
        float t1 =
            Timing::RangeMappedSinceStart(ring.Timed(ticks), 0, static_cast<vdouble>(sproffs), ring.RingSeconds(), boost::ref(
                            easeInOutQuad));
        int offset = static_cast<int>(t1);

        sprite->SetSpriteOffset(offset);

        if(m_pOverlay) {
            std::ostringstream out6005;
            out6005 << "ticks%sproffs: (" << fmod(ticks, sproffs) << ")";
            m_pOverlay->SetTextLabelText(6005, out6005.str());

            std::ostringstream out6006;
            out6006 << "ticks: (" << ticks << ")";
            out6006 << " ring1: (" << ring1 << ")";
            m_pOverlay->SetTextLabelText(6006, out6006.str());
            //dbgOut(out6006.str());

            std::ostringstream out6007;
            out6007 << "t1: (" << t1 << ")";
            m_pOverlay->SetTextLabelText(6007, out6007.str());
            //dbgOut(out6007.str());

            std::ostringstream out6008;
            out6008 << std::setfill('0') << std::setw(3) << std::fixed << std::setprecision(3) << "t1: (" << t1 << ")";
            out6008 << " ticks: (" << ticks << ")";
            out6008 << " offset: (" << offset << ")";
            m_pOverlay->SetTextLabelText(6008, out6008.str());
            //dbgOut(out6008.str());
        }

        lastSpritePos = sprite->GetPosition();
    }     // ()
};
}

/** @class PlayerShip:
 *  Detailed description.
 *  @param pEvent TODO
 */
class PlayerShip : public HitHandler {
    CSprite* m_pSprShip;
    CSprite* m_pSprLaser;
    int m_iSprLaserId;
    CRectangle sprDimension;
    CRectangle mainDimension;
    boost::scoped_ptr<PlayerKeys4> m_pKeyHandler;
    boost::shared_ptr<hspriv::ShipMover> updfuncShip;
    CSpriteManager* m_pSprMgr;
    //CSpriteManager::CSpriteModifierFunc laserUpdfunc;
    CCanvas* m_pCanvas;
    FileLoader& m_Loader;
    DebugOverlay* m_pOverlay;
    float m_fFireRate;
    Timing timing;
    bool m_bFired;

public:

    PlayerShip(FileLoader& loader, CCanvas* canvas, CSpriteManager* sprMgr, DebugOverlay* dbgOverlay, seconds fireRate)
        : m_pSprMgr(sprMgr), m_pCanvas(canvas), m_Loader(loader), m_pOverlay(dbgOverlay), m_fFireRate(fireRate),
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
        updfuncShip = boost::make_shared<hspriv::ShipMover>(m_pKeyHandler.get(), delta_y);
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

    static void LaserUpdfunc(CSprite* sprite, int ticks, CSpriteModifierData& mdata) {
        int ySpeed = -16;
        sprite->SetPosition(sprite->GetPosition().Move(0, ySpeed));
        CRectangle scr(0, 0, 1024, 768);
        if(!scr.Contains(sprite->GetPosition())) {
            mdata.markedForDeletion = true;
        }
    }

    void LaserUpdfunc2(CSprite* sprite, int ticks, CSpriteModifierData& mdata) const {
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
    } // LaserUpdfunc2

    void HitBy(const CSprite& hitter, const components::CRectangle& paintHitbox, int id, const std::string& tag, CSpriteModifierData& mdata) override {
        std::ostringstream out6002;
        out6002 << "PlayerHit: (" << paintHitbox << ")";
        out6002 << " id:(" << id << ")";
        out6002 << " tag:(" << tag << ")";

        m_pOverlay->SetTextLabelText(6002, out6002.str());
    }

    void Fire() {
        if (timing.IsAfter(m_fFireRate)) {
            m_bFired = false;
            timing.Reset(0);
        }

        if (m_bFired) {
            return;
        }

        m_bFired = true;

        //CSpriteManager::CSpriteModifierFunc fnc = boost::bind(&PlayerShip::LaserUpdfunc2,
        // boost::ref(*this), _1, _2, _3);
        //m_pSprMgr->AddSprite(m_pSprLaser, boost::bind(&PlayerShip::LaserUpdfunc2,
        // boost::ref(*this), _1, _2, _3));
        CPoint pos = m_pSprShip->PaintLocation().Position(CRectangle::CompassRose::N) - m_pSprLaser->PaintDimension().Position(
                CRectangle::CompassRose::S).Up(-50);
        m_pSprMgr->AddSpriteDraw(m_iSprLaserId, pos, boost::bind(&PlayerShip::LaserUpdfunc2, boost::ref(
                                *this), _1, _2, _3), { "Enemy", "Enemy1" });
    }

    void HookEventloop(SDL_Event* pEvent) {
        m_pKeyHandler->HookEventloop(pEvent);
        if (m_pKeyHandler->IsPressed(SDLK_SPACE))
        {
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
        }     // switch
    } // HookEventloop

    void HookIdle(int ticks, float speed) const {
        m_pKeyHandler->HookIdle(ticks, speed);
    }
};

/** @class EnemyShip1Mover:
 *  Detailed description.
 *  @param hitter TODO
 *  @param paintHitbox TODO
 *  @param id TODO
 *  @param tag TODO
 */
class EnemyShip1Mover;
/** @class EnemyShip:
 *  Detailed description.
 *  @param hitter TODO
 *  @param paintHitbox TODO
 *  @param id TODO
 *  @param tag TODO
 */
class EnemyShip : public HitHandler {
    CSprite* m_pEnemy1Ship;
    CSprite* m_pSprLaser;
    int m_iSprShipId;
    int m_iSprLaserId;
    CRectangle sprDimension;
    CRectangle mainDimension;
    boost::shared_ptr<EnemyShip1Mover> updfuncShip;
    CSpriteManager* m_pSprMgr;
    CCanvas* m_pCanvas;
    DebugOverlay* m_pOverlay;
    CPoint m_pos;
    Timing timing;
    bool m_bFired;

public:

    EnemyShip(const CPoint& pos,
            CSprite* enemy1Ship,
            int sprShipId,
            CSprite* sprLaser,
            int sprLaserId,
            CCanvas* canvas,
            CSpriteManager* sprMgr,
            DebugOverlay* dbgOverlay);

    void HitBy(const CSprite& hitter, const components::CRectangle& paintHitbox, int id, const std::string& tag, CSpriteModifierData& mdata) override {
        Fire(hitter);
        if (tag == "Laser" && id > 1023)
        {
            mdata.markedForDeletion = true;
        }
    }

    void LaserUpdfunc2(CSprite* sprite, int ticks, CSpriteModifierData& mdata) const {
        // Todo: test when not const .... say when modulating the alpha
        //int ySpeed = -16;
        int ySpeed = 4;
        sprite->SetPosition(sprite->GetPosition().Move(0, ySpeed));
        CRectangle scr(0, 0, 1024, 768);

        if(mdata.isHit) {
            sprite->SetSpriteOffset(1 + ticks % 1);
        }
        else {
            sprite->SetSpriteOffset(0);
        }

        CPoint pt = sprite->PaintLocation().Position(CRectangle::CompassRose::S);
        if(!scr.Contains(pt)) {
            mdata.markedForDeletion = true;
        }
    } // LaserUpdfunc2

    void Fire(const CSprite& hitter) {
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
        CPoint pos = hitter.PaintLocation();
        m_pSprMgr->AddSpriteDraw(m_iSprLaserId, pos, boost::bind(&EnemyShip::LaserUpdfunc2, boost::ref(*this), _1, _2, _3), { "Ship" });
    } // Fire
};

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

        sprite->SetPosition(CPoint(mdata.initialpos.GetX() + deltaX_ + scos, mdata.initialpos.GetY() + ssin));
        int delta = lastSpritePos.Distance(sprite->GetPosition());
        float angle = lastSpritePos.Angle(sprite->GetPosition());

        //uint32_t offset = sproffsAct % sproffs;
        uint32_t offset = h_/4 % sproffs;
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
    }     // ()
};

EnemyShip::EnemyShip(const CPoint& pos,
        CSprite* enemy1Ship,
        int sprShipId,
        CSprite* sprLaser,
        int sprLaserId,
        CCanvas* canvas,
        CSpriteManager* sprMgr,
        DebugOverlay* dbgOverlay) : m_pEnemy1Ship(enemy1Ship), m_pSprLaser(sprLaser), m_iSprShipId(sprShipId), m_iSprLaserId(sprLaserId),
    m_pSprMgr(sprMgr), m_pCanvas(canvas), m_pOverlay(dbgOverlay), m_pos(pos),
    timing(boost::bind(&CSpriteManager::UpdateTimeFunc, boost::ref(*sprMgr))), m_bFired(false) {

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

/** @class EnemyWave:
 *  Detailed description.
 *  @param hitter TODO
 *  @param paintHitbox TODO
 *  @param id TODO
 *  @param tag TODO
 */
class EnemyWave : public HitHandler {
    CSprite* m_pSprEnemy1Ship;
    CSprite* m_pSprLaser;
    int m_iSprEnemy1ShipId;
    int m_iSprLaserId;
    CRectangle sprPaintDimension;
    CRectangle mainDimension;
    //boost::shared_ptr<EnemyShip1Mover> updfuncShip;
    CSpriteManager* m_pSprMgr;
    CCanvas* m_pCanvas;
    FileLoader& m_Loader;
    DebugOverlay* m_pOverlay;
    //boost::shared_ptr<EnemyShip> m_pEnemyShip;
    boost::ptr_vector<EnemyShip> m_pEnemyShips;

public:

    EnemyWave(FileLoader& loader, CCanvas* canvas, CSpriteManager* sprMgr, DebugOverlay* dbgOverlay)
        : m_pSprMgr(sprMgr), m_pCanvas(canvas), m_Loader(loader), m_pOverlay(dbgOverlay) {
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
        
        const int rows = 7;
        const int columns = 16;
//        const int rows = 2;
//        const int columns = 2;
        const int startPos = 32;
        CPoint pos(startPos, 128);

        //m_pEnemyShip = boost::make_shared<EnemyShip>(m_pSprEnemy1Ship, m_iSprEnemy1ShipId,
        // m_pSprLaser, m_iSprLaserId, canvas, sprMgr, dbgOverlay);
        for (size_t row = 0; row < rows; row++)
        {
            int rowNotEven = row % 1;
            pos = CPoint(startPos + rowNotEven * 32, startPos + row * 64);
            for (size_t column = 0; column < columns; column++)
            {
                m_pEnemyShips.push_back(new EnemyShip(pos, m_pSprEnemy1Ship, m_iSprEnemy1ShipId, m_pSprLaser, m_iSprLaserId, canvas, sprMgr,
                    dbgOverlay));
                pos.Move(sprPaintDimension.GetW() + sprPaintDimension.GetW() / 2, 0);
            }
        }
    }

    void HitBy(const CSprite& hitter, const components::CRectangle& paintHitbox, int id, const std::string& tag, CSpriteModifierData& mdata) override {
    }
};

struct ScrollerLevelA::ScrollerLevelAImpl {
private:

    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    int x;
    ScrollerLevelA* host;

public:

    boost::shared_ptr<hspriv::LaserMover> updfunc2;
    boost::shared_ptr<hspriv::SaucerMover> updfunc3;
    boost::shared_ptr<PlayerShip> m_pPlayerShip;
    boost::shared_ptr<EnemyWave> m_pEnemyShip;

    explicit ScrollerLevelAImpl(ScrollerLevelA* host)
        : x(0), host{host}
    {}

    void Draw() const {
        auto aaaa = host->m_pBackground->GetDimension();
    }
};

ScrollerLevelA::ScrollerLevelA(FileLoader& loader, CCanvas* background) :
    Screen(background, true),
    pimpl_(new ScrollerLevelAImpl(this)),
    m_Loader(loader),
    m_pArialfont(NULL),
    m_pScrollText(NULL),
    m_pScroller(NULL),
    m_pSprMgr(new CSpriteManager),
    m_pSeamlessImage(NULL),
    m_pKeyHandler(NULL) {
    dbgOut(__FUNCTION__ << " " << this);
}

ScrollerLevelA::~ScrollerLevelA(void) {
    delete m_pSeamlessImage;
    dbgOut(__FUNCTION__ << " " << this);
}

/** $(class), OnInit:
 *  Detailed description.
 *  @param argc TODO
 * @param argv TODO
 * @return TODO
 */
bool ScrollerLevelA::OnInit(int argc, char* argv[]) {
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    mcol = CColor::White();
    m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 30);
    /*if (!controls::CLabel::GetLabelFont())
       {
       controls::CLabel::SetLabelFont(m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 16));
       }*/

    m_pOverlay.reset(new DebugOverlay(m_Loader, NULL, 1, "ScrollerLevelA"));
    m_pOverlay->AddTextLabel();
    m_pOverlay->AddTextLabel();
    m_pOverlay->AddTextLabel();
    m_pOverlay->AddTextLabel();
    m_pOverlay->AddTextLabel();

    SDL_Surface* tmpfsurf = (m_Loader.FL_LOADIMG("Intro/TestScreenBg.png"));
    m_pBackground.reset(new CCanvas(tmpfsurf));

    m_Loader.FreeLast();

    SDL_Surface* g_pBitmapSurface = (m_Loader.FL_LOADIMG("Images/SeamlessB.png"));
    m_pSeamlessImage = new CSeamlessImage(new CCanvas(g_pBitmapSurface), true);
    m_Loader.FreeLast();
    m_pSeamlessImage->SetLoader(&m_Loader);

    // m_pBlue = new CImage(new CCanvas(fl.FL_LOADIMG("icons/blue.png")), true);
    m_pBlue.reset(new CCanvas(m_Loader.FL_LOADIMG("icons/blue.png")));

    m_pBanding1.reset(new CImage(new CCanvas(m_Loader.FL_LOADIMG("Text/ColorBandedTextWhite01.png")), true));
    m_pBanding1->Scale(0.6f);
    CanvasStripeRendererA stripeModifier(m_Loader, 16, m_pArialfont, m_pOverlay.get());
    m_pBanding1->GetCanvas()->AddModifier(stripeModifier);

    m_pBanding2.reset(new CImage(new CCanvas(m_Loader.FL_LOADIMG("Text/ColorBandedTextWhite01.png")), true));
    m_pBanding2->GetCanvas()->AddModifier(stripeModifier);
    FadeInOutRenderer fadeRenderer(this, 3.0f, FadeInOutRenderer::FadeMode::FadeIn);
    m_pBanding2->GetCanvas()->AddModifier(fadeRenderer);

    CColor m_colText = CColor::White();
    std::ostringstream outstring;
    outstring << "Bla fasel:" << CApplication::ShownFrames();
    outstring << " ";

    //std::string pstr;
    outstring <<
        "The Test Level! \n"
              <<
        "declared in class " <<
        "'boost::noncopyable_::noncopyable'" << "\t" <<
        "d:/e/projects/c++/humbug/projects/humbug/src/gui/visual/Hookable.h" <<
        "\t" << "48" << "\t" << "Humbug" << "\r\n" <<
        "\r\n" <<
        "Error" << "\t" << "3" << "\t" <<
        "error C2248: 'boost::scoped_ptr<T>::scoped_ptr' : cannot access private member declared in "
              <<
        "class " <<
        "'boost::scoped_ptr<T>'" << "\t" <<
        "d:/e/projects/c++/humbug/projects/humbug/src/gui/visual/Hookable.h" << "\t" << "48" << "\t" <<
        "Humbug" << "\r\n" <<
        "";

    m_pScrollText.reset(new CText(m_pArialfont, outstring.str(), m_colText));

    pimpl_->m_pPlayerShip = boost::make_shared<PlayerShip>(m_Loader, m_pMainCanvas, m_pSprMgr.get(), m_pOverlay.get(), 0.25f);
    pimpl_->m_pEnemyShip = boost::make_shared<EnemyWave>(m_Loader, m_pMainCanvas, m_pSprMgr.get(), m_pOverlay.get());

    /*CSprite* m_pSprLaser =
        new CSprite(m_Loader, "Sprites/Ship/Laser/Laser01.png", m_pMainCanvas, CPoint(49, 480));
       int offsetW = m_pMainCanvas->GetWidth() / 2 - m_pSprLaser->SprImage()->DstRect().GetW() / 2;
       pimpl_->updfunc2 = boost::make_shared<hspriv::LaserMover>(m_pBackground.get(), offsetW);
       pimpl_->updfunc2->SetDebugOverlay(m_pOverlay.get());
       m_pSprMgr->AddSprite(m_pSprLaser, "mytag", boost::ref(*pimpl_->updfunc2));*/

    CSprite* m_pSprSaucer = new CSprite(m_Loader, "Sprites/Ship/Saucer02.png", m_pMainCanvas, CPoint(256, 256));
    //m_pSprSaucer->SprImage()->Scale(0.5);
    int offsetW = m_pMainCanvas->GetWidth() / 2 - m_pSprSaucer->SprImage()->DstRect().GetW() / 2;
    offsetW += 300;
    pimpl_->updfunc3 = boost::make_shared<hspriv::SaucerMover>(m_pBackground.get(), offsetW, 90);
    pimpl_->updfunc3->SetDebugOverlay(m_pOverlay.get());
    m_pSprMgr->AddSprite(m_pSprSaucer, "Enemy1", boost::ref(*pimpl_->updfunc3), pimpl_->m_pEnemyShip.get());

    return Screen::OnInit(argc, argv);

    //return true;
}     // OnInit

/** $(class), OnIdle:
 *  Detailed description.
 *  @param ticks TODO
 * @return TODO
 */
void ScrollerLevelA::OnIdle(int ticks) {
    m_iTicks = ticks;
    m_pOverlay->IdleSetVars(ticks);
    //m_pKeyHandler->HookIdle(ticks, 1.0f);
    pimpl_->m_pPlayerShip->HookIdle(ticks, 1.0f);
    //m_pScroller->Scroll(4);
    m_pSprMgr->OnIdle(ticks);
}

/** $(class), OnDraw:
 *  Detailed description.
 *  @return TODO
 */
void ScrollerLevelA::OnDraw() {
    static int coldelta = 0;

    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    m_pMainCanvas->Lock();
    //m_pMainCanvas->MainRenderClear();

    // m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), *m_pBackground,
    // m_pBackground->GetDimension());
    m_pBackground->RenderCopy();
    CRectangle frect(700, 500, 185, 185);
    static SDL_Color* wavemap = ColorData::Instance()->Wavemap();
    int index = (coldelta * 2 & 63);

    //static CPoint sp(-480, 110);
    CPoint sp(0, m_iTicks);
    //m_pSprite->SetPosition(sp);
    //m_pSprite->Draw();
    //m_pSeamlessImage->RenderPut(m_pMainCanvas, sp);
    m_pSeamlessImage->RenderPut(m_pBackground.get(), sp);
    //m_pSeamlessImage->RenderPut(m_pBackground.get(), m_pKeyHandler->Char());

    /*if ( testbutton->IsPressed() ) {
        CPoint point(-3, 0);
        sp.Subtract(point);
       }
       else {
        CPoint point(3, 0);
        sp.Subtract(point);
       }*/

    //m_pMainCanvas->AddUpdateRect( m_pSprite->SprImage()->SrcRect() );
    //m_pMainCanvas->AddUpdateRect( m_pMainCanvas->GetDimension() );

    //m_pMainCanvas->FillRect( frect, mcol );
    SDL_Color& fcol = wavemap[index];
    CColor sdl_color = CColor(fcol.r, fcol.g, fcol.b, fcol.a);
    m_pMainCanvas->RenderFillRect(frect, &sdl_color);
    //m_pMainCanvas->AddUpdateRect(frect);

    //CColor hitTestRecColor = CColor::LightMagenta();
    //m_pMainCanvas->RenderDrawRect(hitTestRect, &hitTestRecColor);

    /*static int xxx = 0;
       CRectangle dstDims( 0 + xxx, 0 + xxx, 600, 200);
       CRectangle srcDims(0 + xxx, 0, 600, 200 - xxx);
       m_pScrollText->RenderPut(m_pMainCanvas, dstDims, srcDims );
       xxx++;

       if (xxx > 128) {
        xxx = 0;
       }*/

    //testbutton->Invalidate();
    //testbutton->Draw();

    m_pBlue->SetTextureColorMod(sdl_color);
    //m_pBlue->ClearColorKey();
    CRectangle sdl_rect = CRectangle(300, 300, 256, 256);
    //m_pBlue->RenderCopy(&sdl_rect, static_cast<CRectangle*>(nullptr));
//    m_pBlue->RenderCopy(&sdl_rect);
    //CPoint point = CPoint(300, 300);
    //m_pBlue->RenderCopy(point);

    /*CColor bannercolor(sdl_color);
       bannercolor.SetR(255 - coldelta);
       m_pBanding1->RenderPut( m_pMainCanvas, CPoint(40, 550) );
       m_pBanding2->RenderPut( m_pBackground.get(), CPoint(140, 250) );*/

    pimpl_->Draw();

    coldelta++;

    if(coldelta > 64) {
        coldelta = 0;
    }

    m_pOverlay->Draw();
    m_pOverlay->SetTextLabelText(6002, "Player Idle");
    m_pSprMgr->Render();
    //m_pSprMgr->OnDraw();
    m_pMainCanvas->Unlock();
}     // OnDraw

/** $(class), OnUpdate:
 *  Detailed description.
 *  @return TODO
 */
void ScrollerLevelA::OnUpdate() {
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR(rand());
    mcol.SetG(rand());
    mcol.SetB(rand());

    /*if (testbutton->IsPressed()) {
        m_pKeyHandler->Reset();
       }*/

    //m_iUpdateTimes++;
}

void ScrollerLevelA::OnEvent(SDL_Event* pEvent) {
    //m_pKeyHandler->HookEventloop(pEvent);
    pimpl_->m_pPlayerShip->HookEventloop(pEvent);

    Screen::OnEvent(pEvent);
}

void ScrollerLevelA::OnKeyDown(SDL_Keycode sym, Uint16) {
    switch(sym) {
    case SDLK_SPACE:
    {
        //pimpl_->x = 0;
        //pimpl_->timing.Reset();
        break;
    }
    case SDLK_KP_PLUS:
    {
        pimpl_->updfunc2->IncrementOffset();
        break;
    }
    case SDLK_KP_MINUS:
    {
        pimpl_->updfunc2->DecrementOffset();
        break;
    }
    default:
        break;
    }     // switch
} // ZoomInScreen::OnKeyDown
}
}
