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
        /** contains the source rectangle. */
        CRectangle* srcRect;
        /** contains the destination rectangle. */
        CRectangle*  dstRect;
        bool isHandled;
        /** If set to true the TextAnimator will be removed and deleted from the execution queue.
        The TextAnimator::nextAnimator next animator is added and called on the next run of the queue. */
        bool markedForDeletion;
        int state;

        CCanvasRenderModifierData(CRectangle* srcRect, CRectangle* dstRect)
            : srcRect(srcRect), dstRect(dstRect), isHandled(false), markedForDeletion(false), state(1)
        {

        };
    };

typedef enum
{
    /**< no blending
     dstRGBA = srcRGBA */
    BLENDMODE_NONE = 0x00000000,     
                                             
    /**< alpha blending
     dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
     dstA = srcA + (dstA * (1-srcA)) */
    BLENDMODE_BLEND = 0x00000001,    
                                     
    /**< additive blending
     dstRGB = (srcRGB * srcA) + dstRGB
     dstA = dstA */
    BLENDMODE_ADD = 0x00000002,      
                                     
    /**< color modulate
     dstRGB = srcRGB * dstRGB
     dstA = dstA */
    BLENDMODE_MOD = 0x00000004       
} BlendMode;

//CCanvas class
class CCanvas {
public:
    typedef boost::function<void(const CCanvas *target, CCanvas* source, CCanvasRenderModifierData& mdata)> CCanvasRenderer;
    void AddModifier(const CCanvasRenderer& updfunc);
private:
    // remove them
    // Render from other Canvas
    void Render(CCanvas* source, const CRectangle* dstRect = NULL, const CRectangle* srcRect = NULL);

    // Render from a surface
    void Render(SDL_Surface* source, const CRectangle* dstRect = NULL, const CRectangle* srcRect = NULL);


private:

    //a list of update rectangles
    typedef std::vector<CCanvasRenderer> CCanvasRendererStorage;

    static int UpdateTexture(SDL_Texture * texture, const CRectangle * rect, const void *pixels, int pitch);
    void CanvasRenderCopy(SDL_Texture* texture, const CRectangle* dstRect, const CRectangle* srcRect);
    bool ApplyRenderers(CCanvasRendererStorage& storage, CCanvas* source, const CCanvas* target, const CRectangle* dstRect, const CRectangle* srcRect) const;

    void SetWindow(SDL_Window* pWindow);
    SDL_Renderer * GetRenderer() const;

    std::list < SDL_Rect * > m_lstUpdateRects;
    bool m_bOwner;
    bool m_bTextureOwner;
    bool m_bIsParameterClass;
    CCanvasRendererStorage m_vecRendererVault;

private:

    struct CCanvasImpl;
    boost::scoped_ptr<CCanvasImpl> pimpl_;

    //pointer to an SDL_Surface
    SDL_Window* m_pWindow;
    SDL_GLContext m_glContext;
    SDL_Surface* m_pSurface;
    SDL_Texture* m_pTexture;
    SDL_Renderer* m_pRenderer;

protected:
    void CanvasSwapWindow();

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
    void UpdateTexture(const CRectangle* dstRect = NULL, const CRectangle* srcRect = NULL);
    /** Update Texture from other canvas surface.
    *  Draw the underlying surface to the texture. You should use texture only functions.
    *  @param srcRect source area
    * @param dstRect target area
    */
    void UpdateTexture(CCanvas* source, const CRectangle* dstRect = NULL, const CRectangle* srcRect = NULL);

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
    void RenderPutCopy(CCanvas* source, const CRectangle* dstRect = NULL, const CRectangle* srcRect = NULL) ;

    /** RenderCopy a texture.
    *  Use this function to copy a portion of the texture to the main window rendering target.
    *  @param source The source texture to render.
    *  @param srcRect the source CRectangle structure or NULL for the entire texture
    * @param dstRect the destination CRectangle structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void RenderCopy(SDL_Texture* texture, const CRectangle* dstRect = NULL, const CRectangle* srcRect = NULL);

    /** RenderCopy the texture of this canvas.
    *  Use this function to copy a portion of the texture to the main window rendering target. If no texture is
    *  present, one is created. As there is only one rendering target at the moment, this is the same as calling
    *  CCanvas::MainRenderCopyTo(const CRectangle* srcRect, const CRectangle* dstRect).
    *  @param srcRect the source CRectangle structure or NULL for the entire texture
    * @param dstRect the destination CRectangle structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void RenderCopy(const CRectangle* dstRect = NULL, const CRectangle* srcRect = NULL);

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
    void FinalRenderCopy(SDL_Texture* texture, const CRectangle* dstRect, const CRectangle* srcRect) const;

    /** Update Texture from surface and RenderCopy to the main render target.
    *  Works only on the main canvas. Gets or possibly creates the texture, runs UpdateTexture and finally RenderCopy.
    *  @param srcRect the source CRectangle structure or NULL for the entire texture
    * @param dstRect the destination CRectangle structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void MainUpdateAndRenderCopy(const CRectangle* dstRect = NULL, const CRectangle* srcRect = NULL);

    /** RenderCopy to the main render target.
    *  Use this function to copy a portion of the texture to the main window rendering target. If no texture is
    *  present, one is created. As there is only one rendering target at the moment, this is the same as calling
    *  CCanvas::RenderCopy(const CRectangle* srcRect, const CRectangle* dstRect).
    *  @param srcRect the source CRectangle structure or NULL for the entire texture
    * @param dstRect the destination CRectangle structure or NULL for the entire rendering target; the texture will be stretched to fill the given rectangle
    */
    void MainRenderCopyTo(const CRectangle* dstRect = NULL, const CRectangle* srcRect = NULL);
    static void MainRenderFinal();

    static void MainRenderClear();

    /** Use this function to set an additional color value multiplied into render copy operations. 
    *  When this texture is rendered, during the copy operation each source color channel is modulated by the appropriate color value according to the following formula:
    *  "srcC = srcC * (color / 255)"
    *  Color modulation is not always supported by the renderer; it will return -1 if color modulation is not supported. 
    *  A new texture is instantiated when there is no one.
    *  @param color the color values multiplied into copy operations. Only r,g and b are used.
    */
    void SetTextureColorMod(const CColor& color);
    
    /** Use this function to set an additional alpha value multiplied into render copy operations.
    *  When this texture is rendered, during the copy operation the source alpha value is modulated by this alpha value according to the following formula: 
    *  "srcA = srcA * (alpha / 255)"
    *  Alpha modulation is not always supported by the renderer; it will return -1 if alpha modulation is not supported. 
    *  A new texture is instantiated when there is no one.
    *  @param alpha The source alpha value multiplied into copy operations.
    */
    void SetTextureAlphaMod(Uint8 alpha);

    /** Set drawing blend mode.
    *  Use this function to set the blend mode used for drawing operations (Fill and Line). 
    *  @param mode the BlendMode to use for blending.
    */
    void SetRenderDrawBlendMode(BlendMode mode) const;

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
    void SetClipRect ( CRectangle* pRect ) const;

    //get the clipping rectangle
    CRectangle GetClipRect ( ) const;

    //solid color fill fill a rectangle
    bool FillRect(const CRectangle& rect, const CColor& color) const;

    /** Render a Point.
    *  Use this function to draw a point on the current rendering target.
    *  @param coordinates The x and y coordinates of the point.
    *  @param color The drawing color of the point or NULL if no color change is wanted.
    */
    void RenderDrawPoint(const CPoint& coordinates, const CColor* color) const;

    /** Render a Line.
    *  Use this function to draw a line on the canvas rendering target.
    *  @param pStart The start point of the line.
    *  @param pEnd The end point of the line.
    *  @param color The drawing color of the line or NULL if no color change is wanted.
    */
    void RenderDrawLine(const CPoint& pStart, const CPoint& pEnd, const CColor* color) const;

    /** Draw a rectangle.
    *  Use this function to draw a rectangle on the current rendering target. 
    *  @param rect a CRectangle representing the rectangle to draw.
    *  @param color The drawing color of the rectangle or NULL if no color change is wanted.
    */
    bool RenderDrawRect(const CRectangle& rect, const CColor* color) const;

    /** Fill a rectangle.
    *  Use this function to fill a rectangle on the current rendering target with the drawing color. 
    *  @param rect a CRectangle representing the rectangle to draw.
    *  @param color The drawing color of the rectangle or NULL if no color change is wanted.
    */
    bool RenderFillRect(const CRectangle& rect, const CColor* color) const;

    /** Fill a rectangle.
    *  Use this function to fill a rectangle on the current rendering target with the drawing color.
    *  @param rect a CRectangle representing the rectangle to draw.
    *  @param color The drawing color of the rectangle or NULL if no color change is wanted.
    */
    bool RenderFillRect(const CRectangle& rect, const CColor& color) const;

    //clear entire surface to a color
    bool Clear ( const CColor& color ) const;

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
