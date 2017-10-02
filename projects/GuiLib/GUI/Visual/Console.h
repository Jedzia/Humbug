/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Console.h class.
 * \folder     $(folder)
 * \file       Console.h
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef __HUMBUG_GUI_VISUAL_CCONSOLE_H
#define __HUMBUG_GUI_VISUAL_CCONSOLE_H

#include "../Components/Canvas.h"
#include "../Components/Rectangle.h"
#include "boost/smart_ptr/scoped_ptr.hpp"
#include <string>

typedef struct _TTF_Font TTF_Font;

namespace gui {
  class CEventHandler;

  class CConsole {
public:

  	  typedef boost::function<void(std::string)> ConsoleCommandCallback;

      CConsole(CEventHandler* parent, SDL_Surface *font, gui::components::CCanvas* displayScreen, int lines,
              gui::components::CRectangle rect);
      ~CConsole();

      void Draw(void) const;

      void Toggle(void);

      bool OnEvent(SDL_Event* pEvent);

      void DoSomething(void);

      //friend std::ostream& operator<<(std::ostream& o, const CConsole& r);

private:

	  void commandCalled(std::string s);

	  struct CConsoleImpl;
      boost::scoped_ptr<CConsoleImpl> pimpl_;
      gui::components::CCanvas* m_pScreen;
      gui::components::CRectangle m_crDimensions;
      bool m_bIsVisible;
  };

//std::ostream& operator<<(std::ostream& o, const CConsole& r);
} // namespace gui

#endif // __HUMBUG_GUI_VISUAL_CCONSOLE_H guard
