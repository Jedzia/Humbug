#ifndef __CoordSystem_H__
#define __CoordSystem_H__

#include "Canvas.h"

class FileLoader;

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
    CPoint m_Offset;
    FileLoader* m_pLoader;
    TTF_Font* m_pFont;
    CPoint m_Max;
    CPoint m_Min;

    void RenderAxis(const CCanvas* target) const;
    void RenderText(const CCanvas* target) const;
    void TrackMinMax(int x, int y);

    FileLoader* Loader() const {  return m_pLoader; }

public:
    //constructor
    CCoordSystem(const char * title, int width, int height, const CPoint& offset = CPoint(0,0), Uint32 flags = 0);
    //destructor
    virtual ~CCoordSystem ( ) ;

    void Reset();
    void AddDatapoint(const CPoint& point);
    
    int NumDatapoints() const
    {
        return m_vPoints.size();
    }

    /** Render a Line.
        *  Use this function to draw a line on the specified rendering target.
        *  @param target The canvas to paint on.
        *  @param pStart The start point of the line.
        *  @param pEnd The end point of the line.
        *  @param color The drawing color of the line or NULL if no color change is wanted.
        */
    void RenderPut(const CCanvas* target);

    void SetLoader(FileLoader* const loader);
};

} // namespace components
} // namespace gui

#endif
