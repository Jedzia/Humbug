/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the VersionToken.cpp class.
 * \file       VersionToken.cpp
 * \date       2016-01-27
 * \author     Jedzia.
 *
 * modified    2016-01-27, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
#include "../stddefs.h"
//
#include "VersionToken.h"
//
//#include <build/cmake/include/debug.h>

namespace humbug {
namespace serialization {
VersionToken::VersionToken() : i(0) {
    dbgOut(__FUNCTION__);
}

VersionToken::~VersionToken(void) {
    dbgOut(__FUNCTION__);
}

const char * VersionToken::Language(int x) const {
    return "AsciiDoc";
}

std::ostream& operator<<(std::ostream& o, const VersionToken& obj) {
    return o;
}

std::istream& operator>>(std::istream& i, VersionToken& obj) {
    return i;
}
}
}
