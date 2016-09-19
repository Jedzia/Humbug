/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the GVector2D.cpp class.
 * \folder     $(folder)
 * \file       GVector2D.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
#include "GPoint2D.h"

//#include <build/cmake/include/debug.h>
namespace gob {
  GPoint2D::GPoint2D()
  {}

  GPoint2D::GPoint2D( float r, float s ) : GVector2D(r, s)
  {}

  /** $(class), operator =:
   *  Detailed description.
   *  @param v TODO
   * @return TODO
   */
  GPoint2D& GPoint2D::operator=( const GVector2D& v ){
      x = v.x;
      y = v.y;
      return (*this);
  }

  /** $(class), operator *=:
   *  Detailed description.
   *  @param t TODO
   * @return TODO
   */
  GPoint2D& GPoint2D::operator*=( float t ){
      x *= t;
      y *= t;
      return (*this);
  }

  /** $(class), operator /=:
   *  Detailed description.
   *  @param t TODO
   * @return TODO
   */
  GPoint2D& GPoint2D::operator/=( float t ){
      float f = 1.0F / t;
      x *= f;
      y *= f;
      return (*this);
  }

  /** $(class), operator -:
   *  Detailed description.
   *  @return TODO
   */
  gob::GPoint2D GPoint2D::operator-( void ) const {
      return ( GPoint2D(-x, -y) );
  }

  /** $(class), operator +:
   *  Detailed description.
   *  @param v TODO
   * @return TODO
   */
  gob::GPoint2D GPoint2D::operator+( const GVector2D& v ) const {
      return ( GPoint2D(x + v.x, y + v.y) );
  }

  /** $(class), operator -:
   *  Detailed description.
   *  @param v TODO
   * @return TODO
   */
  gob::GPoint2D GPoint2D::operator-( const GVector2D& v ) const {
      return ( GPoint2D(x - v.x, y - v.y) );
  }

  /** $(class), operator -:
   *  Detailed description.
   *  @param p TODO
   * @return TODO
   */
  gob::GVector2D GPoint2D::operator-( const GPoint2D& p ) const {
      return ( GVector2D(x - p.x, y - p.y) );
  }

  /** $(class), operator *:
   *  Detailed description.
   *  @param t TODO
   * @return TODO
   */
  gob::GPoint2D GPoint2D::operator*( float t ) const {
      return ( GPoint2D(x * t, y * t) );
  }

  /** $(class), operator /:
   *  Detailed description.
   *  @param t TODO
   * @return TODO
   */
  gob::GPoint2D GPoint2D::operator/( float t ) const {
      float f = 1.0F / t;
      return ( GPoint2D(x * f, y * f) );
  }
}
