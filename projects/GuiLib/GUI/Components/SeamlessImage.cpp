/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
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
#include "../../Filesystem/FileLoader.h"
#include "Text.h"

//using gui::controls::CControl;

namespace gui {
  namespace components {

	  //gui::controls::CButton* testbutton;

      enum CSeamlessImageOrigin
      {
          Origin,
          N,
          NE,
          E,
          SE,
          S,
          SW,
          W,
          NW,
          CSeamlessImageOrigin_END
      };

      static char *CSeamlessImageOriginNames[CSeamlessImageOrigin_END] =
      {
          "Origin",
          "N",
          "NE",
          "E",
          "SE",
          "S",
          "SW",
          "W",
          "NW"
      };

      static float windrose[CSeamlessImageOrigin_END][2] = {
          {  0,  0 }, // Origin
          {  0,  1 }, // N
          {  1,  1 }, // NE
          {  1,  0 }, // E
          {  1, -1 }, // SE
          {  0, -1 }, // S
          { -1, -1 }, // SW
          { -1,  0 }, // W
          { -1,  1 }  // NW
      };

    CSeamlessImage::CSeamlessImage ( CCanvas* pcnvSource, bool freeSrc ) :
        m_bFreeSrc(freeSrc), m_pLoader(NULL){
        dbgOut(__FUNCTION__);
        SetCanvas ( pcnvSource );
        m_rcSrc = m_rcDst = pcnvSource->GetDimension();

		
		//CControl* masterctrl = new CControl(CControl::GetMainControl()->GetCanvas());
		//CControl* masterctrl = new CControl(CControl::GetMainControl()->GetCanvas());
		//testbutton = new gui::controls::CButton(CControl::GetMainControl(), CRectangle(0,0,160,40), 21345, "Change Direction");
		//testbutton->SetPosition(CPoint(200,200));
    }

    CSeamlessImage::CSeamlessImage ( CCanvas* pcnvSource, CRectangle rcSource, bool freeSrc, CPoint ptOffset ) :
        m_bFreeSrc(freeSrc), m_pLoader(NULL){
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

    void CSeamlessImage::RenderPut(CCanvas* pcnvDest, const CPoint& ptDstOrig)
    {
        int w = m_rcDst.GetW();
        int h = m_rcDst.GetH();
        CPoint ptDst((ptDstOrig.GetX() % w), (ptDstOrig.GetY() % h));
        CRectangle painton = pcnvDest->GetDimension();
        CRectangle diffrec = m_rcDst + ptDst;

        int maxX = static_cast<int>(ceil(painton.GetW() / static_cast<float>(w)));
        int maxY = static_cast<int>(ceil(painton.GetH() / static_cast<float>(h)));

        int maxExpansionX = maxX;
        int maxExpansionY = maxY;
//        int maxExpansionX = 3;
//        int maxExpansionY = 3;

        for (int xr = -maxExpansionX; xr < maxExpansionX + 1; xr++)
        {
            for (int yr = -maxExpansionY; yr < maxExpansionY + 1; yr++)
            {
                //for (int i = 0; i < CSeamlessImageOrigin_END; i++)
                {
                    //float diffx = windrose[i][0];
                    //float diffy = windrose[i][1];
                    float diffx = static_cast<float>(xr);
                    float diffy = static_cast<float>(yr);

                    int x = static_cast<int>(ceil(w * diffx));
                    int y = static_cast<int>(ceil(h * diffy));
                    CRectangle diffrec2 = diffrec + CPoint(x, y);
                    //pcnvDest->RenderCopy(GetCanvas(), painton, diffrec);
                    pcnvDest->RenderPutCopy(GetCanvas(), &diffrec2, &painton);

#ifdef DEBUG_SEAMLESSIMAGE
                    if (m_pLoader)
                    {
                        // show a label for each part of the image
                        static TTF_Font* arialfont = m_pLoader->FL_LOADFONT("Fonts/ARIAL.TTF", 24);
                        //char* c_seamless_image_origin_name = CSeamlessImageOriginNames[i];
                        std::ostringstream labelText;
                        labelText << "O(" << diffx << ", " << diffy << ")";
                        CText label(arialfont, (labelText.str()), CColor::DarkRed());
                        int labelWidth = label.GetCanvas()->GetWidth() / 2;
                        int labelHeight = label.GetCanvas()->GetHeight() / 2;
                        CRectangle diffrec3 = diffrec2 + CPoint((m_rcDst.GetW() / 2) - labelWidth, (m_rcDst.GetH() / 2) - labelHeight);
                        label.RenderPut(pcnvDest, diffrec3);
                    }
#endif
                }
            }
        }
        return;
//        CRectangle painton = pcnvDest->GetDimension();
//        CRectangle diffrec = m_rcDst + ptDst;
//        pcnvDest->RenderCopy(GetCanvas(), painton, diffrec);
//
//        // east
//        CRectangle diffrec2 = diffrec + CPoint(m_rcDst.GetW(), 0);
//        pcnvDest->RenderCopy(GetCanvas(), painton, diffrec2);
//
//        // west
//        CRectangle diffrec3 = diffrec + CPoint(-m_rcDst.GetW(), 0);
//        pcnvDest->RenderCopy(GetCanvas(), painton, diffrec3);
//
//        // north
//        CRectangle diffrec4 = diffrec + CPoint(0, m_rcDst.GetH());
//        pcnvDest->RenderCopy(GetCanvas(), painton, diffrec4);
//
//        // south
//        CRectangle diffrec5 = diffrec + CPoint(0, -m_rcDst.GetH());
//        pcnvDest->RenderCopy(GetCanvas(), painton, diffrec5);
    }
  }       // namespace components
} // namespace gui
