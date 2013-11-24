/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Template.h class.
 * \folder     $(folder)
 * \file       Template.h
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef GAMEOBJECTS_TEMPLATE_H
#define GAMEOBJECTS_TEMPLATE_H

#include <string>

namespace gob {
  /** @class Template:
   *  Detailed description.
   *  @return TODO
   */
  class Template {
public:

      Template();
      ~Template();

      /** Template, Str:
       *  Detailed description.
       *  @return TODO
       */
      std::string Str() const { return str; }

      /** Template, Str:
       *  Detailed description.
       *  @param val TODO
       */
      void Str(std::string val) { str = val; }

      /** Template, Language:
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
#endif // ifndef GAMEOBJECTS_TEMPLATE_H
