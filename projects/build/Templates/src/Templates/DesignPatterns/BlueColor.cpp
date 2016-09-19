/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the BlueColor.cpp class.
 * \folder     $(folder)
 * \file       BlueColor.cpp
 * \date       2011-09-09
 * \author     Jedzia.
 *
 * modified    2011-09-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"

//
#include "BlueColor.h"
#include "Visitor.h"

//
#include <build/cmake/include/debug.h>
namespace templates {
namespace designpatterns {
//! The accept() method of an element class calls back the visit() method for its class.
/// The visitor pattern also specifies how iteration occurs over the object structure.
/// In the simplest version, where each algorithm needs to iterate in the same way, the accept()
/// method of a container element, in addition to calling back the visit() method of the visitor,
// also
/// passes the visitor object to the accept() method of all its constituent child elements.
void BlueColor::accept(Visitor* v) {
    v->visit(this);

    // if this was a container-element with several childs,
    // here we call the accept methods of them, e.g.:
    /*
       for (int i = 0; childs[i]; i++)
       {
        childs[i]->accept(v);
       }
     */
}

void BlueColor::sky() {
    std::cout << "Blu::sky\n";
}
} // namespace templates::designpatterns
} // namespace templates
