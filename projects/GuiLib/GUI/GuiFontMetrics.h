/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the GuiFontMetrics.h class.
 * \file       GuiFontMetrics.h
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef __GuiFontMetrics_H__
#define __GuiFontMetrics_H__

namespace gui {
namespace components {
class CRectangle;
class CColor;
}

/** @class GuiFontMetrics:
 *  Detailed description.
 *  $(javaparam)
 */
class GuiFontMetrics {
public:

    //constructor
    GuiFontMetrics(TTF_Font* font);
    //destructor
    virtual ~GuiFontMetrics ( );

    components::CRectangle CalculateDimensions(const std::string& text) const;

private:

    TTF_Font* m_pFont;
};
} // namespace gui

#endif // ifndef __GuiFontMetrics_H__
