/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SpriteManager.h class.
 * \folder     $(folder)
 * \file       SpriteManager.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_GUI_SPRITE_SPRITEMANAGER_H
#define HUMBUG_GUI_SPRITE_SPRITEMANAGER_H

//
#include "Sprite.h"
#include <boost/ptr_container/ptr_vector.hpp>

//
namespace gui {
  //
  class CSpriteHook;
  class CSpriteManager {
public:

      CSpriteManager(/*SDL_Surface* screen*/);
      ~CSpriteManager();
      void AddSprite(gui::CSprite* sprite, const boost::function<void(gui::CSprite *,
                                                                      int)>& updfunc = NULL);

      void OnDraw();

      void OnIdle(int ticks);

      friend std::ostream& operator<<(std::ostream& o, const CSpriteManager& r);

private:

      typedef boost::ptr_vector<CSpriteHook> SprStorage;
      SprStorage m_pvSprites;
  };

  std::ostream& operator<<(std::ostream& o, const CSpriteManager& r);
}
#endif // HUMBUG_GUI_SPRITE_SPRITEMANAGER_H guard
