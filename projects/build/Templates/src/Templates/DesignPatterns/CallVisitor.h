/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the CallVisitor.h class.
 * \folder     $(folder)
 * \file       CallVisitor.h
 * \date       2011-09-09
 * \author     Jedzia.
 *
 * modified    2011-09-09, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef TEMPLATES_DESIGNPATTERNS_CALLVISITOR_H
#define TEMPLATES_DESIGNPATTERNS_CALLVISITOR_H
#include "../global.h"

//
#include "Visitor.h"
namespace templates { namespace designpatterns { class RedColor;
                      }  }
namespace templates { namespace designpatterns { class BlueColor;
                      }  }
namespace templates {
namespace designpatterns {
//! A Concrete Visitor.
/// Separate concrete visitor classes can then be written to perform some particular operations,
/// by implementing these operations in their respective visit() methods.
class PLATFORM_DECL CallVisitor : public Visitor {
public:

    //! One of these visit() methods of a concrete visitor can be thought of as a method not of a
    // single class,
    /// but rather a method of a pair of classes: the concrete visitor and the particular element
    // class.
    /// Thus the visitor pattern simulates double dispatch in a conventional single-dispatch
    // object-oriented
    /// language such as Java, Smalltalk, and C++.
    virtual void visit(RedColor* element);

    //! One of these visit() methods of a concrete visitor can be thought of as a method not of a
    // single class,
    /// but rather a method of a pair of classes: the concrete visitor and the particular element
    // class.
    /// Thus the visitor pattern simulates double dispatch in a conventional single-dispatch
    // object-oriented
    /// language such as Java, Smalltalk, and C++.
    virtual void visit(BlueColor* element);
};
} // namespace templates::designpatterns
} // namespace templates
#endif // ifndef TEMPLATES_DESIGNPATTERNS_CALLVISITOR_H
