#include "../../stdafx.h"
#include "Canvas.h"
#include <memory.h>

namespace gui {
namespace components {

using namespace std;

#if !SDL_GUILIB_ENABLED

void SDL_FreeSurface(SDL_Surface *surface)
{
};

#endif

CCanvas::CCanvas ( SDL_Surface* pSurface ){
    //dbgOut(__FUNCTION__ << std::endl);
    SetSurface ( pSurface );
    m_lstUpdateRects.clear ( );
}

CCanvas::~CCanvas ( ){
	ClearUpdateRects ( );
    if ( GetSurface ( ) ) {
        SDL_FreeSurface ( GetSurface ( ) );
        SetSurface ( NULL );
    }

    //dbgOut(__FUNCTION__ << std::endl);
}

SDL_Surface * CCanvas::GetSurface ( ) const {
    return ( m_pSurface );
}

void CCanvas::SetSurface ( SDL_Surface* pSurface ){
    m_pSurface = pSurface;
}

bool CCanvas::Lock ( ) const {
#if SDL_GUILIB_ENABLED
	    if ( SDL_MUSTLOCK ( GetSurface ( ) ) ) {
	        if ( SDL_LockSurface ( GetSurface ( ) ) == 0 ) {
	            return ( true );
	        }
	        else {
	            return ( false );
	        }
	    }
#endif

    return ( true );
}

void CCanvas::Unlock ( ) const {
#if SDL_GUILIB_ENABLED
	    if ( SDL_MUSTLOCK ( GetSurface ( ) ) ) {
	        SDL_UnlockSurface ( GetSurface ( ) );
	    }
#endif
}

CColor CCanvas::GetPixel ( int x, int y ){
#if SDL_GUILIB_ENABLED
	    Uint32 color = 0;
	    int position = y * GetSurface ( )->pitch + GetSurface ( )->format->BytesPerPixel * x;
	    char* buffer = ( char * ) GetSurface ( )->pixels;
	    buffer += position;
	    memcpy ( &color, buffer, GetSurface ( )->format->BytesPerPixel );
	    CColor col;
	    SDL_GetRGB ( color, GetSurface ( )->format, &col.R ( ), &col.G ( ), &col.B ( ) );
		return ( col );
#else
	return ( CColor::Yellow() );
#endif
}

void CCanvas::SetPixel ( int x, int y, CColor& color ){
#if SDL_GUILIB_ENABLED
	    int position = y * GetSurface ( )->pitch + GetSurface ( )->format->BytesPerPixel * x;
	    char* buffer = ( char * ) GetSurface ( )->pixels;
	    buffer += position;
	    Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.R ( ), color.G ( ), color.B ( ) );
	    memcpy ( buffer, &col, GetSurface ( )->format->BytesPerPixel );
#endif
}

int CCanvas::GetWidth ( ) const{
#if SDL_GUILIB_ENABLED
	    return ( GetSurface ( )->w );
#else
		return 0;
#endif
}

int CCanvas::GetHeight ( ) const{
#if SDL_GUILIB_ENABLED
	return ( GetSurface ( )->h );
#else
	return 0;
#endif
}

CRectangle CCanvas::GetDimension ( ) const {
    CRectangle rect( 0, 0, GetWidth( ), GetHeight( ) );
    return rect;
}

void CCanvas::AddUpdateRect ( const CRectangle& UpdateRect ){
    {
#if SDL_GUILIB_ENABLED
		    SDL_Rect* pRect = NULL;
		    pRect = new SDL_Rect;
		    pRect->x = UpdateRect.GetX();
		    pRect->y = UpdateRect.GetY ( );
		    pRect->w = UpdateRect.GetW ( );
		    pRect->h = UpdateRect.GetH ( );
		    m_lstUpdateRects.push_back ( pRect );
#endif
    }
}

void CCanvas::ClearUpdateRects ( ){
    list < SDL_Rect * >::iterator iter;
    SDL_Rect* pRect;

    while ( !m_lstUpdateRects.empty ( ) )
    {
        iter = m_lstUpdateRects.begin ( );
        pRect = *iter;
        m_lstUpdateRects.erase ( iter );

        if ( pRect ) { delete pRect; }}
}

void CCanvas::UpdateRects ( ){
#if SDL_GUILIB_ENABLED
	    list < SDL_Rect * >::iterator iter;
	    SDL_Rect* pRect;
	
	    for ( iter = m_lstUpdateRects.begin ( ); iter != m_lstUpdateRects.end ( ); iter++ )
	    {
	        pRect = *iter;
	
	        if ( pRect ) {
	            SDL_UpdateRect ( GetSurface ( ), pRect->x, pRect->y, pRect->w, pRect->h );
	        }
	        else {
	            SDL_UpdateRect ( GetSurface ( ), 0, 0, GetWidth ( ), GetHeight ( ) );
	        }
	    }
	    ClearUpdateRects ( );
#endif
} // UpdateRects

bool CCanvas::Flip ( ){
#if SDL_GUILIB_ENABLED
	    return ( SDL_Flip ( GetSurface ( ) ) == 0 );
#else
		return false;
#endif
}

bool CCanvas::SetColorKey ( CColor& color ){
#if SDL_GUILIB_ENABLED
	    Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.R ( ), color.G ( ), color.B ( ) );
	    return ( SDL_SetColorKey ( GetSurface ( ), SDL_SRCCOLORKEY, col ) == 0 );
#else
		return false;
#endif
}

CColor CCanvas::GetColorKey ( ){
#if SDL_GUILIB_ENABLED
	    Uint32 col = GetSurface ( )->format->colorkey;
	    CColor color;
	    SDL_GetRGB ( col, GetSurface ( )->format, &color.R ( ), &color.G ( ), &color.B ( ) );
	    return ( color );
#else
		return CColor::Green();
#endif
}

bool CCanvas::ClearColorKey ( ){
#if SDL_GUILIB_ENABLED
	    return ( SDL_SetColorKey ( GetSurface ( ), 0, 0 ) == 0 );
#else
		return false;
#endif
}

void CCanvas::SetClipRect ( CRectangle* pRect ){
#if SDL_GUILIB_ENABLED
	    if ( pRect ) {
	        SDL_SetClipRect ( GetSurface ( ), *pRect );
	    }
	    else {
	        SDL_SetClipRect ( GetSurface ( ), NULL );
	    }
#endif
}

CRectangle CCanvas::GetClipRect ( ){
#if SDL_GUILIB_ENABLED
	    SDL_Rect rect;
	    SDL_GetClipRect ( GetSurface ( ), &rect );
		return ( CRectangle(rect.x,rect.y,rect.w,rect.h) );
#else
		return CRectangle();
#endif
}

bool CCanvas::FillRect ( CRectangle& rect, const CColor& color ){
#if SDL_GUILIB_ENABLED
	    Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.GetR ( ), color.GetG ( ), color.GetB ( ) );
	    return ( SDL_FillRect ( GetSurface ( ), rect, col ) == 0 );
#else
		return false;
#endif
}

bool CCanvas::Clear ( const CColor& color ){
#if SDL_GUILIB_ENABLED
	    Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.GetR ( ), color.GetG ( ), color.GetB ( ) );
	    return ( SDL_FillRect ( GetSurface ( ), NULL, col ) == 0 );
#else
		return false;
#endif
}

bool CCanvas::Blit ( const CRectangle& rectDst, const CCanvas& cnvSrc, const CRectangle& rectSrc ) const {
#if SDL_GUILIB_ENABLED
	    CRectangle rectDst2 = rectDst;
	    CRectangle rectSrc2 = rectSrc;
	    return ( SDL_BlitSurface ( cnvSrc.GetSurface ( ), rectSrc2, GetSurface ( ), rectDst2 ) == 0 );
#else
		return false;
#endif
}

CCanvas * CCanvas::CreateRGB ( Uint32 flags, int width, int height, int depth, Uint32 Rmask,
        Uint32 Gmask, Uint32 Bmask,
        Uint32 Amask){
#if SDL_GUILIB_ENABLED
	    CCanvas* pCanvas = new CCanvas ( NULL );
	    pCanvas->SetSurface ( SDL_CreateRGBSurface ( flags, width, height, depth, Rmask, Gmask, Bmask,
	                    Amask ) );
	    return ( pCanvas );
#else
		return new CCanvas ( NULL );
#endif
}

CCanvas * CCanvas::CreateRGBCompatible ( Uint32 flags, int width, int height ){
#if SDL_GUILIB_ENABLED
	    SDL_PixelFormat* format = SDL_GetVideoSurface ( )->format;
	    return ( CreateRGB ( flags, width, height, format->BitsPerPixel, format->Rmask, format->Gmask,
	                     format->Bmask, format->Amask ) );
#else
		return new CCanvas ( NULL );
#endif
}

CCanvas * CCanvas::LoadBMP ( string sFileName ){
#if SDL_GUILIB_ENABLED
	    SDL_Surface* pSurface = SDL_LoadBMP ( sFileName.c_str ( ) );
	    return ( new CCanvas ( pSurface ) );
#else
		return new CCanvas ( NULL );
#endif
}

CCanvas * CCanvas::LoadBMPCompatible ( string sFileName ){
#if SDL_GUILIB_ENABLED
	    SDL_Surface* pSurface = SDL_LoadBMP ( sFileName.c_str ( ) );
	    SDL_Surface* pSurface2 = SDL_DisplayFormat ( pSurface );
	    SDL_FreeSurface ( pSurface );
	    return ( new CCanvas ( pSurface2 ) );
#else
		return new CCanvas ( NULL );
#endif
}

//match color with closest
CColor CCanvas::MatchColor ( CColor color ){
#if SDL_GUILIB_ENABLED
	    //convert it to the pixel format
	    Uint32 col = SDL_MapRGB ( GetSurface ( )->format, color.R ( ), color.G ( ), color.B ( ) );
	
	    //convert it from the pixel format
	    SDL_GetRGB ( col, GetSurface ( )->format, &color.R ( ), &color.G ( ), &color.B ( ) );
	
	    //return the matched color
	    return ( color );
#else
	return CColor::Red();
#endif
}

} // namespace components
} // namespace gui
