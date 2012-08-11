/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ConcreteStrategy.cpp class.
 * \folder     $(folder)
 * \file       ConcreteStrategy.cpp
 * \date       2011-09-08
 * \author     Jedzia.
 *
 * modified    2011-09-08, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"

//
#include "ConcreteStrategy.h"

//
#include <build/cmake/include/debug.h>
namespace templates {
namespace designpatterns {
int ConcreteStrategyAdd::execute(int a, int b) {
    std::cout << "Called ConcreteStrategyAdd's execute()" << std::endl;
    return a + b; // Do an addition with a and b
}

int ConcreteStrategySubtract::execute(int a, int b) {
    std::cout << "Called ConcreteStrategySubtract's execute()" << std::endl;
    return a - b; // Do a subtraction with a and b
}

int ConcreteStrategyMultiply::execute(int a, int b) {
    std::cout << "Called ConcreteStrategyMultiply's execute()" << std::endl;
    return a * b; // Do a multiplication with a and b
}
} // namespace templates::designpatterns
} // namespace templates
