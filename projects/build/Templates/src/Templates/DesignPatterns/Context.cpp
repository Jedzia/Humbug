/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Context.cpp class.
 * \folder     $(folder)
 * \file       Context.cpp
 * \date       2011-09-08
 * \author     Jedzia.
 *
 * modified    2011-09-08, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"

//
#include "Context.h"
#include "Strategy.h"

//
#include <build/cmake/include/debug.h>
namespace templates {
namespace designpatterns {
Context::Context(Strategy* pStrategy) :
    mpStrategy(pStrategy){}

int Context::executeStrategy(int a, int b) {
	ASSERT(mpStrategy != NULL);
    return mpStrategy->execute(a, b);
}

void Context::setStrategy(Strategy* value) {
    mpStrategy = value;
}
} // namespace templates::designpatterns
} // namespace templates
