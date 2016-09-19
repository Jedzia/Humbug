/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the CountVisitor.cpp class.
 * \folder     $(folder)
 * \file       CountVisitor.cpp
 * \date       2011-09-09
 * \author     Jedzia.
 *
 * modified    2011-09-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"

//
#include "BlueColor.h"
#include "CountVisitor.h"
#include "RedColor.h"

//
#include <build/cmake/include/debug.h>
namespace templates {
namespace designpatterns {
CountVisitor::CountVisitor() {
    m_num_red = m_num_blu = 0;
}

//! One of these visit() methods of a concrete visitor can be thought of as a method not of a single
// class,
/// but rather a method of a pair of classes: the concrete visitor and the particular element class.
/// Thus the visitor pattern simulates double dispatch in a conventional single-dispatch
// object-oriented
/// language such as Java, Smalltalk, and C++.
void CountVisitor::visit(RedColor* element) {
    ++m_num_red;
}

//! One of these visit() methods of a concrete visitor can be thought of as a method not of a single
// class,
/// but rather a method of a pair of classes: the concrete visitor and the particular element class.
/// Thus the visitor pattern simulates double dispatch in a conventional single-dispatch
// object-oriented
/// language such as Java, Smalltalk, and C++.
void CountVisitor::visit(BlueColor* element) {
    ++m_num_blu;
}

void CountVisitor::report() {
    std::cout << "Reds " << m_num_red << ", Blus " << m_num_blu << '\n';
}
} // namespace templates::designpatterns
} // namespace templates
