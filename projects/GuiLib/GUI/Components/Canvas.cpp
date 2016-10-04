/*---------------------------------------------------------*/
/*!
 * This file is part of Playground, your C++ vacation spot.
 * License details can be found in the file COPYING.
 * Copyright (c) 2016, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Canvas.cpp class.
 * \file       Canvas.cpp
 * \date       2016-04-26 $(date)
 * \author     Jedzia.
 *
 * modified    2016-04-26, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../stdafx.h"
//
#define USE_NEW_GL_METHOD 1
#include "Canvas.h"
#include "CanvasDisplayApi.h"
#include "Impl/BothDisplay.h"
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
#include <HumbugGLLib/Log.h>
#include <build/cmake/include/debug.h>

namespace gui {
namespace components {
using namespace std;

struct CCanvas::CCanvasImpl {
private:

    // For OGLPLUS use
    //   OGLPLUS_FORCE_GL_API_LIB = GLEW
    //   OGLPLUS_FORCE_GL_INIT_LIB = SDL
    // ***************************************
    // wrapper around the current OpenGL context
    //oglplus::Context gl;

    // Vertex shader
    //oglplus::VertexShader vs;

    // Fragment shader
    //oglplus::FragmentShader fs;

    // Program
    //oglplus::Program prog;

    // A vertex array object for the rendered triangle
    //oglplus::VertexArray triangle;
    // VBO for the triangle's vertices
    //oglplus::Buffer verts;
    // ***************************************
    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    float glColorR;
    float glColorG;
    float glColorB;
    static boost::random::mt19937 gen;
    glm::mat4 cam;
    boost::scoped_ptr<oglplus::Context> m_context;
    boost::scoped_ptr<CanvasDisplayApi> dApi_;

    static float RandomFloat(float min, float max) {
        boost::random::uniform_real_distribution<> dist(min, max);
        float rnd = static_cast<float>(dist(gen));
        return rnd;
    }

    float rangeMap(float input, float outMin, float outMax, float inMin, float inMax) {
        float slope = 1.0f * (outMax - outMin) / (inMax - inMin);
        //float result = outMin + round(slope * (input - inMin));
        float result = outMin + (slope * (input - inMin));

        return result;
    }

    static glm::mat4 camera(float Translate, glm::vec2 const & Rotate) {
        glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
        glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
        View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
        View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
        return Projection * View * Model;
    }

public:

    explicit CCanvasImpl(CanvasDisplayApi* api) : dApi_(api) {
        glColorR = RandomFloat(0.0f, 1.0f);
        glColorG = RandomFloat(0.0f, 1.0f);
        glColorB = RandomFloat(0.0f, 1.0f);

        // beware: under the hood the context is all static
        m_context.reset(new oglplus::Context);
    }

    ~CCanvasImpl() {
    }

    CanvasDisplayApi * dAPI() const {
        return dApi_.get();
    }

    /**
     * \brief Initialize OpenGL and glew.
     * \return true on success
     */
    static bool InitGL() {
        bool success = true;
        GLenum error = GL_NO_ERROR;

        //Initialize Projection Matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //Check for error
        error = glGetError();
        if(error != GL_NO_ERROR) {
            printf("Error initializing OpenGL! %s\n", gluErrorString(error));
            success = false;
        }

        //Initialize Modelview Matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //Check for error
        error = glGetError();
        if(error != GL_NO_ERROR) {
            printf("Error initializing OpenGL! %s\n", gluErrorString(error));
            success = false;
        }

        //Initialize clear color
        glClearColor(0.f, 0.f, 0.f, 1.f);

        //Check for error
        error = glGetError();
        if(error != GL_NO_ERROR) {
            printf("Error initializing OpenGL! %s\n", gluErrorString(error));
            success = false;
        }

        GLenum err = glewInit();
        if(GLEW_OK != err) {
            /* Problem: glewInit failed, something is seriously wrong. */
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            success = false;

            fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
        }
        else {
        }

        return success;
    } // initGL

    /**
     * \brief Initialize the OGLplus OpenGL wrapper library.
     * This is the static way and should only happen in the
     * main window creation path.
     * \return true on success
     */
    bool InitOGLplus() {
        bool success = true;
        static bool isInitialized = false;
        //return true;
        if(isInitialized) {
            throw  std::runtime_error("CCanvas::CCanvasImpl::InitOGLplus initialized twice.");
        }

        isInitialized = true;

        try
        {
            glGetError();
            //oglplus::Context context;
            //m_context.reset(new oglplus::Context);
            oglplus::Context& context = *m_context;

            std::cout << "Vendor: " << context.Vendor() << std::endl;
            std::cout << "Version: " << context.Version() << std::endl;
            std::cout << "Major version: " << context.MajorVersion() << std::endl;
            std::cout << "Minor version: " << context.MinorVersion() << std::endl;
            std::cout << "GLSL Version: " << context.ShadingLanguageVersion() << std::endl;
            std::cout << "Renderer: " << context.Renderer() << std::endl;
            std::cout << "Extensions:" << std::endl;

            for(auto r = context.Extensions(); !r.Empty(); r.Next()) {
                std::cout << '\t' << r.Front() << std::endl;
            }
            /*std::cout << "Limits:" << std::endl;
               //
               std::size_t w = 0;
               for(auto r=oglplus::EnumValueRange<oglplus::LimitQuery>(); !r.Empty(); r.Next())
               {
               std::size_t n = EnumValueName(r.Front()).size();
               if(w < n) w = n;
               }
               for(auto r=oglplus::EnumValueRange<oglplus::LimitQuery>(); !r.Empty(); r.Next())
               {
               auto ev = r.Front();
               std::cout << std::setw(int(w)) << EnumValueName(ev).c_str() << ": ";
               try { std::cout << context.FloatLimit(ev); }
               catch(...){ std::cout << "N/A"; }
               std::cout << std::endl;
               }*/
             
            //oglplus::VertexShader vs;
        }
        catch(oglplus::Error& err)
        {
            std::cerr <<
                "Error (in " <<
                err.GLFunc() <<
                "'): " <<
                err.what() <<
                " [" <<
                err.SourceFile() <<
                ":" <<
                err.SourceLine() <<
                "] " <<
                std::endl;
            success = false;
        }

        //m_example.reset(new QuadRenderer);
        //InitRenderSetup();
        //m_example->InitShaders();
        //m_example->InitVerts();

        return success;
    } // initGL

    bool InitRenderSetup() {
        bool success = true;
        //dApi_->m_example.reset(new QuadRenderer);
        dApi_->InitGPU();
        //m_example->InitVerts();

        return success;
    } // initGL

    glm::mat4 UpdateCamera() {
        cam = camera(1.0f, glm::vec2(0.5f, 0.5f));
        return cam;
    }
};

boost::random::mt19937 CCanvas::CCanvasImpl::gen;

CCanvas::CCanvas(SDL_Surface* pSurface, bool owner)
    :  pimpl_(new CCanvasImpl(new BothDisplay(this, owner))) {
    //dbgOut(__FUNCTION__ << std::endl);
    //SetSurface(pSurface);
    dAPI()->SetSurface(pSurface);

    m_lstUpdateRects.clear();
}

CCanvas::CCanvas (SDL_Window* pWindow)
    : pimpl_(new CCanvasImpl((new BothDisplay(this, true)))) {
    //dbgOut(__FUNCTION__ << std::endl);
    //SetWindow(pWindow);
    pimpl_->dAPI()->SetWindow(pWindow);

    if(CCanvasImpl::InitGL()) {
#ifdef USE_NEW_GL_METHOD
        pimpl_->InitOGLplus();
#endif
    }

    pimpl_->InitRenderSetup();

    // Todo: Error checking for context and window.
    m_lstUpdateRects.clear();
#if defined GL_VERSION_4_5
    GLint sup_major = 0;
    GLint sup_minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &sup_major);
    glGetIntegerv(GL_MINOR_VERSION, &sup_minor);
    dbgOut("we have opengl 4.5. detected:" << sup_major << "." << sup_minor << " .");
#endif
}

CCanvas::~CCanvas () {
    // Clean up
    ClearUpdateRects();
/*
    if(pimpl_->m_glTextureId) {
        glDeleteTextures(1, &pimpl_->m_glTextureId);
    }

 */
    //dbgOut(__FUNCTION__ << std::endl);
}

CanvasDisplayApi * CCanvas::dAPI() const {
    return pimpl_->dAPI();
}

void CCanvas::CanvasSwapWindow() {
    //SDL_GL_SwapWindow(m_pWindow);
    pimpl_->dAPI()->CanvasSwapWindow();
}

void CCanvas::MainWindowClosing() {
    //pimpl_->m_example.reset();
    pimpl_->dAPI()->Cleanup();
}

bool CCanvas::ToggleOpenGL() {
    return pimpl_->dAPI()->ToggleOpenGL();
}

void CCanvas::AddModifier(const CCanvasRenderer& updfunc) {
    m_vecRendererVault.push_back(updfunc);
}

SDL_Surface * CCanvas::GetSurface() const {
    return pimpl_->dAPI()->GetSurface();
}

SDL_Texture * CCanvas::GetTexture() {
    return pimpl_->dAPI()->GetTexture();
}

void CCanvas::SetSurface(SDL_Surface* pSurface) {
    pimpl_->dAPI()->SetSurface(pSurface);
}

void CCanvas::SetWindow(SDL_Window* pWindow) {
    pimpl_->dAPI()->SetWindow(pWindow);
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
                // it has to be checked, if removing has no side effects. see CSpriteManager::OnIdle
                // for a solution with "while".
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
    source->dAPI()->GLDrawTexture(dstRect);
} // CCanvas::RenderPutCopy

void CCanvas::RenderCopy(SDL_Texture* texture, const CRectangle* dstRect, const CRectangle* srcRect) {
    CanvasRenderCopy(texture, dstRect, srcRect);
}

void CCanvas::RenderCopy(const CRectangle* dstRect, const CRectangle* srcRect) {
    CanvasRenderCopy(GetTexture(), dstRect, srcRect);
    CRectangle rect(0, 0, GetSurface()->w, GetSurface()->h);
    pimpl_->dAPI()->GLDrawTexture(dstRect ? dstRect : &rect);
}

void CCanvas::RenderCopy(const CPoint& offset) {
    CRectangle sdl_rect = GetDimension() + offset;
    CanvasRenderCopy(GetTexture(), &sdl_rect, NULL);
    //RenderCopy(static_cast<const CRectangle*>(NULL), &sdl_rect);
}

void CCanvas::CanvasRenderCopy(SDL_Texture* texture, const CRectangle* dstRect, const CRectangle* srcRect) {
    // all RenderCopy calls flow here

    // canvas based renderer, this instance modifier

    if(!m_vecRendererVault.empty()) {
        // Todo: problematic ? ... other way to do it? only used in TutorA1
        CCanvas source(this->GetSurface());
        pimpl_->dAPI()->SetupParameterClass(&source, texture);

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
    //pimpl_->GLDrawTexture(dstRect);
} // CCanvas::CanvasRenderCopy

void CCanvas::FinalRenderCopy(SDL_Texture* texture, const CRectangle* dstRect, const CRectangle* srcRect) const {
    pimpl_->dAPI()->FinalRenderCopy(texture, dstRect, srcRect);
} // CCanvas::FinalRenderCopy

void CCanvas::MainUpdateAndRenderCopy(const CRectangle* dstRect, const CRectangle* srcRect) {
    // this works only for the main canvas
    /*if(!dApi_->GetRenderer()) {
        return;
       }*/

    //SDL_Texture *tex = SDL_CreateTextureFromSurface(this->m_pRenderer, GetSurface());
    UpdateTexture(GetTexture(), srcRect, GetSurface()->pixels, GetSurface()->pitch);
    RenderCopy(GetTexture(), dstRect, srcRect);
    //  FinalRenderCopy(GetTexture(), dstRect, srcRect);
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
    BothDisplay::MainRenderFinal();
}

void CCanvas::MainRenderClear() {
    BothDisplay::MainRenderClear();
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
    pimpl_->dAPI()->SetRenderDrawBlendMode(mode);
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
    ClearUpdateRects();
    return;
/*
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
 */
}     // UpdateRects

bool CCanvas::Flip () {
    //SDL_RenderPresent(m_pRenderer);
    //return SDL_Flip(GetSurface()) == 0;
    return true;
}

bool CCanvas::SetColorKey(Uint32 key) {
    int result = SDL_SetColorKey(GetSurface(), SDL_TRUE, key);
    return (result == 0);
}

bool CCanvas::SetColorKey(CColor& color) {
    Uint32 col = SDL_MapRGB(GetSurface()->format, color.R(), color.G(), color.B());
    SetTextureColorMod(color);
    int result = SDL_SetColorKey(GetSurface(), SDL_TRUE, col);
    return result == 0;
}

bool CCanvas::SetPaletteColors(const SDL_Color* colors, int firstcolor, int ncolors) const {
    int result = SDL_SetPaletteColors(GetSurface()->format->palette, colors, firstcolor, ncolors);
    return result == 0;
}

bool CCanvas::SetSurfaceAlphaMod(Uint8 alpha) {
    int result = SDL_SetSurfaceAlphaMod(GetSurface(), alpha);
    return result == 0;
}

CColor CCanvas::GetColorKey () const {
    Uint32 col;
    Uint32 result = SDL_GetColorKey(GetSurface(), &col);
    CColor color;
    SDL_GetRGB(col, GetSurface()->format, &color.R(), &color.G(), &color.B());
    return (color);
}

bool CCanvas::ClearColorKey () const {
    return pimpl_->dAPI()->ClearColorKey();
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
    return pimpl_->dAPI()->FillRect(rect, color);
}

void CCanvas::RenderDrawPoint(const CPoint& coordinates, const CColor* color) const {
    pimpl_->dAPI()->RenderDrawPoint(coordinates, color);
}

void CCanvas::RenderDrawLine(const CPoint& pStart, const CPoint& pEnd, const CColor* color) const {
    pimpl_->dAPI()->RenderDrawLine(pStart, pEnd, color);
}

bool CCanvas::RenderDrawRect(const CRectangle& rect, const CColor* color) const {
    return pimpl_->dAPI()->RenderDrawRect(rect, color);
}

bool CCanvas::RenderFillRect(const CRectangle& rect, const CColor* color) const {
    return pimpl_->dAPI()->RenderFillRect(rect, color);
}

bool CCanvas::RenderFillRect(const CRectangle& rect, const CColor& color) const {
    return pimpl_->dAPI()->RenderFillRect(rect, color);
}

bool CCanvas::Clear(const CColor& color) const {
    return pimpl_->dAPI()->Clear(color);
}

bool CCanvas::Blit (const CRectangle& rectDst, const CCanvas& cnvSrc, const CRectangle& rectSrc) const {
    CRectangle rectDst2 = rectDst;
    CRectangle rectSrc2 = rectSrc;
    return (SDL_BlitSurface(cnvSrc.GetSurface(), rectSrc2, GetSurface(), rectDst2) == 0);
}

CCanvas * CCanvas::CreateRGB (Uint32 flags, int width, int height, int depth, Uint32 Rmask,
        Uint32 Gmask, Uint32 Bmask,
        Uint32 Amask) {
    auto surface = SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask, Amask);
    CCanvas* pCanvas = new CCanvas(surface, true);
    return pCanvas;
}

CCanvas * CCanvas::CreateRGBCompatible (Uint32 flags, int width, int height) {
    // throw std::exception("Fuck !");
    //auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
    auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
    SDL_PixelFormat* format = surface->format;
    return (CreateRGB(flags, width, height, format->BitsPerPixel, format->Rmask, format->Gmask,
                    format->Bmask, format->Amask));
}

CCanvas * CCanvas::CreateConvertSurfaceFormat(SDL_Surface* tmpfsurf, Uint32 pixel_format, Uint32 flags) {
    CCanvas* result = new CCanvas(SDL_ConvertSurfaceFormat(tmpfsurf, pixel_format, flags), true);
    return result;
}

CCanvas * CCanvas::CreateConvertSurfaceFormat(SDL_Surface* tmpfsurf) const {
    return CreateConvertSurfaceFormat(tmpfsurf, GetSurface()->format->format, GetSurface()->flags);
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
