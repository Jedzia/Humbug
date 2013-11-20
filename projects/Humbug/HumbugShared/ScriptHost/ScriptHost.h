/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ScriptHost.h class.
 * \folder     $(folder)
 * \file       ScriptHost.h
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef GAMEOBJECTS_SCRIPTHOST_H
#define GAMEOBJECTS_SCRIPTHOST_H

#include <string>

namespace gob {
  class ScriptHost {
public:

      ScriptHost();
      ~ScriptHost();

      /** ScriptHost, Str:
       *  Detailed description.
       *  @return TODO
       */
      std::string Str() const { return str; }

      /** ScriptHost, Str:
       *  Detailed description.
       *  @param val TODO
       */
      void Str(std::string val) { str = val; }

      /** ScriptHost, Language:
       *  Detailed description.
       *  @param x TODO
       *  @return TODO
       */
      const char * Language(int x) const;

private:

      int i;
      std::string str;
  };
}
#endif // ifndef GAMEOBJECTS_SCRIPTHOST_H
