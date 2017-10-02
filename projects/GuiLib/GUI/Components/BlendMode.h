/*---------------------------------------------------------*/
/*!
 * This file is part of Playground, your C++ vacation spot.
 * License details can be found in the file COPYING.
 * Copyright (c) 2016, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the BlendMode.h class.
 * \file       BlendMode.h
 * \date       2016-04-26 $(date)
 * \author     Jedzia.
 *
 * modified    2016-04-26, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

namespace gui {
namespace components {
typedef enum {
    /**< no blending
       dstRGBA = srcRGBA */
    BLENDMODE_NONE = 0x00000000,

    /**< alpha blending
       dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
       dstA = srcA + (dstA * (1-srcA)) */
    BLENDMODE_BLEND = 0x00000001,

    /**< additive blending
       dstRGB = (srcRGB * srcA) + dstRGB
       dstA = dstA */
    BLENDMODE_ADD = 0x00000002,

    /**< color modulate
       dstRGB = srcRGB * dstRGB
       dstA = dstA */
    BLENDMODE_MOD = 0x00000004
} BlendMode;
}
}
