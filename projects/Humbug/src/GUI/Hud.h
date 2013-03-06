/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Hud.h class.
 * \folder     $(folder)
 * \file       Hud.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef GUI_HUD_H
#define GUI_HUD_H

#include "GUI/Components/Canvas.h"
#include "GUI/Controls/Control.h"
#include <string>

namespace gui {
  namespace components {
    class CCanvas;
  }
}
class FileLoader;

namespace humbug {
  class HudBackground  {
public:

      // Hud(const FileLoader& loader, CCanvas* pCanvas);
      HudBackground(FileLoader& loader, std::string filename);
      ~HudBackground();

      //void Draw();
      gui::components::CCanvas * GetCanvas();

private:

      gui::components::CCanvas* m_pFooter;
  };

  struct HudImages
  {
      char* Meter;
      char* Lamp;
      char* Switch;
      char* Nothing;
      //int rotz :1;
  };

  class Hud : public gui::controls::CControl {
public:

      // Hud(const FileLoader& loader, CCanvas* pCanvas);
      Hud(const FileLoader& loader, gui::controls::CControl* pParent, HudBackground* bkg, Uint32 id);
      ~Hud();

      //void Draw();
      void OnDraw();

      virtual bool OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight, bool bMiddle);

private:

      void Init(gui::controls::CControl* pParent);

      gui::components::CRectangle InitRect(const FileLoader& loader);

      //canvas used by window
      const FileLoader& m_pLoader;
      //CCanvas* m_pCanvas;
      //CPoint dst;
      HudBackground* m_pBackground;
      // CCanvas* footer;
      gui::components::CImage* footerImage;
      bool oldstate;
      gui::components::CCanvas* tmpcanvas;
      bool flank;
  };
}

#endif // GUI_HUD_H
