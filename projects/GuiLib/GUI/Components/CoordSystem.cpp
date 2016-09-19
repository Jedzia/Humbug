/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the CoordSystem.cpp class.
 * \folder     $(folder)
 * \file       CoordSystem.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../stdafx.h"
#include "CoordSystem.h"
#include "Text.h"
#include "Shapes/Line.h"
#include "../../Filesystem/FileLoader.h"

namespace gui {
namespace components {
CCoordSystem::CCoordSystem(const char* title, int width, int height, const CPoint& offset, Uint32 flags) : m_pTitle(title), m_iWidth(width),
    m_iHeight(height), m_uFlags(flags), m_LastPoint(0, 0), m_Offset(offset), m_pLoader(nullptr), m_pFont(nullptr)
{}

CCoordSystem::~CCoordSystem() {
    // SDL_FreeSurface ( GetSurface ( ) );
    //SetWindow ( NULL );
}

void CCoordSystem::Reset() {
    m_vPoints.clear();
}

void CCoordSystem::AddDatapoint(const CPoint& point) {
    //m_vPoints.push_back(point);
    m_LastPoint.SetX(point.GetX());
    m_LastPoint.SetY(point.GetY());
    std::set<CPoint>::_Pairib ins = m_vPoints.insert(point);
}

void CCoordSystem::RenderAxis(const CCanvas* target) const {
    CColor color = CColor::LightRed();
    SLine::RenderDrawLine(target, CPoint(0, m_iHeight).Add(m_Offset), CPoint(m_iHeight, m_iWidth).Add(m_Offset), &color);
    SLine::RenderDrawLine(target, CPoint(0, 0).Add(m_Offset), CPoint(0, m_iHeight).Add(m_Offset), &color);
}

void CCoordSystem::RenderText(const CCanvas* target) const {
    if (!m_pFont)
    {
        return;
    }

    const CColor colorAxisText = CColor::LightGray();
    const CColor colorMinMaxText = CColor::Black();
    std::ostringstream labelText;
    //labelText << "{" << "Bla" << "}" << title << "(" << degrees << ")";
    labelText << "x" << "->";
    CText textXAxis(m_pFont, labelText.str(), colorAxisText, CPoint(m_iWidth - 80, m_iHeight).Add(m_Offset));
    textXAxis.RenderPut(target);

    std::ostringstream labelText2;
    labelText2 << "(" << "Max:" << ") " << m_Max.GetX() << ", " << m_Max.GetY();
    CText textMax(m_pFont, labelText2.str(), colorMinMaxText, CPoint(80, m_iHeight - 40).Add(m_Offset));
    textMax.RenderPut(target);

    std::ostringstream labelText3;
    labelText3 << "(" << "Min:" << ") " << m_Min.GetX() << ", " << m_Min.GetY();
    CText textMin(m_pFont, labelText3.str(), colorMinMaxText, CPoint(80, m_iHeight - 40).Add(m_Offset) - textMax.VerticalSpacing());
    textMin.RenderPut(target);

}

    void CCoordSystem::TrackMinMax(int x, int y)
    {
        if (x > m_Max.GetX())
        {
            m_Max.SetX(x);
        }

        if (x < m_Min.GetX())
        {
            m_Min.SetX(x);
        }

        if (y > m_Max.GetY())
        {
            m_Max.SetY(y);
        }

        if (y < m_Min.GetY())
        {
            m_Min.SetY(y);
        }
    }

    void CCoordSystem::RenderPut(const CCanvas* target) {
    RenderAxis(target);
    const CColor color = CColor::Cyan();
    const CColor color3 = CColor::LightCyan();

    CPoint lastp;
    bool lastpSet = false;
    std::for_each(m_vPoints.begin(), m_vPoints.end(), [&](const CPoint &p)
            {
                int x = p.GetX();
                int y = p.GetY();
                TrackMinMax(x, y);
                CPoint coordinates = CPoint(x, m_iHeight - y) + m_Offset;
                if(lastpSet) {
                    target->RenderDrawLine(coordinates, lastp, &color3);
                }

                target->RenderDrawPoint(coordinates, &color);
                lastp = coordinates;
                lastpSet = true;
            }
            );

    const CColor color2 = CColor::DarkRed();
    if(NumDatapoints() > 0) {
        CPoint coordinates = CPoint(m_LastPoint.GetX(), m_iHeight - m_LastPoint.GetY());
        //target->RenderDrawPoint(coordinates, &color2);
        auto wh = CPoint(8, 8);
        auto xy = coordinates;
        xy.X() -= 4;
        xy.Y() -= 4;
        auto rect = CRectangle(xy, wh);
        target->RenderFillRect(rect + m_Offset, &color2);
    }

    RenderText(target);

} // CCoordSystem::RenderPut
    void CCoordSystem::SetLoader(FileLoader* const loader)
    {
        this->m_pLoader = loader;
        if (m_pLoader &&  !m_pFont)
        {
            m_pFont = m_pLoader->FL_LOADFONT("Fonts/ARIAL.TTF", 24);

        }
    }
}   // namespace components
} // namespace gui
