/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TestThread.h class.
 * \folder     $(folder)
 * \file       TestThread.h
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef __TESTTHREAD_H__
#define __TESTTHREAD_H__

#include "GUI/Visual/Thread.h"

namespace humbug {
/*
        ==CTestThread==
        Test case for CThread
 */
  class CTestThread : public gui::CThread {
public:

      //constructor
      CTestThread(CMessageHandler* pmhParent);
      virtual ~CTestThread();
      //execute
      int OnExecute();
  };
}

#endif //#ifndef __TESTTHREAD_H__
