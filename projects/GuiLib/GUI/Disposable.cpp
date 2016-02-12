/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Disposable.cpp class.
 * \file       Disposable.cpp
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
//
#include "Disposable.h"

namespace gui {
    Disposable::Disposable(): m_bIsDisposed{false}
    {}

    void Disposable::Dispose() {
    m_bIsDisposed = true;
}
}
