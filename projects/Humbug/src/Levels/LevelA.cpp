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
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Components/Text.h"
#include "GUI/Components/TextScroller.h"
#include "GUI/Data/ColorData.h"
#include "GUI/TileEngine/TileEngine.h"
#include "GUI/TileEngine/TileImage.h"
#include "GUI/TileEngine/TileSet.h"
#include "GUI/Sprite/Sprite.h"
#include "GUI/Sprite/SpriteManager.h"
#include "GUI/Visual/EventHandler.h"
#include "HumbugShared/ScriptHost/ScriptHost.h"
#include "../Screens/WavyTextFloat.h"
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <cstdlib>

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

using namespace gui::components;
using namespace gui;
using namespace humbug::screens;

namespace humbug {
  namespace levels {
    struct LevelA::LevelAImpl {
        //prv::EyeMover eyemover;
        //prv::WormMover wormmover;
        int x;
        //shost::LuaScript<int, int, int> *script;
        long allocReqNum;
        boost::shared_ptr<shost::LuaScript<int, double, double >> script;
    };

    LevelA::LevelA( FileLoader& loader, CCanvas* background) :
        pimpl_(new LevelA::LevelAImpl ),
        Screen(background),
        m_Loader(loader),
        m_pArialfont(NULL),
        //m_iUpdateTimes(0),
        m_pScrollText(NULL),
        m_pScroller(NULL),
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
          void operator()(CSprite* sprite, int ticks) {
              double ss = std::sin(static_cast<double>(h_) / 3.14159 / 4.0);
              int ssin = static_cast<int>(ss * 100);

              //sprite->SetPos(CPoint(100 + ((ticks % 128) * 6), 460 + h_ + deltaY_ + ssin));
              sprite->SetPos( CPoint(130 + ssin, deltaY_) );
              sprite->SprOffset(ticks % sproffs);

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


	void greetHopperA(){
		std::cout << "hello world from LevelA!\n";
	}

	class TestClass {
	public:
		TestClass(std::vector<int> v) : m_vec(v) {}

		TestClass(int b, int e) {
			for (int i = b; i <= e; ++i)
				m_vec.push_back(i);
		}

		int get(size_t i) const {
			return m_vec[i];
		}

	private:
		std::vector<int> m_vec;
	};

	class SpriteFrame {
	public:

		SpriteFrame(unsigned int x, unsigned int y) 
			: m_x(x), m_y(y) {
		}

		unsigned int X() const { return m_x; }
		unsigned int Y() const { return m_y; }


	private:
		unsigned int m_x;
		unsigned int m_y;
	};

	class SpriteMovie {
	public:

		SpriteMovie(std::string x, std::vector<SpriteFrame> y) 
			: m_x(x), m_y(y) {
		}

		std::string X() const { return m_x; }
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

        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
        // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
        m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
        //m_pArialfont =
        // TTF_OpenFont("E:/Projects/C++/Humbug/projects/Humbug/Resources/Fonts/ARIAL.TTF", 24);
        mcol = CColor::White();
        SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( m_Loader.FL_LOADIMG("Intro/LevelABg.png") );

        //SDL_SetColorKey(tmpfsurf, SDL_SRCCOLORKEY, 0xff00ff);
        //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_SRCCOLORKEY, 0xff00ff);
        //SDL_SetAlpha(tmpfsurf, SDL_SRCALPHA, 0);
        //SDL_SetAlpha(m_pMainCanvas->GetSurface(), SDL_SRCALPHA, 128);
        m_pBackground.reset( new CCanvas( tmpfsurf ) );

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
        //text->AddModifier(boost::ref( mtextfloat ));
        text->AddModifier( WavyTextFloat(64) );
        m_pScrollText.reset(text);
 
		// ### Tiles ###



		// ###
		

		CTileSet* tileSet = NULL;
		CTileImageSetup tilesetup;
		tilesetup.TileSetName = LevelNames::LevelAName;
		tilesetup.TileWidth = 32;
		tilesetup.TileHeight = 32;
		tilesetup.TileCountX = 4;
		tilesetup.TileCountY = 1;
		tilesetup.TransparentX = 0;
		tilesetup.TransparentY = 0;
		tilesetup.Sequences = 0;
		tileSet = new CTileSet( m_pMainCanvas, new CTileImage(m_Loader, "data/levels/LevelA/LevelA.png", tilesetup),
			m_pBackground.get(), CRectangle(0, 0, 1024, 768) );

		m_pTileEngine = new CTileEngine( m_pMainCanvas, m_pBackground.get() );
		m_pTileEngine->AddTileSet(tileSet);

		//std::string humbugTilesTil = m_Loader.FL_LOADASSTRING("data/levels/LevelA/HumbugTiles.til");
		//CTileMap *tmap = new CTileMap(m_Loader.FL_LOADASSTRING("data/levels/LevelA/HumbugTiles.til"));
		CTileMap *tmap = new CTileMap(m_Loader.FL_LOADASSTRING("data/levels/LevelA/Map1.map"));
		//FileLoadingInfo& finf = m_Loader.FL_LOAD("data/levels/LevelA/HumbugTiles.bin");
		//tmap->ReadBinary(finf.Data(), finf.Size());
		m_pTileEngine->AddTileMap(tmap);
		(*m_pTileEngine)["Map1"].DrawMap(m_pBackground.get());

		/*CTileEngine& eng = (*m_pTileEngine);
		//(*m_pTileEngine)[LevelNames::LevelAName]->GetTileImage()->ShowTiles( m_pBackground.get() );
		
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
			"lua/sprite1.lua"), "Ticks", "X", "Y" );
		pimpl_->script = s;

        world.FPS = CApplication::FramesCap();
        CRectangle screenRect = m_pMainCanvas->GetDimension();
        world.ScreenX = screenRect.GetW();
        world.ScreenY = screenRect.GetH();

		// Todo maybe an functor to initialize more global stuff 
		(*s->AddStatic(world))("World")
			.def("greet", &greetHopperA)
			.def_readonly("FPS", &World::FPS)
			.def_readonly("ScreenX", &World::ScreenX)
			.def_readonly("ScreenY", &World::ScreenY);



		ScriptType::Script sprInit = shost.generate<int, double, double>( m_Loader.FL_LOADASSTRING(
			"Sprites/male_spritesA.spr"), "Ticks", "X", "Y" );
		//ScriptType::Script sprInit = shost.generate<int, double, double>( m_Loader.FL_LOADASSTRING(
		//	"Sprites/male_sprites.spr"), "Ticks", "X", "Y" );

		TestClass st(12,99);

		(*sprInit->AddStatic(st))("TestClass", "tc")
			.def(luabind::constructor<std::vector<int> >())
			.def(luabind::constructor<int, int>())
			.def("get", &TestClass::get);

		//boost::shared_ptr<shost::LuaScript::register_binder<SpriteFrame >>& bla=
		int xyz = 55;

		typedef shost::LuaVarCapsule<luabind::class_<SpriteFrame>> SprCapsule;
		SprCapsule maleSpriteCap = shost::makeFarm(sprInit,
		(*sprInit->Register<SpriteFrame>())("SpriteFrame")
			.def(luabind::constructor<int, int>())
			.def("X", &SpriteFrame::X)
			.def("Y", &SpriteFrame::Y));

		(*sprInit->Register<SpriteMovie>())("SpriteMovie")
			.def(luabind::constructor<std::string, std::vector<SpriteFrame>>())
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

		luabind::object o3(luabind::globals(sprInit->L())["tcx"]);
		if (o3)
		{
			// is_valid
			// ...

			int luatype = luabind::type(o3);
			if (luabind::type(o3) == LUA_TUSERDATA)
			{
				TestClass otherValue = luabind::object_cast<TestClass>(o3);
				int abc = 4;
				abc++;
			}
		}

		SpriteFrame otherValue2(0,0);
		bool success3 = maleSpriteCap.GetLuaValue("spf", otherValue2);
		SpriteFrame otherValuex = maleSpriteCap.GetLuaValue("spf");
		
		SpriteFrame otherValue3(0,0);
		bool fsuccess = sprInit->GetLuaValue<SpriteFrame>("spf", otherValue3);

		luabind::object o4(luabind::globals(sprInit->L())["spf"]);
		if (o4)
		{
			// is_valid
			// ...

			int luatype = luabind::type(o4);
			if (luabind::type(o4) == LUA_TUSERDATA)
			{
				SpriteFrame otherValue = luabind::object_cast<SpriteFrame>(o4);
				int abc = 4;
				abc++;
			}
		}




		//SpriteMovie otherValue3(0,0);
		//fsuccess = sprInit->GetLuaValue<SpriteMovie>("spMovie", otherValue3);
		SpriteMovie smovie = sprInit->GetLuaValue<SpriteMovie>("spMovie");

		//int *x = new int(666);

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
		//m_pSprEye->SetPos( CPoint( static_cast<int>(spr1X), static_cast<int>(spr1Y) ) );

		m_pSprMgr->OnIdle(ticks);
    }

    /** LevelA, OnDraw:
     *  Detailed description.
     *  @return TODO
     */
    void LevelA::OnDraw(){
        static int coldelta = 0;

        CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
        m_pMainCanvas->Lock();

        m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension() );
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
		m_pMainCanvas->AddUpdateRect(m_pMainCanvas->GetDimension());*/


        m_pSprMgr->OnDraw();

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
        //m_iUpdateTimes++;
    }
  }
}
