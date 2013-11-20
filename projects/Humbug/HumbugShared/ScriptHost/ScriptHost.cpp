/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ScriptHost.cpp class.
 * \folder     $(folder)
 * \file       ScriptHost.cpp
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
//
#include "ScriptHost.h"

//#include <build/cmake/include/debug.h>

namespace gob {
  ScriptHost::ScriptHost(){
      dbgOut(__FUNCTION__ << std::endl);
  }

  ScriptHost::~ScriptHost(void){
      dbgOut(__FUNCTION__ << std::endl);
  }

  /** ScriptHost, Language:
   *  Detailed description.
   *  @param x TODO
   * @return TODO
   */
  const char * ScriptHost::Language(int x) const {
      return "AsciiDoc";
  }
}
