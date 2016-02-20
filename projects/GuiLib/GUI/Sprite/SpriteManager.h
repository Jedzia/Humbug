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
  struct CSpriteModifierData
  {
      /** contains the source rectangle. */
      components::CRectangle* srcRect;
      /** contains the destination rectangle. */
      components::CRectangle*  dstRect;
      bool isHandled;
      /** If set to true the TextAnimator will be removed and deleted from the execution queue.
      The TextAnimator::nextAnimator next animator is added and called on the next run of the queue. */
      bool markedForDeletion;
      int state;
      bool isHit;

      CSpriteModifierData(components::CRectangle* srcRect, components::CRectangle* dstRect)
          : srcRect(srcRect), dstRect(dstRect), isHandled(false), markedForDeletion(false), state(1), isHit(false)
      {

      };
  };

  class CSpriteManager {
public:
    typedef boost::function<void(CSprite *, int, CSpriteModifierData& mdata)> CSpriteModifierFunc;
    typedef boost::function<void(CSprite *, CSpriteModifierData& mdata)> CSpriteRenderFunc;

      CSpriteManager(/*SDL_Surface* screen*/);
      ~CSpriteManager();
      int AddSprite(CSprite* sprite, const CSpriteModifierFunc& updfunc = NULL);
      void AddSpriteDraw(int id, const components::CPoint& position, const CSpriteModifierFunc& updfunc, const CSpriteRenderFunc& renderfunc = NULL);

      void OnDraw();

      void OnIdle(int ticks);

      friend std::ostream& operator<<(std::ostream& o, const CSpriteManager& r);
      void Render();
  private:

      struct CSpriteManagerImpl;
      boost::scoped_ptr<CSpriteManagerImpl> pimpl_;
      //typedef boost::ptr_vector<CSpriteHook> SprStorage;
      //SprStorage m_pvSprites;
  };

  std::ostream& operator<<(std::ostream& o, const CSpriteManager& r);
}
#endif // HUMBUG_GUI_SPRITE_SPRITEMANAGER_H guard
