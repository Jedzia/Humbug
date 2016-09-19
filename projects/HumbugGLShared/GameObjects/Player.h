/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Player.h class.
 * \folder     $(folder)
 * \file       Player.h
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef GAMEOBJECTS_PLAYER_H
#define GAMEOBJECTS_PLAYER_H

#include "GPoint2D.h"
#include "GVector2D.h"
#include "GameObject.h"
#include <string>

namespace gob {
  /** @class Player:
   *  Detailed description.
   *  @param direction TODO
   */
  class Player : public GameObject {
public:

      Player();
      ~Player();

	  gob::GPoint2D GetPosition() const { return m_position; }
	  void SetPosition(gob::GPoint2D val) { m_position = val; }
      virtual void Move(GVector2D direction);

private:

      GPoint2D m_position;
  };
}
#endif // ifndef GAMEOBJECTS_PLAYER_H
