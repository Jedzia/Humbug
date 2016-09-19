/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the StrategyExample.cpp class.
 * \folder     $(folder)
 * \file       StrategyExample.cpp
 * \date       2011-09-08
 * \author     Jedzia.
 *
 * modified    2011-09-08, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"

//
#include "ConcreteStrategy.h"
#include "Context.h"
#include "Strategy.h"
#include "StrategyExample.h"

//
#include <build/cmake/include/debug.h>
namespace templates {
namespace designpatterns {
int StrategyExample::main(int argc, char* argv[])
{
    {
        Context* context;

        // Three contexts following different strategies
        context = new Context( new ConcreteStrategyAdd() );
        int resultA = context->executeStrategy(3, 4);
        context = new Context( new ConcreteStrategySubtract() );
        int resultB = context->executeStrategy(3, 4);
        context = new Context( new ConcreteStrategyMultiply() );
        int resultC = context->executeStrategy(3, 4);
    }
    {
        // as local
        ConcreteStrategyAdd strategyA;
        ConcreteStrategySubtract strategyB;
        ConcreteStrategyMultiply strategyC;
        Context context(&strategyA);
        int resultA = context.executeStrategy(3, 4);
        context.setStrategy(&strategyB);
        int resultB = context.executeStrategy(3, 4);
        context.setStrategy(&strategyC);
        int resultC = context.executeStrategy(3, 4);
    }
    return 0;
} // main
} // namespace templates::designpatterns
} // namespace templates
