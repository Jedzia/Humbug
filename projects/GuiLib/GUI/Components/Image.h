#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Canvas.h"

namespace gui {
namespace components {

//CImage--abstracts a blittable portion of a canvas
class CImage
{
private:
	//pointer to canvas
	CCanvas* m_pcnvSrc ;
	//source rectangle
	CRectangle m_rcSrc ;
	//destination rectangle
	CRectangle m_rcDst ;
    bool m_bFreeSrc;
public:
	//construct from source canvas, source rectangle,and offset point
	CImage ( CCanvas* pcnvSource, bool freeSrc = false ) ;
	CImage ( CCanvas* pcnvSource , CRectangle rcSource, bool freeSrc = false, CPoint ptOffset = CPoint(0 ,0) ) ;
	//destroy image
	virtual ~CImage ( ) ;
	//retrieve pointer to canvas
	CCanvas* GetCanvas ( ) ;
	//set new canvas
	void SetCanvas ( CCanvas* pcnvSource ) ;
	//access source rectangle
	CRectangle& SrcRect ( ) ;
	//access destination rectangle
	CRectangle& DstRect ( ) ;
	//blit image onto a canvas
	void Put ( CCanvas* pcnvDest , const CPoint& ptDst ) ;
    void RenderPut(CCanvas* pcnvDest, const CPoint& ptDst);
    void Scale(float factor);
    void Scale(float wFactor, float hFactor);
};

} // namespace components
} // namespace gui

#endif
