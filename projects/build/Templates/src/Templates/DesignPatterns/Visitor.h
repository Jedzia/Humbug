/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Visitor.h class.
 * \folder     $(folder)
 * \file       Visitor.h
 * \date       2011-09-09
 * \author     Jedzia.
 *
 * modified    2011-09-09, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef TEMPLATES_DESIGNPATTERNS_VISITOR_H
#define TEMPLATES_DESIGNPATTERNS_VISITOR_H
#include "../global.h"

//
namespace templates { namespace designpatterns { class RedColor;
                      }  }
namespace templates { namespace designpatterns { class BlueColor;
                      }  }
namespace templates {
namespace designpatterns {
//! Visitor Interface
/// A user object receives a pointer to another object which implements an algorithm. The first is
// designated the
/// "element class" and the latter the "visitor class." The idea is to use a structure of element
// classes, each of
/// which has an accept() method taking a visitor object for an argument. visitor is a protocol
// (interface in Java)
/// having a visit() method for each element class. The accept() method of an element class calls
// back the visit()
/// method for its class.
class PLATFORM_DECL Visitor {
public:

    //! One of these visit() methods of a concrete visitor can be thought of as a method not of a
    // single class,
    /// but rather a method of a pair of classes: the concrete visitor and the particular element
    // class.
    /// Thus the visitor pattern simulates double dispatch in a conventional single-dispatch
    // object-oriented
    /// language such as Java, Smalltalk, and C++.
    virtual void visit(RedColor* element) = 0;

    //! One of these visit() methods of a concrete visitor can be thought of as a method not of a
    // single class,
    /// but rather a method of a pair of classes: the concrete visitor and the particular element
    // class.
    /// Thus the visitor pattern simulates double dispatch in a conventional single-dispatch
    // object-oriented
    /// language such as Java, Smalltalk, and C++.
    virtual void visit(BlueColor* element) = 0;
};
} // namespace templates::designpatterns
} // namespace templates
#endif // ifndef TEMPLATES_DESIGNPATTERNS_VISITOR_H
