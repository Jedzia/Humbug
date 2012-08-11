/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Color.h class.
 * \folder     $(folder)
 * \file       Color.h
 * \date       2011-09-09
 * \author     Jedzia.
 *
 * modified    2011-09-09, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef TEMPLATES_DESIGNPATTERNS_COLOR_H
#define TEMPLATES_DESIGNPATTERNS_COLOR_H
#include "../global.h"

//
namespace templates { namespace designpatterns { class Visitor;
                      }  }
namespace templates {
namespace designpatterns {
//! Element
class PLATFORM_DECL Color {
public:

    //! The accept() method of an element class calls back the visit() method for its class.
    virtual void accept(Visitor* v) = 0;
};
} // namespace templates::designpatterns
} // namespace templates
#endif // ifndef TEMPLATES_DESIGNPATTERNS_COLOR_H
