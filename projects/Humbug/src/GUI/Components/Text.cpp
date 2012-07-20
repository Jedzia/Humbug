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
#include "stdafx.h"
#include "Text.h"
#include "Canvas.h"

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

static SDL_Color wavemap[] = {
    {0,2,103}, {0,7,110}, {0,13,117}, {0,19,125},
    {0,25,133}, {0,31,141}, {0,37,150}, {0,43,158},
    {0,49,166}, {0,55,174}, {0,61,182}, {0,67,190},
    {0,73,198}, {0,79,206}, {0,86,214}, {0,96,220},
    {5,105,224}, {12,112,226}, {19,120,227}, {26,128,229},
    {33,135,230}, {40,143,232}, {47,150,234}, {54,158,236},
    {61,165,238}, {68,173,239}, {75,180,241}, {82,188,242},
    {89,195,244}, {96,203,246}, {103,210,248}, {112,218,250},
    {124,224,250}, {135,226,251}, {146,229,251}, {156,231,252},
    {167,233,252}, {178,236,252}, {189,238,252}, {200,240,252},
    {211,242,252}, {222,244,252}, {233,247,252}, {242,249,252},
    {237,250,252}, {209,251,252}, {174,251,252}, {138,252,252},
    {102,251,252}, {63,250,252}, {24,243,252}, {7,225,252},
    {4,203,252}, {3,181,252}, {2,158,252}, {1,136,251},
    {0,111,248}, {0,82,234}, {0,63,213}, {0,50,192},
    {0,39,172}, {0,28,152}, {0,17,132}, {0,7,114}
};

void CText::Put(CCanvas *canvas, const CRectangle& dstRect, const CRectangle& srcRect  ) const {

    SDL_Color cmap[256];
    memset(cmap, 0, sizeof(cmap));
    //SDL_SetPalette(canvas->GetSurface(), SDL_PHYSPAL, cmap, 0, 256);

    m_pText->Lock();
    static int boatcols=0;
    static int frames=0;
    for(int i = 0; i < 64; i++)
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

