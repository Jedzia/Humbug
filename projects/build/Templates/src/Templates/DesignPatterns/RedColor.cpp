/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the RedColor.cpp class.
 * \folder     $(folder)
 * \file       RedColor.cpp
 * \date       2011-09-09
 * \author     Jedzia.
 *
 * modified    2011-09-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"

//
#include "RedColor.h"
#include "Visitor.h"

//
#include <build/cmake/include/debug.h>
namespace templates {
namespace designpatterns {
//! The accept() method of an element class calls back the visit() method for its class.
void RedColor::accept(Visitor* v) {
    v->visit(this);
}

void RedColor::eye() {
    std::cout << "Red::eye\n";
}
} // namespace templates::designpatterns
} // namespace templates
