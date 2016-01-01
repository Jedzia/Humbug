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
#include <GuiLib/GUI/Visual/Application.h>

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

void CText::RenderPut(CCanvas* canvas, const CRectangle& dstRect) const
{
    RenderPut(canvas, dstRect, GetCanvas()->GetDimension());
}


void CText::RenderPut(CCanvas* canvas, const CRectangle& dstRect, const CRectangle& srcRect) const
{
    m_pText->Lock();

    CTextModifierData mdata;

    if (!m_vecModifierVault.empty()) {
        TextModifierStorage::const_iterator end = m_vecModifierVault.end();

        for (TextModifierStorage::const_iterator it = m_vecModifierVault.begin(); it < end; it++)
        {
            (*it)(m_pText.get(), const_cast<CText *>(this), mdata);
        }
    }

    m_pText->Unlock();




    /*TTF_Font* Sans = m_pFont; //this opens a font style and sets a size

    SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_pMainCanvas->m_pRenderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = dstRect.GetX();  //controls the rect's x coordinate 
    Message_rect.y = dstRect.GetY(); // controls the rect's y coordinte
    Message_rect.w = surfaceMessage->w; // controls the width of the rect
    Message_rect.h = surfaceMessage->h; // controls the height of the rect

    //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

    //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(m_pMainCanvas->m_pRenderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    */








    //CRectangle dstRect2(dstRect);
    //dstRect2.Offset(mdata.DeltaX, mdata.DeltaY);
    //CRectangle srcRect2(srcRect);
    //srcRect2.Offset(mdata.DeltaX, mdata.DeltaY);

    SDL_Rect src_rect = srcRect.SDLRect();
    SDL_Rect dst_rect = dstRect.SDLRect();
    CRectangle dest(dstRect);
    dest.SetW(srcRect.GetW());
    dest.SetH(srcRect.GetH());

    //SDL_BlitSurface(m_pRenderText, &src_rect, msurf, &dst_rect);
    //m_pMainCanvas->Blit(dstRect, *m_pText, srcRect);
    
    SDL_Rect sdl_rect = dest.SDLRect();

    //int offsX = 0;
    //int offsY = 0;
    //SDL_Rect rect = CRectangle(offsX, offsY, 373 - offsX, 55 - offsY).SDLRect();
    //canvas->Render(m_pRenderText, &rect, &sdl_rect);
    //canvas->Render(m_pRenderText, NULL, &sdl_rect);
    //canvas->Render(m_pText.get());
    m_pText->RenderCopy(NULL, &sdl_rect);
    //m_pText->RenderCopyToMain(NULL, &sdl_rect);

    //SDL_Rect rect = m_pText->GetDimension().SDLRect();
    //SDL_RenderCopy(m_pMainCanvas->m_pRenderer, m_pText->GetTexture(), NULL, &sdl_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    //SDL_Surface* tmpfsurf2 = SDL_ConvertSurfaceFormat(m_pRenderText, msurf->format->format, 0);
    //canvas->Render(tmpfsurf2);

    //canvas->UpdateTexture(m_pText.get(), &src_rect, &dst_rect);
    //CColor color = CColor::Red();
    //Uint32 col = SDL_MapRGB(msurf->format, color.GetR(), color.GetG(), color.GetB());
    //SDL_FillRect(msurf, &dst_rect, col);
    //canvas->AddUpdateRect(dstRect);
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

    canvas->Blit(dstRect, *m_pText, srcRect);
   
    //CRectangle dest(dstRect);
    //dest.SetW(srcRect.GetW());
    //dest.SetH(srcRect.GetH());
    //SDL_Rect sdl_rect = dest.SDLRect();
    //m_pText->RenderCopyToMain(NULL, &sdl_rect);

    canvas->AddUpdateRect(dstRect);
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
void CText::SetColor(const CColor textcolor){
    //return;
    if (m_pRenderText)
    {
        SDL_FreeSurface(m_pRenderText);
    }
    //if (m_pText) {
    //    delete m_pText;
   // }

    m_colText = textcolor;
    SDL_Color color = { 0, 0, 0 }, bgcolor = { 0xff, 0xff, 0xff };
    m_pRenderText = TTF_RenderText_Solid(m_pFont, m_strText.c_str(), m_colText);
    //m_pRenderText = TTF_RenderUTF8_Shaded(m_pFont, m_strText.c_str(), m_colText, bgcolor);
    //m_pRenderText = TTF_RenderUTF8_Shaded(m_pFont, m_strText.c_str(), m_colText, bgcolor);
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
