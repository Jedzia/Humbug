/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Context.h class.
 * \folder     $(folder)
 * \file       Context.h
 * \date       2011-09-08
 * \author     Jedzia.
 *
 * modified    2011-09-08, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef TEMPLATES_DESIGNPATTERNS_CONTEXT_H
#define TEMPLATES_DESIGNPATTERNS_CONTEXT_H
#include "../global.h"

//
namespace templates { namespace designpatterns { class Strategy;
                      }  }
namespace templates {
namespace designpatterns {
class PLATFORM_DECL Context {
public:

    Context(Strategy* pStrategy);
    int executeStrategy(int a, int b);

    void setStrategy(Strategy* value);

private:

    Strategy* mpStrategy;
};
} // namespace templates::designpatterns
} // namespace templates
#endif // ifndef TEMPLATES_DESIGNPATTERNS_CONTEXT_H
