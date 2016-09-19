/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the PlayerKeys.cpp class.
 * \folder     $(folder)
 * \file       PlayerKeys.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"

//
#include "PlayerKeys.h"

//#include <build/cmake/include/debug.h>
namespace humbug {
  PlayerKeys::PlayerKeys(int x, int y) :
      upup(false),
      downup(false),
      leftup(false),
      rightup(false),
      charx(x),
      chary(y),
      charxvel(0),
      charyvel(0),
      done(0){
      dbgOut(__FUNCTION__);
  }

  PlayerKeys::~PlayerKeys(void){
      dbgOut(__FUNCTION__);
  }

  /** PlayerKeys, HookKeyDown:
   *  Detailed description.
   *  @param sym TODO
   * @return TODO
   */
  void PlayerKeys::HookKeyDown(SDL_Keycode sym){
      switch(sym) {
      case SDLK_LEFT:
          leftup = false;
          charxvel = -1;
          break;
      case SDLK_RIGHT:
          rightup = false;
          charxvel = 1;
          break;
      case SDLK_UP:
          upup = false;
          charyvel = -1;
          break;
      case SDLK_DOWN:
          downup = false;
          charyvel = 1;
          break;
      default:
          done = 1;
          break;
      } // switch
  } // HookKeyDown

  /** PlayerKeys, HookKeyUp:
   *  Detailed description.
   *  @param sym TODO
   * @return TODO
   */
  void PlayerKeys::HookKeyUp(SDL_Keycode sym){
      switch(sym) {
      case SDLK_LEFT:
          leftup = true;
          charxvel = 0;
          break;
      case SDLK_RIGHT:
          rightup = true;
          charxvel = 0;
          break;
      case SDLK_UP:
          upup = true;
          charyvel = 0;
          break;
      case SDLK_DOWN:
          downup = true;
          charyvel = 0;
          break;
      default:
          break;
      } // switch
  } // HookKeyUp

  /** PlayerKeys, HookEventloop:
   *  Detailed description.
   *  @param keyevent TODO
   * @return TODO
   */
  void PlayerKeys::HookEventloop( SDL_Event* keyevent ){
      upup = true;         //Initialize all the key booleans to true.
      downup = true;
      leftup = true;
      rightup = true;

      if (keyevent->type == SDL_KEYDOWN) {
          HookKeyDown(keyevent->key.keysym.sym);
      }

      if (keyevent->type == SDL_KEYUP) {
          HookKeyUp(keyevent->key.keysym.sym);
      }

      HookIdle();
  } // HookEventloop

  /** PlayerKeys, HookIdle:
   *  Detailed description.
   *  @return TODO
   */
  void PlayerKeys::HookIdle(){
      //These continue to accelerate the character if the user is holding
      // down a button.
      if (!upup) {        charyvel -= 1;    }

      if (!downup) {
          charyvel += 1;
      }

      if (!rightup) {
          charxvel += 1;
      }

      if (!leftup) {
          charxvel -= 1;
      }

      charx += charxvel;
      chary += charyvel;

      if (charx < 0) {
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
      }
  } // HookIdle

  /** $(fclass), operator <<:
   *  Detailed description.
   *  @param o TODO
   * @param r TODO
   * @return TODO
   */
  std::ostream& operator<<(std::ostream& o, const PlayerKeys& r) {
      return o << "PlayerKeys[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                      << ", W=" << r.GetW() << ", H=" << r.GetH()
                                      <<*/
             " ]";
  }
}
