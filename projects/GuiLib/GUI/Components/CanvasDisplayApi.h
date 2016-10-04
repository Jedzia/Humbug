#pragma once

#include "Color.h"
#include "Rectangle.h"
#include "SDL.h"
#include "BlendMode.h"

namespace gui {
    namespace components {

        class CCanvas;

        /** @class RenderApi:
        *  Detailed description.
        *
        */
        class CanvasDisplayApi {
        public:

            virtual ~CanvasDisplayApi()
            {}

            virtual bool ToggleOpenGL() = 0;

            virtual SDL_Surface * GetSurface() const = 0;

            virtual void InitGPU() = 0;

            virtual void SetSurface(SDL_Surface* pSurface) = 0;

            virtual void SetWindow(SDL_Window* pWindow) = 0;

            virtual SDL_Texture * GetTexture() = 0;

            virtual void SetupParameterClass(CCanvas* source, SDL_Texture* texture) const = 0;

            virtual bool Clear(const CColor& color) const = 0;

            virtual void FinalRenderCopy(SDL_Texture* texture, const CRectangle* dstRect, const CRectangle* srcRect) const = 0;

            virtual void RenderPresent() = 0;

            virtual void CanvasSwapWindow() = 0;

            virtual void SetRenderDrawBlendMode(BlendMode mode) const = 0;

            virtual bool ClearColorKey() const = 0;

            virtual bool FillRect(const CRectangle& rect, const CColor& color) const = 0;

            virtual void RenderDrawPoint(const CPoint& coordinates, const CColor* color) const = 0;

            virtual void RenderDrawLine(const CPoint& pStart, const CPoint& pEnd, const CColor* color) const = 0;

            virtual bool RenderDrawRect(const CRectangle& rect, const CColor* color) const = 0;

            virtual bool RenderFillRect(const CRectangle& rect, const CColor* color) const = 0;

            virtual bool RenderFillRect(const CRectangle& rect, const CColor& color) const = 0;

            inline virtual void GLDrawTexture(const CRectangle* rect) = 0;

            virtual void Cleanup() = 0;
        };


    }
}