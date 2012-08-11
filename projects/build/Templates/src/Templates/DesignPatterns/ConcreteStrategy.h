/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ConcreteStrategy.h class.
 * \folder     $(folder)
 * \file       ConcreteStrategy.h
 * \date       2011-09-08
 * \author     Jedzia.
 *
 * modified    2011-09-08, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef TEMPLATES_DESIGNPATTERNS_CONCRETESTRATEGY_H
#define TEMPLATES_DESIGNPATTERNS_CONCRETESTRATEGY_H
#include "../global.h"

//
#include "Strategy.h"
namespace templates {
namespace designpatterns {
//! Implements the algorithm using the strategy interface.
class PLATFORM_DECL ConcreteStrategyAdd : public Strategy {
public:

    virtual int execute(int a, int b);
};

//! Implements the algorithm using the strategy interface.
class PLATFORM_DECL ConcreteStrategySubtract : public Strategy {
public:

    virtual int execute(int a, int b);
};

//! Implements the algorithm using the strategy interface.
class PLATFORM_DECL ConcreteStrategyMultiply : public Strategy {
public:

    virtual int execute(int a, int b);
};
} // namespace templates::designpatterns
} // namespace templates
#endif // ifndef TEMPLATES_DESIGNPATTERNS_CONCRETESTRATEGY_H
