//include guards
#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "Color.h"
#include "Rectangle.h"
#include "SDL.h"
#include <list>
#include <string>

namespace gui {
namespace components {
//CCanvas class
class CCanvas {
private:
    // remove them
    // Render from other Canvas
    void Render(CCanvas* source, const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL);

    // Render from a surface
    void Render(SDL_Surface* source, const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL);


private:

    //a list of update rectangles
    std::list < SDL_Rect * > m_lstUpdateRects;
    void SetWindow(SDL_Window* pWindow);

    SDL_Renderer * GetRenderer() const;

    bool m_bOwner;

protected:

    //pointer to an SDL_Surface
    SDL_Window* m_pWindow;
    SDL_Surface* m_pSurface;
    SDL_Texture* m_pTexture;
    SDL_Renderer* m_pRenderer;

public:

    //constructor
    // Note: takes ownership of the pSurface pointer that gets deleted, when this instance is
    // destroyed.
    explicit CCanvas(SDL_Window* pWindow);
    CCanvas(SDL_Surface* pSurface = NULL, bool owner = false);

    //destructor
    virtual ~CCanvas ( );

    // getter for the SDL_Surface*
    SDL_Surface * GetSurface() const;

    SDL_Texture * GetTexture();

    // setter for the SDL_Surface*
    void SetSurface(SDL_Surface* pSurface);

    // setter for the SDL_Surface*
    // Note: takes ownership of the pSurface pointer that gets deleted, when this instance is
    // destroyed.

    /** CCanvas, UpdateTexture:
     *  Draw the underlying surface to the texture. You should use texture only functions.
     *  @param srcRect source area
     * @param dstRect target area
     */
    void UpdateTexture(const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL);

    void UpdateTexture(CCanvas* source, const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL);

    /** CCanvas, RenderCopy:
    *  Use this function to copy a portion of the texture to the main window rendering target. If no texture at the source is
    *  present, one is created. As there is only one rendering target at the moment, this is the same as calling
    *  CCanvas::MainRenderCopyTo(const SDL_Rect* srcRect, const SDL_Rect* dstRect).
    *  @param source The source canvas to get the texture from.
    *  @param srcRect the source SDL_Rect structure or NULL for the entire texture
    * @param dstRect the destination SDL_Rect structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void RenderCopy(CCanvas* source, const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL) const;

    /** CCanvas, RenderCopy:
    *  Use this function to copy a portion of the texture to the main window rendering target.
    *  @param source The source texture to render.
    *  @param srcRect the source SDL_Rect structure or NULL for the entire texture
    * @param dstRect the destination SDL_Rect structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void RenderCopy(SDL_Texture* texture, const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL) const;

    /** CCanvas, RenderCopy:
    *  Use this function to copy a portion of the texture to the main window rendering target. If no texture is
    *  present, one is created. As there is only one rendering target at the moment, this is the same as calling
    *  CCanvas::MainRenderCopyTo(const SDL_Rect* srcRect, const SDL_Rect* dstRect).
    *  @param srcRect the source SDL_Rect structure or NULL for the entire texture
    * @param dstRect the destination SDL_Rect structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void RenderCopy(const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL);

    /** CCanvas, MainUpdateAndRenderCopy:
    *  Works only on the main canvas. Gets or possibly creates the texture, runs UpdateTexture and finally RenderCopy.
    *  @param srcRect the source SDL_Rect structure or NULL for the entire texture
    * @param dstRect the destination SDL_Rect structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void MainUpdateAndRenderCopy(const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL);

    /** CCanvas, MainRenderCopyTo:
    *  Use this function to copy a portion of the texture to the main window rendering target. If no texture is
    *  present, one is created. As there is only one rendering target at the moment, this is the same as calling
    *  CCanvas::RenderCopy(const SDL_Rect* srcRect, const SDL_Rect* dstRect).
    *  @param srcRect the source SDL_Rect structure or NULL for the entire texture
    * @param dstRect the destination SDL_Rect structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void MainRenderCopyTo(const SDL_Rect* srcRect = NULL, const SDL_Rect* dstRect = NULL);

    void MainRenderFinal() const;

    //lock and unlock ( for direct pixel access )
    bool Lock ( ) const;

    void Unlock ( ) const;

    //get/set pixel (canvas should be locked)
    CColor GetPixel ( int x, int y );

    void SetPixel ( int x, int y, CColor& color );

    //match color with closest
    CColor MatchColor ( CColor color );

    //width and height retrieval
    int GetWidth ( ) const;

    int GetHeight ( ) const;

    //get the clipping rectangle
    CRectangle GetDimension ( ) const;

    //add an update rectangle
    void AddUpdateRect ( const CRectangle& pUpdateRect );

    //clear all update rectangles
    void ClearUpdateRects ( );

    //update any rectangles in the queue
    void UpdateRects ( );

    // invalidate the whole surface.
    void Invalidate();

    //flip surface.  normally, this just updates the entire surface
    bool Flip ( );

    //set a color key
    bool SetColorKey ( CColor& color );

    //retrieve the color key
    CColor GetColorKey ( ) const;

    //clear the color key
    bool ClearColorKey ( );

    //set the clipping rectangle
    void SetClipRect ( CRectangle* pRect );

    //get the clipping rectangle
    CRectangle GetClipRect ( );

    //solid color fill fill a rectangle
    bool FillRect ( CRectangle& rect, const CColor& color );

    bool RenderFillRect(CRectangle& rect, const CColor& color);

    //clear entire surface to a color
    bool Clear ( const CColor& color );

    //blit to this surface from another surface
    bool Blit ( const CRectangle& rectDst, const CCanvas& cnvSrc, const CRectangle& rectSrc ) const;

    //factory methods
    //create an rgb surface of a particular format
    static CCanvas * CreateRGB ( Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask,
            Uint32 Bmask, Uint32 Amask);

    //create an rgb surface of the display format
    static CCanvas * CreateRGBCompatible ( Uint32 flags, int width, int height );

    //load a bitmap
    static CCanvas * LoadBMP ( std::string sFileName );

    //load a bitmap, convert it to the display format
    static CCanvas * LoadBMPCompatible ( std::string sFileName );
};
} // namespace components
} // namespace gui

#endif // ifndef __CANVAS_H__
