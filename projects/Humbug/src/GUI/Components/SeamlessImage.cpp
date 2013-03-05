/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SeamlessImage.cpp class.
 * \folder     $(folder)
 * \file       SeamlessImage.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../stdafx.h"
#include "SeamlessImage.h"

namespace gui {
  namespace components {
    CSeamlessImage::CSeamlessImage ( CCanvas* pcnvSource, bool freeSrc ) :
        m_bFreeSrc(freeSrc){
        dbgOut(__FUNCTION__ << std::endl);
        SetCanvas ( pcnvSource );
        m_rcSrc = m_rcDst = pcnvSource->GetDimension();
    }

    CSeamlessImage::CSeamlessImage ( CCanvas* pcnvSource, CRectangle rcSource, bool freeSrc, CPoint ptOffset ) :
        m_bFreeSrc(freeSrc){
        dbgOut(__FUNCTION__ << std::endl);
        SetCanvas ( pcnvSource );
        m_rcSrc = rcSource;
        m_rcDst = rcSource;
        m_rcDst -= ptOffset;
    }

    CSeamlessImage::~CSeamlessImage ( ){
        if (m_bFreeSrc) {
            delete m_pcnvSrc;
        }

        dbgOut(__FUNCTION__ << std::endl);
    }

    /** CSeamlessImage, GetCanvas:
     *  Detailed description.
     *  @return TODO
     */
    CCanvas * CSeamlessImage::GetCanvas ( ){
        return ( m_pcnvSrc );
    }

    /** CSeamlessImage, SetCanvas:
     *  Detailed description.
     *  @param pcnvSource TODO
     * @return TODO
     */
    void CSeamlessImage::SetCanvas ( CCanvas* pcnvSource ){
        m_pcnvSrc = pcnvSource;
    }

    /** CSeamlessImage, SrcRect:
     *  Detailed description.
     *  @return TODO
     */
    const CRectangle& CSeamlessImage::SrcRect ( ) const {
        return ( m_rcSrc );
    }

    /** CSeamlessImage, DstRect:
     *  Detailed description.
     *  @return TODO
     */
    const CRectangle& CSeamlessImage::DstRect ( ) const {
        return ( m_rcDst );
    }

    /** CSeamlessImage, Put:
     *  Detailed description.
     *  @param pcnvDest TODO
     * @param ptDst TODO
     * @return TODO
     */
    void CSeamlessImage::Put ( CCanvas* pcnvDest, const CPoint& ptDst ){
        CRectangle painton = pcnvDest->GetDimension();
        CRectangle diffrec = m_rcDst + ptDst;
        pcnvDest->Blit ( diffrec, *GetCanvas ( ), m_rcSrc );
        //DstRect ( ) -= ptDst;
    }
  }       // namespace components
} // namespace gui
