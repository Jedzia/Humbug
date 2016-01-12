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
  namespace controls {
      class CLabel;
  }
}
class FileLoader;

namespace humbug {
  class DebugOverlay : public gui::controls::CControl {
public:

      // DebugOverlay(const FileLoader& loader, CCanvas* pCanvas);
      DebugOverlay(FileLoader& loader, gui::controls::CControl* pParent, Uint32 id);
      ~DebugOverlay();

	  void OnDraw() override;
      
      /** Idle update.
      *  Call during the idle method of your display loop.
      *  @param ticks Use this to pass the ticks parameter of the idle loop.
      */
      void IdleSetVars(int ticks);

      /** Create a text label and add it to the overlay.
      *  Creates a new text label with the specified text and adds it to the debug overlay.
      *  @return a unique identifier of the label. This id can be used by functions like SetTextLabelText.
      */
      int AddTextLabel();

      /** Sets the text of a label.
      *  Use this method to set the text of a label, created by AddTextLabel().
      *  @param id The identifikation number of the text label.
      *  @param text The new caption of the label.
      *  @return a unique identifier of the label. This id can be used by functions like SetTextLabelText.
      */
      void SetTextLabelText(int id, const std::string& text);

      bool OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight, bool bMiddle) override;

private:
        
      static int LabelId;
      void Init(gui::controls::CControl* pParent);

      gui::components::CRectangle InitRect(const FileLoader& loader);

      //canvas used by window
      const FileLoader& m_pLoader;
	  TTF_Font* m_pDebugfont;
	  boost::scoped_ptr<gui::components::CText> m_pTextA;
      
      boost::ptr_map<int, gui::controls::CLabel> m_mLabels;
      int m_iLastAutoLabelPosition;

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
