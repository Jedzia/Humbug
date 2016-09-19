/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TimingDefs.h class.
 * \file       TimingDefs.h
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
#include <boost/function.hpp>

namespace gui {
typedef float seconds;
typedef boost::function<int (void)> const UpdateTimeFunc;
typedef boost::function<bool (seconds time)> UnaryTimeCheckFunc;

static const int FRAMESPERSECOND = 60;
}
