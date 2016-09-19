/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
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
#ifndef GAMEOBJECTS_GPOINT2D_H
#define GAMEOBJECTS_GPOINT2D_H

#include "GVector2D.h"

namespace gob {
/** @class GVector2D:
 *  Detailed description.
 *  $(javaparam)
 */

  class GPoint2D : public GVector2D {
public:

      GPoint2D();

      GPoint2D(float r, float s);

      GPoint2D& operator =(const GVector2D& v);

      GPoint2D& operator *=(float t);

      GPoint2D& operator /=(float t);

      GPoint2D operator -(void) const;

      GPoint2D operator +(const GVector2D& v) const;

      GPoint2D operator -(const GVector2D& v) const;

      GVector2D operator -(const GPoint2D& p) const;

      GPoint2D operator *(float t) const;

      GPoint2D operator /(float t) const;
  };

  /*inline GVector2D operator *(float t, const GVector2D& v)
  {
	  return (GVector2D(t * v.x, t * v.y));
  }

  inline GPoint2D operator *(float t, const GPoint2D& p)
  {
	  return (GPoint2D(t * p.x, t * p.y));
  }

  inline float Dot(const GVector2D& v1, const GVector2D& v2)
  {
	  return (v1 * v2);
  }

  inline float Magnitude(const GVector2D& v)
  {
	  return (sqrtf(v.x * v.x + v.y * v.y));
  }

  inline float InverseMag(const GVector2D& v)
  {
	  return (1.0F / sqrtf(v.x * v.x + v.y * v.y));
  }

  inline float SquaredMag(const GVector2D& v)
  {
	  return (v.x * v.x + v.y * v.y);
  }*/

}
#endif // GAMEOBJECTS_GPOINT2D_H
