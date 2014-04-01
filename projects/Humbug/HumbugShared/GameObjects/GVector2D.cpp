/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
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
#include "GVector2D.h"

//#include <build/cmake/include/debug.h>
namespace gob {
  GVector2D::GVector2D(float X, float Y){
      x = X;
      y = Y;
      dbgOut(__FUNCTION__);
  }

  GVector2D::~GVector2D(void){
      dbgOut(__FUNCTION__);
  }

/** $(class), operator *:
 *  Detailed description.
 *  @param scalar TODO
 * @return TODO
 */
  GVector2D GVector2D::operator*( float scalar ) const {
      return GVector2D(x * scalar, y * scalar);
  }

/** $(class), dotproduct:
 *  Detailed description.
 *  @param vect TODO
 * @return TODO
 */
  float GVector2D::dotproduct( const GVector2D &vect ) const {
      return (x * vect.x) + (y * vect.y);
  }

/** $(class), operator +:
 *  Detailed description.
 *  @param vect TODO
 * @return TODO
 */
  GVector2D GVector2D::operator+( const GVector2D &vect ) const {
      return GVector2D(x + vect.x, y + vect.y);
  }

/** $(class), operator -:
 *  Detailed description.
 *  @param vect TODO
 * @return TODO
 */
  GVector2D GVector2D::operator-( const GVector2D &vect ) const {
      return GVector2D(x - vect.x, y - vect.y);
  }

/** $(class), rotate:
 *  Detailed description.
 *  @param angle TODO
 * @return TODO
 */
  void GVector2D::rotate( float angle ){
      float xt = ( x * cosf(angle) ) - ( y * sinf(angle) );
      float yt = ( y * cosf(angle) ) + ( x * sinf(angle) );
      x = xt;
      y = yt;
  }

/** $(class), crossproduct:
 *  Detailed description.
 *  @param vect2 TODO
 * @return TODO
 */
  float GVector2D::crossproduct( const GVector2D &vect2 ) const {
      return (this->x * vect2.y) - (this->y * vect2.x);
  }

/** $(class), magnitude:
 *  Detailed description.
 *  @return TODO
 */
  float GVector2D::magnitude(){
      return sqrtf(x * x + y * y);
  }

/** $(class), normalise:
 *  Detailed description.
 *  @return TODO
 */
  void GVector2D::normalise(){
      float mag = sqrtf(x * x + y * y);
      this->x = x / mag;
      this->y = y / mag;
  }

  /** $(class), Up:
   *  Detailed description.
   *  @return TODO
   */
  gob::GVector2D GVector2D::Up(){
      return GVector2D(0, 1);
  }

  /** $(class), Down:
   *  Detailed description.
   *  @return TODO
   */
  gob::GVector2D GVector2D::Down(){
      return GVector2D(0, -1);
  }

  /** $(class), Left:
   *  Detailed description.
   *  @return TODO
   */
  gob::GVector2D GVector2D::Left(){
      return GVector2D(-1, 0);
  }

  /** $(class), Right:
   *  Detailed description.
   *  @return TODO
   */
  gob::GVector2D GVector2D::Right(){
      return GVector2D(1, 0);
  }
}
