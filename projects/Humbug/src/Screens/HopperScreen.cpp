/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the HopperScreen.cpp class.
 * \folder     $(folder)
 * \file       HopperScreen.cpp
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
#include "HopperScreen.h"

//#include <build/cmake/include/debug.h>
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Components/Text.h"
#include "GUI/Components/TextScroller.h"
#include "GUI/Data/ColorData.h"
#include "GUI/Sprite/Sprite.h"
#include "GUI/Sprite/SpriteManager.h"
#include "GUI/Visual/EventHandler.h"
#include "HumbugShared/ScriptHost/ScriptHost.h"
#include "WavyTextFloat.h"
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <cstdlib>
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

namespace humbug {
  namespace screens {
    struct HopperScreen::HopperScreenImpl {
        //prv::EyeMover eyemover;
        //prv::WormMover wormmover;
        int x;
        //shost::LuaScript<int, int, int> *script;
        long allocReqNum;
        boost::shared_ptr<shost::LuaScript<int, double, double >> script;
    };

    HopperScreen::HopperScreen( FileLoader& loader, CCanvas* background) :
        pimpl_(new HopperScreen::HopperScreenImpl ),
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

    HopperScreen::~HopperScreen(void){
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

/*GroupId HopperScreen::GetGroupID()
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

	void greetHopper(){
		std::cout << "hello world from HopperScreen!\n";
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

	// checked type with success return value.
	template<typename ObjType>
	bool GetLuaValue(lua_State *L, const char * varName, ObjType& value)  
	{
		bool success = false;
		luabind::object o4(luabind::globals(L)[varName]);
		if (o4)
		{
			// is_valid

			int luatype = luabind::type(o4);
			if (luabind::type(o4) == LUA_TUSERDATA)
			{
				success = true;
				value = luabind::object_cast<ObjType>(o4);
			}
		}
		// or throw ?

		return success;
	};


    /** HopperScreen, OnInit:
     *  Detailed description.
     *  @param argc TODO
     * @param argv TODO
     * @return TODO
     */
    bool HopperScreen::OnInit( int argc, char* argv[] ){
        // Master()->GetMainCanvas();
        CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
        // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
        m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
        //m_pArialfont =
        // TTF_OpenFont("E:/Projects/C++/Humbug/projects/Humbug/Resources/Fonts/ARIAL.TTF", 24);
        mcol = CColor::White();
        SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( m_Loader.FL_LOADIMG("Intro/HopperScreenBg.png") );

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

        // ### Sprites ###
        m_pSprEye = new CSprite( m_Loader, "Sprites/male_sprites.png", m_pMainCanvas,
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
			.def("greet", &greetHopper)
			.def_readonly("FPS", &World::FPS)
			.def_readonly("ScreenX", &World::ScreenX)
			.def_readonly("ScreenY", &World::ScreenY);



		ScriptType::Script sprInit = shost.generate<int, double, double>( m_Loader.FL_LOADASSTRING(
			"lua/male_sprites.spr"), "Ticks", "X", "Y" );
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

		SpriteFrame otherValue = maleSpriteCap.GetLuaValue("spf");
		
		SpriteFrame otherValue2(0,0);
		bool fsuccess = sprInit->GetLuaValue<SpriteFrame>("spf", otherValue2);

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


        return Screen::OnInit(argc, argv);
    } // OnInit

    /** HopperScreen, OnIdle:
     *  Detailed description.
     *  @param ticks TODO
     * @return TODO
     */
    void HopperScreen::OnIdle(int ticks){
        //m_pScroller->Scroll(4);
        pimpl_->script->run_script(ticks);
        double spr1X = pimpl_->script->GetData1();
        double spr1Y = pimpl_->script->GetData2();
		//m_pSprEye->SetPos( CPoint( static_cast<int>(spr1X), static_cast<int>(spr1Y) ) );

		m_pSprMgr->OnIdle(ticks);
    }

    /** HopperScreen, OnDraw:
     *  Detailed description.
     *  @return TODO
     */
    void HopperScreen::OnDraw(){
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

        m_pSprMgr->OnDraw();

        m_pMainCanvas->Unlock();
    } // OnDraw

    /** HopperScreen, OnUpdate:
     *  Detailed description.
     *  @return TODO
     */
    void HopperScreen::OnUpdate(){
        Screen::OnUpdate();
        x += 1 + (rand() << 21);
        mcol.SetR( rand() );
        mcol.SetG( rand() );
        mcol.SetB( rand() );
        //m_iUpdateTimes++;
    }
  }
}
