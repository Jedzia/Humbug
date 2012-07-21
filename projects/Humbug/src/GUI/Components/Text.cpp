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
#include "../Data/ColorData.h"

//#include <build/cmake/include/debug.h>
CText::CText( TTF_Font* font, std::string text, CColor textcolor /*= CColor::Black()*/ ) :
    m_pFont(font),
    m_strText(text),
    m_colText(textcolor){
    dbgOut(__FUNCTION__ << std::endl);
    m_pText = new CCanvas(TTF_RenderText_Solid(m_pFont, m_strText.c_str(), m_colText));

}

CText::~CText(void){
    m_pFont = NULL;
    delete m_pText;
    m_pText = NULL;
    dbgOut(__FUNCTION__ << std::endl);
}

void CText::Put(CCanvas *canvas, const CRectangle& dstRect, const CRectangle& srcRect  ) const {

    SDL_Color cmap[256];
    memset(cmap, 0, sizeof(cmap));
    //SDL_SetPalette(canvas->GetSurface(), SDL_PHYSPAL, cmap, 0, 256);

    m_pText->Lock();
    static int boatcols=0;
    static int frames=0;

    SDL_Color *wavemap = ColorData::Instance()->Wavemap();
    for(int i = 0; i < 64; i++)
        //cmap[boatcols + ((i + frames) & 63)] = wavemap[i];
        cmap[boatcols + ((i + frames) & 63)] = wavemap[i];

    //SDL_SetPalette(m_pText->GetSurface(), SDL_LOGPAL, wavemap, boatcols, 32);
    SDL_SetPalette(m_pText->GetSurface(), SDL_LOGPAL, cmap, 0, 256);
    m_pText->Unlock();
    //boatcols++;
    frames++;
    if ( frames > 16   )
    {
        //frames = 0;
    }

    canvas->Blit(dstRect , *m_pText, srcRect );
    canvas->AddUpdateRect(dstRect);
}

