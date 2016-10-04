/*---------------------------------------------------------*/
/*!
 * This file is part of Playground, your C++ vacation spot.
 * License details can be found in the file COPYING.
 * Copyright (c) 2016, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the BothDisplay.h class.
 * \file       BothDisplay.h
 * \date       2016-04-26 $(date)
 * \author     Jedzia.
 *
 * modified    2016-04-26, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

#include "Canvas.h"
#include "CanvasDisplayApi.h"
#include "QuadRenderer.h"
//
#include <GuiLib/GUI/Visual/Application.h>
#include <boost/foreach.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
//
#include <GL/glew.h>
//
#include <GL/GLU.h>
#include <SDL_opengl.h>
//
#include <glm/gtc/constants.hpp> // glm::pi
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
//
#include <oglplus/all.hpp>
#include <oglplus/gl.hpp>
//

namespace gui {
namespace components {
/** @class BothRenderApi:
 *  Detailed description.
 *  @return TODO
 */
class BothDisplay : public CanvasDisplayApi {
    static bool m_bUseOpenGL;
    CCanvas* host_;
    //CCanvas::CCanvasImpl* pimpl_;
    BothDisplay* MainApi;

    boost::scoped_ptr<QuadRenderer> m_example;

    SDL_Window* m_pWindow;
    SDL_GLContext m_glContext;
    SDL_Surface* m_pSurface;
    SDL_Texture* m_pTexture;
    SDL_Renderer* m_pRenderer;

    bool m_bTextureOwner;
    bool m_bOwner;
    bool m_bIsParameterClass;

    float glColorR;
    float glColorG;
    float glColorB;
    static boost::random::mt19937 gen;
    GLuint m_glTextureId;

    /** Brief description of BothDisplay, RandomFloat
     *  Detailed description.
     *  @param min TODO
     *  @param max TODO
     *  @return TODO
     */
    static float RandomFloat(float min, float max) {
        boost::random::uniform_real_distribution<> dist(min, max);
        float rnd = static_cast<float>(dist(gen));
        return rnd;
    }

    /** Brief description of BothDisplay, rangeMap
     *  Detailed description.
     *  @param input TODO
     *  @param outMin TODO
     *  @param outMax TODO
     *  @param inMin TODO
     *  @param inMax TODO
     *  @return TODO
     */
    float rangeMap(float input, float outMin, float outMax, float inMin, float inMax) {
        float slope = 1.0f * (outMax - outMin) / (inMax - inMin);
        //float result = outMin + round(slope * (input - inMin));
        float result = outMin + (slope * (input - inMin));

        return result;
    }

    /** Brief description of BothDisplay, GetRenderer
     *  Detailed description.
     *  @return TODO
     */
    SDL_Renderer * GetRenderer() const {
        if(this->m_pRenderer) {
            return m_pRenderer;
        }
        else {
            //return CApplication::GetApplication()->GetMainCanvas()->m_pRenderer;
            return MainApi->m_pRenderer;
        }
    }

    /** Brief description of BothDisplay, GetTexture
     *  Detailed description.
     *  @return TODO
     */
    SDL_Texture * GetTexture() override {
        // Lazy Texture
        if(m_pTexture == nullptr) {
            if(this->m_pRenderer) {
                m_pTexture = SDL_CreateTextureFromSurface(this->m_pRenderer, m_pSurface);
            }
            else {
                //m_pTexture = SDL_CreateTextureFromSurface(
                //    CApplication::GetApplication()->GetMainCanvas()->m_pRenderer, m_pSurface);
                //BothDisplay* api =
                // dynamic_cast<BothDisplay*>(CApplication::GetApplication()->GetMainCanvas()->dApi_.get());
                m_pTexture = SDL_CreateTextureFromSurface(MainApi->m_pRenderer, m_pSurface);
            }

            m_bTextureOwner = true;
        }

        return m_pTexture;
    }         // GetTexture

    /** Brief description of BothDisplay, GetGlColorR
     *  Detailed description.
     *  @return TODO
     */
    float GetGlColorR() const { return glColorR; }

    /** Brief description of BothDisplay, GetGlColorG
     *  Detailed description.
     *  @return TODO
     */
    float GetGlColorG() const { return glColorG; }

    /** Brief description of BothDisplay, GetGlColorB
     *  Detailed description.
     *  @return TODO
     */
    float GetGlColorB() const { return glColorB; }

    /** Brief description of BothDisplay, SetColor
     *  Detailed description.
     *  @param r TODO
     *  @param g TODO
     *  @param b TODO
     */
    void SetColor(float r, float g, float b) {
        m_example->SetColor(r, g, b);
    }

    /** Brief description of BothDisplay, GLAttachTexture
     *  Detailed description.
     *  @param surface TODO
     *  @param textw TODO
     *  @param texth TODO
     *  @return TODO
     */
    GLuint GLAttachTexture(SDL_Surface* surface, int* textw = nullptr, int* texth = nullptr) {
        GLuint textureid;
        int mode;

        // Or if you don't use SDL_image you can use SDL_LoadBMP here instead:
        // surface = SDL_LoadBMP(filename);

        // could not load filename
        if(!surface) {
            return 0;
        }

        // work out what format to tell glTexImage2D to use...
        if(surface->format->BytesPerPixel == 3) {            // RGB 24bit
            mode = GL_RGB;
        }
        else if(surface->format->BytesPerPixel == 4) {            // RGBA 32bit
            mode = GL_RGBA;
            //mode = GL_RGBA16;
        }
        else {
            //SDL_FreeSurface(surface);
            return 0;
        }

        if(textw) {
            *textw = surface->w;
        }

        if(texth) {
            *texth = surface->h;
        }

        // create one texture name
        glGenTextures(1, &textureid);

        // tell opengl to use the generated texture name
        glBindTexture(GL_TEXTURE_2D, textureid);

        // this reads from the sdl surface and puts it into an opengl texture
        glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

        // these affect how this texture is drawn later on...
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // clean up
        //SDL_FreeSurface(surface);
        m_glTextureId = textureid;
        return textureid;
    }         // GLAttachTexture

    /** Brief description of BothDisplay, GLDrawTextureNew
     *  Detailed description.
     *  @param rect TODO
     */
    void GLDrawTextureNew(const CRectangle* rect) {
        //return;
        if(!rect) {
            return;
        }

        const SDL_Rect* prect = rect->SDLRectCP();

        float x = rangeMap(static_cast<float>(prect->x), -1.0f, 1.0f, 0, 1024);
        float x1 = rangeMap(static_cast<float>(prect->x + prect->w), -1.0f, 1.0f, 0, 1024);
        float y = rangeMap(static_cast<float>(prect->y), 1.0f, -1.0f, 0, 768);
        float y1 = rangeMap(static_cast<float>(prect->y + prect->h), 1.0f, -1.0f, 0, 768);

        GLfloat triangle_verts[18] = {
            x, y, 0.0f,
            x, y1, 0.0f,
            x1, y1, 0.0f,

            x1, y, 0.0f,
            x1, y1, 0.0f,
            x, y, 0.0f
        };

        m_example->InitVerts(triangle_verts, 6);

        if(m_example->IsInitialized()) {
            m_example->SetColor(GetGlColorR(), GetGlColorG(), GetGlColorB());
            m_example->Display();
        }
    }         // GLDrawTexture

    /** Brief description of BothDisplay, GLDrawTextureOld
     *  Detailed description.
     *  @param rect TODO
     */
    void GLDrawTextureOld(const CRectangle* rect) {
        //return;
        if(!rect) {
            return;
        }

        const SDL_Rect* prect = rect->SDLRectCP();

        float x = rangeMap(static_cast<float>(prect->x), -1.0f, 1.0f, 0, 1024);
        float x1 = rangeMap(static_cast<float>(prect->x + prect->w), -1.0f, 1.0f, 0, 1024);
        float y = rangeMap(static_cast<float>(prect->y), 1.0f, -1.0f, 0, 768);
        float y1 = rangeMap(static_cast<float>(prect->y + prect->h), 1.0f, -1.0f, 0, 768);

        int aaa = 0;
        float texfac = 1.0f;

        //glColor3f(GetGlColorR(), GetGlColorG(), GetGlColorB());

        if(m_glTextureId) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //glEnable(GL_BLEND); glBlendFunc(GL_ONE, GL_ONE);
            glBindTexture(GL_TEXTURE_2D, m_glTextureId);
            glEnable(GL_TEXTURE_2D);
        }

        /*
         * B  D
         *
         * A  C
         *
         *
         */
        glBegin(GL_TRIANGLES);
        glTexCoord2f(0, 0);
        glVertex2f(x, y);                                       // A
        glTexCoord2f(0, 1.0f * texfac);
        glVertex2f(x, y1);                                      // B
        glTexCoord2f(1.0f * texfac, 1.0f * texfac);
        glVertex2f(x1, y1);                                     // C

        glTexCoord2f(1.0f * texfac, 0);
        glVertex2f(x1, y);                                      // D
        glTexCoord2f(1.0f * texfac, 1.0f * texfac);
        glVertex2f(x1, y1);                                     // C
        glTexCoord2f(0, 0);
        glVertex2f(x, y);                                       // A
        glEnd();

        //glRotatef(-rotation, 0, 0, 1);

        glDisable(GL_TEXTURE_2D);

        //SDL_GL_SwapWindow(m_pWindow);
    }         // GLDrawTexture

public:

    /** Brief description of BothDisplay, GLDrawTexture
     *  Detailed description.
     *  @param rect TODO
     */
    void GLDrawTexture(const CRectangle* rect) override {
        if (!m_bUseOpenGL)
            return;
#ifdef USE_NEW_GL_METHOD
        GLDrawTextureNew(rect);
#else
        GLDrawTextureOld(rect);
#endif
    }
     
    void InstRenderer()
    {
        try {
            //LOGSTD(__FUNCTION__ << " [" << typeid(*this).name() << "] (" << this << ")");
            m_example.reset(new QuadRenderer);
        }
        catch (oglplus::Error& err)
        {
            LOGSTD(
                "Fucking Error (in " <<
                err.GLFunc() <<
                "'): " <<
                err.what() <<
                " [" <<
                err.SourceFile() <<
                ":" <<
                err.SourceLine() <<
                "] ");
				throw err; 
        }

    }

    explicit BothDisplay(CCanvas* host, bool owner)
        : host_(host),
        m_pWindow(nullptr),
        m_glContext(nullptr),
        m_pSurface(nullptr),
        m_pTexture(nullptr),
        m_pRenderer(nullptr), m_bTextureOwner(false), m_bOwner(owner), m_bIsParameterClass(false) {

        glColorR = RandomFloat(0.0f, 1.0f);
        glColorG = RandomFloat(0.0f, 1.0f);
        glColorB = RandomFloat(0.0f, 1.0f);

        CMainCanvas* main_canvas = CApplication::GetApplication()->GetMainCanvas();
        if (!main_canvas) {
            MainApi = this;
            return;
        }

        MainApi = static_cast<BothDisplay *>(main_canvas->dAPI());

        InstRenderer();
    }

    /** Brief description of BothDisplay, InitGPU
     *  Detailed description.
     *
     */
    void InitGPU() override {
        //m_example.reset(new QuadRenderer);
        if (!m_example) {
            InstRenderer();
        }
#ifdef USE_NEW_GL_METHOD
        m_example->InitGPUProgram();
#endif
    }

    ~BothDisplay() {
        //return;
        // Clean up
        if(m_glTextureId) {
            glDeleteTextures(1, &m_glTextureId);
        }

        if(m_pTexture) {
            if(m_bTextureOwner) {
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
            BothDisplay::SetWindow(NULL);
        }

        if(m_bOwner && m_pSurface) {
            SDL_FreeSurface(m_pSurface);
            m_pSurface = nullptr;
        }

        //dbgOut(__FUNCTION__ << std::endl);
    }

    /** Brief description of BothDisplay, Cleanup
     *  Detailed description.
     *
     */
    void Cleanup() override {
        // the static shader programs have to be cleaned up before leaving
        if(m_example) {
            m_example->Cleanup();
            m_example.reset();
        }
    }

    /** Brief description of BothDisplay, GetSurface
     *  Detailed description.
     *  @return TODO
     */
    SDL_Surface * GetSurface() const override {
        return (m_pSurface);
    }

    /** Brief description of BothDisplay, SetSurface
     *  Detailed description.
     *  @param pSurface TODO
     */
    void SetSurface(SDL_Surface* pSurface) override {
        if(!pSurface) {
            return;
        }

        m_pSurface = pSurface;
#ifndef USE_NEW_GL_METHOD
        GLAttachTexture(pSurface);
#endif
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    bool ToggleOpenGL() override {
        m_bUseOpenGL = !m_bUseOpenGL;
        return m_bUseOpenGL;
    }

    /*
       void Final() override {
       if(m_bUseOpenGL) {
       CApplication::GetApplication()->GetMainCanvas()->SwapWindow();
       }
       else {
       // error, later the SDL renderer should be a class member
       //SDL_RenderPresent(CApplication::GetApplication()->GetMainCanvas()->GetRenderer());
       CApplication::GetApplication()->GetMainCanvas()->dApi_->RenderPresent();
       //SDL_RenderPresent(MainApi->m_pRenderer);
       }
       }
     */
    void SetWindow(SDL_Window* pWindow) override {
        m_pWindow = pWindow;

        if(pWindow) {
            SetSurface(SDL_GetWindowSurface(pWindow));
            // Renderer uses VSYNC
            m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            dbgOut(
                    __FUNCTION__ << " [" << this << "]" << " created Renderer " << " (" << m_pRenderer << ")" << " for Window " << " (" << pWindow <<
                        ")");
            m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pSurface);

            m_glContext = SDL_GL_CreateContext(pWindow);
            SDL_GL_SetSwapInterval(1);
        }
    }

    /** Brief description of BothDisplay, ClearColorKey
     *  Detailed description.
     *  @return TODO
     */
    bool ClearColorKey() const override {
        if(m_pTexture) {
            SDL_SetTextureColorMod(m_pTexture, 255, 255, 255);
        }

        return (SDL_SetColorKey(GetSurface(), 0, 0) == 0);
    }

    /** Brief description of BothDisplay, CanvasSwapWindow
     *  Detailed description.
     *
     */
    void CanvasSwapWindow() override {
        SDL_GL_SwapWindow(m_pWindow);
    }

    /** Brief description of BothDisplay, Clear
     *  Detailed description.
     *  @param color TODO
     *  @return TODO
     */
    bool Clear(const CColor& color) const override {
        Uint32 col = SDL_MapRGB(GetSurface()->format, color.GetR(), color.GetG(), color.GetB());

        if(m_pTexture) {
            CRectangle dimension = host_->GetDimension();
            host_->RenderFillRect(dimension, &color);
            //SDL_RenderClear(GetRenderer());
        }

        return (SDL_FillRect(GetSurface(), NULL, col) == 0);
    }

    /** Brief description of BothDisplay, SetupParameterClass
     *  Detailed description.
     *  @param source TODO
     *  @param texture TODO
     */
    void SetupParameterClass(CCanvas* source, SDL_Texture* texture) const override {
        auto sourceApi = static_cast<BothDisplay *>(source->dAPI());

        sourceApi->m_bIsParameterClass = true;
        sourceApi->m_pRenderer = GetRenderer();
        sourceApi->m_pTexture = texture;
    }

    /** Brief description of BothDisplay, RenderPresent
     *  Detailed description.
     *
     */
    void RenderPresent() override {
        SDL_RenderPresent(GetRenderer());
    }

    /** Brief description of BothDisplay, MainRenderFinal
     *  Detailed description.
     *
     */
    static void MainRenderFinal() {
        if(m_bUseOpenGL) {
            //CApplication::GetApplication()->GetMainCanvas()->SwapWindow();
            CApplication::GetApplication()->GetMainCanvas()->dAPI()->CanvasSwapWindow();
        }
        else {
            //SDL_RenderPresent(CApplication::GetApplication()->GetMainCanvas()->GetRenderer());
            //SDL_RenderPresent(CApplication::GetApplication()->GetMainCanvas()->dApi_->GetRenderer());
            CApplication::GetApplication()->GetMainCanvas()->dAPI()->RenderPresent();
        }
    }

    /** Brief description of BothDisplay, MainRenderClear
     *  Detailed description.
     *
     */
    static void MainRenderClear() {
        //SDL_RenderClear(CApplication::GetApplication()->GetMainCanvas()->GetRenderer());
        //glColor3f(1, 1, 1);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(m_bUseOpenGL) {
            oglplus::Context::Clear().ColorBuffer().DepthBuffer();
        }
    }

    /** Brief description of BothDisplay, FinalRenderCopy
     *  Detailed description.
     *  @param texture TODO
     *  @param dstRect TODO
     *  @param srcRect TODO
     */
    void FinalRenderCopy(SDL_Texture* texture, const CRectangle* dstRect, const CRectangle* srcRect) const override {
        // *** OpenGL incomplete ***
        // all RenderCopy calls flow here
        const SDL_Rect* sdl_src_rect = srcRect ? srcRect->SDLRectCP() : NULL;
        const SDL_Rect* sdl_dst_rect = dstRect ? dstRect->SDLRectCP() : NULL;
        int result = SDL_RenderCopy(GetRenderer(), texture, sdl_src_rect, sdl_dst_rect);

        //pimpl_->GLDrawTexture(dstRect);
    }

    /** Brief description of BothDisplay, SetRenderDrawBlendMode
     *  Detailed description.
     *  @param mode TODO
     */
    void SetRenderDrawBlendMode(BlendMode mode) const override {
        // *** OpenGL incomplete ***
        SDL_SetRenderDrawBlendMode(GetRenderer(), static_cast<SDL_BlendMode>(mode));
    }

    /** Brief description of BothDisplay, FillRect
     *  Detailed description.
     *  @param rect TODO
     *  @param color TODO
     *  @return TODO
     */
    bool FillRect(const CRectangle& rect, const CColor& color) const override {
        // *** OpenGL incomplete ***
        Uint32 col = SDL_MapRGB(GetSurface()->format, color.GetR(), color.GetG(), color.GetB());
        return (SDL_FillRect(GetSurface(), rect.SDLRectCP(), col) == 0);
    }

    /** Brief description of BothDisplay, RenderDrawPoint
     *  Detailed description.
     *  @param coordinates TODO
     *  @param color TODO
     */
    void RenderDrawPoint(const CPoint& coordinates, const CColor* color) const override {
        // *** OpenGL incomplete ***
        if(color) {
            SDL_SetRenderDrawColor(GetRenderer(), color->GetR(), color->GetG(), color->GetB(), color->GetA());
        }

        SDL_RenderDrawPoint(GetRenderer(), coordinates.GetX(), coordinates.GetY());
    }

    /** Brief description of BothDisplay, RenderDrawLine
     *  Detailed description.
     *  @param pStart TODO
     *  @param pEnd TODO
     *  @param color TODO
     */
    void RenderDrawLine(const CPoint& pStart, const CPoint& pEnd, const CColor* color) const override {
        // *** OpenGL incomplete ***
        if(color) {
            SDL_SetRenderDrawColor(GetRenderer(), color->GetR(), color->GetG(), color->GetB(), color->GetA());
        }

        SDL_RenderDrawLine(GetRenderer(), pStart.GetX(), pStart.GetY(), pEnd.GetX(), pEnd.GetY());
    }

    /** Brief description of BothDisplay, RenderDrawRect
     *  Detailed description.
     *  @param rect TODO
     *  @param color TODO
     *  @return TODO
     */
    bool RenderDrawRect(const CRectangle& rect, const CColor* color) const override {
        // *** OpenGL incomplete ***
        int ret = 0;
        if(color) {
            ret = SDL_SetRenderDrawColor(GetRenderer(), color->GetR(), color->GetG(), color->GetB(), color->GetA());
        }

        ret = SDL_RenderDrawRect(GetRenderer(), rect.SDLRectCP());
        return true;
    }

    /** Brief description of BothDisplay, RenderFillRect
     *  Detailed description.
     *  @param rect TODO
     *  @param color TODO
     *  @return TODO
     */
    bool RenderFillRect(const CRectangle& rect, const CColor* color) const override {
        // *** OpenGL incomplete ***
        // Uint32 col = SDL_MapRGB(GetSurface()->format, color.GetR(), color.GetG(), color.GetB());
        int ret = 0;
        if(color) {
            ret = SDL_SetRenderDrawColor(GetRenderer(), color->GetR(), color->GetG(), color->GetB(), color->GetA());
        }

        ret = SDL_RenderFillRect(GetRenderer(), rect.SDLRectCP());
        return true;
    }

    /** Brief description of BothDisplay, RenderFillRect
     *  Detailed description.
     *  @param rect TODO
     *  @param color TODO
     *  @return TODO
     */
    bool RenderFillRect(const CRectangle& rect, const CColor& color) const override {
        // *** OpenGL incomplete ***
        int ret = SDL_SetRenderDrawColor(GetRenderer(), color.GetR(), color.GetG(), color.GetB(), color.GetA());
        ret = SDL_RenderFillRect(GetRenderer(), rect.SDLRectCP());
        return true;
    }
};

//bool CCanvas::m_bUseOpenGL = false;
bool BothDisplay::m_bUseOpenGL = false;
boost::random::mt19937 BothDisplay::gen;
}
}
