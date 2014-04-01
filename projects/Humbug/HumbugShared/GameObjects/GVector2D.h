/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the GVector2D.h class.
 * \folder     $(folder)
 * \file       GVector2D.h
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef GAMEOBJECTS_GVECTOR2D_H
#define GAMEOBJECTS_GVECTOR2D_H

namespace gob {
/** @class GVector2D:
 *  Detailed description.
 *  $(javaparam)
 */
  class GVector2D {
public:

      GVector2D(float X = 0, float Y = 0);
      ~GVector2D();

      GVector2D operator*(float scalar) const;

      GVector2D operator+(const GVector2D &vect) const;

      GVector2D operator-(const GVector2D &vect) const;

      void rotate(float angle);

      float crossproduct(const GVector2D &vect2) const;

      float magnitude();

      void normalise();

      // return dot product
      float dotproduct(const GVector2D &vect) const;

      float x, y;

      static GVector2D Up();

      static GVector2D Down();

      static GVector2D Left();

      static GVector2D Right();
  };
}
#endif // GAMEOBJECTS_GVECTOR2D_H
