/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Disposable.h class.
 * \file       Disposable.h
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

namespace gui {
/** @class Disposable:
 *  Detailed description.
 *  $(javaparam)
 */
class Disposable {
    bool m_bIsDisposed;

public:

    explicit Disposable()
        : m_bIsDisposed{false}
    {}

    virtual ~Disposable()    {    }

    /** Brief description of Disposable, Dispose
     *  Detailed description.
     *
     */
    virtual void Dispose();

    /** Brief description of Disposable, IsDisposed
     *  Detailed description.
     *  @return TODO
     */
    bool IsDisposed() const {
        return m_bIsDisposed;
    }
};

}
