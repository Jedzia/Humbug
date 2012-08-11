/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Strategy.h class.
 * \folder     $(folder)
 * \file       Strategy.h
 * \date       2011-09-08
 * \author     Jedzia.
 *
 * modified    2011-09-08, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef TEMPLATES_DESIGNPATTERNS_STRATEGY_H
#define TEMPLATES_DESIGNPATTERNS_STRATEGY_H
#include "../global.h"

//
namespace templates {
namespace designpatterns {
//The context class uses this to call the concrete strategy.
class PLATFORM_DECL Strategy {
public:

    virtual int execute(int a, int b) = 0;
};
} // namespace templates::designpatterns
} // namespace templates
#endif // ifndef TEMPLATES_DESIGNPATTERNS_STRATEGY_H
