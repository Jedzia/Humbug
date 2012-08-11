/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the StrategyExample.h class.
 * \folder     $(folder)
 * \file       StrategyExample.h
 * \date       2011-09-08
 * \author     Jedzia.
 *
 * modified    2011-09-08, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef TEMPLATES_DESIGNPATTERNS_STRATEGYEXAMPLE_H
#define TEMPLATES_DESIGNPATTERNS_STRATEGYEXAMPLE_H
#include "../global.h"

//
namespace templates { namespace designpatterns { class Context;
                      }  }
namespace templates { namespace designpatterns { class Strategy;
                      }  }
namespace templates { namespace designpatterns { class ConcreteStrategyMultiply;
                      }  }
namespace templates { namespace designpatterns { class ConcreteStrategySubtract;
                      }  }
namespace templates { namespace designpatterns { class ConcreteStrategyAdd;
                      }  }
namespace templates {
namespace designpatterns {
//The client.
class PLATFORM_DECL StrategyExample {
public:

    static int main(int argc, char* argv[]);
};
} // namespace templates::designpatterns
} // namespace templates
#endif // ifndef TEMPLATES_DESIGNPATTERNS_STRATEGYEXAMPLE_H
