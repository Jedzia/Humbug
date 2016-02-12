/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Player.cpp class.
 * \folder     $(folder)
 * \file       Player.cpp
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
//
#include "Player.h"

//#include <build/cmake/include/debug.h>

namespace gob {
	Player::Player() : GameObject("Player1"){
      dbgOut(__FUNCTION__);
  }

  Player::~Player(void){
      dbgOut(__FUNCTION__);
  }

  void Player::Move( GVector2D direction )
  {
	  m_position = m_position + direction;
  }

}
