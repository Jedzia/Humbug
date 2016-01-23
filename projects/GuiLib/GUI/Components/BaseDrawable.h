/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the BaseDrawable.h class.
 * \file       BaseDrawable.h
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

#include "../Disposable.h"

namespace gui {
namespace components {
/** @class BaseDrawable:
 *  Base class for all items that draw on their member canvas.
 *  See: BaseShape's are lightweight items that draw themselves to a CCanvas, but don't own a CCanvas.
 *  $(javaparam)
 */
class BaseDrawable : public Disposable {
public:
};
}
}
