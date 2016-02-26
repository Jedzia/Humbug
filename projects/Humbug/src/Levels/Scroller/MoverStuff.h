#pragma once
#include "PlayerShip.h"
#include <GuiLib/GUI/Components/EasingFunctors.h>
#include <GuiLib/Timing.h>

namespace hspriv {


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

