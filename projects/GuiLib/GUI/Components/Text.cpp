/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
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
#include "../../stdafx.h"
//
#include "Text.h"
//
#include "../Visual/Hookable.h"
#include "Canvas.h"
#include "TextAnimator.h"
#include "TextAnimatorImpl.h"

/*#include <gmtl/Matrix.h>
   #include <gmtl/Vec.h>
 #include <gmtl/gmtl.h>*/

//#include "../Data/ColorData.h"

//#include <build/cmake/include/debug.h>

namespace gui {
namespace components {
    CText::CText(TTF_Font* font, std::string text, CColor textcolor, const CPoint& position) : BaseDrawable(position),
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

    TextAnimatorData mdata(&srcRect, &dstRect);

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

    TextAnimatorData mdata(&srcRect, &dstRect);

    if(!m_vecAnimatorVault.empty()) {
        AnimatorStorage::iterator end = m_vecAnimatorVault.end();

        for(AnimatorStorage::iterator it = m_vecAnimatorVault.begin(); it < end; ++it)
        {
            (*it)(m_pText.get(), this, mdata);
            if(mdata.markedForDeletion) {
                TextAnimator* savedAnimator = (*it).nextAnimator;

                if(savedAnimator) {
                    //savedAnimator->x = (*it).x;
                    //savedAnimator->y = (*it).y;
                    (*it).nextAnimator = NULL;
                    m_vecAnimatorVault.erase(it);
                    mdata.markedForDeletion = false;
                    AddAnimator(savedAnimator);
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

    m_pText->RenderCopy(&dest, &src);
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

void CText::AddAnimator(const TextModifierFunc& updfunc) {
    m_vecModifierVault.push_back(updfunc);
}

void CText::AddAnimator(TextAnimator* animator) {
    m_vecAnimatorVault.push_back(animator);
}

TextAnimator* CText::Wait(Hookable* hookable, Timing::seconds waitTime)
{
    auto mover = new WaitingAnimator(hookable, waitTime);
    AddAnimator(mover);
    return mover;
}

TextAnimator * CText::MoveTo(CPoint c_point, Hookable* hookable, float speed, Timing::seconds timeIn, Timing::seconds timeOut, const TimeEasingFunc& easingFunc) {
    //auto bla = *this;
    //AddAnimator(NULL);
    //return NULL;
    //TextMover mover(c_point, hookable);
    auto mover = new TextMover(c_point, hookable, speed, timeIn, timeOut, easingFunc);

    //GetCanvas()->AddAnimator(mover);
    AddAnimator(mover);
    return mover;
}

TextAnimator * CText::FadeIn(Hookable* hookable, Timing::seconds fadeInTime) {
    auto mover = new FadeInOutAnimator(hookable, fadeInTime);
    AddAnimator(mover);
    return mover;
}

TextAnimator * CText::FadeOut(Hookable* hookable, Timing::seconds fadeOutTime, bool fadeOutRemovesText) {
    auto mover = new FadeInOutAnimator(hookable, fadeOutTime, FadeInOutRenderer::FadeMode::FadeOut, fadeOutRemovesText);
    AddAnimator(mover);
    return mover;
}

CTextParagraph::CTextParagraph(TTF_Font* font, std::string text, CColor textcolor)
{}

CTextParagraph::~CTextParagraph()
{}
}   // namespace components
} // namespace gui
