/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TextAnimatorImpl.h class.
 * \file       TextAnimatorImpl.h
 * \date       2016-01-22
 * \author     Jedzia.
 *
 * modified    2016-01-22, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
#include "../../MathDefs.h"

namespace gui {
namespace components {
#define DEBUGPRINT 1

class EaseNone {
public:

    explicit EaseNone(const vdouble alpha = static_cast<vdouble>(1.0f)) { };

    vdouble operator()(vdouble t) const
    {
        return t;
    }
};

/** @class EaseOutQuad:
 *  Detailed description.
 *  @param t TODO
 *  @return TODO
 */
class EaseOutQuad {
public:

    explicit EaseOutQuad(const vdouble alpha = static_cast<vdouble>(1.0f)) { }

    vdouble operator()(vdouble t) const;
};

/** @class EaseInQuad:
 *  Detailed description.
 *  @param t TODO
 *  @return TODO
 */
class EaseInQuad {
public:

    explicit EaseInQuad(const vdouble alpha = static_cast<vdouble>(1.0f)) { }

    vdouble operator()(vdouble t) const;
};

/** @class EaseInOutQuad:
 *  Detailed description.
 *  @param t TODO
 *  @return TODO
 */
class EaseInOutQuad {
public:

    explicit EaseInOutQuad(const vdouble alpha = static_cast<vdouble>(1.0f)) { }

    vdouble operator()(vdouble t) const;
};

/** @class EaseOutInQuad:
 *  Detailed description.
 *  @param t TODO
 *  @return TODO
 */
class EaseOutInQuad {
    EaseInQuad easeInQuad;
    EaseOutQuad easeOutQuad;

public:

    explicit EaseOutInQuad(const vdouble alpha = static_cast<vdouble>(1.0f)) { }

    vdouble operator()(vdouble t) const;
};

/** @class EaseOutQuart:
 *  Detailed description.
 *  @param t TODO
 *  @return TODO
 */
class EaseOutQuart {
public:

    explicit EaseOutQuart(const vdouble alpha = static_cast<vdouble>(1.0f)) { }

    vdouble operator()(vdouble t) const;
};

/** @class EaseInOutQuart:
 *  Detailed description.
 *  @param t TODO
 *  @return TODO
 */
class EaseInOutQuart {
public:

    explicit EaseInOutQuart(const vdouble alpha = static_cast<vdouble>(1.0f)) { }

    vdouble operator()(vdouble t) const;
};

/** @class EaseInOutElastic:
 *  Detailed description.
 *  @param t TODO
 *  @return TODO
 */
class EaseInOutElastic {
    vdouble m_amplitude;
    vdouble m_period;

public:

    explicit EaseInOutElastic(const vdouble amplitude = static_cast<vdouble>(1.0f),
            const vdouble period = static_cast<vdouble>(1.0f)) : m_amplitude(amplitude), m_period(period)
    { }

    vdouble operator()(vdouble t) const;
};

/** @class EaseOutInElastic:
 *  Detailed description.
 *  @param t TODO
 *  @return TODO
 */
class EaseOutElastic {
    vdouble m_amplitude;
    vdouble m_period;

public:

    explicit EaseOutElastic(const vdouble amplitude = static_cast<vdouble>(1.0f),
            const vdouble period = static_cast<vdouble>(1.0f)) : m_amplitude(amplitude), m_period(period)
    { }

    vdouble operator()(vdouble t) const;
};

/** @class EaseOutInElastic:
 *  Detailed description.
 *  @param t TODO
 *  @return TODO
 */
class EaseOutInElastic {
    vdouble m_amplitude;
    vdouble m_period;

public:

    explicit EaseOutInElastic(const vdouble amplitude = static_cast<vdouble>(1.0f),
            const vdouble period = static_cast<vdouble>(1.0f)) : m_amplitude(amplitude), m_period(period)
    { }

    vdouble operator()(vdouble t) const;
};

/** @class EaseOutBounce:
 *  Detailed description.
 *  @param t TODO
 *  @return TODO
 */
class EaseOutBounce {
    vdouble m_amplitude;

public:

    explicit EaseOutBounce(const vdouble amplitude = static_cast<vdouble>(1.0f)) : m_amplitude(amplitude)
    { }

    vdouble operator()(vdouble t) const;
};

/** @class EaseInOutBounce:
 *  Detailed description.
 *  @param t TODO
 *  @return TODO
 */
class EaseInOutBounce {
    vdouble m_amplitude;

public:

    explicit EaseInOutBounce(const vdouble amplitude = static_cast<vdouble>(1.0f)) : m_amplitude(amplitude)
    { }

    vdouble operator()(vdouble t) const;
};
}
}
