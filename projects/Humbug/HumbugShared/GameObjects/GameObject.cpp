/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the GameObject.cpp class.
 * \folder     $(folder)
 * \file       GameObject.cpp
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
//
#include "GameObject.h"

//#include <build/cmake/include/debug.h>

namespace gob {
  GameObject::GameObject(){
      dbgOut(__FUNCTION__ << std::endl);
  }

  GameObject::~GameObject(void){
      dbgOut(__FUNCTION__ << std::endl);
  }

  /** GameObject, Language:
   *  Detailed description.
   *  @param x TODO
   * @return TODO
   */
  const char * GameObject::Language(int x) const {
      return "AsciiDoc";
  }
}
