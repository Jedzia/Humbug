/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the LuaScreen.cpp class.
 * \folder     $(folder)
 * \file       LuaScreen.cpp
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#include "LuaScreen.h"
#include "../stdafx.h"

//#include <build/cmake/include/debug.h>
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
//
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Components/Text.h"
#include "GUI/Components/TextScroller.h"
#include "GUI/Data/ColorData.h"
#include "GUI/Sprite/Sprite.h"
#include "GUI/Sprite/SpriteManager.h"
#include "GUI/Visual/EventHandler.h"
#include "WavyTextFloat.h"
#include "HumbugShared/ScriptHost/ScriptHost.h"
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


using namespace gui::components;
using namespace gui;

namespace humbug {
  namespace screens {
    struct LuaScreen::LuaScreenImpl {
        //prv::EyeMover eyemover;
        //prv::WormMover wormmover;
        int x;
    };

    LuaScreen::LuaScreen( FileLoader& loader, CCanvas* background) :
        pimpl_(new LuaScreen::LuaScreenImpl ),
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

    LuaScreen::~LuaScreen(void){
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

/*GroupId LuaScreen::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/

    namespace hspriv {
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
           * @param frameNumber TODO
           * @return TODO
           */
          void operator()(CSprite* sprite, int frameNumber) {
              double ss = std::sin(static_cast<double>(h_) / 3.14159 / 4.0);
              int ssin = static_cast<int>(ss * 100);

              //sprite->SetPos(CPoint(100 + ((frameNumber % 128) * 6), 460 + h_ + deltaY_ + ssin));
              sprite->SetPos( CPoint(130 + ssin, deltaY_) );
              sprite->SprOffset(frameNumber % sproffs);

              if (h_ >= 180) {
                  toggle_ = false;
              }
              else if (h_ <= -180)   {
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

    /** LuaScreen, OnInit:
     *  Detailed description.
     *  @param argc TODO
     * @param argv TODO
     * @return TODO
     */
    bool LuaScreen::OnInit( int argc, char* argv[] ){
        // Master()->GetMainCanvas();
        CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
        // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
        m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
        //m_pArialfont =
        // TTF_OpenFont("E:/Projects/C++/Humbug/projects/Humbug/Resources/Fonts/ARIAL.TTF", 24);
        mcol = CColor::White();
        SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( m_Loader.FL_LOADIMG("Intro/LuaScreenBg.png") );

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
        CSprite* m_pSprEye = new CSprite( m_Loader, "Sprites/eye.png", m_pMainCanvas,
                CRectangle(0, 0, 64, 64), CPoint(64, 0) );
        m_pSprMgr->AddSprite( m_pSprEye, hspriv::EyeMover(160) );
        //m_pSprMgr->AddSprite(m_pSprEye, boost::ref( pimpl_->eyemover ) );
        //m_pSprMgr->AddSprite(m_pSprEye);
        CSprite* m_pSprWormler = new CSprite( m_Loader, "Sprites/wormtiles.png", m_pMainCanvas,
                CRectangle(0, 0, 256, 64), CPoint(0, 64) );
        m_pSprWormler->SetColorAndAlpha(0xff00ff, 128);
        m_pSprMgr->AddSprite( m_pSprWormler, hspriv::EyeMover(260, 40) );


		shost::ScriptHost shost;
		//shost.RunScript2(m_Loader.FL_LOADASSTRING("lua/hello.lua"));
		shost.RunScript(m_Loader.FL_LOADASSTRING("lua/funcret.lua"));

        return Screen::OnInit(argc, argv);
    } // OnInit


    /** LuaScreen, OnIdle:
     *  Detailed description.
     *  @param frameNumber TODO
     * @return TODO
     */
    void LuaScreen::OnIdle(int frameNumber){
        //m_pScroller->Scroll(4);
        m_pSprMgr->OnIdle(frameNumber);
    }

    /** LuaScreen, OnDraw:
     *  Detailed description.
     *  @return TODO
     */
    void LuaScreen::OnDraw(){
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

    /** LuaScreen, OnUpdate:
     *  Detailed description.
     *  @return TODO
     */
    void LuaScreen::OnUpdate(){
        Screen::OnUpdate();
        x += 1 + (rand() << 21);
        mcol.SetR( rand() );
        mcol.SetG( rand() );
        mcol.SetB( rand() );
        //m_iUpdateTimes++;
    }
  }
}
