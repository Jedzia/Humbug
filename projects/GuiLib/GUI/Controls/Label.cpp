// Label.cpp: implementation of the CLabel class.
//
//////////////////////////////////////////////////////////////////////
#include "../../stdafx.h"
#include "Label.h"

namespace gui {
  namespace controls {
    MSGID CLabel::MSGID_LabelClick = CMessageHandler::GetNextMSGID(); //parm1=id
//label font
    TTF_Font * CLabel::s_LabelFont = NULL;

    components::CRectangle CLabel::CreateTextCanvas(const std::string& sCaption, const gui::components::CRectangle& rcDimensions, const gui::components::CColor& colText)
      {
          //set the caption
          //m_pcnvText = NULL;
          if (sCaption != "" && s_LabelFont != NULL) {
              // Todo: when no font ... throw? ... or warn? 
              m_pcnvText.reset(
                  new components::CCanvas(TTF_RenderText_Blended(s_LabelFont, sCaption.c_str(), colText.SDLColor()), true));
          }
          
          //SetCaption(sCaption);
          if (m_pcnvText && (rcDimensions.GetW() < 1 || rcDimensions.GetH() < 1))
          {
              return m_pcnvText->GetDimension();
          }

          return rcDimensions;
    }

      components::CRectangle CLabel::CalculateDimensions(const std::string& sCaption, const gui::components::CRectangle& rcDimensions, const gui::components::CColor& colText)
      {
          if (sCaption != "" && s_LabelFont != NULL) {
              const char *ctext = sCaption.c_str();
              int width, height;

              if ((TTF_SizeUTF8(s_LabelFont, ctext, &width, &height) < 0) || !width) {
                  // Todo: TTF_SetError("Text has zero width");
                  return rcDimensions;
              }

              return components::CRectangle(0, 0, width, height);
          }

          return rcDimensions;
      }

      // ReSharper disable once CppPossiblyUninitializedMember
    CLabel::CLabel(CControl* pParent, gui::components::CRectangle rcDimensions, Uint32 id, std::string sCaption, bool usesSDL2Render,
            gui::components::CColor colFace, gui::components::CColor colText, gui::components::CColor colHilite,
            gui::components::CColor colShadow) :
            CControl(pParent, CalculateDimensions(sCaption, rcDimensions, colText), id, true, usesSDL2Render),
            m_bPressed(false)
    {
    dbgOut(__FUNCTION__);
//        //set the caption
//        SetCaption(sCaption);
        m_sCaption = sCaption;
        CreateTextCanvas(sCaption, rcDimensions, colText);
        //set the colors
        m_colFace = colFace;
        m_colText = colText;
        m_colHilite = colHilite;
        m_colShadow = colShadow;
        // Invalidate();
    }

//destruction
    CLabel::~CLabel(){
        //set caption to nothing
        SetCaption("");
        dbgOut(__FUNCTION__);
    }

//customize redrawing
    void CLabel::OnDraw(){
        //clear out the surface
        GetCanvas()->Clear(m_colFace);
        //lock the surface
        GetCanvas()->Lock();

        gui::components::CRectangle rcDst, rcSrc;
        //set destination rectangle
        rcDst.Set(GetPosition().GetX(), GetPosition().GetY(), GetWidth(), GetHeight());
        //set source rectangle
        rcSrc.Copy(rcDst);
        rcSrc.SetX(0);
        rcSrc.SetY(0);

        if(m_bPressed) {
            if (m_bUsesSDL2Render)
            {
                // Todo: use render to texture ?
                // https://gist.github.com/Twinklebear/8265888

                // Todo: when using textures, they should be (re)generated at ctor or invalidation.
                // the coordinates have to be relative and recursive paint must be used by the control parent to draw.
                auto wid = GetWidth();
                auto hei = GetHeight();
                components::CRectangle sdl_rect = GetCanvas()->GetDimension();
                //GetCanvas()->RenderFillRect(sdl_rect, CColor::Red());
                //GetCanvas()->FillRect(rcDst, CColor::Red());
            }
            else
            {
                //draw top and bottom
                for (int x = 0; x < GetWidth(); x++)
                {
                    GetCanvas()->SetPixel(x, 0, m_colShadow);
                    GetCanvas()->SetPixel(x, GetHeight() - 1, m_colHilite);
                }

                //draw left and right
                for (int y = 0; y < GetHeight(); y++)
                {
                    GetCanvas()->SetPixel(0, y, m_colShadow);
                    GetCanvas()->SetPixel(GetWidth() - 1, y, m_colHilite);
                }
            }
        }
        else {
           /* //draw top and bottom
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
            }*/
        }

        //unlock the surface
        GetCanvas()->Unlock();
        //blit text
        //gui::components::CRectangle rcSrc, rcDst;
        //rcSrc.Set( 0, 0, m_pcnvText->GetWidth(), m_pcnvText->GetHeight() );
        //rcDst = rcSrc;
       // rcDst.SetX( ( GetWidth() - rcSrc.GetW() ) / 2 );
        //rcDst.SetY( ( GetHeight() - rcSrc.GetH() ) / 2 );
        //GetCanvas()->FillRect(CRectangle(0,0,100,100), CColor::Blue());


        // remove the next line, just for testing
        GetCanvas()->Blit(rcDst, *m_pcnvText, rcSrc);
        if (m_bUsesSDL2Render)
        {
            GetCanvas()->RenderPutCopy(m_pcnvText.get(), &rcSrc, &rcDst);
            //GetCanvas()->UpdateTexture(m_pcnvText, rcSrc, rcDst);
            //GetCanvas()->UpdateTexture(m_pcnvText);
        }
        else
            GetCanvas()->Blit(rcDst, *m_pcnvText, rcSrc);

        //Invalidate();
    } // OnDraw
      Uint16 CLabel::GetWidth()
      {
          if (m_pcnvText)
              return m_pcnvText->GetWidth();
          else
              return CControl::GetWidth();
      }

      /// <summary>
      /// Gets the height.
      /// </summary>
      /// <returns>Uint16.</returns>
      Uint16 CLabel::GetHeight()
      {
          if (m_pcnvText)
              return m_pcnvText->GetHeight();
          else
              return CControl::GetHeight();
      }

      //set caption
    void CLabel::SetCaption(const std::string& sCaption){
        //delete any existing text canvas
        /*if(m_pcnvText) {
            delete m_pcnvText;
            m_pcnvText = NULL;
        }*/

        //set the caption
        m_sCaption = sCaption;

        components::CRectangle dim = CreateTextCanvas(sCaption, components::CRectangle(), m_colText);
        
        /*return;
        //create text canvas
        if(m_sCaption!="" && s_LabelFont!=NULL) {
            // Todo: when no font ... throw? ... or warn? 
            m_pcnvText =
                new gui::components::CCanvas( TTF_RenderText_Blended(s_LabelFont, m_sCaption.c_str(), m_colText) );
        }*/
    }

//get caption
    std::string CLabel::GetCaption(){
        //return the caption
        return(m_sCaption);
    }

//set label font
    void CLabel::SetLabelFont(TTF_Font* pFont){
        //set the label font
        s_LabelFont = pFont;
    }

    /** CLabel, GetLabelFont:
     *  Detailed description.
     *  @return TODO
     */
    TTF_Font * CLabel::GetLabelFont(){
        //return buton font
        return(s_LabelFont);
    }
  } // namespace controls
} // namespace gui
