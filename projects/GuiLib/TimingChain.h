/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Timing.h class.
 * \file       Timing.h
 * \date       2016-01-30
 * \author     Jedzia.
 *
 * modified    2016-01-30, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
#include "Timing.h"

namespace gui {
class Hookable;

/** @class Timing:
 *  Detailed description.
 *
 */
class TimingChain {
    Hookable* m_pUpdater;
    seconds m_secStarttime;
    Timing m_timTimer;
public:
    explicit TimingChain(Hookable* updater);
    TimingChain& At(seconds time, Timing::ConditionalTimeFunc func = NULL, seconds time2 = 0);
    TimingChain& At(seconds after, seconds before, Timing::ConditionalTimeFunc func = NULL);
    void Commit(seconds loopAfter = 0);
};
}
