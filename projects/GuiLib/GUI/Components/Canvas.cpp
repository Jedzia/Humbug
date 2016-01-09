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
#include <build/cmake/include/debug.h>
#include <memory.h>
//
#include "Canvas.h"
#include <GuiLib/GUI/Visual/Application.h>

namespace gui {
namespace components {
using namespace std;

CCanvas::CCanvas(SDL_Surface* pSurface, bool owner)
    : m_bOwner(false), m_pWindow(nullptr), m_pSurface(nullptr), m_pTexture(nullptr), m_pRenderer(nullptr){
    //dbgOut(__FUNCTION__ << std::endl);
    SetSurface(pSurface);
    m_lstUpdateRects.clear();
}

CCanvas::CCanvas ( SDL_Window* pWindow )
    : m_bOwner(false), m_pWindow(nullptr), m_pSurface(nullptr), m_pTexture(nullptr), m_pRenderer(nullptr){
    //dbgOut(__FUNCTION__ << std::endl);
    SetWindow(pWindow);
    m_lstUpdateRects.clear ( );
}

CCanvas::~CCanvas ( ){
    ClearUpdateRects ( );

    // Clean up
    if (m_pTexture) {
        SDL_DestroyTexture(m_pTexture);
    }

    if (m_pRenderer) {
        SDL_DestroyRenderer(m_pRenderer);
    }

    if (m_pWindow) {
        SDL_DestroyWindow(m_pWindow);
        SetWindow(NULL);
    }

    if (m_bOwner && m_pSurface) {
        SDL_FreeSurface(m_pSurface);
        m_pSurface = nullptr;
    }

    //dbgOut(__FUNCTION__ << std::endl);
}

SDL_Surface * CCanvas::GetSurface() const {
    return ( m_pSurface );
}

SDL_Texture * CCanvas::GetTexture(){
    // Lazy Texture
    if (m_pTexture == nullptr) {
        if (this->m_pRenderer) {
            m_pTexture = SDL_CreateTextureFromSurface(this->m_pRenderer, m_pSurface);
        }
        else {
            m_pTexture = SDL_CreateTextureFromSurface(
                    CApplication::GetApplication()->GetMainCanvas()->m_pRenderer, m_pSurface);
        }
    }

    return m_pTexture;
}

void CCanvas::SetSurface(SDL_Surface* pSurface){
    if (!pSurface) {
        return;
    }

    //m_pSurface = SDL_CreateRGBSurfaceFrom() pSurface;
    //m_pSurface = SDL_CreateRGBSurfaceFrom(pSurface->pixels,);
    //auto mc = CApplication::GetApplication()->GetMainCanvas();
    //auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
    //if (surface)
    //m_pSurface = SDL_ConvertSurfaceFormat(pSurface, surface->format->format, 0);
    //else
    m_pSurface = pSurface;
}

void CCanvas::SetWindow(SDL_Window* pWindow){
    m_pWindow = pWindow;

    if (pWindow) {
        m_pSurface = SDL_GetWindowSurface(pWindow);
        m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
        m_pTexture = SDL_CreateTextureFromSurface(this->m_pRenderer, m_pSurface);
    }
}

SDL_Renderer * CCanvas::GetRenderer() const {
    if (this->m_pRenderer) {
        return m_pRenderer;
    }
    else {
        return CApplication::GetApplication()->GetMainCanvas()->m_pRenderer;
    }
}

void CCanvas::UpdateTexture(CCanvas* source, const SDL_Rect* srcRect, const SDL_Rect* dstRect){
    if ( !GetTexture() || !source->GetSurface() ) {
        return;
    }

    SDL_UpdateTexture(GetTexture(), srcRect, source->GetSurface()->pixels, source->GetSurface()->pitch);
    //SDL_RenderCopy(this->m_pRenderer, m_pTexture, srcRect, dstRect);
    //SDL_RenderCopy(this->m_pRenderer, source->GetTexture(), srcRect, dstRect);
}

void CCanvas::UpdateTexture(const SDL_Rect* srcRect, const SDL_Rect* dstRect){
    if ( !GetTexture() || !GetSurface() ) {
        return;
    }

    SDL_UpdateTexture(GetTexture(), NULL, GetSurface()->pixels, GetSurface()->pitch);
    //SDL_RenderCopy(this->m_pRenderer, m_pTexture, srcRect, dstRect);
    //SDL_RenderCopy(this->m_pRenderer, GetTexture(), srcRect, dstRect);
}

void CCanvas::RenderCopy(CCanvas* source, const SDL_Rect* srcRect, const SDL_Rect* dstRect) const {
    if ( !source->GetTexture() ) {
        return;
    }

    //SDL_UpdateTexture(m_pTexture, NULL, source->GetSurface()->pixels,
    // source->GetSurface()->pitch);
    //SDL_RenderCopy(this->m_pRenderer, m_pTexture, srcRect, dstRect);
    SDL_RenderCopy(GetRenderer(), source->GetTexture(), srcRect, dstRect);
}

void CCanvas::RenderCopy(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) const {
    //        if (!m_pRenderer) {
    //            return;
    //        }

    //SDL_RenderClear(this->m_pRenderer);
    //Draw the texture
    //SDL_UpdateTexture(texture, srcRect, GetSurface()->pixels, GetSurface()->pitch);
    SDL_RenderCopy(GetRenderer(), texture, srcRect, dstRect);
}

void CCanvas::RenderCopy(const SDL_Rect* srcRect, const SDL_Rect* dstRect){
    SDL_RenderCopy(GetRenderer(), GetTexture(), srcRect, dstRect);
}

void CCanvas::Render(CCanvas* source, const SDL_Rect* srcRect, const SDL_Rect* dstRect){
//        if ( /*!m_pRenderer ||*/ !GetTexture() ) {
//            return;
//        }

    m_pTexture = SDL_CreateTextureFromSurface( GetRenderer(), source->GetSurface() );
    SDL_UpdateTexture(GetTexture(), srcRect, source->GetSurface()->pixels, source->GetSurface()->pitch);
    RenderCopy(GetTexture(), srcRect, dstRect);
}

void CCanvas::Render(SDL_Surface* source, const SDL_Rect* srcRect, const SDL_Rect* dstRect){
    m_pTexture = SDL_CreateTextureFromSurface(GetRenderer(), source);
    SDL_UpdateTexture(GetTexture(), srcRect, source->pixels, source->pitch);
    RenderCopy(GetTexture(), srcRect, dstRect);
}

void CCanvas::MainUpdateAndRenderCopy(const SDL_Rect* srcRect, const SDL_Rect* dstRect){
    // this works only for the main canvas
    if (!m_pRenderer) {
        return;
    }

    //SDL_Texture *tex = SDL_CreateTextureFromSurface(this->m_pRenderer, GetSurface());
    SDL_UpdateTexture(GetTexture(), srcRect, GetSurface()->pixels, GetSurface()->pitch);
    RenderCopy(GetTexture(), srcRect, dstRect);
}

void CCanvas::MainRenderCopyTo(const SDL_Rect* srcRect, const SDL_Rect* dstRect){
    // Todo: all Render** should check the exit codes
    // see: https://wiki.libsdl.org/SDL_RenderCopy
    // Return Value
    // Returns 0 on success or a negative error code on failure; call SDL_GetError() for more
    // information.
    CApplication::GetApplication()->GetMainCanvas()->RenderCopy(this, srcRect, dstRect);

    //SDL_UpdateTexture(m_pTexture, NULL, source->GetSurface()->pixels,
    // source->GetSurface()->pitch);
    //SDL_RenderCopy(this->m_pRenderer, m_pTexture, srcRect, dstRect);
    //SDL_RenderCopy(this->m_pRenderer, GetTexture(), srcRect, dstRect);
}

void CCanvas::MainRenderFinal(){
    SDL_RenderPresent( CApplication::GetApplication()->GetMainCanvas()->GetRenderer() );
}

void CCanvas::MainRenderClear(){
    SDL_RenderClear( CApplication::GetApplication()->GetMainCanvas()->GetRenderer() );
}

void CCanvas::SetTextureColorMod(SDL_Color sdl_color) const {
    if (!m_pTexture) {
        return;
    }

    // SDL_SetTextureColorMod(GetTexture(), 128, 255, 255);
    SDL_SetTextureColorMod(m_pTexture, sdl_color.r, sdl_color.g, sdl_color.b);
    // Returns 0 on success or a negative error code on failure; call SDL_GetError() for more
    // information.
    // Todo: check error info, like in all of these calls ...
}

bool CCanvas::Lock ( ) const {
    /*if ( SDL_MUSTLOCK ( GetSurface ( ) ) ) {
        if ( SDL_LockSurface ( GetSurface ( ) ) == 0 ) {
            return ( true );
        }
        else {
            return ( false );
        }
       }*/

    return ( true );
}

void CCanvas::Unlock ( ) const {
    //MainUpdateAndRenderCopy();
//    if ( SDL_MUSTLOCK ( GetSurface ( ) ) ) {
//        SDL_UnlockSurface ( GetSurface ( ) );
//    }
}

CColor CCanvas::GetPixel ( int x, int y ){
    Uint32 color = 0;
    int position = y * GetSurface ( )->pitch + GetSurface ( )->format->BytesPerPixel * x;
    char* buffer = static_cast<char *>(GetSurface ( )->pixels);
    buffer += position;
    memcpy ( &color, buffer, GetSurface ( )->format->BytesPerPixel );
    CColor col;
    SDL_GetRGB ( color, GetSurface ( )->format, &col.R ( ), &col.G ( ), &col.B ( ) );
    return ( col );
}

void CCanvas::SetPixel ( int x, int y, CColor& color ){
    int position = y * GetSurface ( )->pitch + GetSurface ( )->format->BytesPerPixel * x;
    char* buffer = static_cast<char *>(GetSurface ( )->pixels);
    buffer += position;
    Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.R ( ), color.G ( ), color.B ( ) );
    memcpy ( buffer, &col, GetSurface ( )->format->BytesPerPixel );
}

int CCanvas::GetWidth ( ) const {
    return ( GetSurface ( )->w );
}

int CCanvas::GetHeight ( ) const {
    return ( GetSurface ( )->h );
}

CRectangle CCanvas::GetDimension ( ) const {
    CRectangle rect( 0, 0, GetWidth( ), GetHeight( ) );
    return rect;
}

void CCanvas::AddUpdateRect ( const CRectangle& UpdateRect ){
    SDL_Rect* pRect = NULL;
    pRect = new SDL_Rect;
    pRect->x = UpdateRect.GetX();
    pRect->y = UpdateRect.GetY ( );
    pRect->w = UpdateRect.GetW ( );
    pRect->h = UpdateRect.GetH ( );
    m_lstUpdateRects.push_back ( pRect );
}

void CCanvas::ClearUpdateRects ( ){
    list < SDL_Rect * >::iterator iter;
    SDL_Rect* pRect;

    while ( !m_lstUpdateRects.empty ( ) )
    {
        iter = m_lstUpdateRects.begin ( );
        pRect = *iter;
        m_lstUpdateRects.erase ( iter );

        if ( pRect ) { delete pRect; }
    }
}

void CCanvas::UpdateRects ( ){
    list < SDL_Rect * >::iterator iter;
    SDL_Rect* pRect;

    for ( iter = m_lstUpdateRects.begin ( ); iter != m_lstUpdateRects.end ( ); ++iter )
    {
        pRect = *iter;

        if ( pRect ) {
            //SDL_UpdateRect ( GetSurface ( ), pRect->x, pRect->y, pRect->w, pRect->h );
            //SDL_RenderPresent(m_pRenderer);
        }
        else {
            //SDL_UpdateRect ( GetSurface ( ), 0, 0, GetWidth ( ), GetHeight ( ) );
            //SDL_RenderPresent(m_pRenderer);
        }
    }
    ClearUpdateRects ( );
}     // UpdateRects

bool CCanvas::Flip ( ){
    //SDL_RenderPresent(m_pRenderer);
    //return SDL_Flip(GetSurface()) == 0;
    return true;
}

bool CCanvas::SetColorKey ( CColor& color ){
    Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.R ( ), color.G ( ), color.B ( ) );
    return (SDL_SetColorKey(GetSurface(), SDL_TRUE, col) == 0);
}

CColor CCanvas::GetColorKey ( ) const {
    throw new std::exception("Fuck !");
//
//    Uint32 col = GetSurface ( )->format->colorkey;
//    CColor color;
//    SDL_GetRGB ( col, GetSurface ( )->format, &color.R ( ), &color.G ( ), &color.B ( ) );
//    return ( color );
}

bool CCanvas::ClearColorKey ( ){
    return ( SDL_SetColorKey ( GetSurface ( ), 0, 0 ) == 0 );
}

void CCanvas::SetClipRect ( CRectangle* pRect ){
    if ( pRect ) {
        SDL_SetClipRect ( GetSurface ( ), *pRect );
    }
    else {
        SDL_SetClipRect ( GetSurface ( ), NULL );
    }
}

CRectangle CCanvas::GetClipRect ( ){
    SDL_Rect rect;
    SDL_GetClipRect ( GetSurface ( ), &rect );
    return ( rect );
}

bool CCanvas::FillRect ( CRectangle& rect, const CColor& color ){
    Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.GetR ( ), color.GetG ( ), color.GetB ( ) );
    return ( SDL_FillRect ( GetSurface ( ), rect, col ) == 0 );
}

bool CCanvas::RenderFillRect(CRectangle& rect, const CColor& color){
    // Uint32 col = SDL_MapRGB(GetSurface()->format, color.GetR(), color.GetG(), color.GetB());
    int ret = SDL_SetRenderDrawColor( GetRenderer(), color.GetR(), color.GetG(), color.GetB(), color.GetA() );
    return SDL_RenderFillRect(GetRenderer(), rect);
}

bool CCanvas::Clear ( const CColor& color ){
    Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.GetR ( ), color.GetG ( ), color.GetB ( ) );

    if (m_pTexture) {
        CRectangle dimension = GetDimension();
        RenderFillRect(dimension, color);
        //SDL_RenderClear(GetRenderer());
    }

    return ( SDL_FillRect ( GetSurface ( ), NULL, col ) == 0 );
}

bool CCanvas::Blit ( const CRectangle& rectDst, const CCanvas& cnvSrc, const CRectangle& rectSrc ) const {
    CRectangle rectDst2 = rectDst;
    CRectangle rectSrc2 = rectSrc;
    return ( SDL_BlitSurface ( cnvSrc.GetSurface ( ), rectSrc2, GetSurface ( ), rectDst2 ) == 0 );
}

CCanvas * CCanvas::CreateRGB ( Uint32 flags, int width, int height, int depth, Uint32 Rmask,
        Uint32 Gmask, Uint32 Bmask,
        Uint32 Amask){
    CCanvas* pCanvas = new CCanvas ( static_cast<SDL_Surface *>(NULL) );
    pCanvas->SetSurface ( SDL_CreateRGBSurface ( flags, width, height, depth, Rmask, Gmask, Bmask,
                    Amask ) );
    pCanvas->m_bOwner = true;
    return ( pCanvas );
}

CCanvas * CCanvas::CreateRGBCompatible ( Uint32 flags, int width, int height ){
    // throw new std::exception("Fuck !");
    //auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
    auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
    SDL_PixelFormat* format = surface->format;
    return ( CreateRGB ( flags, width, height, format->BitsPerPixel, format->Rmask, format->Gmask,
                     format->Bmask, format->Amask ) );
}

CCanvas * CCanvas::LoadBMP ( string sFileName ){
    SDL_Surface* pSurface = SDL_LoadBMP ( sFileName.c_str ( ) );
    return ( new CCanvas ( pSurface, true ) );
}

CCanvas * CCanvas::LoadBMPCompatible ( string sFileName ){
    //throw new std::exception("Fuck !");
    SDL_Surface* pSurface = SDL_LoadBMP( sFileName.c_str() );
    //SDL_Surface* pSurface2 = SDL_DisplayFormat(pSurface);
    auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
    SDL_Surface* pSurface2 = SDL_ConvertSurfaceFormat(pSurface, surface->format->format, 0);
    SDL_FreeSurface ( pSurface );
    return ( new CCanvas ( pSurface2, true ) );
}

//match color with closest
CColor CCanvas::MatchColor ( CColor color ){
    //convert it to the pixel format
    Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.R ( ), color.G ( ), color.B ( ) );

    //convert it from the pixel format
    SDL_GetRGB ( col, GetSurface ( )->format, &color.R ( ), &color.G ( ), &color.B ( ) );

    //return the matched color
    return ( color );
}

void CCanvas::Invalidate(){
    AddUpdateRect( GetDimension() );
}
}   // namespace components
} // namespace gui
