/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the BlueColor.h class.
 * \folder     $(folder)
 * \file       BlueColor.h
 * \date       2011-09-09
 * \author     Jedzia.
 *
 * modified    2011-09-09, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef TEMPLATES_DESIGNPATTERNS_BLUECOLOR_H
#define TEMPLATES_DESIGNPATTERNS_BLUECOLOR_H
#include "../global.h"

//
#include "Color.h"
namespace templates { namespace designpatterns { class Visitor;
                      }  }
namespace templates {
namespace designpatterns {
//! A Concrete Element.
class PLATFORM_DECL BlueColor : public Color {
public:

    //! The accept() method of an element class calls back the visit() method for its class.
    /// The visitor pattern also specifies how iteration occurs over the object structure.
    /// In the simplest version, where each algorithm needs to iterate in the same way, the accept()
    /// method of a container element, in addition to calling back the visit() method of the
    // visitor, also
    /// passes the visitor object to the accept() method of all its constituent child elements.
    virtual void accept(Visitor* v);

    void sky();
};
} // namespace templates::designpatterns
} // namespace templates
#endif // ifndef TEMPLATES_DESIGNPATTERNS_BLUECOLOR_H
