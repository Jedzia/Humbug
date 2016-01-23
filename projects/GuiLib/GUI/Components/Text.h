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

#include "BaseDrawable.h"
#include "Color.h"
#include "Rectangle.h"
#include "SDL_ttf.h"

namespace gui {
class Hookable;
namespace components {
class CText;
class CCanvas;
struct TextAnimatorData;
class TextAnimator;

/** @class CText:
 *  Detailed description.
 */
class CText : public BaseDrawable {
public:

    /// <summary>
    /// Initializes a new instance of the <see cref="CText"/> class.
    /// </summary>
    /// <param name="font">The font.</param>
    /// <param name="text">The text.</param>
    /// <param name="textcolor">The textcolor.</param>
    /// <param name="position">The position.</param>
    CText(TTF_Font* font, std::string text, CColor textcolor = CColor::Black(), const CPoint& position = CPoint(0, 0));
    ~CText();

    // Todo: "const boost::function<void" does not work under gcc
    // typedef const boost::function<void (const CCanvas* ,const CText *text, TextAnimatorData&
    // mdata)> TextModifierFunc;
    typedef boost::function<void (const CCanvas *, CText * text, TextAnimatorData& mdata)> TextModifierFunc;

    /** Add animator function.
     *  Adds a function with the TextModifierFunc signature to the queue of this text.
     *  @param updfunc The functor with the animation code.
     */
    void AddAnimator(TextModifierFunc updfunc);

    /** Add animator object.
     *  Adds a TextAnimator to the queue of this text.
     *  @param animator The animator object.
     */
    void AddAnimator(TextAnimator* animator);

    /** Animate to position.
     *  Translate the hosting object to the specified position and with specified speed.
     *  @param destination The final point of the object to animate.
     *  @param speed The speed of the translation.
     *  @param hookable hosting object that provides access to Hookable::GetTicks() for timing
     *  purposes.
     *  @return a new TextAnimator that can be used to build a method chain initialization.
     *  (like ->MoveTo(CPoint(200, 200), 4.0f, this)->MoveTo(CPoint(300, 600), 8.0f,
     *  this)->MoveTo(CPoint(900, 40), 12.0f, this)-> ...
     */
    TextAnimator * MoveTo(CPoint point, Hookable* hookable = NULL, float speed = 1.0f, float timeIn = 1.0f, float timeOut = 1.0f);

    /** Render to canvas.
     *  Render this instance to the specified canvas. The position is specified via the
     *  SetPosition(CPoint position) method.
     *  @param canvas The render target.
     */
    void RenderPut(const CCanvas* canvas);

    /** Render to canvas.
     *  Render this instance to the specified canvas.
     *  @param canvas The render target.
     *  @param dstRect The destination dimension. The complete size of the text is taken as source.
     */
    void RenderPut(const CCanvas* canvas, const CRectangle& dstRect);

    /** Render to canvas.
     *  Render this instance to the specified canvas.
     *  @param canvas The render target.
     *  @param dstRect The destination dimension.
     *  @param srcRect The sector of the source text to render.
     */
    void RenderPut(const CCanvas* canvas, const CRectangle& dstRect, const CRectangle& srcRect);

    /** Blit to canvas.
     *  Blit this instance to the specified canvas.
     *  @param canvas The blitting target.
     *  @param dstRect The destination dimension. The complete size of the text is taken as source.
     */
    void Put(CCanvas* canvas, const CRectangle& dstRect);

    /** Blit to canvas.
     *  Blit this instance to the specified canvas.
     *  @param canvas The blitting target.
     *  @param dstRect The destination dimension.
     *  @param srcRect The sector of the source text to render.
     */
    void Put(CCanvas* canvas, const CRectangle& dstRect, const CRectangle& srcRect);

    void Dings(SDL_Color sdl_color);

    /**  Get the canvas of this instance.
     *  Gets the canvas of this text instance.
     *  @return the text canvas.
     */
    CCanvas * GetCanvas() const { return m_pText.get(); }

    /**  Get vertical expansion.
     *  Gets the vertical space of this text.
     *  @return the vertical size of the text.
     */
    CPoint VerticalSpacing() const;

    /**  Get horizontal expansion.
     *  Gets the horizontal space of this text.
     *  @return the horizontal size of the text.
     */
    CPoint HorizontalSpacing() const;

    /**  Get the text color.
     *  Retrieves the value of the current text color.
     *  @return the current value of the text color.
     */
    CColor GetColor() const { return m_colText; }

    /**  Set the text color.
     *  Sets the value of the current text color.
     *  @param textcolor The value of the text color.
     */
    void SetColor(const CColor textcolor);

    /** Get current text Position.
     *  Gets the current text position of this instance.
     *  @return the point of the text position.
     */
    CPoint GetPosition() const { return m_ptPosition; }

    /** Set text Position.
     *  Sets the text position of this instance used by RenderPut(const CCanvas* canvas).
     *  @param position The value of the text position.
     */
    void SetPosition(CPoint position) { m_ptPosition = position; }

    /**  Get the font.
     *  Gets the font used by this text instance.
     *  @return the text font.
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
    typedef std::vector<TextModifierFunc> TextModifierStorage;
    TextModifierStorage m_vecModifierVault;
    typedef boost::ptr_vector<TextAnimator> AnimatorStorage;
    AnimatorStorage m_vecAnimatorVault;
    SDL_Surface* m_pRenderText;
};

/** @class CTextParagraph:
 *  Placeholder. No function at the moment.
 */
class CTextParagraph {
public:

    CTextParagraph(TTF_Font* font, std::string text, CColor textcolor = CColor::Black());
    ~CTextParagraph();
};
} // namespace components
} // namespace gui

#endif // HUMBUG_GUI_COMPONENTS_TEXT_H
