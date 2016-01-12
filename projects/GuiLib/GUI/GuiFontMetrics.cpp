/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the GuiFontMetrics.cpp class.
 * \file       GuiFontMetrics.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
#include "Components/Rectangle.h"
#include "GuiFontMetrics.h"

namespace gui {
using namespace components;
GuiFontMetrics::GuiFontMetrics(TTF_Font* font) : m_pFont(font)
{}

GuiFontMetrics::~GuiFontMetrics() {}

CRectangle GuiFontMetrics::CalculateDimensions(const std::string& text) const {
    if (text != "" && m_pFont != NULL) {
        const char* ctext = text.c_str();
        int width, height;

        if ( (TTF_SizeUTF8(m_pFont, ctext, &width, &height) < 0) || !width ) {
            // Todo: TTF_SetError("Text has zero width");
            return CRectangle();
        }

        return CRectangle(0, 0, width, height);
    }

    return CRectangle();
}
} // namespace gui
