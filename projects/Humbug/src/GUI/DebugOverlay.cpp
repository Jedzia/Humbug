/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the DebugOverlay.cpp class.
 * \folder     $(folder)
 * \file       DebugOverlay.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Image.h"
#include "GUI/Components/Text.h"

#include "DebugOverlay.h"

using namespace gui::components;

namespace humbug {
//#include <build/cmake/include/debug.h>

  DebugOverlay::DebugOverlay(FileLoader& m_Loader, CControl* pParent, Uint32 id) :
      CControl(pParent, CRectangle(0,0,200,100), id),
      m_pLoader(m_Loader){
      dbgOut(__FUNCTION__);

      //Init(pParent);
      //FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");
      //footer = new CCanvas( m_pLoader.LoadImg("footer.png") );

      // BringToFront();
      //SetMouseHover(this);

	  m_pDebugfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 12);

      tmpcanvas = GetCanvas()->CreateRGBCompatible( NULL, GetWidth(), GetHeight() );
      SDL_SetAlpha(tmpcanvas->GetSurface(), SDL_SRCALPHA, 122);
      
	  //footerImage->Put( GetCanvas(), CPoint(0, 0) );
      //const CRectangle& ownDimensions = GetCanvas()->GetDimension();
      //GetCanvas()->Blit(ownDimensions, *tmpcanvas, ownDimensions);
	  //CControl::GetMainControl()->GetCanvas()->AddUpdateRect( CRectangle(0, 0, 1024, 768) );
	  pParent->GetCanvas()->AddUpdateRect( CRectangle(0, 0, 1024, 768) );
      //Invalidate();
  }

  DebugOverlay::~DebugOverlay(void){
      //delete footerImage;
      delete tmpcanvas;
      dbgOut(__FUNCTION__);
  }

  /** DebugOverlay, Init:
   *  Detailed description.
   *  @param pParent TODO
   * @return TODO
   */
  void DebugOverlay::Init(CControl* pParent){}

  /** DebugOverlay, InitRect:
   *  Detailed description.
   *  @param loader TODO
   * @return TODO
   */
  CRectangle DebugOverlay::InitRect(const FileLoader& loader){
      /*footer = new CCanvas( m_pLoader.LoadImg("footer.png") );
         LOGSTREAM << "The rect: |" << footer->GetDimension() << "|ends" << std::endl;
         //CControl::set
         footerImage = new CImage( footer );
         dst = CPoint( 0, GetCanvas()->GetHeight( ) - footer->GetHeight( ) );*/
      return CRectangle(0, 0, 1024, 354);
  }

  /** DebugOverlay, OnDraw:
   *  Detailed description.
   *  @return TODO
   */
  void DebugOverlay::OnDraw(){

	  CCanvas *pCanvas = GetParent()->GetCanvas();
	  CRectangle globalPosition( GetLeft(), GetTop(), GetWidth(), GetHeight() );
	  CRectangle& ownDimensions = GetCanvas()->GetDimension();


	  CColor m_colText = CColor::White();
	  std::ostringstream outstring;
	  outstring << "Ticks: " << m_ticks;

	  CText* text = new CText(m_pDebugfont, outstring.str(), m_colText);

	  CRectangle txtDims = text->GetCanvas()->GetDimension();
	  CRectangle dstDims = globalPosition;
	  text->Put(pCanvas, dstDims, txtDims );

	  pCanvas->AddUpdateRect(dstDims);

	  //CText prText()
	  int x = 1;
	  x++;
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

  /** DebugOverlay, OnMouseMove:
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
  bool DebugOverlay::OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight,
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

  void DebugOverlay::IdleSetVars( int ticks )
  {
	  m_ticks = ticks;
  }

}
