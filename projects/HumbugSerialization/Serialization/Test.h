/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Test.h class.
 * \file       Test.h
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

#include "../global.h"
//
#include <string>
//

namespace humbug {
    namespace serialization {
/** @class Template:
 *  Detailed description.
 *  @return TODO
 */
class Template {
public:

    Template();
    ~Template();

    /** Template, Str:
     *  Detailed description.
     *  @return TODO
     */
    std::string Str() const { return str; }

    /** Template, Str:
     *  Detailed description.
     *  @param val TODO
     */
    void Str(std::string val) { str = val; }

    /** Template, Language:
     *  Detailed description.
     *  @param x TODO
     *  @return TODO
     */
    const char * Language(int x);

private:

    int i;
    std::string str;
};
}
}
