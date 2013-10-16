// Button.cpp: implementation of the CButton class.
//
//////////////////////////////////////////////////////////////////////
#include "../../stdafx.h"
#include "Button.h"

namespace gui {
  namespace controls {
    MSGID CButton::MSGID_ButtonClick = CMessageHandler::GetNextMSGID(); //parm1=id
//button font
    TTF_Font * CButton::s_ButtonFont = NULL;

//construction
    CButton::CButton(CControl* pParent, gui::components::CRectangle rcDimensions, Uint32 id, std::string sCaption,
            gui::components::CColor colFace, gui::components::CColor colText, gui::components::CColor colHilite,
            gui::components::CColor colShadow) :
        CControl(pParent, rcDimensions, id),
        m_pcnvText(NULL),
        m_bPressed(false){
        //set the caption
        SetCaption(sCaption);
        //set the colors
        m_colFace = colFace;
        m_colText = colText;
        m_colHilite = colHilite;
        m_colShadow = colShadow;
        // Invalidate();
    }

//destruction
    CButton::~CButton(){
        //set caption to nothing
        SetCaption("");
    }

//customize redrawing
    void CButton::OnDraw(){
        //clear out the surface
        GetCanvas()->Clear(m_colFace);
        //lock the surface
        GetCanvas()->Lock();

        if(m_bPressed) {
            //draw top and bottom
            for(int x = 0; x<GetWidth(); x++)
            {
                GetCanvas()->SetPixel(x, 0, m_colShadow);
                GetCanvas()->SetPixel(x, GetHeight() - 1, m_colHilite);
            }

            //draw left and right
            for(int y = 0; y<GetHeight(); y++)
            {
                GetCanvas()->SetPixel(0, y, m_colShadow);
                GetCanvas()->SetPixel(GetWidth() - 1, y, m_colHilite);
            }
        }
        else {
            //draw top and bottom
            for(int x = 0; x<GetWidth(); x++)
            {
                GetCanvas()->SetPixel(x, 0, m_colHilite);
                GetCanvas()->SetPixel(x, GetHeight() - 1, m_colShadow);
            }

            //draw left and right
            for(int y = 0; y<GetHeight(); y++)
            {
                GetCanvas()->SetPixel(0, y, m_colHilite);
                GetCanvas()->SetPixel(GetWidth() - 1, y, m_colShadow);
            }
        }

        //unlock the surface
        GetCanvas()->Unlock();
        //blit text
        gui::components::CRectangle rcSrc, rcDst;
        rcSrc.Set( 0, 0, m_pcnvText->GetWidth(), m_pcnvText->GetHeight() );
        rcDst = rcSrc;
        rcDst.SetX( ( GetWidth() - rcSrc.GetW() ) / 2 );
        rcDst.SetY( ( GetHeight() - rcSrc.GetH() ) / 2 );
        //GetCanvas()->FillRect(CRectangle(0,0,100,100), CColor::Blue());
        GetCanvas()->Blit(rcDst, *m_pcnvText, rcSrc);
        //Invalidate();
    } // OnDraw

//left button handlers
    bool CButton::OnLButtonDown(Uint16 x, Uint16 y){
        //if it is a button hit...
        if( CControl::OnLButtonDown(x, y) ) {
            Invalidate();
            m_bPressed = true;
            return(true);
        }

        return(false);
    }

    /** CButton, OnLButtonUp:
     *  Detailed description.
     *  @param x TODO
     * @param y TODO
     * @return TODO
     */
    bool CButton::OnLButtonUp(Uint16 x, Uint16 y){
        //if button has been pressed...
        if(m_bPressed) {
            //if this is the mouse hover control
            if( HasMouseHover() ) {
                //trigger message
                SendMessageQ( MSGID_ButtonClick, (MSGPARM)GetID() );
                //set pressed state to false
                Invalidate();
                m_bPressed = false;
                return(true);
            }

            //set pressed state to false
            m_bPressed = false;
        }

        return( CControl::OnLButtonUp(x, y) );
    } // OnLButtonUp

//set caption
    void CButton::SetCaption(std::string sCaption){
        //delete any existing text canvas
        if(m_pcnvText) {
            delete m_pcnvText;
            m_pcnvText = NULL;
        }

        //set the caption
        m_sCaption = sCaption;

        //create text canvas
        if(m_sCaption!="" && s_ButtonFont!=NULL) {
            m_pcnvText =
                new gui::components::CCanvas( TTF_RenderText_Blended(s_ButtonFont, m_sCaption.c_str(), m_colText) );
        }
    }

//get caption
    std::string CButton::GetCaption(){
        //return the caption
        return(m_sCaption);
    }

//set button font
    void CButton::SetButtonFont(TTF_Font* pFont){
        //set the button font
        s_ButtonFont = pFont;
    }

    /** CButton, GetButtonFont:
     *  Detailed description.
     *  @return TODO
     */
    TTF_Font * CButton::GetButtonFont(){
        //return buton font
        return(s_ButtonFont);
    }
  } // namespace controls
} // namespace gui
