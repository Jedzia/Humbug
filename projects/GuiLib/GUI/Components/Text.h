/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Text.h class.
 * \file       Text.h
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_GUI_COMPONENTS_TEXT_H
#define HUMBUG_GUI_COMPONENTS_TEXT_H

#include "Color.h"
#include "Rectangle.h"
#include "SDL_ttf.h"

namespace gui {
class Hookable;
namespace components {
class CText;
class CCanvas;

struct CTextModifierData
{
    int DeltaX;
    int DeltaY;
    CRectangle& src;
    CRectangle& dest;
    Hookable* hookable;
    bool markedForDeletion;
    int state;

    CTextModifierData(CRectangle& src_rect, CRectangle& dst_rect)
        : DeltaX(0), DeltaY(0), src{src_rect}, dest{dst_rect}, hookable(nullptr), markedForDeletion(false), state(1)
    {}
};

/** @class Animator:
 *  Detailed description.
 *  @param target TODO
 *  @param text TODO
 *  @param mdata TODO
 *  @return TODO
 */
class Animator {
public:

    explicit Animator() : nextAnimator(nullptr), x(0), y(0)
    {}

    virtual ~Animator(){
        if(nextAnimator) {
            delete nextAnimator;
        }
    }

    virtual void operator()(const CCanvas* target, CText* text, CTextModifierData& mdata) = 0;

    Animator* nextAnimator;
    Animator * FlyTo(CPoint c_point, float speed = 1.0f, Hookable* hookable = NULL);

    double x;
    double y;
};

/** @class CText:
 *  Detailed description.
 *  @param updfunc TODO
 */
class CText {
public:

    CText(TTF_Font* font, std::string text, CColor textcolor = CColor::Black(), const CPoint& position = CPoint(0, 0));
    ~CText();

    // Todo: "const boost::function<void" does not work under gcc
    // typedef const boost::function<void (const CCanvas* ,const CText *text, CTextModifierData&
    // mdata)> TextModifier;
    typedef boost::function<void (const CCanvas *, CText * text, CTextModifierData& mdata)> TextModifier;
    //typedef const boost::function<void(CCanvas*, int)> TextModifierPtr;
    void AddModifier(TextModifier updfunc);

    void AddModifier(Animator* animator);

    Animator * FlyTo(CPoint c_point, float speed = 1.0f, Hookable* hookable = NULL);

    // render, the only one that takes the position into account.
    void RenderPut(const CCanvas* canvas);

    void RenderPut(const CCanvas* canvas, const CRectangle& dstRect);

    void RenderPut(const CCanvas* canvas, const CRectangle& dstRect, const CRectangle& srcRect);

    void Put(CCanvas* canvas, const CRectangle& dstRect);

    void Put(CCanvas* canvas, const CRectangle& dstRect, const CRectangle& srcRect);

    void Dings(SDL_Color sdl_color);

    /** Brief description of CText, GetCanvas
     *  Detailed description.
     *  @return TODO
     */
    CCanvas * GetCanvas() const { return m_pText.get(); }

    CPoint VerticalSpacing() const;

    CPoint HorizontalSpacing() const;

    /** Brief description of CText, Color
     *  Detailed description.
     *  @return TODO
     */
    CColor Color() const { return m_colText; }

    void SetColor(const CColor m_col_text);

    /** Brief description of CText, GetPosition
     *  Detailed description.
     *  @return TODO
     */
    CPoint GetPosition() const { return m_ptPosition; }

    /** Brief description of CText, SetPosition
     *  Detailed description.
     *  @param position TODO
     */
    void SetPosition(CPoint position) { m_ptPosition = position; }

    /** Brief description of CText, GetFont
     *  Detailed description.
     *  @return TODO
     */
    TTF_Font * GetFont() const { return m_pFont; }

private:

    void ApplyModifiers(CRectangle& srcRect, CRectangle& dstRect);

    void ApplyAnimators(CRectangle& srcRect, CRectangle& dstRect);

    void RunModifiers(CCanvas* textcanvas) const;

    CPoint m_ptPosition;
    TTF_Font* m_pFont;
    std::string m_strText;
    CColor m_colText;
    //CCanvas *m_pText;
    boost::scoped_ptr<CCanvas> m_pText;
    typedef std::vector<TextModifier> TextModifierStorage;
    TextModifierStorage m_vecModifierVault;
    typedef boost::ptr_vector<Animator> AnimatorStorage;
    AnimatorStorage m_vecAnimatorVault;
    SDL_Surface* m_pRenderText;
};

/** @class CTextParagraph:
 *  Detailed description.
 *  $(javaparam)
 */
class CTextParagraph {
public:

    CTextParagraph(TTF_Font* font, std::string text, CColor textcolor = CColor::Black());
    ~CTextParagraph();
};
} // namespace components
} // namespace gui

#endif // HUMBUG_GUI_COMPONENTS_TEXT_H
