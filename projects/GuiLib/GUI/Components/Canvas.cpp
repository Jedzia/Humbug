/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Canvas.cpp class.
 * \folder     $(folder)
 * \file       Canvas.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../stdafx.h"
//
#include "Canvas.h"
//
#include <GuiLib/GUI/Visual/Application.h>
#include <boost/foreach.hpp>
//
#include <build/cmake/include/debug.h>

namespace gui {
namespace components {
using namespace std;

CCanvas::CCanvas(SDL_Surface* pSurface, bool owner)
    : m_bOwner(owner), m_bTextureOwner(false), m_bIsParameterClass(false), m_pWindow(nullptr), m_pSurface(nullptr), m_pTexture(nullptr),
    m_pRenderer(nullptr) {
    //dbgOut(__FUNCTION__ << std::endl);
    SetSurface(pSurface);
    m_lstUpdateRects.clear();
}

CCanvas::CCanvas (SDL_Window* pWindow)
    : m_bOwner(true), m_bTextureOwner(false), m_bIsParameterClass(false), m_pWindow(nullptr), m_pSurface(nullptr), m_pTexture(nullptr),
    m_pRenderer(nullptr) {
    //dbgOut(__FUNCTION__ << std::endl);
    SetWindow(pWindow);
    m_lstUpdateRects.clear();
}

CCanvas::~CCanvas () {
    // Clean up
    ClearUpdateRects();

    if(m_pTexture) {
        if(m_bTextureOwner && m_pTexture) {
            SDL_DestroyTexture(m_pTexture);
            m_pTexture = nullptr;
        }
    }

    // do not Clean up when used as parameter
    if(m_bIsParameterClass) {
        return;
    }

    if(m_pRenderer) {
        SDL_DestroyRenderer(m_pRenderer);
        m_pRenderer = nullptr;
    }

    if(m_pWindow) {
        SDL_DestroyWindow(m_pWindow);
        SetWindow(NULL);
    }

    if(m_bOwner && m_pSurface) {
        SDL_FreeSurface(m_pSurface);
        m_pSurface = nullptr;
    }

    //dbgOut(__FUNCTION__ << std::endl);
}

void CCanvas::AddModifier(const CCanvasRenderer& updfunc) {
    m_vecRendererVault.push_back(updfunc);
}

SDL_Surface * CCanvas::GetSurface() const {
    return (m_pSurface);
}

SDL_Texture * CCanvas::GetTexture() {
    // Lazy Texture
    if(m_pTexture == nullptr) {
        if(this->m_pRenderer) {
            m_pTexture = SDL_CreateTextureFromSurface(this->m_pRenderer, m_pSurface);
        }
        else {
            m_pTexture = SDL_CreateTextureFromSurface(
                    CApplication::GetApplication()->GetMainCanvas()->m_pRenderer, m_pSurface);
        }

        m_bTextureOwner = true;
    }

    return m_pTexture;
}

void CCanvas::SetSurface(SDL_Surface* pSurface) {
    if(!pSurface) {
        return;
    }

    m_pSurface = pSurface;
}

void CCanvas::SetWindow(SDL_Window* pWindow) {
    m_pWindow = pWindow;

    if(pWindow) {
        m_pSurface = SDL_GetWindowSurface(pWindow);
        // Renderer uses VSYNC
        m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        dbgOut(__FUNCTION__ << " [" << this << "]" << " created Renderer " << " (" << m_pRenderer << ")" << " for Window " << " (" << pWindow << ")");
        m_pTexture = SDL_CreateTextureFromSurface(this->m_pRenderer, m_pSurface);
    }
}

SDL_Renderer * CCanvas::GetRenderer() const {
    if(this->m_pRenderer) {
        return m_pRenderer;
    }
    else {
        return CApplication::GetApplication()->GetMainCanvas()->m_pRenderer;
    }
}

void CCanvas::UpdateTexture(CCanvas* source, const CRectangle* dstRect, const CRectangle* srcRect) {
    if(!GetTexture() || !source->GetSurface()) {
        return;
    }

    UpdateTexture(GetTexture(), srcRect, source->GetSurface()->pixels, source->GetSurface()->pitch);
}

int CCanvas::UpdateTexture(SDL_Texture* texture, const CRectangle* rect, const void* pixels, int pitch) {
    const SDL_Rect* sdl_rect = rect ? rect->SDLRectCP() : NULL;
    return SDL_UpdateTexture(texture, sdl_rect, pixels, pitch);
}

void CCanvas::UpdateTexture(const CRectangle* dstRect, const CRectangle* srcRect) {
    if(!GetTexture() || !GetSurface()) {
        return;
    }

    UpdateTexture(GetTexture(), NULL, GetSurface()->pixels, GetSurface()->pitch);
}

bool CCanvas::ApplyRenderers(CCanvasRendererStorage& storage,
        CCanvas* source,
        const CCanvas* target,
        const CRectangle* dstRect,
        const CRectangle* srcRect) const {
    if(!source->m_vecRendererVault.empty()) {
        std::vector<CCanvasRendererStorage::iterator> removeList;

        CCanvasRendererStorage::iterator end = storage.end();
        CRectangle rdstRect;
        CRectangle rsrcRect;

        if(dstRect) {
            rdstRect = CRectangle(*dstRect);
        }

        if(srcRect) {
            rsrcRect = CRectangle(*srcRect);
        }

        CCanvasRenderModifierData mdata(&rsrcRect, &rdstRect);

        for(CCanvasRendererStorage::iterator it = storage.begin(); it < end; ++it)
        {
            (*it)(target, const_cast<CCanvas *>(source), mdata);
            if(mdata.markedForDeletion) {
                CCanvasRendererStorage::iterator it2 = it;
                // it has to be checked, if removing has no side effects. see CSpriteManager::OnIdle for a solution with "while".
                //removeList.push_back(it2);
                removeList.insert(removeList.begin(), it2);
            }
        }
        BOOST_FOREACH(CCanvasRendererStorage::iterator itpos, removeList)
        {
            storage.erase(itpos);
        }

        if(mdata.isHandled) {
            return true;
        }
    }

    return false;
} // CCanvas::ApplyRenderers

void CCanvas::RenderPutCopy(CCanvas* source, const CRectangle* dstRect, const CRectangle* srcRect) {
    if(!source->GetTexture()) {
        return;
    }

    // canvas based renderer, source modifier
    if(ApplyRenderers(source->m_vecRendererVault, source, this, dstRect, srcRect)) {
        return;
    }

    CanvasRenderCopy(source->GetTexture(), dstRect, srcRect);
} // CCanvas::RenderPutCopy

void CCanvas::RenderCopy(SDL_Texture* texture, const CRectangle* dstRect, const CRectangle* srcRect) {
    CanvasRenderCopy(texture, dstRect, srcRect);
}

void CCanvas::RenderCopy(const CRectangle* dstRect, const CRectangle* srcRect) {
    CanvasRenderCopy(GetTexture(), dstRect, srcRect);
}

void CCanvas::RenderCopy(const CPoint& offset) {
    CRectangle sdl_rect = GetDimension() + offset;
    CanvasRenderCopy(GetTexture(), &sdl_rect, NULL);
    //RenderCopy(static_cast<const CRectangle*>(NULL), &sdl_rect);
}

void CCanvas::Render(CCanvas* source, const CRectangle* dstRect, const CRectangle* srcRect) {
    m_pTexture = SDL_CreateTextureFromSurface(GetRenderer(), source->GetSurface());
    UpdateTexture(GetTexture(), srcRect, source->GetSurface()->pixels, source->GetSurface()->pitch);
    RenderCopy(GetTexture(), dstRect, srcRect);
}

void CCanvas::Render(SDL_Surface* source, const CRectangle* dstRect, const CRectangle* srcRect) {
    m_pTexture = SDL_CreateTextureFromSurface(GetRenderer(), source);
    const SDL_Rect* sdl_src_rect = NULL;
    UpdateTexture(GetTexture(), srcRect, source->pixels, source->pitch);
    RenderCopy(GetTexture(), dstRect, srcRect);
}

void CCanvas::CanvasRenderCopy(SDL_Texture* texture, const CRectangle* dstRect, const CRectangle* srcRect) {
    // all RenderCopy calls flow here

    // canvas based renderer, this instance modifier

    if(!m_vecRendererVault.empty()) {
        CCanvas source(this->GetSurface());
        source.m_bIsParameterClass = true;
        source.m_pRenderer = GetRenderer();
        source.m_pTexture = texture;

        if(ApplyRenderers(m_vecRendererVault, this, &source, dstRect, srcRect)) {
            return;
        }

        /*CCanvasRendererStorage::iterator end = m_vecRendererVault.end();

           for(CCanvasRendererStorage::iterator it = m_vecRendererVault.begin(); it < end; ++it)
           {
            //(*it)(&source, const_cast<CCanvas *>(this), mdata);
            (*it)(this, const_cast<CCanvas *>(&source), mdata);
           }
           if(mdata.isHandled) {
            return;
           }*/
    }

    FinalRenderCopy(texture, dstRect, srcRect);
} // CCanvas::CanvasRenderCopy

void CCanvas::FinalRenderCopy(SDL_Texture* texture, const CRectangle* dstRect, const CRectangle* srcRect) const {
    // all RenderCopy calls flow here
    const SDL_Rect* sdl_src_rect = srcRect ? srcRect->SDLRectCP() : NULL;
    const SDL_Rect* sdl_dst_rect = dstRect ? dstRect->SDLRectCP() : NULL;
    int result = SDL_RenderCopy(GetRenderer(), texture, sdl_src_rect, sdl_dst_rect);
}

void CCanvas::MainUpdateAndRenderCopy(const CRectangle* dstRect, const CRectangle* srcRect) {
    // this works only for the main canvas
    if(!m_pRenderer) {
        return;
    }

    //SDL_Texture *tex = SDL_CreateTextureFromSurface(this->m_pRenderer, GetSurface());
    UpdateTexture(GetTexture(), srcRect, GetSurface()->pixels, GetSurface()->pitch);
    RenderCopy(GetTexture(), dstRect, srcRect);
}

void CCanvas::MainRenderCopyTo(const CRectangle* dstRect, const CRectangle* srcRect) {
    // Todo: all Render** should check the exit codes
    // see: https://wiki.libsdl.org/SDL_RenderCopy
    // Return Value
    // Returns 0 on success or a negative error code on failure; call SDL_GetError() for more
    // information.
    CApplication::GetApplication()->GetMainCanvas()->RenderPutCopy(this, dstRect, srcRect);

    //SDL_UpdateTexture(m_pTexture, NULL, source->GetSurface()->pixels,
    // source->GetSurface()->pitch);
    //CanvasRenderCopy(this->m_pRenderer, m_pTexture, srcRect, dstRect);
    //CanvasRenderCopy(this->m_pRenderer, GetTexture(), srcRect, dstRect);
}

void CCanvas::MainRenderFinal() {
    SDL_RenderPresent(CApplication::GetApplication()->GetMainCanvas()->GetRenderer());
}

void CCanvas::MainRenderClear() {
    SDL_RenderClear(CApplication::GetApplication()->GetMainCanvas()->GetRenderer());
}

void CCanvas::SetTextureColorMod(const CColor& sdl_color) {
    /*if (!m_pTexture) {
        // for testing, remove later.
        throw std::runtime_error("no texture available");
        return;
       }*/

    SDL_SetTextureColorMod(GetTexture(), sdl_color.GetR(), sdl_color.GetG(), sdl_color.GetB());
// Returns 0 on success or a negative error code on failure; call SDL_GetError() for more
// information.
// Todo: check error info, like in all of these calls ...
}

void CCanvas::SetTextureAlphaMod(Uint8 alpha) {
    SDL_SetTextureAlphaMod(GetTexture(), alpha);
}

void CCanvas::SetRenderDrawBlendMode(BlendMode mode) const {
    SDL_SetRenderDrawBlendMode(GetRenderer(), static_cast<SDL_BlendMode>(mode));
}

bool CCanvas::Lock() const {
    /*if ( SDL_MUSTLOCK ( GetSurface ( ) ) ) {
       if ( SDL_LockSurface ( GetSurface ( ) ) == 0 ) {
       return ( true );
       }
       else {
       return ( false );
       }
       }*/

    return (true);
}

void CCanvas::Unlock() const {
    //MainUpdateAndRenderCopy();
//    if ( SDL_MUSTLOCK ( GetSurface ( ) ) ) {
//        SDL_UnlockSurface ( GetSurface ( ) );
//    }
}

CColor CCanvas::GetPixel (int x, int y) {
    Uint32 color = 0;
    int position = y * GetSurface()->pitch + GetSurface()->format->BytesPerPixel * x;
    char* buffer = static_cast<char *>(GetSurface()->pixels);
    buffer += position;
    memcpy(&color, buffer, GetSurface()->format->BytesPerPixel);
    CColor col;
    SDL_GetRGB(color, GetSurface()->format, &col.R(), &col.G(), &col.B());
    return (col);
}

void CCanvas::SetPixel (int x, int y, CColor& color) {
    int position = y * GetSurface()->pitch + GetSurface()->format->BytesPerPixel * x;
    char* buffer = static_cast<char *>(GetSurface()->pixels);
    buffer += position;
    Uint32 col = SDL_MapRGB(GetSurface()->format, color.R(), color.G(), color.B());
    memcpy(buffer, &col, GetSurface()->format->BytesPerPixel);
}

int CCanvas::GetWidth () const {
    return (GetSurface()->w);
}

int CCanvas::GetHeight () const {
    return (GetSurface()->h);
}

CRectangle CCanvas::GetDimension () const {
    CRectangle rect(0, 0, GetWidth(), GetHeight());
    return rect;
}

void CCanvas::AddUpdateRect (const CRectangle& UpdateRect) {
    return;

    SDL_Rect* pRect = NULL;
    pRect = new SDL_Rect;
    pRect->x = UpdateRect.GetX();
    pRect->y = UpdateRect.GetY();
    pRect->w = UpdateRect.GetW();
    pRect->h = UpdateRect.GetH();
    m_lstUpdateRects.push_back(pRect);
}

void CCanvas::ClearUpdateRects () {
    list<SDL_Rect *>::iterator iter;
    SDL_Rect* pRect;

    while(!m_lstUpdateRects.empty())
    {
        iter = m_lstUpdateRects.begin();
        pRect = *iter;
        m_lstUpdateRects.erase(iter);

        if(pRect) { delete pRect; }
    }
}

void CCanvas::UpdateRects () {
    list<SDL_Rect *>::iterator iter;
    SDL_Rect* pRect;

    for(iter = m_lstUpdateRects.begin(); iter != m_lstUpdateRects.end(); ++iter)
    {
        pRect = *iter;

        if(pRect) {
            //SDL_UpdateRect ( GetSurface ( ), pRect->x, pRect->y, pRect->w, pRect->h );
            //SDL_RenderPresent(m_pRenderer);
        }
        else {
            //SDL_UpdateRect ( GetSurface ( ), 0, 0, GetWidth ( ), GetHeight ( ) );
            //SDL_RenderPresent(m_pRenderer);
        }
    }
    ClearUpdateRects();
}     // UpdateRects

bool CCanvas::Flip () {
    //SDL_RenderPresent(m_pRenderer);
    //return SDL_Flip(GetSurface()) == 0;
    return true;
}

bool CCanvas::SetColorKey (CColor& color) {
    Uint32 col = SDL_MapRGB(GetSurface()->format, color.R(), color.G(), color.B());
    SetTextureColorMod(color);
    int result = SDL_SetColorKey(GetSurface(), SDL_TRUE, col);
    return (result == 0);
}

CColor CCanvas::GetColorKey () const {
    Uint32 col;
    Uint32 result = SDL_GetColorKey(GetSurface(), &col);
    CColor color;
    SDL_GetRGB(col, GetSurface()->format, &color.R(), &color.G(), &color.B());
    return (color);
}

bool CCanvas::ClearColorKey () const {
    if(m_pTexture) {
        SDL_SetTextureColorMod(m_pTexture, 255, 255, 255);
    }

    return (SDL_SetColorKey(GetSurface(), 0, 0) == 0);
}

void CCanvas::SetClipRect (CRectangle* pRect) const {
    if(pRect) {
        SDL_SetClipRect(GetSurface(), *pRect);
    }
    else {
        SDL_SetClipRect(GetSurface(), NULL);
    }
}

CRectangle CCanvas::GetClipRect () const {
    SDL_Rect rect;
    SDL_GetClipRect(GetSurface(), &rect);
    return (rect);
}

bool CCanvas::FillRect(const CRectangle& rect, const CColor& color) const {
    Uint32 col = SDL_MapRGB(GetSurface()->format, color.GetR(), color.GetG(), color.GetB());
    return (SDL_FillRect(GetSurface(), rect.SDLRectCP(), col) == 0);
}

void CCanvas::RenderDrawPoint(const CPoint& coordinates, const CColor* color) const {
    if(color) {
        SDL_SetRenderDrawColor(GetRenderer(), color->GetR(), color->GetG(), color->GetB(), color->GetA());
    }

    SDL_RenderDrawPoint(GetRenderer(), coordinates.GetX(), coordinates.GetY());
}

void CCanvas::RenderDrawLine(const CPoint& pStart, const CPoint& pEnd, const CColor* color) const {
    if(color) {
        SDL_SetRenderDrawColor(GetRenderer(), color->GetR(), color->GetG(), color->GetB(), color->GetA());
    }

    SDL_RenderDrawLine(GetRenderer(), pStart.GetX(), pStart.GetY(), pEnd.GetX(), pEnd.GetY());
}

bool CCanvas::RenderDrawRect(const CRectangle& rect, const CColor* color) const {
    int ret = 0;
    if(color) {
        ret = SDL_SetRenderDrawColor(GetRenderer(), color->GetR(), color->GetG(), color->GetB(), color->GetA());
    }

    ret = SDL_RenderDrawRect(GetRenderer(), rect.SDLRectCP());
    return true;
}

bool CCanvas::RenderFillRect(const CRectangle& rect, const CColor* color) const {
    // Uint32 col = SDL_MapRGB(GetSurface()->format, color.GetR(), color.GetG(), color.GetB());
    int ret = 0;
    if (color) {
        ret = SDL_SetRenderDrawColor(GetRenderer(), color->GetR(), color->GetG(), color->GetB(), color->GetA());
    }

    ret = SDL_RenderFillRect(GetRenderer(), rect.SDLRectCP());
    return true;
}

bool CCanvas::RenderFillRect(const CRectangle& rect, const CColor& color) const {
    int   ret = SDL_SetRenderDrawColor(GetRenderer(), color.GetR(), color.GetG(), color.GetB(), color.GetA());
    ret = SDL_RenderFillRect(GetRenderer(), rect.SDLRectCP());
    return true;
}

bool CCanvas::Clear(const CColor& color) const {
    Uint32 col = SDL_MapRGB(GetSurface()->format, color.GetR(), color.GetG(), color.GetB());

    if(m_pTexture) {
        CRectangle dimension = GetDimension();
        RenderFillRect(dimension, &color);
        //SDL_RenderClear(GetRenderer());
    }

    return (SDL_FillRect(GetSurface(), NULL, col) == 0);
}

bool CCanvas::Blit (const CRectangle& rectDst, const CCanvas& cnvSrc, const CRectangle& rectSrc) const {
    CRectangle rectDst2 = rectDst;
    CRectangle rectSrc2 = rectSrc;
    return (SDL_BlitSurface(cnvSrc.GetSurface(), rectSrc2, GetSurface(), rectDst2) == 0);
}

CCanvas * CCanvas::CreateRGB (Uint32 flags, int width, int height, int depth, Uint32 Rmask,
        Uint32 Gmask, Uint32 Bmask,
        Uint32 Amask) {
    CCanvas* pCanvas = new CCanvas(static_cast<SDL_Surface *>(NULL));
    pCanvas->SetSurface(SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask,
                    Amask));
    pCanvas->m_bOwner = true;
    return (pCanvas);
}

CCanvas * CCanvas::CreateRGBCompatible (Uint32 flags, int width, int height) {
    // throw std::exception("Fuck !");
    //auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
    auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
    SDL_PixelFormat* format = surface->format;
    return (CreateRGB(flags, width, height, format->BitsPerPixel, format->Rmask, format->Gmask,
                    format->Bmask, format->Amask));
}

CCanvas * CCanvas::LoadBMP (string sFileName) {
    SDL_Surface* pSurface = SDL_LoadBMP(sFileName.c_str());
    return (new CCanvas(pSurface, true));
}

CCanvas * CCanvas::LoadBMPCompatible (string sFileName) {
    //throw std::exception("Fuck !");
    SDL_Surface* pSurface = SDL_LoadBMP(sFileName.c_str());
    //SDL_Surface* pSurface2 = SDL_DisplayFormat(pSurface);
    auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
    SDL_Surface* pSurface2 = SDL_ConvertSurfaceFormat(pSurface, surface->format->format, 0);
    SDL_FreeSurface(pSurface);
    return (new CCanvas(pSurface2, true));
}

//match color with closest
CColor CCanvas::MatchColor (CColor color) {
    //convert it to the pixel format
    Uint32 col = SDL_MapRGB(GetSurface()->format, color.R(), color.G(), color.B());

    //convert it from the pixel format
    SDL_GetRGB(col, GetSurface()->format, &color.R(), &color.G(), &color.B());

    //return the matched color
    return (color);
}

void CCanvas::Invalidate() {
    AddUpdateRect(GetDimension());
}
}   // namespace components
} // namespace gui
