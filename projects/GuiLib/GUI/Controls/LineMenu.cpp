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
#include <boost/foreach.hpp>

using namespace gui::components;
using namespace gui::controls;

namespace gui {
namespace components {
//#include <build/cmake/include/debug.h>

int LineMenu::LabelId = 6000;
const int LABELFONTSIZE = 32;

LineMenu::LineMenu(FileLoader& m_Loader, CControl* pParent, Uint32 id, const std::string& name,
        const CRectangle& dimensions, const CRectangle& padding) :
    CControl(pParent, dimensions, id), m_pLoader(m_Loader), m_iLastAutoLabelPosition(0), m_sName(name),
    m_rPadding(padding), m_iWantedOffset(0), m_iMoveOffset(0),
    m_iSelectedLabel(LabelId) {
    dbgOut(__FUNCTION__);

    //Init(pParent);
    //FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");
    //footer = new CCanvas( m_pLoader.LoadImg("footer.png") );

    // BringToFront();
    //SetMouseHover(this);

    m_pDebugfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", LABELFONTSIZE);

    m_tmpcanvas = GetCanvas()->CreateRGBCompatible(NULL, CControl::GetWidth(), CControl::GetHeight());
    SDL_SetSurfaceAlphaMod(m_tmpcanvas->GetSurface(), 122);

    //m_pFooterImage->Put( GetCanvas(), CPoint(0, 0) );
    //const CRectangle& ownDimensions = GetCanvas()->GetDimension();
    //GetCanvas()->Blit(ownDimensions, *m_pTmpCanvas, ownDimensions);
    //Invalidate();
}

LineMenu::~LineMenu(void) {
    //delete m_pFooterImage;
    delete m_tmpcanvas;
    dbgOut(__FUNCTION__);
}

void LineMenu::Init(CControl* pParent) {}

CRectangle LineMenu::InitRect(const FileLoader& loader) {
    /*footer = new CCanvas( m_pLoader.LoadImg("footer.png") );
       LOGSTREAM << "The rect: |" << footer->GetDimension() << "|ends" << std::endl;
       //CControl::set
       m_pFooterImage = new CImage( footer );
       dst = CPoint( 0, GetCanvas()->GetHeight( ) - footer->GetHeight( ) );*/
    return CRectangle(0, 0, 1024, 354);
}

void LineMenu::DrawRect(CCanvas* pCanvas, const CRectangle& r, const CColor& c) {
    pCanvas->RenderDrawLine(r.Position(CRectangle::CompassRose::NW), r.Position(CRectangle::CompassRose::SW), &c);
    pCanvas->RenderDrawLine(r.Position(CRectangle::CompassRose::SW), r.Position(CRectangle::CompassRose::SE), &c);
    pCanvas->RenderDrawLine(r.Position(CRectangle::CompassRose::SE), r.Position(CRectangle::CompassRose::NE), &c);
    pCanvas->RenderDrawLine(r.Position(CRectangle::CompassRose::NE), r.Position(CRectangle::CompassRose::NW), &c);
}

void LineMenu::OnDraw() {
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
    CRectangle canvasDimensions = GetCanvas()->GetDimension();
    CRectangle globalPosition(GetLeft(), GetTop(), GetWidth(), GetHeight());
    CRectangle ownDimensions = GetCanvas()->GetDimension();

    CColor m_colText = CColor::White();
    CColor m_colBack = CColor::Black();
    std::ostringstream outstring;
    outstring << "[" << m_sName << "] FPS: " << gui::CApplication::ShownFrames() << ", Ticks: " << m_iTicks;
    CText text(m_pDebugfont, outstring.str(), m_colText);
    CRectangle txtDims = text.GetCanvas()->GetDimension();
    CRectangle dstDims = canvasDimensions;
    pCanvas->RenderFillRect(txtDims, &m_colBack);
    text.RenderPut(pCanvas, dstDims, txtDims);

    std::ostringstream outstring2;
    outstring2 << " Off: " << GetOffset() << ", Sel: " << m_iSelectedLabel;
    CText text2(m_pDebugfont, outstring2.str(), m_colText);
    CRectangle txtDims2 = text2.GetCanvas()->GetDimension();
    CRectangle dstDims2 = canvasDimensions + CPoint(0, 40);
    text2.RenderPut(pCanvas, dstDims2, txtDims2);

    //CRectangle paddedDimensions = canvasDimensions.Pad(m_rPadding);
    CRectangle paddedDimensions = globalPosition.Pad(m_rPadding);

    DrawRect(pCanvas, globalPosition, m_colBack);
    DrawRect(pCanvas, paddedDimensions, CColor::Red());

    std::string hello("Hello, world!");

    bool overflowDown = false;
    bool overflowUp = false;
    BOOST_FOREACH(auto ch, m_mLabels)
    {
        const CLabel& labelD = *ch.second;

        if(labelD.Intersects(labelD.VisibleArea() - GetOffset()) == CRectangle()) {
            if(m_iSelectedLabel < ch.first) {
                overflowDown = true;
            }

            if(m_iSelectedLabel > ch.first) {
                overflowUp = true;
            }

            //break;
        }
    }

    /*if (GetOffset().GetY() > 0)
       {
        overflowDown = true;

       }*/

    if(overflowDown) {
        //pCanvas->RenderFillRect(paddedDimensions - CRectangle(40,40,40,40), &m_colBack);
        CRectangle downrect = CRectangle(-30, -30, 30, 30) + paddedDimensions.Position(CRectangle::CompassRose::SE);
        //downrect += paddedDimensions.Position(CRectangle::CompassRose::SE);
        //CRectangle rect = paddedDimensions;
        pCanvas->RenderFillRect(downrect, &m_colBack);
    }

    if(overflowUp) {
        CRectangle downrect = CRectangle(-30, 0, 30, 30) + paddedDimensions.Position(CRectangle::CompassRose::NE);
        pCanvas->RenderFillRect(downrect, &m_colBack);
    }

    //CControl::OnDraw();
}         // OnDraw

bool LineMenu::OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight,
        bool bMiddle) {
    bool res = CControl::OnMouseMove(x, y, relx, rely, bLeft, bRight, bMiddle);

    //if(GetMouseHover()==NULL) SetMouseHover(this);
    /*if(HasMouseHover())
        {
        //clear to light gray
        GetCanvas()->FillRect(CRectangle(0,0,GetWidth(),GetHeight()),CColor(155,255,155));
        }*/
    return res;
}

void LineMenu::CalculateBounds()
{}

void LineMenu::IdleSetVars(int ticks) {
    m_iTicks = ticks;

    const int scrollSpeed = 5;
    // SetOffset(GetOffset() + CalculateStepValue(labelD));
    CRectangle currentOffset = GetOffset();

    if(m_iWantedOffset > m_iMoveOffset) {
        m_iMoveOffset += scrollSpeed;
    }
    else if(m_iWantedOffset < m_iMoveOffset) {
        m_iMoveOffset -= scrollSpeed;
    }

    //while (m_iWantedOffset != m_iMoveOffset)
    {
        if(m_iWantedOffset > m_iMoveOffset) {
            m_iMoveOffset += 1;
        }
        else if(m_iWantedOffset < m_iMoveOffset) {
            m_iMoveOffset -= 1;
        }
    }
    //CRectangle offset = CRectangle(currentOffset.GetX(), currentOffset.GetY() + m_iMoveOffset,
    // currentOffset.GetW(), currentOffset.GetH());
    CRectangle offset = CRectangle(currentOffset.GetX(), m_iMoveOffset, currentOffset.GetW(), currentOffset.GetH());
    SetOffset(offset);
} // LineMenu::IdleSetVars

void LineMenu::HookEventloop(SDL_Event* keyevent, bool onlyRecognizeQuit) {
    //m_KeyboardHandler.HandleKeyboardEvent(keyevent);

    //if (keyevent->type != SDL_KEYDOWN && keyevent->type != SDL_KEYUP) {
    if(keyevent->type != SDL_KEYDOWN) {
        return;
    }

    if(onlyRecognizeQuit) {
        switch(keyevent->key.keysym.sym) {
        case SDLK_BACKSPACE:
        case SDLK_q:
            m_sigMenuChanged(-1);
            break;
        default:
            break;
        }       // switch
        return;
    }

    switch(keyevent->key.keysym.sym) {
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
    case SDLK_q:
        m_sigMenuChanged(-1);
        break;
    default:
        break;
    }       // switch
} // LineMenu::HookEventloop

int LineMenu::AddTextLabel(const std::string& text) {
    //if ( !CLabel::GetLabelFont() ) {
    //}
    CRectangle globalPosition(GetLeft(), GetTop(), GetWidth(), GetHeight());
    //CRectangle globalPosition = GetCanvas()->GetDimension();
    CRectangle ownDimensions = globalPosition.Pad(m_rPadding);

    int id = LabelId;
    LabelId++;

    std::string labelTextString = text;

    if(labelTextString.empty()) {
        std::ostringstream labelText;
        labelText << "AddTextLabel " << id << "";
        labelTextString = labelText.str();
    }

    CColor color = CColor::Blue();

    if(m_mLabels.size() == 0) {
        color = CColor::Red();
    }

    CLabel* label1 = new CLabel(this, CRectangle(0, 0, -1, -1), id, labelTextString, m_pDebugfont, true,
            CColor::Black(), color);
    m_mLabels.insert(id, label1);

    Uint16 height = label1->GetHeight();
    label1->SetPosition(CPoint(ownDimensions.GetX(), ownDimensions.GetX() + m_iLastAutoLabelPosition));
    m_iLastAutoLabelPosition += height + LABELFONTSIZE;

    this->AddChild(label1);

    //NavigateDown();
    //NavigateUp();

    return id;
} // LineMenu::AddTextLabel

void LineMenu::SetTextLabelText(int id, const std::string& text) {
    //CLabel& label = m_mLabels[id];
    CLabel& label = m_mLabels.at(id);
    label.SetCaption(text);
}

void LineMenu::NavigateDown() {
    if(m_iWantedOffset != m_iMoveOffset) {
        return;
    }

    auto search = m_mLabels.find(m_iSelectedLabel + 1);

    if(search != m_mLabels.end()) {
        auto search1 = m_mLabels.find(m_iSelectedLabel);

        if(search1 != m_mLabels.end()) {
            CLabel& labelD = m_mLabels.at(m_iSelectedLabel);
            labelD.SetTextColor(CColor::Blue());
        }

        m_iSelectedLabel++;
        CLabel& labelD = m_mLabels.at(m_iSelectedLabel);
        labelD.SetTextColor(CColor::Red());

        /*CRectangle parenglobalPosition(GetLeft(), GetTop(), GetWidth(), GetHeight());
           CRectangle labelPosition(labelD.GetLeft(), labelD.GetTop(), labelD.GetWidth(),
              labelD.GetHeight());

           CRectangle glInter(labelPosition);
           CRectangle correctionRect = parenglobalPosition + CPoint(0, labelD.GetHeight());
           glInter.Intersect(correctionRect);*/

        //if (glInter == CRectangle())
        CRectangle intersects = labelD.Intersects(labelD.VisibleArea() - GetOffset());

        if(intersects == CRectangle()) {
            /*CRectangle offset = GetOffset();
               offset += CPoint(0, labelD.GetHeight() * 2);
               SetOffset(offset);*/
            m_iWantedOffset += CalculateStepValue(labelD).GetY();
            //SetOffset(GetOffset() + CalculateStepValue(labelD));

            //GetOffset() += CPoint(0, labelD.GetHeight() * 2);
        }
    }
} // LineMenu::NavigateDown

CPoint LineMenu::CalculateStepValue(const CLabel& label) const {
    return CPoint(0, label.GetHeight() * 2);
}

void LineMenu::DrawChild(const CControl& parent, CControl* pChild)
{
    const int varX = 1;
    auto pos = pChild->GetPosition();
    //pChild->SetPosition(CPoint(pos.GetX() + (varX - (rand() % (2 * varX))), pos.GetY()));
    pChild->SetPosition(CPoint(pos.GetX() + (varX - sin(m_iTicks / 6.0f)*4), pos.GetY()));
    // call painters
    ControlPainterParameters param;
    // painter.Draw(parent, pChild, param)
    // if(!param.IsDrawn())
    CControl::DrawChild(parent, pChild);
    pChild->SetPosition(pos);
}

void LineMenu::NavigateUp() {
    if(m_iWantedOffset != m_iMoveOffset) {
        return;
    }

    auto search = m_mLabels.find(m_iSelectedLabel - 1);

    if(search != m_mLabels.end()) {
        auto search1 = m_mLabels.find(m_iSelectedLabel);

        if(search1 != m_mLabels.end()) {
            CLabel& labelD = m_mLabels.at(m_iSelectedLabel);
            //labelD.SetCaption("Moooooo");
            labelD.SetTextColor(CColor::Blue());
        }

        m_iSelectedLabel--;
        CLabel& labelD = m_mLabels.at(m_iSelectedLabel);
        labelD.SetTextColor(CColor::Red());

        auto vis = VisibleArea();
        CRectangle intersects = labelD.Intersects(labelD.VisibleArea() - GetOffset());

        if(intersects == CRectangle()) {
            //SetOffset(GetOffset() - CalculateStepValue(labelD));
            m_iWantedOffset -= CalculateStepValue(labelD).GetY();

            /*CRectangle offset = GetOffset();
               offset -= CPoint(0, labelD.GetHeight() * 2);
               SetOffset(offset);*/
        }
    }
} // LineMenu::NavigateUp
}
}
