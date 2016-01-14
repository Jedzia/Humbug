/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
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
#include "Shapes/Line.h"

namespace gui {
namespace components {
void CCoordSystem::RenderAxis(const CCanvas* target) const {
    CColor color = CColor::LightRed();
    SLine::RenderDrawLine(target, CPoint(0, m_iHeight), CPoint(m_iHeight, m_iWidth), &color);
    SLine::RenderDrawLine(target, CPoint(0, 0), CPoint(0, m_iHeight), &color);
}

CCoordSystem::CCoordSystem(const char* title, int width, int height, Uint32 flags) : m_pTitle(title), m_iWidth(width),
    m_iHeight(height), m_uFlags(flags), m_LastPoint(0,0)
{}

CCoordSystem::~CCoordSystem() {
    // SDL_FreeSurface ( GetSurface ( ) );
    //SetWindow ( NULL );
}

void CCoordSystem::Reset(){
    m_vPoints.clear();
}

void CCoordSystem::AddDatapoint(const CPoint& point){
    //m_vPoints.push_back(point);
    m_LastPoint.SetX(point.GetX());
    m_LastPoint.SetY(point.GetY());
    std::set<CPoint>::_Pairib ins = m_vPoints.insert(point);
}

void CCoordSystem::RenderPut(const CCanvas* target) const {
    RenderAxis(target);
    const CColor color = CColor::Cyan();
    const CColor color3 = CColor::LightCyan();

    auto size = m_vPoints.size();
    CPoint lastp;
    bool lastpSet = false;
    std::for_each(m_vPoints.begin(), m_vPoints.end(), [&](const CPoint &p)
                  {
                      CPoint coordinates = CPoint(p.GetX(), m_iHeight - p.GetY());
                      if (lastpSet)
                      {
                          target->RenderDrawLine(lastp, coordinates, &color3);
                      }
                      target->RenderDrawPoint(coordinates, &color);
                      lastp = coordinates;
                      lastpSet = true;
                  }
    );

    const CColor color2 = CColor::DarkRed();
    if (size > 0)
    {
        CPoint coordinates = CPoint(m_LastPoint.GetX(), m_iHeight - m_LastPoint.GetY());
        //target->RenderDrawPoint(coordinates, &color2);
        auto wh = CPoint(8, 8);
        auto xy = coordinates;
        xy.X() -= 4;
        xy.Y() -= 4;
        auto rect = CRectangle(xy, wh);
        target->RenderFillRect(rect, &color2);
    }
}
}   // namespace components
} // namespace gui
