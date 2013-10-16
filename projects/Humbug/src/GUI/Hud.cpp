/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Hud.cpp class.
 * \folder     $(folder)
 * \file       Hud.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Image.h"
#include "Hud.h"

using namespace gui::components;

namespace humbug {
//#include <build/cmake/include/debug.h>
/*Hud::Hud(const FileLoader& loader, CCanvas* pCanvas) :
    CControl(pCanvas),
    m_pLoader(loader) //, m_pCanvas(pCanvas)
        {
    dbgOut(__FUNCTION__ << std::endl);

        Init();
   }*/
  HudBackground::HudBackground(FileLoader& loader, std::string filename) :
      m_pFooter(NULL){
      dbgOut(__FUNCTION__ << std::endl);

      //m_pFooter = new CCanvas( loader.LoadImg( filename.c_str() ) );
      m_pFooter = new gui::components::CCanvas( SDL_DisplayFormatAlpha( loader.FL_LOADIMG( filename.c_str() ) ) );
  }

  HudBackground::~HudBackground(void){
      dbgOut(__FUNCTION__ << std::endl);
      delete m_pFooter;
  }

  /** HudBackground, GetCanvas:
   *  Detailed description.
   *  @return TODO
   */
  gui::components::CCanvas * HudBackground::GetCanvas() {
      return m_pFooter;
  }

  Hud::Hud(const FileLoader& loader, CControl* pParent, HudBackground* bkg, Uint32 id) :
      CControl(pParent, bkg->GetCanvas()->GetDimension(), id),
      m_pLoader(loader),
      m_pBackground(bkg){
      dbgOut(__FUNCTION__ << std::endl);

      //Init(pParent);
      //FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");
      //footer = new CCanvas( m_pLoader.LoadImg("footer.png") );
      gui::components::CCanvas* footer = bkg->GetCanvas();
      std::cout << "The rect: |" << footer->GetDimension() << "|ends" << std::endl;
      footerImage = new CImage( footer );
      CPoint dst( 0, pParent->GetCanvas()->GetHeight( ) - footer->GetHeight( ) );
      CControl::SetPosition(dst);
      oldstate = !HasMouseHover();

      // BringToFront();
      //SetMouseHover(this);

      tmpcanvas = GetCanvas()->CreateRGBCompatible( NULL, GetWidth(), GetHeight() );
      SDL_SetAlpha(tmpcanvas->GetSurface(), SDL_SRCALPHA, 122);
      footerImage->Put( GetCanvas(), CPoint(0, 0) );
      const CRectangle& ownDimensions = GetCanvas()->GetDimension();
      GetCanvas()->Blit(ownDimensions, *tmpcanvas, ownDimensions);
      CControl::GetMainControl()->GetCanvas()->AddUpdateRect( CRectangle(0, 0, 1024, 768) );
      //Invalidate();
  }

  Hud::~Hud(void){
      delete footerImage;
      delete m_pBackground;
      delete tmpcanvas;
      dbgOut(__FUNCTION__ << std::endl);
  }

  /** Hud, Init:
   *  Detailed description.
   *  @param pParent TODO
   * @return TODO
   */
  void Hud::Init(CControl* pParent){}

  /** Hud, InitRect:
   *  Detailed description.
   *  @param loader TODO
   * @return TODO
   */
  CRectangle Hud::InitRect(const FileLoader& loader){
      /*footer = new CCanvas( m_pLoader.LoadImg("footer.png") );
         std::cout << "The rect: |" << footer->GetDimension() << "|ends" << std::endl;
         //CControl::set
         footerImage = new CImage( footer );
         dst = CPoint( 0, GetCanvas()->GetHeight( ) - footer->GetHeight( ) );*/
      return CRectangle(0, 0, 1024, 354);
  }

  /** Hud, OnDraw:
   *  Detailed description.
   *  @return TODO
   */
  void Hud::OnDraw(){
      /*
         CRectangle globalPosition( GetLeft(), GetTop(), GetWidth(), GetHeight() );
         flank = true;
         bool checkSwitch = HasMouseHover() ^ flank;

         //footerImage->Put( GetCanvas(), dst );
         if( checkSwitch &&  oldstate == false) {
          //clear to light gray
          CRectangle& ownDimensions = GetCanvas()->GetDimension();
          GetCanvas()->Blit(ownDimensions, *tmpcanvas, ownDimensions);

          //GetCanvas()->FillRect( CRectangle( 0, 0, GetWidth(), GetHeight() ), CColor(155, 255,
             155)
          // );
          CControl::GetMainControl()->GetCanvas()->AddUpdateRect(globalPosition);
          Invalidate();
          //m_ptIsDirty = true;
         }
         else if(!checkSwitch &&  oldstate == true)   {
          //SDL_SetAlpha(footerImage->GetCanvas()->GetSurface(), SDL_SRCALPHA, 44);
          footerImage->Put( GetCanvas(), CPoint(0, 0) );

          //GetParent()->Update();
          int dreck = this->GetWidth();

          //CControl::GetMainControl()->GetCanvas()->AddUpdateRect(CRectangle(0,0,1024,768));
          CControl::GetMainControl()->GetCanvas()->AddUpdateRect(globalPosition);
          Invalidate();
          //m_ptIsDirty = true;
         }

         static bool xset = false;

         if(!xset) {
          xset = true;
         }

         if(m_ptIsDirty) {
          int abc = 123;

          //footerImage->Put( GetCanvas(), CPoint(0, 0) );
          //CControl::GetMainControl()->GetCanvas()->AddUpdateRect(CRectangle(0,0,1024,768));
          //m_ptIsDirty = false;
         }

         oldstate = checkSwitch;*/
      CControl::OnDraw();
  } // OnDraw

  /** Hud, OnMouseMove:
   *  Detailed description.
   *  @param x TODO
   * @param y TODO
   * @param relx TODO
   * @param rely TODO
   * @param bLeft TODO
   * @param bRight TODO
   * @param bMiddle TODO
   * @return TODO
   */
  bool Hud::OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight,
          bool bMiddle){
      bool res = CControl::OnMouseMove( x, y, relx, rely, bLeft, bRight, bMiddle);

      //if(GetMouseHover()==NULL) SetMouseHover(this);
      /*if(HasMouseHover())
          {
                  //clear to light gray
                  GetCanvas()->FillRect(CRectangle(0,0,GetWidth(),GetHeight()),CColor(155,255,155));
         }*/
      return res;
  }
}
