//include guards
#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "SDL.h"
#include "Color.h"
#include "Rectangle.h"
#include <list>
#include <string>

namespace gui {
namespace components {

//CCanvas class
class CCanvas
{
private:
    //a list of update rectangles
    std::list < SDL_Rect* > m_lstUpdateRects ;

protected:
    //pointer to an SDL_Surface
    SDL_Window* m_pWindow;
    SDL_Surface* m_pSurface;

public:
    SDL_Renderer* m_pRenderer;
    //constructor
    // Note: takes ownership of the pSurface pointer that gets deleted, when this instance is destroyed.
    CCanvas(SDL_Window* pWindow = NULL);
    CCanvas(SDL_Surface* pSurface = NULL);

    //destructor
    virtual ~CCanvas ( ) ;

    // getter for the SDL_Surface*
    SDL_Surface* GetSurface() const;

    // setter for the SDL_Surface*
    void SetSurface(SDL_Surface* pSurface);

    // setter for the SDL_Surface*
    // Note: takes ownership of the pSurface pointer that gets deleted, when this instance is destroyed.
    void SetWindow(SDL_Window* pWindow);

    // Render from other Canvas
    void Render(CCanvas* source, const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL) const;
    // Render from a surface
    void Render(SDL_Surface* source, const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL) const;
    // Render from a texture
    void Render(SDL_Texture* texture, const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL) const;
    // Render myself
    void Render(const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL) const;

    //lock and unlock ( for direct pixel access )
    bool Lock ( ) const ;
    void Unlock ( ) const ;

    //get/set pixel (canvas should be locked)
    CColor GetPixel ( int x , int y ) ;
    void SetPixel ( int x , int y , CColor& color ) ;

    //match color with closest
    CColor MatchColor ( CColor color ) ;

    //width and height retrieval
    int GetWidth ( ) const;
    int GetHeight ( ) const;
    //get the clipping rectangle
    CRectangle GetDimension ( ) const;

    //add an update rectangle
    void AddUpdateRect ( const CRectangle& pUpdateRect ) ;

    //clear all update rectangles
    void ClearUpdateRects ( ) ;

    //update any rectangles in the queue
    void UpdateRects ( ) ;
    
    // invalidate the whole surface.
    void Invalidate();

    //flip surface.  normally, this just updates the entire surface
    bool Flip ( ) ;

    //set a color key
    bool SetColorKey ( CColor& color ) ;

    //retrieve the color key
    CColor GetColorKey ( ) const;

    //clear the color key
    bool ClearColorKey ( ) ;

    //set the clipping rectangle
    void SetClipRect ( CRectangle* pRect ) ;

    //get the clipping rectangle
    CRectangle GetClipRect ( ) ;

    //solid color fill fill a rectangle
    bool FillRect ( CRectangle& rect , const CColor& color ) ;

    //clear entire surface to a color
    bool Clear ( const CColor& color ) ;

    //blit to this surface from another surface
    bool Blit ( const CRectangle& rectDst , const CCanvas& cnvSrc , const CRectangle& rectSrc ) const;

    //factory methods
    //create an rgb surface of a particular format
    static CCanvas* CreateRGB ( Uint32 flags , int width , int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) ;
    //create an rgb surface of the display format
    static CCanvas* CreateRGBCompatible ( Uint32 flags , int width , int height ) ;

    //load a bitmap
    static CCanvas* LoadBMP ( std::string sFileName ) ;
    //load a bitmap, convert it to the display format
    static CCanvas* LoadBMPCompatible ( std::string sFileName ) ;

} ;
} // namespace components
} // namespace gui

#endif