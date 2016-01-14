#ifndef __CoordSystem_H__
#define __CoordSystem_H__

#include "Canvas.h"

namespace gui {
namespace components {

//main canvas, abstract primary display surface
class CCoordSystem 
{
    const char* m_pTitle;
    int m_iWidth;
    int m_iHeight;
    Uint32 m_uFlags;
    //std::vector<CPoint> m_vPoints;
    std::set<CPoint> m_vPoints;
    CPoint m_LastPoint;

    void RenderAxis(const CCanvas* target) const;
public:
    //constructor
    CCoordSystem(const char * title, int width, int height, Uint32 flags);
    //destructor
    virtual ~CCoordSystem ( ) ;

    void Reset();
    void AddDatapoint(const CPoint& point);

    /** Render a Line.
        *  Use this function to draw a line on the specified rendering target.
        *  @param target The canvas to paint on.
        *  @param pStart The start point of the line.
        *  @param pEnd The end point of the line.
        *  @param color The drawing color of the line or NULL if no color change is wanted.
        */
    void RenderPut(const CCanvas* target) const;

};

} // namespace components
} // namespace gui

#endif
