#ifndef __SeamlessImage_H__
#define __SeamlessImage_H__

#include "Canvas.h"

namespace gui {
	namespace components {

		//CSeamlessImage--abstracts a blittable portion of a canvas
		class CSeamlessImage
		{
		public:
			//construct from source canvas, source rectangle,and offset point
			CSeamlessImage ( CCanvas* pcnvSource, bool freeSrc = false ) ;
			CSeamlessImage ( CCanvas* pcnvSource , CRectangle rcSource, bool freeSrc = false, CPoint ptOffset = CPoint(0 ,0) ) ;
			//destroy SeamlessImage
			virtual ~CSeamlessImage ( ) ;
			//retrieve pointer to canvas
			CCanvas* GetCanvas ( ) ;
			//set new canvas
			void SetCanvas ( CCanvas* pcnvSource ) ;
			//access source rectangle
			const CRectangle& SrcRect ( ) const;
			//access destination rectangle
			const CRectangle& DstRect ( ) const;
			//blit SeamlessImage onto a canvas
			void Put ( CCanvas* pcnvDest , const CPoint& ptDst ) ;

			CRectangle GetSrc() const { return m_rcSrc; }
			void SetSrc(CRectangle val) { m_rcSrc = val; }
			CRectangle GetDst() const { return m_rcDst; }
			void SetDst(CRectangle val) { m_rcDst = val; }

		private:
			//pointer to canvas
			CCanvas* m_pcnvSrc ;
			//source rectangle
			CRectangle m_rcSrc ;
			//destination rectangle
			CRectangle m_rcDst ;
			bool m_bFreeSrc;
		};

	} // namespace components
} // namespace gui

#endif
