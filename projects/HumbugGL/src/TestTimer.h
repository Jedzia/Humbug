/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TestTimer.h class.
 * \folder     $(folder)
 * \file       TestTimer.h
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef __TESTTIMER_H__
#define __TESTTIMER_H__

#include "GUI/Visual/Timer.h"

namespace humbug {
/*
        ==CTestTimer==
        Test case for CTimer
 */
  class CTestTimer : public gui::CTimer {
public:

      //constructor
      CTestTimer(CMessageHandler* pmhParent);
      //destructor
      virtual ~CTestTimer();
      //timer pulse
      void OnTimer();
  };
}

#endif //#ifndef __TESTTIMER_H__
