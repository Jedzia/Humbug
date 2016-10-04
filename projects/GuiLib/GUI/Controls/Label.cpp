// Label.cpp: implementation of the CLabel class.
//
//////////////////////////////////////////////////////////////////////
#include "../../stdafx.h"
#include "GUI/GuiFontMetrics.h"
#include "Label.h"

namespace gui {
namespace controls {
using namespace components;

MSGID CLabel::MSGID_LabelClick = CMessageHandler::GetNextMSGID();     //parm1=id
//label font
//TTF_Font * CLabel::m_pLabelFont = NULL;
//GuiFontMetrics * CLabel::m_pFontMetrics = NULL;

CRectangle CLabel::CreateTextCanvas(const std::string& sCaption,
        const CRectangle& rcDimensions,
        const CColor& colText){
    //set the caption
    //m_pcnvText = NULL;
    if (sCaption != "" && m_pLabelFont != NULL) {
        // Todo: when no font ... throw? ... or warn?
        LOGSTD(__FUNCTION__ << " [" << typeid(*this).name() << "] (" << this << ")");
        m_pcnvText.reset(
                new CCanvas(TTF_RenderText_Blended( m_pLabelFont, sCaption.c_str(), colText.SDLColor() ),
                        true) );
        LOGSTD(__FUNCTION__ << "-After [" << typeid(*this).name() << "] (" << this << ")");
    }

    //SetCaption(sCaption);
    if ( m_pcnvText && (rcDimensions.GetW() < 1 || rcDimensions.GetH() < 1) ) {
        return m_pcnvText->GetDimension();
    }

    return rcDimensions;
}

CRectangle CLabel::CalculateDimensions(const std::string& sCaption,
        const CRectangle& rcDimensions,
        const CColor& colText,
        TTF_Font* labelFont) const
{
    GuiFontMetrics fm(labelFont);

    if (sCaption != "" && m_pLabelFont != NULL) {
        return fm.CalculateDimensions(sCaption);
    }

    return rcDimensions;
}

// ReSharper disable once CppPossiblyUninitializedMember
CLabel::CLabel(CControl* pParent, CRectangle rcDimensions, Uint32 id, std::string sCaption, TTF_Font* labelFont,
        bool usesSDL2Render,
        CColor colFace, CColor colText, CColor colHilite,
        CColor colShadow) :
        CControl(pParent, CalculateDimensions(sCaption, rcDimensions, colText, labelFont), id, true, usesSDL2Render), m_pLabelFont(labelFont),
    m_bPressed(false){
    dbgOut(__FUNCTION__);
//        //set the caption
//        SetCaption(sCaption);
    m_sCaption = sCaption;
    SetPosition(rcDimensions);
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

/*CRectangle CLabel::Intersects(const CRectangle& paintDestination)
{
    auto parent = GetParent();
    if (!parent)
    {
        return paintDestination;
    }

    CRectangle glInter = paintDestination;
    CRectangle correctionRect(parent->GetLeft(), parent->GetTop(), parent->GetWidth(), parent->GetHeight());

    correctionRect.Y() += GetHeight() ;
    correctionRect.H() -= GetHeight() * 2;

    glInter.Intersect(correctionRect);

    return glInter;
}*/

    //customize redrawing
void CLabel::OnDraw(){
    //clear out the surface
    GetCanvas()->Clear(m_colFace);
    //lock the surface
    GetCanvas()->Lock();

    CRectangle rcDst = VisibleArea(), rcSrc;
    //set source rectangle
    rcSrc.Copy(rcDst);
    rcSrc.SetX(0);
    rcSrc.SetY(0);

    if(m_bPressed) {
        if (m_bUsesSDL2Render) {
            // Todo: use render to texture ?
            // https://gist.github.com/Twinklebear/8265888

            // Todo: when using textures, they should be (re)generated at ctor or invalidation.
            // the coordinates have to be relative and recursive paint must be used by the control
            // parent to draw.
            auto wid = GetWidth();
            auto hei = GetHeight();
            CRectangle sdl_rect = GetCanvas()->GetDimension();
            //GetCanvas()->RenderFillRect(sdl_rect, CColor::Red());
            //GetCanvas()->FillRect(rcDst, CColor::Red());
        }
        else {
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
    //GetCanvas()->Blit(rcDst, *m_pcnvText, rcSrc);

    if (m_bUsesSDL2Render) {
        auto parent = GetParent();
        if (parent)
        {
            rcDst -= parent->GetOffset();
            auto text = GetCaption();

            // Todo: Visual intersection checking. Or better use a scrollable parent canvas control?
            if (Intersects(rcDst) == CRectangle())
            {
                CColor color = CColor::LightYellow();
                GetCanvas()->RenderDrawRect(rcDst, &color);
                return;
            }
        }
        //GetCanvas()->UpdateTexture(m_pcnvText, rcSrc, rcDst);
        //GetCanvas()->UpdateTexture(m_pcnvText);
        LOGSTD(__FUNCTION__ << " [" << typeid(*this).name() << "] (" << this << ")");
        GetCanvas()->RenderPutCopy(m_pcnvText.get(), &rcDst, &rcSrc);
        LOGSTD(__FUNCTION__ << "-After [" << typeid(*this).name() << "] (" << this << ")");
        //auto painter = LabelPainter(downrect, &m_colBack, overflowDown)
    }
    else {
        GetCanvas()->Blit(rcDst, *m_pcnvText, rcSrc);
    }

    //Invalidate();
}     // OnDraw

Uint16 CLabel::GetWidth() const
{
    if (m_pcnvText) {
        return m_pcnvText->GetWidth();
    }
    else {
        return CControl::GetWidth();
    }
}

/// <summary>
/// Gets the height.
/// </summary>
/// <returns>Uint16.</returns>
Uint16 CLabel::GetHeight() const
{
    if (m_pcnvText) {
        return m_pcnvText->GetHeight();
    }
    else {
        return CControl::GetHeight();
    }
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

    CRectangle dim = CreateTextCanvas(sCaption, CRectangle(), m_colText);

    /*return;
       //create text canvas
       if(m_sCaption!="" && m_pLabelFont!=NULL) {
        // Todo: when no font ... throw? ... or warn?
        m_pcnvText =
            new gui::components::CCanvas( TTF_RenderText_Blended(m_pLabelFont, m_sCaption.c_str(),
               m_colText) );
       }*/
}

//get caption
std::string CLabel::GetCaption() const
{
    //return the caption
    return(m_sCaption);
}

//set label font
void CLabel::SetLabelFont(TTF_Font* pFont){
    //set the label font
    m_pLabelFont = pFont;
}

/** CLabel, GetLabelFont:
 *  Detailed description.
 *  @return TODO
 */
TTF_Font * CLabel::GetLabelFont() const
{
    //return buton font
    return(m_pLabelFont);
}

components::CColor CLabel::GetTextColor() const
{
    return m_colText;
}

void CLabel::SetTextColor(const components::CColor color)
{
    m_colText = color;
    CRectangle dim = CreateTextCanvas(m_sCaption, CRectangle(), m_colText);
}
}   // namespace controls
} // namespace gui
