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

void CText::Put(CCanvas *canvas, const CRectangle& dstRect, const CRectangle& srcRect  ) const {

    m_pText->Lock();
    m_pText->Unlock();

    canvas->Blit(dstRect , *m_pText, srcRect );
    canvas->AddUpdateRect(dstRect);
}

