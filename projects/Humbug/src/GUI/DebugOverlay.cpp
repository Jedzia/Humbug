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
#include <GuiLib/GUI/Controls/Label.h>

using namespace gui::components;
using namespace gui::controls;

// Todo: this can be moved to GuiLib. (arial font loading, etc, should be parameterizable)
namespace humbug {
//#include <build/cmake/include/debug.h>

 int DebugOverlay::LabelId = 6000;

 DebugOverlay::DebugOverlay(FileLoader& m_Loader, CControl* pParent, Uint32 id, const std::string& name) :
     CControl(pParent, CRectangle(0, 0, 200, 100), id), m_iLastAutoLabelPosition(16), m_sName(name),
      m_pLoader(m_Loader){
      dbgOut(__FUNCTION__);

      //Init(pParent);
      //FileLoader fl("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/base_data");
      //footer = new CCanvas( m_pLoader.LoadImg("footer.png") );

      // BringToFront();
      //SetMouseHover(this);

	  m_pDebugfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 12);

      m_pTmpCanvas = GetCanvas()->CreateRGBCompatible( NULL, CControl::GetWidth(), CControl::GetHeight() );
      SDL_SetSurfaceAlphaMod(m_pTmpCanvas->GetSurface(), 122);
      
	  //m_pFooterImage->Put( GetCanvas(), CPoint(0, 0) );
      //const CRectangle& ownDimensions = GetCanvas()->GetDimension();
      //GetCanvas()->Blit(ownDimensions, *m_pTmpCanvas, ownDimensions);
	  //CControl::GetMainControl()->GetCanvas()->AddUpdateRect( CRectangle(0, 0, 1024, 768) );
	  //pParent->GetCanvas()->AddUpdateRect( CRectangle(0, 0, 1024, 768) );
      //Invalidate();
  }

  DebugOverlay::~DebugOverlay(void){
      //delete m_pFooterImage;
      delete m_pTmpCanvas;
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
         m_pFooterImage = new CImage( footer );
         dst = CPoint( 0, GetCanvas()->GetHeight( ) - footer->GetHeight( ) );*/
      return CRectangle(0, 0, 1024, 354);
  }

  /** DebugOverlay, OnDraw:
   *  Detailed description.
   *  @return TODO
   */
  void DebugOverlay::OnDraw(){
      /*Child
      std::list<CControl*>::iterator iter;
      for (iter = m_lstChildren.begin(); iter != m_lstChildren.end(); iter++)
      {
          //grab item from list
          CControl* pChild = (*iter);
          //draw
          pChild->Draw();
      }*/

	  CCanvas *pCanvas = GetCanvas();
	  CRectangle globalPosition( GetLeft(), GetTop(), GetWidth(), GetHeight() );
	  CRectangle ownDimensions = GetCanvas()->GetDimension();


	  CColor m_colText = CColor::White();
	  CColor m_colBack = CColor::Black();
	  std::ostringstream outstring;
      outstring << "[" << m_sName << "] FPS: " << gui::CApplication::ShownFrames() << ", Ticks: " << m_ticks;

	  CText text(m_pDebugfont, outstring.str(), m_colText);

	  CRectangle txtDims = text.GetCanvas()->GetDimension();
	  CRectangle dstDims = globalPosition;
	  pCanvas->RenderFillRect(txtDims, &m_colBack);
	  text.RenderPut(pCanvas, dstDims, txtDims );

	  pCanvas->AddUpdateRect(dstDims);

	  //CControl::OnDraw();
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

    int DebugOverlay::AddTextLabel()
    {
        if (!CLabel::GetLabelFont())
        {
            CLabel::SetLabelFont(m_pDebugfont);
        }

        int id = LabelId;
        LabelId++;

        std::ostringstream labelText;
        labelText << "AddTextLabel " << id << "";

        CLabel* label1 = new CLabel(this, CRectangle(0, 0, -1, -1), id, labelText.str(), true, CColor::Black(), CColor::White());
        m_mLabels.insert(id, label1);
        
        Uint16 height = label1->GetHeight();
        label1->SetPosition(CPoint(100, m_iLastAutoLabelPosition));
        m_iLastAutoLabelPosition += height;

        this->AddChild(label1);

        return id;
    }

    void DebugOverlay::SetTextLabelText(int id, const std::string& text)
    {
        //CLabel& label = m_mLabels[id];
        CLabel& label = m_mLabels.at(id);
        label.SetCaption(text);
    }
}
