#include "../../stdafx.h"
#include "SeamlessImage.h"

namespace gui {
	namespace components {

		CSeamlessImage::CSeamlessImage ( CCanvas* pcnvSource, bool freeSrc )
			: m_bFreeSrc(freeSrc){
				dbgOut(__FUNCTION__ << std::endl);
				SetCanvas ( pcnvSource );
				m_rcSrc = m_rcDst = pcnvSource->GetDimension();
		}

		CSeamlessImage::CSeamlessImage ( CCanvas* pcnvSource, CRectangle rcSource, bool freeSrc, CPoint ptOffset )
			: m_bFreeSrc(freeSrc){
				dbgOut(__FUNCTION__ << std::endl);
				SetCanvas ( pcnvSource );
				m_rcSrc = rcSource;
				m_rcDst = rcSource;
				m_rcDst -= ptOffset;
		}

		CSeamlessImage::~CSeamlessImage ( )
		{
			if (m_bFreeSrc)
			{
				delete m_pcnvSrc;
			}
			dbgOut(__FUNCTION__ << std::endl);
		}

		CCanvas * CSeamlessImage::GetCanvas ( ){
			return ( m_pcnvSrc );
		}

		void CSeamlessImage::SetCanvas ( CCanvas* pcnvSource ){
			m_pcnvSrc = pcnvSource;
		}

		const CRectangle& CSeamlessImage::SrcRect ( ) const {
			return ( m_rcSrc );
		}

		const CRectangle& CSeamlessImage::DstRect ( ) const {
			return ( m_rcDst );
		}

		void CSeamlessImage::Put ( CCanvas* pcnvDest, const CPoint& ptDst ){
			CRectangle painton = pcnvDest->GetDimension();
			CRectangle diffrec =  m_rcDst + ptDst;
			pcnvDest->Blit ( diffrec, *GetCanvas ( ), m_rcSrc );
			//DstRect ( ) -= ptDst;
		}

	} // namespace components
} // namespace gui
