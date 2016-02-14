/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             timing easing functions.
 * \file       easing.cpp
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../stdafx.h"
//
#include "EasingFunctors.h"
//

namespace gui {
namespace components {
#include "easing/easing.cpp"

vdouble EaseOutQuad::operator()(vdouble t) const {
    return -t * (t - 2);
}

vdouble EaseInQuad::operator()(vdouble t) const {
    return t * t;
}

vdouble EaseInOutQuad::operator()(vdouble t) const {
    t *= vdouble(2.0);
    if(t < 1) {
        return t * t / vdouble(2);
    }
    else {
        --t;
        return vdouble(-0.5) * (t * (t - 2) - 1);
    }
}

vdouble EaseOutInQuad::operator()(vdouble t) const {
    if(t < vdouble(0.5)) { return easeOutQuad(t * 2) / 2; }

    return easeInQuad((2 * t) - 1) / 2 + vdouble(0.5);
}

vdouble EaseOutQuart::operator()(vdouble t) const {
    return easeOutQuart(t);
}

vdouble EaseInOutQuart::operator()(vdouble t) const {
    return easeInOutQuart(t);
}

vdouble EaseOutElastic::operator()(vdouble t) const {
    return easeOutElastic_helper(t, 0, 1, 1, m_amplitude, m_period);
}

vdouble EaseOutBounce::operator()(vdouble t) const {
    return easeOutBounce(t, m_amplitude);
}

vdouble EaseInOutBounce::operator()(vdouble t) const {
    return easeInOutBounce(t, m_amplitude);
}
}
}
