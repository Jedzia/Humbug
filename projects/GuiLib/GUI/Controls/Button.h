/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Button.h class.
 * \folder     $(folder)
 * \file       Button.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef BUTTON_H__
#define BUTTON_H__

#include "../Components/Color.h"
#include "Control.h"
#include "sdl_ttf.h"
#include <string>

namespace gui {
  namespace controls {
    using gui::components::CColor;
//CButton class
//abstracts a ui button
    class CButton : public CControl {
private:

        //caption for button
        std::string m_sCaption;
        //colors for button
        CColor m_colFace;
        CColor m_colText;
        CColor m_colHilite;
        CColor m_colShadow;
        //canvas for text
        gui::components::CCanvas* m_pcnvText;
        //pressed state
        bool m_bPressed;
		//button font
        static TTF_Font* s_ButtonFont;

public:

        //construction
        CButton( CControl* pParent, gui::components::CRectangle rcDimensions, Uint32 id, std::string sCaption,
                gui::components::CColor colFace = CColor(192, 192,
                        192), CColor colText =
                    CColor(0, 0, 0), CColor colHilite = CColor(255, 255, 255), CColor colShadow = CColor(128, 128, 128) );
        //destruction
        virtual ~CButton();

		bool IsPressed() const { return m_bPressed; }

		//customize redrawing
        virtual void OnDraw();

        //left button handlers
        virtual bool OnLButtonDown(Uint16 x, Uint16 y);

        virtual bool OnLButtonUp(Uint16 x, Uint16 y);

        //set caption
        void SetCaption(std::string sCaption);

        //get caption
        std::string GetCaption();

        //set button font
        static void SetButtonFont(TTF_Font* pFont);

        static TTF_Font * GetButtonFont();

        //message for clicking button
        static MSGID MSGID_ButtonClick; //parm1=id
    };
  } // namespace controls
} // namespace gui

#endif // #ifndef BUTTON_H__
