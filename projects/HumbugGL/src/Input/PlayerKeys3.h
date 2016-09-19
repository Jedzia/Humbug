/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the PlayerKeys3.h class.
 * \folder     $(folder)
 * \file       PlayerKeys3.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef PROJECT_PlayerKeys3_H
#define PROJECT_PlayerKeys3_H
#include "GUI/Components/Point.h"
#include "HumbugGLShared/GameObjects/GPoint2D.h"
#include <GuiLib/Input/KeyboardHandler.h>

namespace humbug {

// see http://content.gpwiki.org/index.php/SDL:Tutorials:Practical_Keyboard_Input
  class PlayerKeys3 {
public:

    PlayerKeys3(float x = 0, float y = 0, bool accumulate = true, bool stopOnRelease = false, float maxSpeed = 0.0f);
      ~PlayerKeys3();
      void HookEventloop(SDL_Event* pEvent);

      /** PlayerKeys3, HookIdle:
       *  Here we update the player movement.
       *  @return TODO
       */
      void HookIdle(int ticks, float speed);

      /** $(class), Char:
       *  Detailed description.
       *  @return TODO
       */
      gui::components::CPoint Char() const { return gui::components::CPoint( static_cast<int>( m_position.x),
                                                     static_cast<int>(m_position.y) ); }

      /** $(class), CharX:
       *  Detailed description.
       *  @return TODO
       */
      float CharX() const { return m_position.x; }

      /** $(class), CharX:
       *  Detailed description.
       *  @param val TODO
       */
      void CharX(float val) { m_position.x = val; }

      /** $(class), CharY:
       *  Detailed description.
       *  @return TODO
       */
      float CharY() const { return m_position.y; }

      /** $(class), CharY:
       *  Detailed description.
       *  @param val TODO
       */
      void CharY(float val) { m_position.y = val; }

      /** PlayerKeys3, Reset:
      *  Stop movement and return to the initial position set by the constructor.
      */
      void Reset();

      /** PlayerKeys3, Stop:
      *  Immediately stops all movement.
      */
      void Stop();

      friend std::ostream& operator<<(std::ostream& o, const PlayerKeys3& r);
  private:

      gui::KeyboardHandler m_KeyboardHandler;
      gob::GVector2D m_direction;
      gob::GPoint2D m_position;
      gob::GPoint2D m_InitialPosition;
      float m_fSpeed;
	  int m_iLastTick;
      float m_fCurrentSpeed;
      float m_fMaxSpeed;
      bool m_bStopOnRelease;
      bool m_bAccumulate;
  };

  std::ostream& operator<<(std::ostream& o, const PlayerKeys3& r);
}

#endif // PROJECT_PlayerKeys3_H guard
