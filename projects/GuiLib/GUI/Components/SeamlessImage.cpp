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
#include "../Controls/Button.h"

//using gui::controls::CControl;

namespace gui {
  namespace components {

	  //gui::controls::CButton* testbutton;

    CSeamlessImage::CSeamlessImage ( CCanvas* pcnvSource, bool freeSrc ) :
        m_bFreeSrc(freeSrc){
        dbgOut(__FUNCTION__);
        SetCanvas ( pcnvSource );
        m_rcSrc = m_rcDst = pcnvSource->GetDimension();

		
		//CControl* masterctrl = new CControl(CControl::GetMainControl()->GetCanvas());
		//CControl* masterctrl = new CControl(CControl::GetMainControl()->GetCanvas());
		//testbutton = new gui::controls::CButton(CControl::GetMainControl(), CRectangle(0,0,160,40), 21345, "Change Direction");
		//testbutton->SetPosition(CPoint(200,200));
    }

    CSeamlessImage::CSeamlessImage ( CCanvas* pcnvSource, CRectangle rcSource, bool freeSrc, CPoint ptOffset ) :
        m_bFreeSrc(freeSrc){
        dbgOut(__FUNCTION__);
        SetCanvas ( pcnvSource );
        m_rcSrc = rcSource;
        m_rcDst = rcSource;
        m_rcDst -= ptOffset;
    }

    CSeamlessImage::~CSeamlessImage ( ){
        if (m_bFreeSrc) {
            delete m_pcnvSrc;
        }

        dbgOut(__FUNCTION__);
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
		
		CRectangle diffrec2 = diffrec + CPoint(2400,0);
		pcnvDest->Blit ( diffrec2, *GetCanvas ( ), m_rcSrc );
        //DstRect ( ) -= ptDst;
		
		//testbutton->Invalidate();
		//testbutton->Draw();
    }

    void CSeamlessImage::RenderPut(CCanvas* pcnvDest, const CPoint& ptDst)
    {
        CRectangle painton = pcnvDest->GetDimension();
        CRectangle diffrec = m_rcDst + ptDst;
        pcnvDest->RenderCopy(GetCanvas(), painton, diffrec);

        CRectangle diffrec2 = diffrec + CPoint(2400, 0);
        pcnvDest->RenderCopy(GetCanvas(), painton, diffrec);
    }
  }       // namespace components
} // namespace gui
