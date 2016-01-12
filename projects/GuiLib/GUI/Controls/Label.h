/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Label.h class.
 * \folder     $(folder)
 * \file       Label.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef LABEL_H__
#define LABEL_H__

#include "../Components/Color.h"
#include "Control.h"
#include "SDL_ttf.h"
#include <string>

namespace gui {
    class GuiFontMetrics;
    namespace controls {
    using gui::components::CColor;
//CLabel class
//abstracts a ui Label
    class CLabel : public CControl {
private:

        //caption for Label
        std::string m_sCaption;
        //colors for Label
        CColor m_colFace;
        CColor m_colText;
        CColor m_colHilite;
        CColor m_colShadow;
        //canvas for text
        boost::shared_ptr<components::CCanvas> m_pcnvText;
        //pressed state
        bool m_bPressed;
		//Label font
        static TTF_Font* s_LabelFont;
        static GuiFontMetrics* s_FontMetrics;

        components::CRectangle CreateTextCanvas(const std::string& sCaption, const gui::components::CRectangle& rcDimensions, const gui::components::CColor& colText);
        static components::CRectangle CalculateDimensions(const std::string& sCaption, const gui::components::CRectangle& rcDimensions, const gui::components::CColor& colText);
    public:

        /** Initializes a new instance of the <see cref="CLabel"/> class.
        *  Detailed description.
        *  @param pParent The parent control of the label.
        *  @param rcDimensions The dimensions of the label. If the width or height are lesser than 1 the size is determined via the text
        *                      and the font.
        *  @param id The unique control identifier.
        *  @param sCaption The caption of the label.
        *  @param usesSDL2Render Set to true if the label should use SDL2 rendering techniques. (Obsolete later, as this is a transition to SDL2).
        *  @param colFace The controls face color.
        *  @param colText The text color.
        *  @param colHilite The controls hilight color.
        *  @param colShadow The controls shadow color.
        */
        CLabel(CControl* pParent, gui::components::CRectangle rcDimensions, Uint32 id, std::string sCaption, bool usesSDL2Render = false,
        gui::components::CColor colFace = CColor(192, 192, 192), CColor colText = CColor(0, 0, 0),
        CColor colHilite = CColor(255, 255, 255), CColor colShadow = CColor(128, 128, 128) );
        //destruction
        virtual ~CLabel();

        CLabel(const CLabel& that) = delete;

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
        std::string GetCaption();

        //set label font
        static void SetLabelFont(TTF_Font* pFont);

        static TTF_Font * GetLabelFont();

        //message for clicking label
        static MSGID MSGID_LabelClick; //parm1=id
    };
  } // namespace controls
} // namespace gui

#endif // #ifndef BUTTON_H__
