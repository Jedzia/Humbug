/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the VisitorClient.cpp class.
 * \folder     $(folder)
 * \file       VisitorClient.cpp
 * \date       2011-09-09
 * \author     Jedzia.
 *
 * modified    2011-09-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"

//
#include "BlueColor.h"
#include "CallVisitor.h"
#include "CountVisitor.h"
#include "RedColor.h"
#include "VisitorClient.h"

//
#include <build/cmake/include/debug.h>
namespace templates {
namespace designpatterns {
void VisitorClient::main() {
    Color* set[] =
    {
        new RedColor, new BlueColor, new BlueColor, new RedColor, new RedColor, 0
    };
    CountVisitor count_operation;
    CallVisitor call_operation;

    for (int i = 0; set[i]; i++)
    {
        set[i]->accept(&count_operation);
        set[i]->accept(&call_operation);
    }
    // Report data.
    count_operation.report();

    for (int i = 0; set[i]; i++) {
        delete set[i];
    }
} // main
} // namespace templates::designpatterns
} // namespace templates
