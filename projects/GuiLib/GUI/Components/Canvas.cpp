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

    CCanvas::CCanvas(SDL_Surface* pSurface)
        : m_pRenderer(nullptr), m_pWindow(nullptr), m_pSurface(nullptr), m_pTexture(nullptr){
        //dbgOut(__FUNCTION__ << std::endl);
        SetSurface(pSurface);
        m_lstUpdateRects.clear();
    }

    CCanvas::CCanvas ( SDL_Window* pWindow )
        : m_pRenderer(nullptr), m_pWindow(nullptr), m_pSurface(nullptr), m_pTexture(nullptr){
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

        //dbgOut(__FUNCTION__ << std::endl);
    }

    /** $(class), GetSurface:
     *  Detailed description.
     *  @return TODO
     */
    SDL_Surface * CCanvas::GetSurface() const {
        return ( m_pSurface );
    }

    /** $(class), GetTexture:
     *  Detailed description.
     *  @return TODO
     */
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

    /** $(class), SetSurface:
     *  Detailed description.
     *  @param pSurface TODO
     * @return TODO
     */
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

    /** $(class), SetWindow:
     *  Detailed description.
     *  @param pWindow TODO
     * @return TODO
     */
    void CCanvas::SetWindow(SDL_Window* pWindow){
        m_pWindow = pWindow;

        if (pWindow) {
            m_pSurface = SDL_GetWindowSurface(pWindow);
            m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
            m_pTexture = SDL_CreateTextureFromSurface(this->m_pRenderer, m_pSurface);
        }
    }

    /** $(class), GetRenderer:
     *  Detailed description.
     *  @return TODO
     */
    SDL_Renderer * CCanvas::GetRenderer() const {
        if (this->m_pRenderer) {
            return m_pRenderer;
        }
        else {
            return CApplication::GetApplication()->GetMainCanvas()->m_pRenderer;
        }
    }

    /** $(class), UpdateTexture:
     *  Detailed description.
     *  @param source TODO
     * @param srcRect TODO
     * @param dstRect TODO
     * @return TODO
     */
    void CCanvas::UpdateTexture(CCanvas* source, const SDL_Rect* srcRect, const SDL_Rect* dstRect){
        if ( !GetTexture() || !source->GetSurface() ) {
            return;
        }

        SDL_UpdateTexture(GetTexture(), NULL, source->GetSurface()->pixels, source->GetSurface()->pitch);
        //SDL_RenderCopy(this->m_pRenderer, m_pTexture, srcRect, dstRect);
        //SDL_RenderCopy(this->m_pRenderer, source->GetTexture(), srcRect, dstRect);
    }

    /** CCanvas, UpdateTexture:
     *  Draw the underlying surface to the texture. You should use texture only functions.
     *  @param srcRect source area
     * @param dstRect target area
     */
    void CCanvas::UpdateTexture(const SDL_Rect* srcRect, const SDL_Rect* dstRect){
        if ( !GetTexture() || !GetSurface() ) {
            return;
        }

        SDL_UpdateTexture(GetTexture(), NULL, GetSurface()->pixels, GetSurface()->pitch);
        //SDL_RenderCopy(this->m_pRenderer, m_pTexture, srcRect, dstRect);
        //SDL_RenderCopy(this->m_pRenderer, GetTexture(), srcRect, dstRect);
    }

    /** $(class), RenderCopy:
     *  Detailed description.
     *  @param source TODO
     * @param srcRect TODO
     * @param dstRect TODO
     * @return TODO
     */
    void CCanvas::RenderCopy(CCanvas* source, const SDL_Rect* srcRect, const SDL_Rect* dstRect) const {
        if ( !this->m_pRenderer || !source->GetTexture() ) {
            return;
        }

        //SDL_UpdateTexture(m_pTexture, NULL, source->GetSurface()->pixels,
        // source->GetSurface()->pitch);
        //SDL_RenderCopy(this->m_pRenderer, m_pTexture, srcRect, dstRect);
        SDL_RenderCopy(this->m_pRenderer, source->GetTexture(), srcRect, dstRect);
    }

    /** $(class), RenderCopy:
     *  Detailed description.
     *  @param srcRect TODO
     * @param dstRect TODO
     * @return TODO
     */
    void CCanvas::RenderCopy(const SDL_Rect* srcRect, const SDL_Rect* dstRect){
        if ( !this->m_pRenderer || !GetTexture() ) {
            return;
        }

        //SDL_UpdateTexture(m_pTexture, NULL, source->GetSurface()->pixels,
        // source->GetSurface()->pitch);
        //SDL_RenderCopy(this->m_pRenderer, m_pTexture, srcRect, dstRect);
        SDL_RenderCopy(this->m_pRenderer, GetTexture(), srcRect, dstRect);
    }

    /** $(class), RenderCopyToMain:
     *  Detailed description.
     *  @param srcRect TODO
     * @param dstRect TODO
     * @return TODO
     */
    void CCanvas::RenderCopyToMain(const SDL_Rect* srcRect, const SDL_Rect* dstRect){
        CApplication::GetApplication()->GetMainCanvas()->RenderCopy(this, srcRect, dstRect);

        //SDL_UpdateTexture(m_pTexture, NULL, source->GetSurface()->pixels,
        // source->GetSurface()->pitch);
        //SDL_RenderCopy(this->m_pRenderer, m_pTexture, srcRect, dstRect);
        //SDL_RenderCopy(this->m_pRenderer, GetTexture(), srcRect, dstRect);
    }

    /** $(class), Render:
     *  Detailed description.
     *  @param source TODO
     * @param srcRect TODO
     * @param dstRect TODO
     * @return TODO
     */
    void CCanvas::Render(CCanvas* source, const SDL_Rect* srcRect, const SDL_Rect* dstRect){
        if ( !m_pRenderer || !GetTexture() ) {
            return;
        }

        //SDL_Texture *tex = SDL_CreateTextureFromSurface(this->m_pRenderer, source->GetSurface());
        SDL_UpdateTexture(GetTexture(), NULL, source->GetSurface()->pixels, source->GetSurface()->pitch);
        Render(GetTexture(), srcRect, dstRect);
    }

    /** $(class), Render:
     *  Detailed description.
     *  @param source TODO
     * @param srcRect TODO
     * @param dstRect TODO
     * @return TODO
     */
    void CCanvas::Render(SDL_Surface* source, const SDL_Rect* srcRect, const SDL_Rect* dstRect){
        if ( !m_pRenderer || !GetTexture() ) {
            return;
        }

        //SDL_Texture *tex = SDL_CreateTextureFromSurface(this->m_pRenderer, source);
        SDL_UpdateTexture(GetTexture(), NULL, source->pixels, source->pitch);
        Render(GetTexture(), srcRect, dstRect);
    }

    /** $(class), Render:
     *  Detailed description.
     *  @param srcRect TODO
     * @param dstRect TODO
     * @return TODO
     */
    void CCanvas::Render(const SDL_Rect* srcRect, const SDL_Rect* dstRect){
        if ( !m_pRenderer || !GetTexture() ) {
            return;
        }

        //SDL_Texture *tex = SDL_CreateTextureFromSurface(this->m_pRenderer, GetSurface());
        SDL_UpdateTexture(GetTexture(), NULL, GetSurface()->pixels, GetSurface()->pitch);
        Render(GetTexture(), srcRect, dstRect);
    }

    /** $(class), Render:
     *  Detailed description.
     *  @param texture TODO
     * @param srcRect TODO
     * @param dstRect TODO
     * @return TODO
     */
    void CCanvas::Render(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) const {
        if (!m_pRenderer) {
            return;
        }

        //SDL_RenderClear(this->m_pRenderer);
        //Draw the texture
        SDL_RenderCopy(this->m_pRenderer, texture, srcRect, dstRect);
        //Update the screen
        //SDL_RenderPresent(this->m_pRenderer);
    }

    /** $(class), RenderFinal:
     *  Detailed description.
     *  @return TODO
     */
    void CCanvas::RenderFinal() const {
        if (!m_pRenderer) {
            return;
        }

        //SDL_RenderClear(this->m_pRenderer);
        //Draw the texture
        //SDL_RenderCopy(this->m_pRenderer, texture, srcRect, dstRect);
        //Update the screen
        SDL_RenderPresent(this->m_pRenderer);
    }

    /** $(class), Lock:
     *  Detailed description.
     *  @return TODO
     */
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

    /** $(class), Unlock:
     *  Detailed description.
     *  @return TODO
     */
    void CCanvas::Unlock ( ) const {
        //Render();
//    if ( SDL_MUSTLOCK ( GetSurface ( ) ) ) {
//        SDL_UnlockSurface ( GetSurface ( ) );
//    }
    }

    /** $(class), GetPixel:
     *  Detailed description.
     *  @param x TODO
     * @param y TODO
     * @return TODO
     */
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

    /** $(class), SetPixel:
     *  Detailed description.
     *  @param x TODO
     * @param y TODO
     * @param color TODO
     * @return TODO
     */
    void CCanvas::SetPixel ( int x, int y, CColor& color ){
        int position = y * GetSurface ( )->pitch + GetSurface ( )->format->BytesPerPixel * x;
        char* buffer = static_cast<char *>(GetSurface ( )->pixels);
        buffer += position;
        Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.R ( ), color.G ( ), color.B ( ) );
        memcpy ( buffer, &col, GetSurface ( )->format->BytesPerPixel );
    }

    /** $(class), GetWidth:
     *  Detailed description.
     *  @return TODO
     */
    int CCanvas::GetWidth ( ) const {
        return ( GetSurface ( )->w );
    }

    /** $(class), GetHeight:
     *  Detailed description.
     *  @return TODO
     */
    int CCanvas::GetHeight ( ) const {
        return ( GetSurface ( )->h );
    }

    /** $(class), GetDimension:
     *  Detailed description.
     *  @return TODO
     */
    CRectangle CCanvas::GetDimension ( ) const {
        CRectangle rect( 0, 0, GetWidth( ), GetHeight( ) );
        return rect;
    }

    /** $(class), AddUpdateRect:
     *  Detailed description.
     *  @param UpdateRect TODO
     * @return TODO
     */
    void CCanvas::AddUpdateRect ( const CRectangle& UpdateRect ){
        SDL_Rect* pRect = NULL;
        pRect = new SDL_Rect;
        pRect->x = UpdateRect.GetX();
        pRect->y = UpdateRect.GetY ( );
        pRect->w = UpdateRect.GetW ( );
        pRect->h = UpdateRect.GetH ( );
        m_lstUpdateRects.push_back ( pRect );
    }

    /** $(class), ClearUpdateRects:
     *  Detailed description.
     *  @return TODO
     */
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

    /** $(class), UpdateRects:
     *  Detailed description.
     *  @return TODO
     */
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
    } // UpdateRects

    /** $(class), Flip:
     *  Detailed description.
     *  @return TODO
     */
    bool CCanvas::Flip ( ){
        //SDL_RenderPresent(m_pRenderer);
        //return SDL_Flip(GetSurface()) == 0;
        return true;
    }

    /** $(class), SetColorKey:
     *  Detailed description.
     *  @param color TODO
     * @return TODO
     */
    bool CCanvas::SetColorKey ( CColor& color ){
        Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.R ( ), color.G ( ), color.B ( ) );
        return (SDL_SetColorKey(GetSurface(), SDL_TRUE, col) == 0);
    }

    /** $(class), GetColorKey:
     *  Detailed description.
     *  @return TODO
     */
    CColor CCanvas::GetColorKey ( ) const {
        throw new std::exception("Fuck !");
//
//    Uint32 col = GetSurface ( )->format->colorkey;
//    CColor color;
//    SDL_GetRGB ( col, GetSurface ( )->format, &color.R ( ), &color.G ( ), &color.B ( ) );
//    return ( color );
    }

    /** $(class), ClearColorKey:
     *  Detailed description.
     *  @return TODO
     */
    bool CCanvas::ClearColorKey ( ){
        return ( SDL_SetColorKey ( GetSurface ( ), 0, 0 ) == 0 );
    }

    /** $(class), SetClipRect:
     *  Detailed description.
     *  @param pRect TODO
     * @return TODO
     */
    void CCanvas::SetClipRect ( CRectangle* pRect ){
        if ( pRect ) {
            SDL_SetClipRect ( GetSurface ( ), *pRect );
        }
        else {
            SDL_SetClipRect ( GetSurface ( ), NULL );
        }
    }

    /** $(class), GetClipRect:
     *  Detailed description.
     *  @return TODO
     */
    CRectangle CCanvas::GetClipRect ( ){
        SDL_Rect rect;
        SDL_GetClipRect ( GetSurface ( ), &rect );
        return ( rect );
    }

    /** $(class), FillRect:
     *  Detailed description.
     *  @param rect TODO
     * @param color TODO
     * @return TODO
     */
    bool CCanvas::FillRect ( CRectangle& rect, const CColor& color ){
        Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.GetR ( ), color.GetG ( ), color.GetB ( ) );
        return ( SDL_FillRect ( GetSurface ( ), rect, col ) == 0 );
    }

    /** $(class), RenderFillRect:
     *  Detailed description.
     *  @param rect TODO
     * @param color TODO
     * @return TODO
     */
    bool CCanvas::RenderFillRect(CRectangle& rect, const CColor& color){
        // Uint32 col = SDL_MapRGB(GetSurface()->format, color.GetR(), color.GetG(), color.GetB());
        int ret = SDL_SetRenderDrawColor(GetRenderer(), color.GetR(), color.GetG(), color.GetB(), SDL_ALPHA_OPAQUE);
        return SDL_RenderFillRect(GetRenderer(), rect);
    }

    /** $(class), Clear:
     *  Detailed description.
     *  @param color TODO
     * @return TODO
     */
    bool CCanvas::Clear ( const CColor& color ){
        Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.GetR ( ), color.GetG ( ), color.GetB ( ) );
        return ( SDL_FillRect ( GetSurface ( ), NULL, col ) == 0 );
    }

    /** $(class), Blit:
     *  Detailed description.
     *  @param rectDst TODO
     * @param cnvSrc TODO
     * @param rectSrc TODO
     * @return TODO
     */
    bool CCanvas::Blit ( const CRectangle& rectDst, const CCanvas& cnvSrc, const CRectangle& rectSrc ) const {
        CRectangle rectDst2 = rectDst;
        CRectangle rectSrc2 = rectSrc;
        return ( SDL_BlitSurface ( cnvSrc.GetSurface ( ), rectSrc2, GetSurface ( ), rectDst2 ) == 0 );
    }

    /** $(class), CreateRGB:
     *  Detailed description.
     *  @param flags TODO
     * @param width TODO
     * @param height TODO
     * @param depth TODO
     * @param Rmask TODO
     * @param Gmask TODO
     * @param Bmask TODO
     * @param Amask TODO
     * @return TODO
     */
    CCanvas * CCanvas::CreateRGB ( Uint32 flags, int width, int height, int depth, Uint32 Rmask,
            Uint32 Gmask, Uint32 Bmask,
            Uint32 Amask){
        CCanvas* pCanvas = new CCanvas ( static_cast<SDL_Surface *>(NULL) );
        pCanvas->SetSurface ( SDL_CreateRGBSurface ( flags, width, height, depth, Rmask, Gmask, Bmask,
                        Amask ) );
        return ( pCanvas );
    }

    /** $(class), CreateRGBCompatible:
     *  Detailed description.
     *  @param flags TODO
     * @param width TODO
     * @param height TODO
     * @return TODO
     */
    CCanvas * CCanvas::CreateRGBCompatible ( Uint32 flags, int width, int height ){
        // throw new std::exception("Fuck !");
        //auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
        auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
        SDL_PixelFormat* format = surface->format;
        return ( CreateRGB ( flags, width, height, format->BitsPerPixel, format->Rmask, format->Gmask,
                         format->Bmask, format->Amask ) );
    }

    /** $(class), LoadBMP:
     *  Detailed description.
     *  @param sFileName TODO
     * @return TODO
     */
    CCanvas * CCanvas::LoadBMP ( string sFileName ){
        SDL_Surface* pSurface = SDL_LoadBMP ( sFileName.c_str ( ) );
        return ( new CCanvas ( pSurface ) );
    }

    /** $(class), LoadBMPCompatible:
     *  Detailed description.
     *  @param sFileName TODO
     * @return TODO
     */
    CCanvas * CCanvas::LoadBMPCompatible ( string sFileName ){
        //throw new std::exception("Fuck !");
        SDL_Surface* pSurface = SDL_LoadBMP( sFileName.c_str() );
        //SDL_Surface* pSurface2 = SDL_DisplayFormat(pSurface);
        auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
        SDL_Surface* pSurface2 = SDL_ConvertSurfaceFormat(pSurface, surface->format->format, 0);
        SDL_FreeSurface ( pSurface );
        return ( new CCanvas ( pSurface2 ) );
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

    /** $(class), Invalidate:
     *  Detailed description.
     *  @return TODO
     */
    void CCanvas::Invalidate(){
        AddUpdateRect( GetDimension() );
    }
  } // namespace components
} // namespace gui
