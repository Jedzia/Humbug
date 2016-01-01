/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Text.cpp class.
 * \folder     $(folder)
 * \file       Text.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
//
#include "stdafx.h"
//
#include "Canvas.h"
#include "Text.h"
//#include "../Data/ColorData.h"

//#include <build/cmake/include/debug.h>

namespace gui {
namespace components {
CText::CText( TTF_Font* font, std::string text, CColor textcolor /*= CColor::Black()*/ ) :
    m_pFont(font),
    m_strText(text),
    m_colText(textcolor){
    dbgOut(__FUNCTION__);
    m_pRenderText = TTF_RenderText_Solid(m_pFont, m_strText.c_str(), m_colText);
    m_pText.reset(new CCanvas(m_pRenderText));
}

CText::~CText(){
    m_pFont = NULL;

    if (m_pRenderText)
    {
        SDL_FreeSurface(m_pRenderText);
    }
    

    //delete m_pText;
    //m_pText = NULL;
    dbgOut(__FUNCTION__);
}

/** $(class), Put:
 *  Detailed description.
 *  @param canvas TODO
 * @param dstRect TODO
 * @param srcRect TODO
 * @return TODO
 */
void CText::Put(CCanvas* canvas, const CRectangle& dstRect, const CRectangle& srcRect  ) const {
    m_pText->Lock();

    CTextModifierData mdata;

    if ( !m_vecModifierVault.empty() ) {
        TextModifierStorage::const_iterator end = m_vecModifierVault.end();

        for (TextModifierStorage::const_iterator it = m_vecModifierVault.begin(); it < end; it++)
        {
            (*it)(m_pText.get(), const_cast<CText *>(this), mdata );
        }
    }

    m_pText->Unlock();

    //CRectangle dstRect2(dstRect);
    //dstRect2.Offset(mdata.DeltaX, mdata.DeltaY);
    //CRectangle srcRect2(srcRect);
    //srcRect2.Offset(mdata.DeltaX, mdata.DeltaY);
    canvas->Blit(dstRect, *m_pText, srcRect);

    //SDL_Rect src_rect = srcRect.SDLRect();
    //SDL_Rect dst_rect = dstRect.SDLRect();
    //canvas->Render(m_pText, &src_rect, &dst_rect);

    //canvas->AddUpdateRect(dstRect);
    canvas->AddUpdateRect(dstRect);
    //canvas->AddUpdateRect(canvas->GetDimension());
}     // CText::Put

/** $(class), Put:
 *  Detailed description.
 *  @param canvas TODO
 * @param dstRect TODO
 * @return TODO
 */
void CText::Put(CCanvas* canvas, const CRectangle& dstRect) const {
    Put( canvas, dstRect, GetCanvas()->GetDimension() );
}

/** $(class), SetColor:
 *  Detailed description.
 *  @param m_col_text TODO
 * @return TODO
 */
void CText::SetColor(const CColor m_col_text){
    //return;
    if (m_pRenderText)
    {
        SDL_FreeSurface(m_pRenderText);
    }
    //if (m_pText) {
    //    delete m_pText;
   // }

    m_colText = m_col_text;
    m_pRenderText = TTF_RenderText_Solid(m_pFont, m_strText.c_str(), m_colText);
    m_pText.reset(new CCanvas(m_pRenderText));
}

/** $(class), RunModifiers:
 *  Detailed description.
 *  @param textcanvas TODO
 * @return TODO
 */
void CText::RunModifiers(CCanvas* textcanvas) const {
    /*return;
       SDL_Color cmap[256];
       memset(cmap, 0, sizeof(cmap));

       static int boatcols=0;
       static int frames=0;

       SDL_Color *wavemap = ColorData::Instance()->Wavemap();
       for(int i = 0; i < 64; i++)
        cmap[boatcols + ((i + frames) & 63)] = wavemap[i];

       //SDL_SetPalette(m_pText->GetSurface(), SDL_LOGPAL, wavemap, boatcols, 32);
       SDL_SetPalette(textcanvas->GetSurface(), SDL_LOGPAL, cmap, 0, 256);
       //boatcols++;
       frames++;
       if ( frames > 16   )
       {
        //frames = 0;
       }*/
}

/** $(class), AddModifier:
 *  Detailed description.
 *  @param updfunc TODO
 * @return TODO
 */
void CText::AddModifier( TextModifier updfunc ){
    m_vecModifierVault.push_back(updfunc);
}

CTextParagraph::CTextParagraph( TTF_Font* font, std::string text, CColor textcolor     /*=
                                                                                          CColor::Black()*/
        )
{}

CTextParagraph::~CTextParagraph()
{}
}   // namespace components
} // namespace gui
