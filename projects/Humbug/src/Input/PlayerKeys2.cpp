/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the PlayerKeys2.cpp class.
 * \folder     $(folder)
 * \file       PlayerKeys2.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"

//
#include "PlayerKeys2.h"

using namespace gob;

//#include <build/cmake/include/debug.h>
namespace humbug {
  PlayerKeys2::PlayerKeys2(float x, float y) :
      m_position(x, y), m_speed(0), m_lastTick(0){
      dbgOut(__FUNCTION__);
  }

  PlayerKeys2::~PlayerKeys2(void){
      dbgOut(__FUNCTION__);
  }

  /** PlayerKeys2, HookEventloop:
   *  Detailed description.
   *  @param keyevent TODO
   * @return TODO
   */
  void PlayerKeys2::HookEventloop( SDL_Event* keyevent ){
      float mul = 0;

      switch(keyevent->type) {
      case SDL_KEYDOWN:
          mul = 1;
          break;
      case SDL_KEYUP:
          mul = -1;
          break;
      default:
          return;
      }     // switch

      switch(keyevent->key.keysym.sym) {
	  case SDLK_LEFT:
	  case SDLK_a:
          m_direction = m_direction + GVector2D::Left() * mul;
          break;
      case SDLK_RIGHT:
	  case SDLK_d:
		  m_direction = m_direction + GVector2D::Right() * mul;
          break;
      case SDLK_UP:
	  case SDLK_w:
		  m_direction = m_direction + GVector2D::Down() * mul;
          break;
      case SDLK_DOWN:
	  case SDLK_s:
		  m_direction = m_direction + GVector2D::Up() * mul;
          break;
      default:
          break;
      }     // switch

      //HookIdle();
  } // HookEventloop

  /** PlayerKeys2, HookIdle:
   *  Here we update the player movement.
   *  @return TODO
   */
  void PlayerKeys2::HookIdle(int ticks, float speed){
      //These continue to accelerate the character if the user is holding
      // down a button.
	  float tickDelta = ticks - m_lastTick;
	  m_curspeed += ( tickDelta / 50 ) * speed;
	  if (m_direction == GVector2D::Zero())
	  {
		  m_curspeed = 0;
	  }
	  if (m_curspeed > speed)
	  {
		  m_curspeed = speed;
	  }

      m_position = m_position + ( m_direction * m_curspeed );

      /*if (charx < 0) {
          charx = 0;
         }
         else if (charx > 1024) {
          charx = 1024;
         }

         if (chary < 0) {
          chary = 0;
         }
         else if (chary > 768) {
          chary = 768;
         }*/
	  m_lastTick = ticks;
  } // HookIdle

  /** $(fclass), operator <<:
   *  Detailed description.
   *  @param o TODO
   * @param r TODO
   * @return TODO
   */
  std::ostream& operator<<(std::ostream& o, const PlayerKeys2& r) {
      return o << "PlayerKeys2[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                       << ", W=" << r.GetW() << ", H=" << r.GetH()
                                       <<*/
             " ]";
  }
}
