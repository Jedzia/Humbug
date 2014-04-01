/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the DebugOverlay.h class.
 * \folder     $(folder)
 * \file       DebugOverlay.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef GUI_DebugOverlay_H
#define GUI_DebugOverlay_H

#include "GUI/Components/Canvas.h"
#include "GUI/Controls/Control.h"
#include <string>
namespace gui {
  namespace components {
	  class CCanvas;
	  class CImage;
	  class CText;
  }
}
class FileLoader;

namespace humbug {


  class DebugOverlay : public gui::controls::CControl {
public:

      // DebugOverlay(const FileLoader& loader, CCanvas* pCanvas);
      DebugOverlay(FileLoader& loader, gui::controls::CControl* pParent, Uint32 id);
      ~DebugOverlay();

      //void Draw();
	  void OnDraw();
	  void IdleSetVars(int ticks);

      virtual bool OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight, bool bMiddle);

private:

      void Init(gui::controls::CControl* pParent);

      gui::components::CRectangle InitRect(const FileLoader& loader);

      //canvas used by window
      const FileLoader& m_pLoader;
	  TTF_Font* m_pDebugfont;
	  boost::scoped_ptr<gui::components::CText> m_pTextA;

      //CCanvas* m_pCanvas;
      //CPoint dst;
      //DebugOverlayBackground* m_pBackground;
      // CCanvas* footer;
      gui::components::CImage* footerImage;
      bool oldstate;
      gui::components::CCanvas* tmpcanvas;
      bool flank;
	  int m_ticks;
  };
}

#endif // GUI_DebugOverlay_H
