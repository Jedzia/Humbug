/*---------------------------------------------------------*/
/*!
 * This file is part of Playground, your C++ vacation spot.
 * License details can be found in the file COPYING.
 * Copyright (c) 2016, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the QuadRenderer.h class.
 * \file       QuadRenderer.h
 * \date       2016-04-26 $(date)
 * \author     Jedzia.
 *
 * modified    2016-04-26, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
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
/** @class GpuProgram:
 *  Detailed description.
 *  @return TODO
 */
class GpuProgram {
    /* Todo: Make the render Engine modular
     * a RenderEngineFacility
     * with:
     *  Setup()
     *  Clear()
     *  Render()
     *  Detach()
     *  Cleanup()
     *  etc.
     */

    oglplus::VertexShader vs;

    oglplus::FragmentShader fs;

    oglplus::Program prog;
    bool isShaderInitialized;

public:

    /** Brief description of GpuProgram, IsShaderInitialized
     *  Detailed description.
     *  @return TODO
     */
    bool IsShaderInitialized() const {
        return isShaderInitialized;
    }

    explicit GpuProgram()
        : isShaderInitialized(false) {
        LOGSTD(__FUNCTION__ << " [" << typeid(*this).name() << "] (" << this << ")");
        InitShaders();
    }

    /** Brief description of GpuProgram, GetProgram
     *  Detailed description.
     *  @return TODO
     */
    const oglplus::Program& GetProgram() const {
        return prog;
    }

    /** Brief description of GpuProgram, SetColor
     *  Detailed description.
     *  @param r TODO
     *  @param g TODO
     *  @param b TODO
     */
    void SetColor(float r, float g, float b) const {
        (GetProgram() / "colorIn") = oglplus::Vec3f(r, g, b);
    }

private:

    /** Brief description of GpuProgram, InitShaders
     *  Detailed description.
     *
     */
    void InitShaders() {
        LOGSTD(__FUNCTION__ << " [" << typeid(*this).name() << "] (" << this << ")");
        try
        {
            // Set the vertex shader source
            /*vs.Source(
               " \
               #version 120\n \
               attribute vec3 Position; \
               //           out vec4 color; \
               void main(void) \
               { \
               gl_Position = vec4(Position, 1.0); \
               //            color = vec4(0.0, 0.3, 0.7, 1.0);  \
               } \
               ");*/

            vs.Source(
            " \
            #version 140\n \
            uniform vec3 colorIn; \
            attribute vec3 Position; \
            out vec4 color; \
            void main(void) \
            { \
            gl_Position = vec4(Position, 1.0); \
            color = vec4(colorIn, 1.0);  \
            } \
            ");
            // compile it
            vs.Compile();

            // set the fragment shader source
            /*fs.Source(
               " \
               #version 120\n \
               //        in vec4 color; \
               //        out vec4 gl_FragColor; \
               void main(void) \
               { \
               //        gl_FragColor = color; \
               gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0); \
             \
               } \
               ");*/

            fs.Source(
            " \
            #version 140\n \
            in vec4 color; \
            out vec4 fragColor; \
            void main(void) \
            { \
            fragColor = color; \
            } \
            ");
            // compile it
            fs.Compile();

            // attach the shaders to the program
            prog.AttachShader(vs);
            prog.AttachShader(fs);
            // link and use it
            prog.Link();
            prog.Use();

            isShaderInitialized = true;
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
            throw err;
        }
    }         // InitShaders
};

/** @class QuadRenderer:
 *  Setup Shaders and vertex buffer objects. Draw with Display();
 *  Associated with the GpuProgram.
 *
 */
class QuadRenderer {
    oglplus::Context gl;

    // for now only one Shader can exist.
    static boost::scoped_ptr<GpuProgram> gprog;
    static int nr;
    boost::scoped_ptr<oglplus::VertexArray> triangle;

    oglplus::Buffer verts;
    oglplus::SizeType vertexCount;
    bool isVertexInitialized;

public:

    explicit QuadRenderer()
        : vertexCount(0), isVertexInitialized(false) {
        LOGSTD(__FUNCTION__ << " [" << typeid(*this).name() << "] (" << this << ")");
        //InitShaders();
        //InitVerts();
        triangle.reset(new oglplus::VertexArray);
        LOGSTD(__FUNCTION__ << "-After [" << typeid(*this).name() << "] (" << this << ")");
    }


    /** Brief description of QuadRenderer, IsInitialized
     *  Detailed description.
     *  @return TODO
     */
    bool IsInitialized() const {
        return gprog && gprog->IsShaderInitialized() && isVertexInitialized;
    }

    //boost::scoped_ptr<oglplus::VertexArrayAttrib> vert_attr;

    void InitGPUProgram()
    {
#ifdef USE_NEW_GL_METHOD
        if (!gprog) {
            LOGSTD(__FUNCTION__ << " [" << typeid(*this).name() << "] (" << this << ")");
            gprog.reset(new GpuProgram);
        }
#endif
        //vert_attr.reset(new oglplus::VertexArrayAttrib(gprog->GetProgram(), "Position"));
    }
    
    /** Brief description of QuadRenderer, InitVerts
     *  Detailed description.
     *  @param triangle_verts TODO
     *  @param vertexCountX TODO
     */
    void InitVerts(const GLfloat* triangle_verts, const oglplus::SizeType& vertexCountX) {
        using namespace oglplus;
        if (!this)
        {
            LOGSTD("PANIC !!! this is NULLPTR !!! ");
        }
        LOGSTD(__FUNCTION__ << " [" << typeid(*this).name() << "] (" << this << ")");
        InitGPUProgram();

        // bind the VAO for the triangle
        LOGSTD(__FUNCTION__ << "+Triangle("<< triangle->HasValidName() << ") [" << typeid(*this).name() << "] (" << this << ")");
        triangle->Bind();
        LOGSTD(__FUNCTION__ << "-Triangle [" << typeid(*this).name() << "] (" << this << ")");

        /*GLfloat triangle_verts[9] = {
           0.0f, 0.0f, 0.0f,
           0.1f, 0.0f, 0.0f,
           0.0f, 0.1f, 0.0f
           };*/
        vertexCount = vertexCountX;

        // bind the VBO for the triangle vertices
        verts.Bind(Buffer::Target::Array);
        LOGSTD(__FUNCTION__ << "-Bind [" << typeid(*this).name() << "] (" << this << ")");

        // upload the data
        Buffer::Data(
                Buffer::Target::Array,
                vertexCount * 3,
                triangle_verts
                );
        // setup the vertex attribs array for the vertices
        VertexArrayAttrib vert_attr(gprog->GetProgram(), "Position");
        //vert_attr->Setup<GLfloat>(3);
       // vert_attr->Enable();
        vert_attr.Setup<GLfloat>(3);
        vert_attr.Enable();

        //gl.ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        //gl.ClearDepth(1.0f);

        isVertexInitialized = true;
    }         // InitVerts

    /** Brief description of QuadRenderer, SetColor
     *  Detailed description.
     *  @param r TODO
     *  @param g TODO
     *  @param b TODO
     */
    void SetColor(float r, float g, float b) const {
        gprog->SetColor(r, g, b);
    }

    /** Brief description of QuadRenderer, Display
     *  Detailed description.
     *
     */
    void Display(void) const {
        using namespace oglplus;

        //gl.Clear().ColorBuffer().DepthBuffer();

        if(!IsInitialized()) {
            return;
        }

        LOGSTD(__FUNCTION__ << " [" << typeid(*this).name() << "] (" << this << ")");
        gl.DrawArrays(PrimitiveType::Triangles, 0, vertexCount);
    }

    /** Brief description of QuadRenderer, Cleanup
     *  Detailed description.
     *
     */
    void Cleanup() const {
        gprog.reset();
    }
};

boost::scoped_ptr<GpuProgram> QuadRenderer::gprog;
int QuadRenderer::nr = 0;

/** @class SingleExample:
 *  Detailed description.
 *  @return TODO
 */
/*
   class SingleExample {
   private:

   static QuadRenderer *& SingleInstance(void) {
   static QuadRenderer* test = nullptr;
   return test;
   }

   SingleExample(const SingleExample&);

   public:

   SingleExample(void) {
   assert(!SingleInstance());
   SingleInstance() = new QuadRenderer();
   }

   ~SingleExample(void) {
   assert(SingleInstance());
   delete SingleInstance();
   SingleInstance() = nullptr;
   }

   static void Display(void) {
   assert(SingleInstance());
   SingleInstance()->Display();
   //glutSwapBuffers();
   }
   };
 */
}
}
