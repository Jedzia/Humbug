/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the GameObject.h class.
 * \folder     $(folder)
 * \file       GameObject.h
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef GAMEOBJECTS_GAMEOBJECT_H
#define GAMEOBJECTS_GAMEOBJECT_H

#include <string>

namespace gob {
  class GameObject {
public:

	GameObject(std::string name);
      virtual ~GameObject();

      /** GameObject, Str:
       *  Detailed description.
       *  @return TODO
       */
      std::string Str() const { return m_name; }

      /** GameObject, Str:
       *  Detailed description.
       *  @param val TODO
       */
      void Str(std::string name) { m_name = name; }

      /** GameObject, Language:
       *  Detailed description.
       *  @param x TODO
       *  @return TODO
       */
      const char * Language(int x) const;

private:

      int i;
      std::string m_name;
  };
}
#endif // ifndef GAMEOBJECTS_GAMEOBJECT_H
