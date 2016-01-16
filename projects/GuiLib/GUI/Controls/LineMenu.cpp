/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the LineMenu.cpp class.
 * \folder     $(folder)
 * \file       LineMenu.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../stdafx.h"
//
#include "LineMenu.h"
//
#include "Label.h"

using namespace gui::components;
using namespace gui::controls;

namespace gui {
namespace components {
//#include <build/cmake/include/debug.h>

int LineMenu::LabelId = 6000;
const int LABELFONTSIZE = 32;

LineMenu::LineMenu(FileLoader& m_Loader, CControl* pParent, Uint32 id, const std::string& name,
        const CRectangle& dimensions, const CRectangle& padding) :
        CControl(pParent, dimensions, id), m_iLastAutoLabelPosition(0), m_sName(name), m_rPadding(padding), m_iSelectedLabel(LabelId),
    m_pLoader(m_Loader){
    dbgOut(__FUNCTION__);

    //Init(pParent);
    //FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");
    //footer = new CCanvas( m_pLoader.LoadImg("footer.png") );

    // BringToFront();
    //SetMouseHover(this);

    m_pDebugfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", LABELFONTSIZE);

    m_tmpcanvas = GetCanvas()->CreateRGBCompatible( NULL, CControl::GetWidth(), CControl::GetHeight() );
    SDL_SetSurfaceAlphaMod(m_tmpcanvas->GetSurface(), 122);

    //m_pFooterImage->Put( GetCanvas(), CPoint(0, 0) );
    //const CRectangle& ownDimensions = GetCanvas()->GetDimension();
    //GetCanvas()->Blit(ownDimensions, *m_pTmpCanvas, ownDimensions);
    //Invalidate();
}

LineMenu::~LineMenu(void){
    //delete m_pFooterImage;
    delete m_tmpcanvas;
    dbgOut(__FUNCTION__);
}

/** LineMenu, Init:
 *  Detailed description.
 *  @param pParent TODO
 * @return TODO
 */
void LineMenu::Init(CControl* pParent){}

/** LineMenu, InitRect:
 *  Detailed description.
 *  @param loader TODO
 * @return TODO
 */
CRectangle LineMenu::InitRect(const FileLoader& loader){
    /*footer = new CCanvas( m_pLoader.LoadImg("footer.png") );
       LOGSTREAM << "The rect: |" << footer->GetDimension() << "|ends" << std::endl;
       //CControl::set
       m_pFooterImage = new CImage( footer );
       dst = CPoint( 0, GetCanvas()->GetHeight( ) - footer->GetHeight( ) );*/
    return CRectangle(0, 0, 1024, 354);
}

/** LineMenu, OnDraw:
 *  Detailed description.
 *  @return TODO
 */
void LineMenu::OnDraw(){
    /*Child
       std::list<CControl*>::iterator iter;
       for (iter = m_lstChildren.begin(); iter != m_lstChildren.end(); iter++)
       {
       //grab item from list
       CControl* pChild = (*iter);
       //draw
       pChild->Draw();
       }*/

    CCanvas* pCanvas = GetCanvas();
    CRectangle globalPosition( GetLeft(), GetTop(), GetWidth(), GetHeight() );
    CRectangle ownDimensions = GetCanvas()->GetDimension();

    CColor m_colText = CColor::White();
    CColor m_colBack = CColor::Black();
    std::ostringstream outstring;
    outstring << "[" << m_sName << "] FPS: " << gui::CApplication::ShownFrames() << ", Ticks: " << m_iTicks;

    CText text(m_pDebugfont, outstring.str(), m_colText);

    CRectangle txtDims = text.GetCanvas()->GetDimension();
    CRectangle dstDims = globalPosition;
    pCanvas->RenderFillRect(txtDims, &m_colBack);
    text.RenderPut(pCanvas, dstDims, txtDims);

    //CControl::OnDraw();
}         // OnDraw

/** LineMenu, OnMouseMove:
 *  Detailed description.
 *  @param x TODO
 * @param y TODO
 * @param relx TODO
 * @param rely TODO
 * @param bLeft TODO
 * @param bRight TODO
 * @param bMiddle TODO
 * @return TODO
 */
bool LineMenu::OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight,
        bool bMiddle){
    bool res = CControl::OnMouseMove(x, y, relx, rely, bLeft, bRight, bMiddle);

    //if(GetMouseHover()==NULL) SetMouseHover(this);
    /*if(HasMouseHover())
        {
        //clear to light gray
        GetCanvas()->FillRect(CRectangle(0,0,GetWidth(),GetHeight()),CColor(155,255,155));
        }*/
    return res;
}

void LineMenu::IdleSetVars(int ticks){
    m_iTicks = ticks;
}

void LineMenu::HookEventloop(SDL_Event* keyevent){
    //m_KeyboardHandler.HandleKeyboardEvent(keyevent);

    //if (keyevent->type != SDL_KEYDOWN && keyevent->type != SDL_KEYUP) {
    if (keyevent->type != SDL_KEYDOWN) {
        return;
    }

    switch (keyevent->key.keysym.sym) {
    case SDLK_UP:
    case SDLK_w:
        NavigateUp();
        break;
    case SDLK_DOWN:
    case SDLK_s:
        NavigateDown();
        break;
    case SDLK_RETURN:
    case SDLK_e:
        m_sigMenuChanged(m_iSelectedLabel);
        break;
    case SDLK_BACKSPACE:
        m_sigMenuChanged(-1);
        break;
    default:
        break;
    }       // switch
} // LineMenu::HookEventloop

int LineMenu::AddTextLabel(){
    //if ( !CLabel::GetLabelFont() ) { 
    //}
    CRectangle globalPosition = GetCanvas()->GetDimension();
    CRectangle ownDimensions = globalPosition.Pad(m_rPadding);

    int id = LabelId;
    LabelId++;

    std::ostringstream labelText;
    labelText << "AddTextLabel " << id << "";

    CLabel* label1 = new CLabel( this, CRectangle(0, 0, -1, -1), id, labelText.str(), m_pDebugfont, true,
            CColor::Black(), CColor::White() );
    m_mLabels.insert(id, label1);

    Uint16 height = label1->GetHeight();
    label1->SetPosition( CPoint(ownDimensions.GetX(), ownDimensions.GetX() + m_iLastAutoLabelPosition) );
    m_iLastAutoLabelPosition += height + LABELFONTSIZE;

    this->AddChild(label1);

    return id;
} // LineMenu::AddTextLabel

void LineMenu::SetTextLabelText(int id, const std::string& text){
    //CLabel& label = m_mLabels[id];
    CLabel& label = m_mLabels.at(id);
    label.SetCaption(text);
}

void LineMenu::NavigateDown()
{
    auto search = m_mLabels.find(m_iSelectedLabel + 1);
    if (search != m_mLabels.end())
    {
        auto search1 = m_mLabels.find(m_iSelectedLabel);
        if (search1 != m_mLabels.end())
        {
            CLabel& labelD = m_mLabels.at(m_iSelectedLabel);
            labelD.SetTextColor(CColor::Blue());
        }

        m_iSelectedLabel++;
        CLabel& labelD = m_mLabels.at(m_iSelectedLabel);
        labelD.SetTextColor(CColor::Red());
    }
}

void LineMenu::NavigateUp()
{
    auto search = m_mLabels.find(m_iSelectedLabel - 1);
    if (search != m_mLabels.end())
    {
        auto search1 = m_mLabels.find(m_iSelectedLabel);
        if (search1 != m_mLabels.end())
        {
            CLabel& labelD = m_mLabels.at(m_iSelectedLabel);
            //labelD.SetCaption("Moooooo");
            labelD.SetTextColor(CColor::Blue());
        }

        m_iSelectedLabel--;
        CLabel& labelD = m_mLabels.at(m_iSelectedLabel);
        labelD.SetTextColor(CColor::Red());
    }
}

}
}
