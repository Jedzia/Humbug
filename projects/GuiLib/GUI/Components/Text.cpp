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
#include "Text.h"
#include "Canvas.h"
//#include "../Data/ColorData.h"

//#include <build/cmake/include/debug.h>

namespace gui {
namespace components {

CText::CText( TTF_Font* font, std::string text, CColor textcolor /*= CColor::Black()*/ ) :
    m_pFont(font),
    m_strText(text),
    m_colText(textcolor){
    dbgOut(__FUNCTION__);
    m_pText = new CCanvas(TTF_RenderText_Solid(m_pFont, m_strText.c_str(), m_colText));

}

CText::~CText(){
    m_pFont = NULL;
    delete m_pText;
    m_pText = NULL;
    dbgOut(__FUNCTION__);
}


void CText::Put(CCanvas *canvas, const CRectangle& dstRect, const CRectangle& srcRect  ) const {
    m_pText->Lock();

    CTextModifierData mdata;
    if (!m_vecModifierVault.empty())
    {
        TextModifierStorage::const_iterator end = m_vecModifierVault.end();
        for (TextModifierStorage::const_iterator it = m_vecModifierVault.begin(); it < end ; it++)
        {
            (*it)(m_pText, const_cast<CText *>(this), mdata );
        }
    }

    m_pText->Unlock();

    //CRectangle dstRect2(dstRect);
    //dstRect2.Offset(mdata.DeltaX, mdata.DeltaY);
    //CRectangle srcRect2(srcRect);
    //srcRect2.Offset(mdata.DeltaX, mdata.DeltaY);
    canvas->Blit(dstRect , *m_pText, srcRect );
    //canvas->AddUpdateRect(dstRect);
    canvas->AddUpdateRect(dstRect);
    //canvas->AddUpdateRect(canvas->GetDimension());
}

void CText::RunModifiers(CCanvas *textcanvas) const
{
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

void CText::AddModifier( TextModifier updfunc )
{
    m_vecModifierVault.push_back(updfunc);
}


CTextParagraph::CTextParagraph( TTF_Font *font, std::string text, CColor textcolor /*= CColor::Black()*/ )
{

}

CTextParagraph::~CTextParagraph()
{

}

} // namespace components
} // namespace gui
