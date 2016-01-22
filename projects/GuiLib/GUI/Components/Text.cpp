/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Text.cpp class.
 * \file       Text.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
//
#include "stdafx.h"
//
#include "Text.h"
//
#include "../../Timing.h"
#include "../Visual/Hookable.h"
#include "Canvas.h"
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

/*#include <gmtl/Matrix.h>
   #include <gmtl/Vec.h>
 #include <gmtl/gmtl.h>*/

//#include "../Data/ColorData.h"

//#include <build/cmake/include/debug.h>

namespace gui {
namespace components {
CText::CText(TTF_Font* font, std::string text, CColor textcolor, const CPoint& position) :
    m_ptPosition(position),
    m_pFont(font),
    m_strText(text),
    m_colText(textcolor) {
    //dbgOut(__FUNCTION__);
    m_pRenderText = TTF_RenderUTF8_Blended(m_pFont, m_strText.c_str(), m_colText);
    m_pText.reset(new CCanvas(m_pRenderText));
}

CText::~CText() {
    m_pFont = NULL;

    if(m_pRenderText) {
        SDL_FreeSurface(m_pRenderText);
    }

    //delete m_pText;
    //m_pText = NULL;
    //dbgOut(__FUNCTION__);
}

void CText::RenderPut(const CCanvas* canvas) {
    RenderPut(canvas, CRectangle(GetPosition(), GetCanvas()->GetDimension()), GetCanvas()->GetDimension());
}

void CText::RenderPut(const CCanvas* canvas, const CRectangle& dstRect) {
    RenderPut(canvas, dstRect, GetCanvas()->GetDimension());
}

void CText::ApplyModifiers(CRectangle& srcRect, CRectangle& dstRect) {
    m_pText->Lock();

    CTextModifierData mdata(srcRect, dstRect);

    if(!m_vecModifierVault.empty()) {
        TextModifierStorage::iterator end = m_vecModifierVault.end();

        for(TextModifierStorage::iterator it = m_vecModifierVault.begin(); it < end; ++it)
        {
            (*it)(m_pText.get(), this, mdata);
            if(mdata.markedForDeletion) {
                //m_vecModifierVault.pop_back();
                //TextModifierStorage::iterator ex;
                m_vecModifierVault.erase(it);
                mdata.markedForDeletion = false;
                // Todo: better fill a deleter list and erase after loop.
                break;
            }
        }
    }

    m_pText->Unlock();
} // CText::ApplyModifiers

void CText::ApplyAnimators(CRectangle& srcRect, CRectangle& dstRect) {
    m_pText->Lock();

    CTextModifierData mdata(srcRect, dstRect);

    if(!m_vecAnimatorVault.empty()) {
        AnimatorStorage::iterator end = m_vecAnimatorVault.end();

        for(AnimatorStorage::iterator it = m_vecAnimatorVault.begin(); it < end; ++it)
        {
            (*it)(m_pText.get(), this, mdata);
            if(mdata.markedForDeletion) {
                Animator* savedAnimator = (*it).nextAnimator;

                if(savedAnimator) {
                    //savedAnimator->x = (*it).x;
                    //savedAnimator->y = (*it).y;
                    (*it).nextAnimator = NULL;
                    m_vecAnimatorVault.erase(it);
                    mdata.markedForDeletion = false;
                    AddModifier(savedAnimator);
                    break;
                }

                m_vecAnimatorVault.erase(it);
                mdata.markedForDeletion = false;
                // Todo: better fill a deleter list and erase after loop.
                break;
            }
        }
    }

    m_pText->Unlock();
} // CText::ApplyAnimators

void CText::RenderPut(const CCanvas* canvas, const CRectangle& dstRect, const CRectangle& srcRect) {
    CRectangle dest(dstRect);
    CRectangle src(srcRect);
    dest.SetW(srcRect.GetW());
    dest.SetH(srcRect.GetH());

    ApplyModifiers(src, dest);
    ApplyAnimators(src, dest);

    m_pText->RenderCopy(&src, &dest);
}

void CText::Put(CCanvas* canvas, const CRectangle& dstRect, const CRectangle& srcRect) {
    CRectangle dest(dstRect);
    CRectangle src(srcRect);
    ApplyModifiers(src, dest);
    ApplyAnimators(src, dest);

    canvas->Blit(dest, *m_pText, src);
    canvas->AddUpdateRect(dest);
}     // CText::Put

void CText::Put(CCanvas* canvas, const CRectangle& dstRect) {
    Put(canvas, dstRect, GetCanvas()->GetDimension());
}

void CText::Dings(SDL_Color sdl_color)
{}

CPoint CText::VerticalSpacing() const {
    return CPoint(0, GetCanvas()->GetDimension().GetH());
}

CPoint CText::HorizontalSpacing() const {
    return CPoint(GetCanvas()->GetDimension().GetW(), 0);
}

void CText::SetColor(const CColor textcolor) {
    //return;
    if(m_pRenderText) {
        SDL_FreeSurface(m_pRenderText);
    }

    //if (m_pText) {
    //    delete m_pText;
    // }

    m_colText = textcolor;
    SDL_Color color = { 0, 0, 0 }, bgcolor = { 0xff, 0xff, 0xff };
    //m_pRenderText = TTF_RenderText_Solid(m_pFont, m_strText.c_str(), m_colText);
    m_pRenderText = TTF_RenderUTF8_Blended(m_pFont, m_strText.c_str(), m_colText);
    //m_pRenderText = TTF_RenderUTF8_Shaded(m_pFont, m_strText.c_str(), m_colText, bgcolor);
    //m_pRenderText = TTF_RenderUTF8_Shaded(m_pFont, m_strText.c_str(), m_colText, bgcolor);
    m_pText.reset(new CCanvas(m_pRenderText));
} // CText::SetColor

void CText::RunModifiers(CCanvas* textcanvas) const {
    /*return;
       SDL_Color cmap[256];
       memset(cmap, 0, sizeof(cmap));

       static int boatcols=0;
       static int frames=0;

       SDL_Color *wavemap = ColorData::Instance()->Wavemap();
       for(int i = 0; i < 64; i++)
        cmap[boatcols + ((i + frames) & 63)] = wavemap[i];

       //SDL_SetPalette(m_pText->GetSurface(), SDL_LOGPAL, wavemap, boatcols, 32);
       SDL_SetPalette(textcanvas->GetSurface(), SDL_LOGPAL, cmap, 0, 256);
       //boatcols++;
       frames++;
       if ( frames > 16   )
       {
        //frames = 0;
       }*/
}

void CText::AddModifier(TextModifier updfunc) {
    m_vecModifierVault.push_back(updfunc);
}

void CText::AddModifier(Animator* animator) {
    m_vecAnimatorVault.push_back(animator);
}

///** @class Mover:
//*  Detailed description.
//*  @param vA TODO
//*  @param vB TODO
//*  @return TODO
//*/
//class Mover {
//    CPoint destination;
//    double x;
//    double y;
//
//public:
//
//    explicit Mover(const CPoint& destination)
//        : destination{ destination }, x(0), y(0)
//    {}
//    boost::numeric::ublas::vector<double> normalizedDirection(
//        const boost::numeric::ublas::vector<double>& vA,
//        const boost::numeric::ublas::vector<double>& vB) {
//
//        //boost::numeric::ublas::vector<double> vdir = vA - vB;
//        auto vdir = vA - vB;
//        return (vdir) / norm_2(vdir) * 2.0;
//    }
//    void operator()(const CCanvas* target, CText* text, CTextModifierData& mdata) {
//        auto color = CColor::DarkGray();
//        target->RenderFillRect(CRectangle(90, 90, 33, 33), &color);
//        //mdata.dest.X()+=x;
//        //x++;
//        /*if (x == 0 && y == 0)
//        {
//        x = mdata.dest.GetX();
//        y = mdata.dest.GetY();
//        }*/
//
//        float r = 564.345f;
//        using namespace boost::math::double_constants;
//        auto xxx = pi * r * r;
//
//        using namespace boost::numeric::ublas;
//        //vector<double> v(3);
//        //for (unsigned i = 0; i < v.size(); ++i)
//        //   v(i) = i;
//
//        unit_vector<double> vUnit(2);
//        vector<double> vA(2);
//        vA[0] = destination.GetX();
//        vA[1] = destination.GetY();
//
//        vector<double> vB(2);
//        vB[0] = mdata.dest.GetX();
//        vB[1] = mdata.dest.GetY();
//
//        //auto vx = vpos + vdest;
//        //auto v2x = inner_prod(vpos, vdest);
//        //vector<double> vdir = vA - vB;
//        //double len1 = norm_2(vdir);
//        //vector<double> delta = vdir / len1;
//
//        vector<double> delta = normalizedDirection(vA, vB);
//        //vector<double> delta = normalizedDirection(vB, vA);
//
//        //vector<double> vdir2 = vpos - vdest;
//        //unit_<double> unit(2, 1);
//        //vdir2 * unit;
//        //std::ostringstream outstring1;
//        //outstring1 << "delta: " << delta << std::endl;
//
//        /* mapped_vector<double> vmap = unit_vector<double>(2, 1);
//        //vector<double> t = norm(vdir);
//        //boost::numeric::ublas::vector3 lookat;
//        using namespace gmtl;
//        Vec<double, 2> gvecA(100, 200);
//        Vec<double, 2> gvecB(300, 500);
//
//        Vec<double, 2> gresult = gvecA - gvecB;
//        double len2 = length(gresult);
//        std::ostringstream outstring2;
//        outstring2 << "gresult: " << gresult << std::endl;
//        gmtl::normalize(gresult);
//        std::ostringstream outstring3;
//        outstring3 << "norm: " << gresult << std::endl;*/
//
//        //gob::GVector2d vec;
//        //int cx = round(x);
//        //int cy = round(y);
//        int cx = x;
//        int cy = y;
//
//        if (mdata.dest.GetX() + cx <= destination.GetX() - delta[0]) {
//            x += delta[0];
//        }
//        else if (mdata.dest.GetX() + cx >= destination.GetX() + delta[0]) {
//            x -= delta[0];
//        }
//
//        if (mdata.dest.GetY() - cy <= destination.GetY() + delta[1]) {
//            y += delta[1];
//        }
//        else if (mdata.dest.GetY() - cy >= destination.GetY() - delta[1]) {
//            y -= delta[1];
//        }
//
//        mdata.dest.X() += ceil(x);
//        mdata.dest.Y() -= ceil(y);
//    } // ()
//};
using namespace boost::numeric::ublas;

/** @class SinusoidWobbler:
 *  Detailed description.
 *  @param hookable TODO
 *  @return TODO
 */
class SinusoidWobbler {
};

/** @class Mover2:
 *  Detailed description.
 *  @param vA TODO
 *  @param vB TODO
 *  @return TODO
 */
class Mover2 : public Animator {
    CPoint destination;
    Hookable* hookable;
    Timing timingStart;
    Timing timingEnd;

    static Timing::UpdateTimeFunc GetTimeUpdateFunction(const Hookable* hookable) {
        if(!hookable) {
            return NULL;
        }

        return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
    }

public:

    explicit Mover2(const CPoint& destination, Hookable* hookable)
        : destination(destination), hookable(hookable), timingStart(GetTimeUpdateFunction(hookable)),
        timingEnd(GetTimeUpdateFunction(hookable)) {
    }

    ~Mover2() {
        int ix = 0;
        ix++;
    }

    static vector<double> normalizedDirection(
            const vector<double>& vA,
            const vector<double>& vB, double speed) {
        auto vdir = vA - vB;
        return (vdir) / norm_2(vdir) * speed;
    }

    void operator()(const CCanvas* target, CText* text, CTextModifierData& mdata) override {
        using namespace boost::numeric::ublas;
        auto color = CColor::DarkGray();
        target->RenderFillRect(CRectangle(90, 90, 33, 33), &color);

        const double speed = 8.0f;

        if(nextAnimator) {
            int r = 0;
            r++;
        }

        if(hookable) {
            int ticks = hookable->GetTicks();
            //timingStart.UpdateIdle(ticks);

            color.SetR(0xa0 | ticks % 255);
            color.SetG(0x5f & ticks % 255);
            color.SetB(ticks % 255);
            text->SetColor(color);

            if(timingStart.IsBefore(1.0f)) {
                mdata.dest.X() += static_cast<int>(ceil(x));
                mdata.dest.Y() -= static_cast<int>(ceil(y));
                return;
            }
        }

        //float r = 564.345f;
        //using namespace boost::math::double_constants;
        //auto xxx = pi * r * r;

        unit_vector<double> vUnit((2));
        vector<double> vA(destination);
        CPoint dest(static_cast<int>(mdata.dest.GetX() + x), static_cast<int>(mdata.dest.GetY() - y));
        vector<double> vB(dest);
        //vector<double> vB(static_cast<CPoint>(mdata.dest));
        vector<double> vresult = normalizedDirection(vA, vB, speed);

        if(mdata.dest.GetX() + x < destination.GetX() - vresult[0]) {
            x += vresult[0];
        }
        else if(mdata.dest.GetX() + x > destination.GetX() + vresult[0]) {
            x -= vresult[0];
        }

        if(mdata.dest.GetY() - y < destination.GetY() + vresult[1]) {
            y += vresult[1];
        }
        else if(mdata.dest.GetY() - y > destination.GetY() - vresult[1]) {
            y -= vresult[1];
        }

        /*CPoint actual3 = CPoint(mdata.dest.GetX() + x + 0, mdata.dest.GetY() - y - 0);
           CPoint actual2 = CPoint(mdata.dest.GetX() + x + 0, mdata.dest.GetY() - y - 1);
           CPoint actual4 = CPoint(mdata.dest.GetX() + x + 1, mdata.dest.GetY() - y - 0);
           CPoint actual = CPoint(mdata.dest.GetX() + x + 1, mdata.dest.GetY() - y - 1);*/

        const int speedInt = static_cast<int>(speed);
        bool xcomp = mdata.dest.GetX() + x - speedInt<destination.GetX() && mdata.dest.GetX() + x + speedInt> destination.GetX();
        bool ycomp = mdata.dest.GetY() - y - speedInt<destination.GetY() && mdata.dest.GetY() - y + speedInt> destination.GetY();

        if(xcomp && ycomp) {
            //if (actual == destination || actual2 == destination || actual3 == destination ||
            // actual4 == destination) {
            if(hookable) {
                /*if (!timingStart)
                   {
                   //timingEnd.UpdateIdle(hookable->GetTicks());
                   }*/

                mdata.dest.X() += static_cast<int>(ceil(x));
                mdata.dest.Y() -= static_cast<int>(ceil(y));

                if(timingEnd.IsBefore(1.0f)) {
                    return;
                }
            }

            mdata.state++;
            mdata.markedForDeletion = true;
        }

        mdata.dest.X() += static_cast<int>(round(x));
        mdata.dest.Y() -= static_cast<int>(round(y));
    } // ()
};

#define DEBUGPRINT 1
typedef float vdouble;
//typedef int vdouble;
/** @class TextMover:
 *  Detailed description.
 *  @param vA TODO
 *  @param vB TODO
 *  @return TODO
 */
class TextMover : public Animator {
    vector<vdouble> origin;
    vector<vdouble> destination;
    vdouble speed;
    Hookable* hookable;
    Timing timingStart;
    Timing timingEnd;
    bool hasFirstRun;
    bool destinationReached;
    vector<vdouble> current;
    vector<vdouble> delta;

    static Timing::UpdateTimeFunc GetTimeUpdateFunction(const Hookable* hookable) {
        if(!hookable) {
            return NULL;
        }

        return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
    }

public:

    explicit TextMover(const CPoint& destination, float speed, Hookable* hookable)
        : destination(destination), speed(static_cast<vdouble>(speed)), hookable(hookable), timingStart(GetTimeUpdateFunction(hookable)),
        timingEnd(GetTimeUpdateFunction(hookable)), hasFirstRun(false), destinationReached(false) {
    }

    ~TextMover() {
    }

    static vector<vdouble> normalizedDirection(const vector<vdouble>& vA, const vector<vdouble>& vB, vdouble speed) {
        auto vdir = vA - vB;
        return ((vdir) / (round(norm_2(vdir / speed))));
    }

    static vector<vdouble> direction(
            vector<vdouble> vA,
            vector<vdouble> vB, vdouble speed) {
        auto vdir = vA - vB;
        return vdir / speed / static_cast<vdouble>(8.0);
    }

    static bool CompareWithTolerance(vector<vdouble> cur, vector<vdouble> des, const vdouble tolerance) {
        bool xcomp = cur[0] - tolerance < des[0] && cur[0] + tolerance > des[0];
        bool ycomp = cur[1] - tolerance < des[1] && cur[1] + tolerance > des[1];
        return xcomp || ycomp;
    }

    void operator()(const CCanvas* target, CText* text, CTextModifierData& mdata) override {
        using namespace boost::numeric::ublas;
        auto color = CColor::DarkGray();
        target->RenderFillRect(CRectangle(CPoint(destination), CPoint(33, 33)), &color);

        if(!hasFirstRun) {
            origin = text->GetPosition();
            current = text->GetPosition();
            delta = normalizedDirection(destination, origin, speed);
            //delta = direction(destination, origin, speed);
            hasFirstRun = true;
        }

        if(hookable) {
            int ticks = hookable->GetTicks();

            color.SetR(0xa0 | ticks % 255);
            color.SetG(0x5f & ticks % 255);
            color.SetB(ticks % 255);
            text->SetColor(color);

            if(timingStart.IsBefore(1.0f)) {
                return;
            }
        }

#if DEBUGPRINT
        std::ostringstream outstring1;
        outstring1 << "delta: " << delta << std::endl;
        CPoint textPos = CPoint(400, 80);
        CText vresText1(text->GetFont(), outstring1.str(), CColor::Black(), textPos);
        vresText1.RenderPut(target);

#endif

        if(!destinationReached) {
            current += delta;
        }

#if DEBUGPRINT
        std::ostringstream outstring2;
        outstring2 << "destination: " << destination << std::endl;
        textPos += vresText1.VerticalSpacing();
        CText vresText2(text->GetFont(), outstring2.str(), CColor::Black(), textPos);
        vresText2.RenderPut(target);

        std::ostringstream outstring3;
        outstring3 << "current: " << current << std::endl;
        textPos += vresText2.VerticalSpacing();
        CText vresText3(text->GetFont(), outstring3.str(), CColor::Black(), textPos);
        vresText3.RenderPut(target);
#endif // if DEBUGPRINT

        text->SetPosition(CPoint(current));

        const vdouble tolerance = static_cast<vdouble>(0.02);
        if(CompareWithTolerance(current, destination, tolerance)) {
            destinationReached = true;

            if(hookable && timingEnd.IsBefore(2.0f)) {
                return;
            }

            mdata.state++;
            mdata.markedForDeletion = true;
        }
    } // ()
};

Animator * CText::FlyTo(CPoint c_point, float speed, Hookable* hookable) {
    //auto bla = *this;
    //AddModifier(NULL);
    //return NULL;
    //TextMover mover(c_point, hookable);
    auto mover = new TextMover(c_point, speed, hookable);

    //GetCanvas()->AddModifier(mover);
    AddModifier(mover);
    return mover;
}

Animator * Animator::FlyTo(CPoint c_point, float speed, Hookable* hookable) {
    //TextMover mover(c_point, hookable);
    auto mover = new TextMover(c_point, speed, hookable);
    nextAnimator = mover;
    return mover;
}

CTextParagraph::CTextParagraph(TTF_Font* font, std::string text, CColor textcolor)
{}

CTextParagraph::~CTextParagraph()
{}
}   // namespace components
} // namespace gui
