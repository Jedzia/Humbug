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
      m_position(x,y){
      dbgOut(__FUNCTION__);
  }

  PlayerKeys2::~PlayerKeys2(void){
      dbgOut(__FUNCTION__);
  }

  /** PlayerKeys2, HookKeyDown:
   *  Detailed description.
   *  @param sym TODO
   * @return TODO
   */
  void PlayerKeys2::HookKeyDown(SDLKey sym){
      switch(sym) {
      case SDLK_LEFT:
		  m_direction = m_direction + GVector2D::Left();
          break;
      case SDLK_RIGHT:
		  m_direction = m_direction + GVector2D::Right();
		  break;
      case SDLK_UP:
		  m_direction = m_direction + GVector2D::Up();
		  break;
      case SDLK_DOWN:
		  m_direction = m_direction + GVector2D::Down();
		  break;
      default:
          break;
      } // switch
  } // HookKeyDown

  /** PlayerKeys2, HookKeyUp:
   *  Detailed description.
   *  @param sym TODO
   * @return TODO
   */
  void PlayerKeys2::HookKeyUp( SDLKey sym ){
      switch(sym) {
      case SDLK_LEFT:
		  m_direction = m_direction - GVector2D::Left();
		  break;
      case SDLK_RIGHT:
		  m_direction = m_direction - GVector2D::Right();
		  break;
      case SDLK_UP:
		  m_direction = m_direction - GVector2D::Up();
		  break;
      case SDLK_DOWN:
		  m_direction = m_direction - GVector2D::Down();
		  break;
      default:
          break;
      } // switch
  } // HookKeyUp

  /** PlayerKeys2, HookEventloop:
   *  Detailed description.
   *  @param keyevent TODO
   * @return TODO
   */
  void PlayerKeys2::HookEventloop( SDL_Event* keyevent ){

      if (keyevent->type == SDL_KEYDOWN) {
          HookKeyDown(keyevent->key.keysym.sym);
      }

      if (keyevent->type == SDL_KEYUP) {
          HookKeyUp(keyevent->key.keysym.sym);
      }

      //HookIdle();
  } // HookEventloop

  /** PlayerKeys2, HookIdle:
   *  Here we update the player movement.
   *  @return TODO
   */
  void PlayerKeys2::HookIdle(float speed){
      //These continue to accelerate the character if the user is holding
      // down a button.
	  m_position = m_position + m_direction;

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
