/*---------------------------------------------------------*/
/*!
 * This file is part of Templater, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the VisitorClient.h class.
 * \folder     $(folder)
 * \file       VisitorClient.h
 * \date       2011-09-09
 * \author     Jedzia.
 *
 * modified    2011-09-09, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef TEMPLATES_DESIGNPATTERNS_VISITORCLIENT_H
#define TEMPLATES_DESIGNPATTERNS_VISITORCLIENT_H
#include "../global.h"

//
namespace templates { namespace designpatterns { class CountVisitor;
                      }  }
namespace templates { namespace designpatterns { class CallVisitor;
                      }  }
namespace templates { namespace designpatterns { class BlueColor;
                      }  }
namespace templates { namespace designpatterns { class RedColor;
                      }  }
namespace templates {
namespace designpatterns {
//Calling Client.
class PLATFORM_DECL VisitorClient {
public:

    void main();
};
} // namespace templates::designpatterns
} // namespace templates
#endif // ifndef TEMPLATES_DESIGNPATTERNS_VISITORCLIENT_H
