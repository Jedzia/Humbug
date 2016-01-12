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
        gui::components::CCanvas* m_pcnvText;
        //pressed state
        bool m_bPressed;
		//Label font
        static TTF_Font* s_LabelFont;

public:

        //construction
    CLabel(CControl* pParent, gui::components::CRectangle rcDimensions, Uint32 id, std::string sCaption, bool usesSDL2Render = false,
        gui::components::CColor colFace = CColor(192, 192, 192), CColor colText = CColor(0, 0, 0),
        CColor colHilite = CColor(255, 255, 255), CColor colShadow = CColor(128, 128, 128) );
        //destruction
        virtual ~CLabel();

		bool IsPressed() const { return m_bPressed; }

		//customize redrawing
        virtual void OnDraw();

        /*//left label handlers
        virtual bool OnLLabelDown(Uint16 x, Uint16 y);

        virtual bool OnLLabelUp(Uint16 x, Uint16 y);*/

        //set caption
        void SetCaption(std::string sCaption);

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
