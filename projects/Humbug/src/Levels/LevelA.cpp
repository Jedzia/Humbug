/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the LevelA.cpp class.
 * \folder     $(folder)
 * \file       LevelA.cpp
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
#include "LevelA.h"

//#include <build/cmake/include/debug.h>
#include "../Input/PlayerKeys2.h"
#include "../Screens/WavyTextFloat.h"
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Components/Text.h"
#include "GUI/Components/TextScroller.h"
#include "GUI/Data/ColorData.h"
#include "GUI/DebugOverlay.h"
#include "GUI/Sprite/Sprite.h"
#include "GUI/Sprite/SpriteManager.h"
#include "GUI/TileEngine/TileEngine.h"
#include "GUI/TileEngine/TileImage.h"
#include "GUI/TileEngine/TileSet.h"
#include "GUI/Visual/EventHandler.h"
#include "HumbugShared/GameObjects/Player.h"
#include "HumbugShared/ScriptHost/ScriptHost.h"
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <cstdlib>

//
#include <build/cmake/include/debug.h>

struct LevelNames
{
    static const char * const LevelAName;
    static const int ddd = 56;
};

const char * const LevelNames::LevelAName = "LevelA";

//
/*extern "C"
   {
   #include "lua.h"
   #include "lauxlib.h"
   #include "lualib.h"
   }

   #include <luabind/luabind.hpp>
   #include <luabind/operator.hpp>
   #include <boost/filesystem/operations.hpp>
   #include <boost/filesystem/path.hpp>
   #include <boost/cregex.hpp>
   //
 */

/*`
   [heading `TEST_category_tag`]

   Documentation about what is detected.
 */

//#define TEST_category_tag TEST_VERSION_NUMBER(0,0,0)

using namespace gob;
using namespace gui::components;
using namespace gui;
using namespace humbug::screens;

namespace humbug {
  namespace levels {
    /** @class Introplayer:
     *  Detailed description.
     *  @param val TODO
     */
    class Introplayer {
public:

        Introplayer(FileLoader& loader, CCanvas* background)
            : m_pBackground(background), m_lastTick(0), m_firstTick(-1), m_done(false), m_step(0){
            m_pArialfont = loader.FL_LOADFONT("Fonts/ARIAL.TTF", 48);
            m_canvas = background->CreateRGBCompatible( NULL, background->GetWidth(), background->GetHeight() );
            SDL_SetSurfaceAlphaMod(m_canvas->GetSurface(), 5);
        }

		~Introplayer()
        {
	        delete m_canvas;
        }


        /** SprConstMover, SetBackground:
         *  Detailed description.
         *  @param val TODO
         */
        void SetBackground(CCanvas* val) { m_pBackground = val; }

        /** SprConstMover, IsDone:
         *  Detailed description.
         *  @return TODO
         */
        bool IsDone() const { return m_done; }

        /** SprConstMover, OnIdle:
         *  Detailed description.
         *  @param ticks TODO
         */
        void OnIdle(int ticks){
            if (m_done) {
                return;
            }

            if (m_firstTick < 0) {
                m_firstTick = ticks;
            }

            int curTicks = ticks - m_firstTick;

            if (curTicks > 400) {
                m_done = true;
            }
            if ((m_step == 0) && (curTicks > 0 && curTicks < 200) ) {
                CText infoText( m_pArialfont, "And Now...", CColor::Red() );
                //infoText.Put(m_pBackground, m_pBackground->GetDimension());
                infoText.Put( m_canvas, m_canvas->GetDimension() + CPoint(200, 400) );

                //m_canvas->Blit(m_pBackground->GetDimension(), *m_pBackground,
                // m_canvas->GetDimension());
                m_pBackground->Blit( m_pBackground->GetDimension(), *m_canvas, m_canvas->GetDimension() );
                m_pBackground->AddUpdateRect( m_pBackground->GetDimension() );
            }
			else if ((m_step == 0) &&(curTicks > 200 && curTicks < 220 )) {
                SDL_SetSurfaceAlphaMod(m_canvas->GetSurface(), 255);
				m_canvas->Clear(CColor::LightGray());
				m_pBackground->Blit( m_pBackground->GetDimension(), *m_canvas, m_canvas->GetDimension() );
				m_pBackground->AddUpdateRect( m_pBackground->GetDimension() );
				m_step++;
			}
			else if ((m_step == 1) &&(curTicks > 220 && curTicks < 320 )) {
                SDL_SetSurfaceAlphaMod(m_canvas->GetSurface(), 11);
				CText infoText( m_pArialfont, "To Something Completely Different!", CColor::Blue() );
				infoText.Put( m_canvas, m_canvas->GetDimension() + CPoint(100, 200) );
				m_pBackground->Blit( m_pBackground->GetDimension(), *m_canvas, m_canvas->GetDimension() );
				m_pBackground->AddUpdateRect( m_pBackground->GetDimension() );
			}

            m_lastTick = ticks;
        } // OnIdle
private:

        CCanvas* m_pBackground;
        CCanvas* m_canvas;
        TTF_Font* m_pArialfont;
        int m_lastTick;
        int m_firstTick;
		int m_step;
        bool m_done;
    };

    struct LevelA::LevelAImpl {
        LevelAImpl(FileLoader& loader, CCanvas* background)
            : m_intro(loader, background)
        {}
        /** @class SprConstMover:
         *  Detailed description.
         *  @param sprite TODO
         * @param ticks TODO
         * @return TODO
         */
        class SprConstMover {
            float x, y;

public:

            SprConstMover(float startX = 0, float startY = 0) : x(startX), y(startY){
                dbgOut(__FUNCTION__ << " created:" << " (" << this << ")");
            }
            ~SprConstMover(){
                dbgOut(__FUNCTION__ << " " << this);
            }
            /** $(fclass), operator ():
             *  Detailed description.
             *  @param sprite TODO
             * @param ticks TODO
             * @return TODO
             */
            void operator()(CSprite* sprite, int ticks, CSpriteModifierData& mdata) {
                sprite->SetPosition( CPoint( static_cast<int>(x), static_cast<int>(y) ) );
            }
            /** EyeMover, Y:
             *  Detailed description.
             *  @return TODO
             */
            float Y() const { return y; }

            /** EyeMover, Y:
             *  Detailed description.
             *  @param val TODO
             */
            void Y(float val) { y = val; }

            /** EyeMover, X:
             *  Detailed description.
             *  @return TODO
             */
            float X() const { return x; }

            /** EyeMover, X:
             *  Detailed description.
             *  @param val TODO
             */
            void X(float val) { x = val; }
        };

        /** EyeMover, UpdatePlayer:
         *  Detailed description.
         *
         */
        void UpdatePlayer(){
            float x = m_player.GetPosition().x;
            float y = m_player.GetPosition().y;
            m_sprConstMover.X(x);
            m_sprConstMover.Y(y);
        }
        /** EyeMover, DoIntro:
         *  Detailed description.
         *  @param ticks TODO
         */
        void DoIntro(int ticks){
            m_intro.OnIdle(ticks);
        }
        /** EyeMover, UpdatePlayer:
         *  Detailed description.
         *  @param p TODO
         */
        void UpdatePlayer(CPoint& p){
            float x = static_cast<float>( p.X() );
            float y = static_cast<float>( p.Y() );
            m_sprConstMover.X(x);
            m_sprConstMover.Y(y);
        }
        //prv::EyeMover eyemover;
        //prv::WormMover wormmover;
        int x;
        //shost::LuaScript<int, int, int> *script;
        long allocReqNum;
        boost::shared_ptr<shost::LuaScript<int, double, double >> script;
        Player m_player;
        SprConstMover m_sprConstMover;
        Introplayer m_intro;
    };

    LevelA::LevelA( FileLoader& loader, CCanvas* background) :
        pimpl_( new LevelA::LevelAImpl(loader, background) ),
        Screen(background),
        m_Loader(loader),
        m_pArialfont(NULL),
        //m_iUpdateTimes(0),
        m_pScrollText(NULL),
        m_pScroller(NULL),
        m_inScreenDelta(0),
        m_pSprMgr(new CSpriteManager){
        //,m_pSprEye(NULL),
        //m_pSprWormler(NULL)
        dbgOut(__FUNCTION__ << " " << this);
    }

    LevelA::~LevelA(void){
        //if (m_pArialfont) { Not needed, is freed by the loader. // Todo: Implement an immediate
        // free function for fonts, like in images
        //    TTF_CloseFont(m_pArialfont);
        //}

        //delete m_pScrollText;
        //delete m_pScroller;
        //delete m_pBackground;
        //delete m_pSprWormler;
        //delete m_pSprEye;
        dbgOut(__FUNCTION__ << " " << this);
    }

/*GroupId LevelA::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/

    namespace hspriv {
      /** @class EyeMover:
       *  Detailed description.
       *  @param sprite TODO
       * @param ticks TODO
       * @return TODO
       */
      class EyeMover {
          int h_;
          bool toggle_;
          int deltaY_;
          uint32_t sproffs;
          //int rnd;

public:

          EyeMover(int deltaY = 0, uint32_t spriteoffset = 4) : deltaY_(deltaY),
              h_(-1),
              toggle_(false),
              sproffs(spriteoffset){
              dbgOut(__FUNCTION__ << " created:" << " (" << this << ")");
              int rnd = 180 - ( rand() % 360);
              h_ = rnd;
          }
          ~EyeMover(){
              dbgOut(__FUNCTION__ << " " << this);
          }
          /** $(fclass), operator ():
           *  Detailed description.
           *  @param sprite TODO
           * @param ticks TODO
           * @return TODO
           */
          void operator()(CSprite* sprite, int ticks, CSpriteModifierData& mdata) {
              double ss = std::sin(static_cast<double>(h_) / 3.14159 / 4.0);
              int ssin = static_cast<int>(ss * 100);

              //sprite->SetPosition(CPoint(100 + ((ticks % 128) * 6), 460 + h_ + deltaY_ + ssin));
              sprite->SetPosition( CPoint(130 + ssin, deltaY_) );
              sprite->SetSpriteOffset(ticks % sproffs);

              if (h_ >= 180) {
                  toggle_ = false;
              }
              else if (h_ <= -180) {
                  toggle_ = true;
              }

              if (toggle_) {
                  h_++;
              }
              else {
                  h_--;
              }
          } // ()
      };
    }

    /** TestClass, greetHopperA:
     *  Detailed description.
     *
     */
    void greetHopperA(){
        std::cout << "hello world from LevelA!\n";
    }

    /** @class TestClass:
     *  Detailed description.
     *  @param i TODO
     * @return TODO
     */
    class TestClass {
public:

        TestClass(std::vector<int> v) : m_vec(v) {}

        TestClass(int b, int e) {
            for (int i = b; i <= e; ++i) {
                m_vec.push_back(i);
            }
        }
        /** SpriteFrame, get:
         *  Detailed description.
         *  @param i TODO
         * @return TODO
         */
        int get(size_t i) const {
            return m_vec[i];
        }
private:

        std::vector<int> m_vec;
    };

    /** @class SpriteFrame:
     *  Detailed description.
     *  @return TODO
     */
    class SpriteFrame {
public:

        SpriteFrame(unsigned int x, unsigned int y)
            : m_x(x), m_y(y) {}

        /** SpriteMovie, X:
         *  Detailed description.
         *  @return TODO
         */
        unsigned int X() const { return m_x; }

        /** SpriteMovie, Y:
         *  Detailed description.
         *  @return TODO
         */
        unsigned int Y() const { return m_y; }

private:

        unsigned int m_x;
        unsigned int m_y;
    };

    /** @class SpriteMovie:
     *  Detailed description.
     *  @return TODO
     */
    class SpriteMovie {
public:

        SpriteMovie(std::string x, std::vector<SpriteFrame> y)
            : m_x(x), m_y(y) {}

        /** $(class), X:
         *  Detailed description.
         *  @return TODO
         */
        std::string X() const { return m_x; }

        /** $(class), Y:
         *  Detailed description.
         *  @return TODO
         */
        std::vector<SpriteFrame> Y() const { return m_y; }

private:

        std::string m_x;
        std::vector<SpriteFrame> m_y;
    };

    /** LevelA, OnInit:
     *  Detailed description.
     *  @param argc TODO
     * @param argv TODO
     * @return TODO
     */
    bool LevelA::OnInit( int argc, char* argv[] ){
        // Master()->GetMainCanvas();
        CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
        m_pMainCanvas->Clear( CColor::Black() );

        //m_pOverlay.reset(new DebugOverlay(m_Loader, controls::CControl::GetMainControl(), 1, "LevelA"));
        m_pOverlay.reset(new DebugOverlay(m_Loader, NULL, 1, "LevelA"));

        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
        // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
        m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
        //m_pArialfont =
        // TTF_OpenFont("E:/Projects/C++/Humbug/projects/Humbug/Resources/Fonts/ARIAL.TTF", 24);
        mcol = CColor::White();

        //	CCanvas tmpCanvas(( m_Loader.FL_LOADIMG("Intro/LevelABg.png")
        // ));
        CCanvas tmpCanvas( ( m_Loader.FL_LOADIMG("Intro/TileScreenBg.png") ) );
        CCanvas* testCanvas =
            CCanvas::CreateRGBCompatible( NULL, m_pMainCanvas->GetWidth(), m_pMainCanvas->GetHeight() );
        //SDL_SetSurfaceAlphaMod(testCanvas->GetSurface(), 255);
	    CColor c_color = CColor(0x00, 0x00, 0x00);
	    testCanvas->SetColorKey( c_color );

        testCanvas->Blit( tmpCanvas.GetDimension(), tmpCanvas, tmpCanvas.GetDimension() );

        // das muss alles in die tiles engine. die muss wissen welchen ColorKey sie braucht und wie
        // gross der canvas sein muss.
        // braucht ihn ja nur einmal zu erstellen und kann ihn dann cachen.
        CCanvas* tmpTilesCanvas = CCanvas::CreateRGBCompatible( NULL,
                m_pMainCanvas->GetWidth() * 2, m_pMainCanvas->GetHeight() );
        tmpTilesCanvas->SetColorKey( c_color );
        m_pTiles.reset( tmpTilesCanvas );

// SDL_SWSURFACE | SDL_SRCALPHA | SDL_TRUE

        //SDL_SetColorKey(tmpfsurf, SDL_TRUE, 0xff00ff);
        //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_TRUE, 0xff00ff);
        //SDL_SetSurfaceAlphaMod(tmpfsurf, 0);
        m_pBackground.reset( testCanvas );
        //m_pBackground->SetColorKey(CColor::Black());
        //SDL_SetSurfaceAlphaMod(m_pBackground->GetSurface(), 128);

        //CCanvas tmpCanvas( tmpfsurf );
        m_Loader.FreeLast();

        //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
        //m_pBackground->Blit(m_pBackground->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
        m_pMainCanvas->AddUpdateRect( m_pBackground->GetDimension() );

        //"\r\n"
        CColor m_colText = CColor::White();
        std::ostringstream outstring;
        outstring << "Jedzia";
        outstring << " .................... ";
        outstring << "328.123.847";

        CText* text = new CText(m_pArialfont, outstring.str(), m_colText);

        //const boost::function<void(CCanvas*, int)> textMo = mtextfloat;
        //text->AddAnimator(boost::ref( mtextfloat ));
        text->AddAnimator( WavyTextFloat(64) );
        m_pScrollText.reset(text);

        // ### Tiles ###

        // ###

        /*CTileSet* tileSet = NULL;
           CTileImageSetup tilesetup;
           tilesetup.TileSetName = LevelNames::LevelAName;
           tilesetup.TileWidth = 32;
           tilesetup.TileHeight = 32;
           tilesetup.TileCountX = 13;
           tilesetup.TileCountY = 2;
           tilesetup.TransparentX = 0;
           tilesetup.TransparentY = 0;
           tilesetup.Sequences = 0;
           tileSet = new CTileSet( m_pMainCanvas, new CTileImage(m_Loader,
              "data/levels/LevelA/LevelA.png", tilesetup),
                m_pBackground.get(), CRectangle(0, 0, 1024, 768) );*/

        // Todo simplify this and let 'em load by CTileEngine with a simplified convention for the
        // files
        // LevelA.til, LevelA.map, LevelA.png ... hmmm no HumbugTiles.til contains descriptions for
        // the available maps and the png
        // so HumbugTiles.til can load the LevelA.png, cos that is inside the .til file
        CTileSet* tileSet =
            new CTileSet( m_pMainCanvas, new CTileImage(m_Loader, "data/levels/LevelA/LevelA.png",
                            "data/levels/LevelA/HumbugTiles.til"),
                    m_pBackground.get(), CRectangle(0, 0, 1024 * 2, 768 * 2) );

        m_pTileEngine.reset( new CTileEngine( m_pMainCanvas, m_pBackground.get() ) );
        m_pTileEngine->AddTileSet(tileSet);

        //std::string humbugTilesTil =
        // m_Loader.FL_LOADASSTRING("data/levels/LevelA/HumbugTiles.til");
        //CTileMap *tmap = new
        // CTileMap(m_Loader.FL_LOADASSTRING("data/levels/LevelA/HumbugTiles.til"));
        CTileMap* tmap = new CTileMap( m_Loader.FL_LOADASSTRING("data/levels/LevelA/Map1.map") );
        //FileLoadingInfo& finf = m_Loader.FL_LOAD("data/levels/LevelA/HumbugTiles.bin");
        //tmap->ReadBinary(finf.Data(), finf.Size());
        m_pTileEngine->AddTileMap(tmap);
        //(*m_pTileEngine)["Map1"].DrawMap(m_pBackground.get());
        (*m_pTileEngine)["Map1"].DrawMap( m_pTiles.get() );

        /*CTileEngine& eng = (*m_pTileEngine);
           //(*m_pTileEngine)[LevelNames::LevelAName]->GetTileImage()->ShowTiles(
              m_pBackground.get() );

           CTile tile1 = eng.GetTileSet(LevelNames::LevelAName)->CreateTile(0);
           CTile tile2 = eng.GetTileSet(LevelNames::LevelAName)->CreateTile(1);
           CTile tile3 = eng.GetTileSet(LevelNames::LevelAName)->CreateTile(2);
           CTile tile4 = eng.GetTileSet(LevelNames::LevelAName)->CreateTile(3);

           for (int i = 0; i < 2; i += 4)
           {
                const int xdiff = 100;
                tile1.Draw( m_pBackground.get(), CPoint(xdiff * i, 300) );
                tile2.Draw( m_pBackground.get(), CPoint(xdiff * (i + 1), 300) );
                tile3.Draw( m_pBackground.get(), CPoint(xdiff * (i + 2), 300) );
                tile4.Draw( m_pBackground.get(), CPoint(xdiff * (i + 3), 300) );
           }
         */
        m_pMainCanvas->AddUpdateRect( m_pBackground->GetDimension() );

        // ### Sprites ###
        m_pSprEye = new CSprite( m_Loader, "Sprites/male_spritesA.png", m_pMainCanvas,
                CRectangle(0, 0, 64, 64), CPoint(64, 0) );
        m_pSprMgr->AddSprite( m_pSprEye, hspriv::EyeMover(160, 8) );
        //m_pSprMgr->AddSprite(m_pSprEye, boost::ref( pimpl_->eyemover ) );
        //m_pSprMgr->AddSprite(m_pSprEye);
        CSprite* m_pSprWormler = new CSprite( m_Loader, "Sprites/wormtiles.png", m_pMainCanvas,
                CRectangle(0, 0, 256, 64), CPoint(0, 64) );
        m_pSprWormler->SetColorAndAlpha(0xff00ff, 128);
        m_pSprMgr->AddSprite( m_pSprWormler, hspriv::EyeMover(260, 40) );

        CSprite* m_pSprite2 = new CSprite( m_Loader, "Sprites/Voiture.bmp", m_pMainCanvas,
                CRectangle(0, 0, 32, 32), CPoint(32, 0) );
        m_pSprMgr->AddSprite( m_pSprite2, boost::ref( pimpl_->m_sprConstMover ) );

        //_CrtSetBreakAlloc(pimpl_->allocReqNum+4);
        //_crtBreakAlloc = pimpl_->allocReqNum+4;

        shost::ScriptHost shost;
        //shost.RunScript2(m_Loader.FL_LOADASSTRING("lua/hello.lua"));
        // shost.RunScript(m_Loader.FL_LOADASSTRING("lua/funcret.lua"));
        //shost.RunScript4(m_Loader.FL_LOADASSTRING("lua/iowrite.lua"));
        //shost.RunScript(m_Loader.FL_LOADASSTRING("lua/globalclass.lua"));
        //shost.RunScript6( m_Loader.FL_LOADASSTRING("lua/globalclass.lua") );
        //shost.RunScript7( m_Loader.FL_LOADASSTRING("lua/--FREE--.lua") );

        typedef shost::LuaScript<int, double, double> ScriptType;
        ScriptType::Script s = shost.generate<int, double, double>( m_Loader.FL_LOADASSTRING(
                        "Lua/sprite1.lua"), "Ticks", "X", "Y" );
        pimpl_->script = s;

        world.FPS = CApplication::FramesCap();
        CRectangle screenRect = m_pMainCanvas->GetDimension();
        world.ScreenX = screenRect.GetW();
        world.ScreenY = screenRect.GetH();

        // Todo maybe an functor to initialize more global stuff
        ( *s->AddStatic(world) )("World")
        .def("greet", &greetHopperA)
        .def_readonly("FPS", &World::FPS)
        .def_readonly("ScreenX", &World::ScreenX)
        .def_readonly("ScreenY", &World::ScreenY);

        // !!! Warning, Sprites/male_spritesA.spr exists on local and virtual filesystem. !!!
        ScriptType::Script sprInit = shost.generate<int, double, double>( m_Loader.FL_LOADASSTRING(
                        "Sprites/male_spritesA.spr"), "Ticks", "X", "Y" );
        //ScriptType::Script sprInit = shost.generate<int, double, double>(
        // m_Loader.FL_LOADASSTRING(
        //	"Sprites/male_sprites.spr"), "Ticks", "X", "Y" );

        TestClass st(12, 99);

        ( *sprInit->AddStatic(st) )("TestClass", "tc")
        .def( luabind::constructor<std::vector<int> >() )
        .def( luabind::constructor<int, int>() )
        .def("get", &TestClass::get);

        //boost::shared_ptr<shost::LuaScript::register_binder<SpriteFrame >>& bla=
        int xyz = 55;

        typedef shost::LuaVarCapsule<luabind::class_<SpriteFrame >> SprCapsule;
        SprCapsule maleSpriteCap = shost::makeFarm( sprInit,
                ( *sprInit->Register<SpriteFrame>() )("SpriteFrame")
                .def( luabind::constructor<int, int>() )
                .def("X", &SpriteFrame::X)
                .def("Y", &SpriteFrame::Y) );

        ( *sprInit->Register<SpriteMovie>() )("SpriteMovie")
        .def( luabind::constructor<std::string, std::vector<SpriteFrame >> () )
        .def("X", &SpriteMovie::X)
        .def("Y", &SpriteMovie::Y);

        //luabind::class_<SpriteFrame>& xasd = maleSpriteCap.Value();
        //SprCapsule::ObjType mmy(1,2);
        //mmy.X();

        /*luabind::module(sprInit->L())
                [
                        luabind::class_<TestClass>("TestClass_")
                        .def(luabind::constructor<std::vector<int> >())
                        .def(luabind::constructor<int, int>())
                        .def("get", &TestClass::get)
                ];*/

        int success = sprInit->run_script(99);

        luabind::object o3(luabind::globals( sprInit->L() )["tcx"]);

        if (o3) {
            // is_valid
            // ...

            int luatype = luabind::type(o3);

            if (luabind::type(o3) == LUA_TUSERDATA) {
                TestClass otherValue = luabind::object_cast<TestClass>(o3);
                int abc = 4;
                abc++;
            }
        }

        SpriteFrame otherValue2(0, 0);
        bool success3 = maleSpriteCap.GetLuaValue("spf", otherValue2);
        SpriteFrame otherValuex = maleSpriteCap.GetLuaValue("spf");

        SpriteFrame otherValue3(0, 0);
        bool fsuccess = sprInit->GetLuaValue<SpriteFrame>("spf", otherValue3);

        luabind::object o4(luabind::globals( sprInit->L() )["spf"]);

        if (o4) {
            // is_valid
            // ...

            int luatype = luabind::type(o4);

            if (luabind::type(o4) == LUA_TUSERDATA) {
                SpriteFrame otherValue = luabind::object_cast<SpriteFrame>(o4);
                int abc = 4;
                abc++;
            }
        }

        //SpriteMovie otherValue3(0,0);
        //fsuccess = sprInit->GetLuaValue<SpriteMovie>("spMovie", otherValue3);
        SpriteMovie smovie = sprInit->GetLuaValue<SpriteMovie>("spMovie");

        //int *x = new int(666);
        m_pKeyHandler.reset( new PlayerKeys2(200, 600) );

        return Screen::OnInit(argc, argv);
    } // OnInit

    /** LevelA, OnIdle:
     *  Detailed description.
     *  @param ticks TODO
     * @return TODO
     */
    void LevelA::OnIdle(int ticks){
        //m_pScroller->Scroll(4);
        pimpl_->script->run_script(ticks);
        double spr1X = pimpl_->script->GetData1();
        double spr1Y = pimpl_->script->GetData2();
        //m_pSprEye->SetPosition( CPoint( static_cast<int>(spr1X), static_cast<int>(spr1Y) ) );

        m_pKeyHandler->HookIdle(ticks, 5);
        m_pOverlay->IdleSetVars(ticks);
        m_pSprMgr->OnIdle(ticks);
        pimpl_->DoIntro(ticks);
    }

    /** LevelA, OnDraw:
     *  Detailed description.
     *  @return TODO
     */
    void LevelA::OnDraw(){
        if ( !pimpl_->m_intro.IsDone() ) {
            return;
        }

        static int coldelta = 0;
        static int tilesDelta = 0;
        tilesDelta += m_inScreenDelta;

        CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
        m_pMainCanvas->Lock();

        CPoint pTilesDelta(m_pKeyHandler->Char().GetX() - 200, 0);
        CPoint pDelta(tilesDelta, 0);
        m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension() - pDelta );

        //(*m_pTileEngine)["Map1"].DrawMap( m_pTiles.get() );
        // (*m_pTileEngine)["Map1"].DrawMap(); sollte einen canvas zurueckgeben, der weiss wie gross
        // er sein muss
        m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pTiles, m_pTiles->GetDimension() + pTilesDelta );

        m_pMainCanvas->AddUpdateRect( m_pMainCanvas->GetDimension() );
        /*CRectangle frect(700, 500, 185, 185);
           SDL_Color* wavemap = ColorData::Instance()->Wavemap();
           int index = (coldelta * 2 & 63);

           //m_pMainCanvas->FillRect( frect, mcol );
           SDL_Color& fcol = wavemap[index];
           m_pMainCanvas->FillRect( frect, CColor(fcol.r, fcol.g, fcol.b) );
           m_pMainCanvas->AddUpdateRect(frect);*/

        CRectangle txtDims = m_pScrollText->GetCanvas()->GetDimension();
        CRectangle dstDims = txtDims + CPoint( 335, 200);
        m_pScrollText->Put(m_pBackground.get(), dstDims, txtDims );
        m_pMainCanvas->AddUpdateRect(dstDims);

        coldelta++;

        if (coldelta > 64) {
            coldelta = 0;
        }

        /*CTileEngine& eng = (*m_pTileEngine);
           CTile tile1 = eng.GetTileSet(LevelNames::LevelAName)->CreateTile(0);
           const int xdiff = 100;
           //tile1.Draw( m_pBackground.get(), CPoint(coldelta * 5, 100) );
           tile1.Draw( m_pMainCanvas, CPoint(coldelta * 5, 100) );
         */

        m_pSprMgr->OnDraw();
        m_pOverlay->OnDraw();

        m_pMainCanvas->Unlock();
    } // OnDraw

    /** LevelA, OnUpdate:
     *  Detailed description.
     *  @return TODO
     */
    void LevelA::OnUpdate(){
        Screen::OnUpdate();
        x += 1 + (rand() << 21);
        mcol.SetR( rand() );
        mcol.SetG( rand() );
        mcol.SetB( rand() );

        //pimpl_->UpdatePlayer();
	    CPoint c_point = m_pKeyHandler->Char();
	    pimpl_->UpdatePlayer( c_point );
        //m_iUpdateTimes++;
    }

    /** $(class), OnEvent:
     *  Detailed description.
     *  @param pEvent TODO
     * @return TODO
     */
    void LevelA::OnEvent( SDL_Event* pEvent ){
        m_pKeyHandler->HookEventloop(pEvent);

        switch(pEvent->type)
        {
        case SDL_KEYDOWN:                            //key press
        {
            //key press
            //OnKeyDown(pEvent->key.keysym.sym, pEvent->key.keysym.mod, pEvent->key.keysym.unicode);
            SDL_Keycode sym = pEvent->key.keysym.sym;

            if( sym == SDLK_w ) {
                //pimpl_->m_player.Move( GVector2D::Up() );
            }
            else if( sym == SDLK_s ) {
                //pimpl_->m_player.Move( GVector2D::Down() );
            }

            if( sym == SDLK_a ) {
                // m_inScreenDelta++;
                //pimpl_->m_player.Move( GVector2D::Left() );
            }
            else if( sym == SDLK_d ) {
                // m_inScreenDelta--;
                //pimpl_->m_player.Move( GVector2D::Right() );
            }
            else if( sym == SDLK_r ) {
                CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
                m_pMainCanvas->Clear( CColor::Black() );
            }
            else if( sym == SDLK_x ) {
                //CApplication::GetApplication()->SendMessageQ(MsgID,Parm1,Parm2,Parm3,Parm4)
                //SendMessageQ(MSGID_QuitApp);
                CApplication::GetApplication()->SendMessageQ(gui::CEventHandler::MSGID_QuitApp);
            }

            break;
        }

        default:
            break;
        }             // switch
    }     // OnEvent
  }
}
