/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Template.cpp class.
 * \folder     $(folder)
 * \file       Template.cpp
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
//
#include "Template.h"

//#include <build/cmake/include/debug.h>

namespace gob {
  Template::Template(){
      dbgOut(__FUNCTION__ << std::endl);
  }

  Template::~Template(void){
      dbgOut(__FUNCTION__ << std::endl);
  }

  /** Template, Language:
   *  Detailed description.
   *  @param x TODO
   * @return TODO
   */
  const char * Template::Language(int x) const {
      return "AsciiDoc";
  }
}
