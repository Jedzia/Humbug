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
    struct CCanvasRenderModifierData
    {
        const CRectangle* srcRect;
        const CRectangle* dstRect;
        bool isHandled;

        CCanvasRenderModifierData(const CRectangle* srcRect, const CRectangle* dstRect)
            : srcRect(srcRect), dstRect(dstRect), isHandled(false)
        {

        };
    };

//CCanvas class
class CCanvas {
public:
    typedef boost::function<void(CCanvas* source, const CCanvas *target, CCanvasRenderModifierData& mdata)> CCanvasRenderer;
    void AddModifier(CCanvasRenderer updfunc);
private:
    // remove them
    // Render from other Canvas
    void Render(CCanvas* source, const CRectangle* srcRect = NULL, const CRectangle* dstRect = NULL);

    // Render from a surface
    void Render(SDL_Surface* source, const CRectangle* srcRect = NULL, const CRectangle* dstRect = NULL);


private:
    static int UpdateTexture(SDL_Texture * texture, const CRectangle * rect, const void *pixels, int pitch);
    void CanvasRenderCopy(SDL_Texture* texture, const CRectangle* srcRect, const CRectangle* dstRect) const;
    void SetWindow(SDL_Window* pWindow);
    SDL_Renderer * GetRenderer() const;

    //a list of update rectangles
    std::list < SDL_Rect * > m_lstUpdateRects;
    typedef std::vector<CCanvasRenderer> CCanvasRendererStorage;
    CCanvasRendererStorage m_vecRendererVault;


    bool m_bOwner;
    bool m_bIsParameterClass;

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

    /// <summary>
    /// Gets the texture or creates one if none exists.
    /// </summary>
    /// <returns>the texture of this canvas.</returns>
    SDL_Texture * GetTexture();

    // setter for the SDL Surface
    // Note: If m_bOwner is set to true takes ownership of the pSurface pointer that gets deleted,
    // when this instance is destroyed.
    void SetSurface(SDL_Surface* pSurface);

    /** Update Texture from surface.
     *  Draw the underlying surface to the texture. You should use texture only functions.
     *  @param srcRect source area
     * @param dstRect target area
     */
    void UpdateTexture(const CRectangle* srcRect = NULL, const CRectangle* dstRect = NULL);

    /** Update Texture from other canvas surface.
    *  Draw the underlying surface to the texture. You should use texture only functions.
    *  @param srcRect source area
    * @param dstRect target area
    */
    void UpdateTexture(CCanvas* source, const CRectangle* srcRect = NULL, const CRectangle* dstRect = NULL);

    /** RenderCopy the texture from source to this canvas.
    *  Use this function to copy a portion of the texture to this rendering target. If no texture at the source is
    *  present, one is created. All modifiers of the source CCanvas are executed. If the modifiers return isHandled
    *  as true, then no CanvasRenderCopy is called, so the modifier has to handle the rendering.
    * 
    *  As there is only one rendering target at the moment, this is the same as calling
    *  CCanvas::MainRenderCopyTo(const CRectangle* srcRect, const CRectangle* dstRect).
    *  @param source The source canvas to get the texture from.
    *  @param srcRect the source CRectangle structure or NULL for the entire texture
    * @param dstRect the destination CRectangle structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void RenderPutCopy(CCanvas* source, const CRectangle* srcRect = NULL, const CRectangle* dstRect = NULL) const;

    /** RenderCopy a texture.
    *  Use this function to copy a portion of the texture to the main window rendering target.
    *  @param source The source texture to render.
    *  @param srcRect the source CRectangle structure or NULL for the entire texture
    * @param dstRect the destination CRectangle structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void RenderCopy(SDL_Texture* texture, const CRectangle* srcRect = NULL, const CRectangle* dstRect = NULL) const;

    /** RenderCopy the texture of this canvas.
    *  Use this function to copy a portion of the texture to the main window rendering target. If no texture is
    *  present, one is created. As there is only one rendering target at the moment, this is the same as calling
    *  CCanvas::MainRenderCopyTo(const CRectangle* srcRect, const CRectangle* dstRect).
    *  @param srcRect the source CRectangle structure or NULL for the entire texture
    * @param dstRect the destination CRectangle structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void RenderCopy(const CRectangle* srcRect = NULL, const CRectangle* dstRect = NULL);

    /** RenderCopy the texture of this canvas with a point offset:
    *  Use this function to copy the full texture to the main window rendering target. If no texture is
    *  present, one is created. As there is only one rendering target at the moment, this is the same as calling
    *  CCanvas::MainRenderCopyTo(const CRectangle* srcRect, const CRectangle* dstRect).
    *  @param offset the location where to render the canvas.
    */
    void RenderCopy(const CPoint& offset);

    /** Final Render step.
    *  Calls SDL_RenderCopy.
    */
    void FinalRenderCopy(SDL_Texture* texture, const CRectangle* srcRect, const CRectangle* dstRect) const;

    /** Update Texture from surface and RenderCopy to the main render target.
    *  Works only on the main canvas. Gets or possibly creates the texture, runs UpdateTexture and finally RenderCopy.
    *  @param srcRect the source CRectangle structure or NULL for the entire texture
    * @param dstRect the destination CRectangle structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void MainUpdateAndRenderCopy(const CRectangle* srcRect = NULL, const CRectangle* dstRect = NULL);

    /** RenderCopy to the main render target.
    *  Use this function to copy a portion of the texture to the main window rendering target. If no texture is
    *  present, one is created. As there is only one rendering target at the moment, this is the same as calling
    *  CCanvas::RenderCopy(const CRectangle* srcRect, const CRectangle* dstRect).
    *  @param srcRect the source CRectangle structure or NULL for the entire texture
    * @param dstRect the destination CRectangle structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void MainRenderCopyTo(const CRectangle* srcRect = NULL, const CRectangle* dstRect = NULL);
    static void MainRenderFinal();

    static void MainRenderClear();

    /** Use this function to set an additional color value multiplied into render copy operations. 
    *  When this texture is rendered, during the copy operation each source color channel is modulated by the appropriate color value according to the following formula:
    *  "srcC = srcC * (color / 255)"
    *  Color modulation is not always supported by the renderer; it will return -1 if color modulation is not supported. 
    *  Does nothing if no texture is instantiated.
    *  @param sdl_color the color values multiplied into copy operations. Only r,g and b are used.
    */
    void SetTextureColorMod(const CColor& color);

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
    bool ClearColorKey ( ) const;

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
