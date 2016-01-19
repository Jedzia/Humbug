/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Label.h class.
 * \file       Label.h
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef LABEL_H__
#define LABEL_H__

#include "../Components/Color.h"
#include "Control.h"
#include "SDL_ttf.h"

namespace gui {
namespace controls {
/** @class CLabel:
*  abstracts a ui Label.
*/
class CLabel : public CControl {
    //caption for Label
    std::string m_sCaption;
    //colors for Label
    components::CColor m_colFace;
    components::CColor m_colText;
    components::CColor m_colHilite;
    components::CColor m_colShadow;
    //canvas for text
    boost::shared_ptr<components::CCanvas> m_pcnvText;
    //pressed state
    bool m_bPressed;
    //Label font
    TTF_Font* m_pLabelFont;

    /** CreateTextCanvas:
    *  Detailed description.
    *  @param sCaption TODO
    *  @param rcDimensions TODO
    *  @param colText TODO
    */
    components::CRectangle CreateTextCanvas(const std::string& sCaption,
            const components::CRectangle& rcDimensions,
            const components::CColor& colText);

    components::CRectangle CalculateDimensions(const std::string& sCaption,
            const components::CRectangle& rcDimensions,
            const components::CColor& colText,
            TTF_Font* labelFont) const;

public:

    /** Initializes a new instance of the <see cref="CLabel"/> class.
     *  Detailed description.
     *  @param pParent The parent control of the label.
     *  @param rcDimensions The dimensions of the label. If the width or height are lesser than 1
     *                      the size is determined via the text and the font.
     *  @param id The unique control identifier.
     *  @param sCaption The caption of the label.
     *  @param usesSDL2Render Set to true if the label should use SDL2 rendering techniques.
     *                        (Obsolete later, as this is a transition to SDL2).
     *  @param colFace The controls face color.
     *  @param colText The text color.
     *  @param colHilite The controls hilight color.
     *  @param colShadow The controls shadow color.
     */
    CLabel(CControl* pParent, components::CRectangle rcDimensions, Uint32 id, std::string sCaption, TTF_Font* labelFont,
            bool usesSDL2Render = false,
            components::CColor colFace = components::CColor(192, 192, 192), components::CColor colText = components::CColor(0, 0, 0),
            components::CColor colHilite = components::CColor(255, 255, 255), components::CColor colShadow = components::CColor(128, 128, 128));
    //destruction
    virtual ~CLabel();
    //components::CRectangle Intersects(const components::CRectangle& rcDst) override;
    CLabel(const CLabel& that) = delete;

    /** Brief description of CLabel, IsPressed
     *  Detailed description.
     *  @return TODO
     */
    bool IsPressed() const { return m_bPressed; }

    //customize redrawing
    void OnDraw() override;

    /*//left label handlers
       virtual bool OnLLabelDown(Uint16 x, Uint16 y);

       virtual bool OnLLabelUp(Uint16 x, Uint16 y);*/

    Uint16 GetWidth() override;

    Uint16 GetHeight() override;

    //set caption
    void SetCaption(const std::string& sCaption);

    //get caption
    std::string GetCaption() const;

    //set label font
    void SetLabelFont(TTF_Font* pFont);

    TTF_Font * GetLabelFont() const;

    components::CColor GetTextColor() const;
    void SetTextColor(const components::CColor color);
    //message for clicking label
    static MSGID MSGID_LabelClick;     //parm1=id
};
}   // namespace controls
} // namespace gui

#endif // #ifndef BUTTON_H__
