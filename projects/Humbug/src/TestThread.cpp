// TestThread.cpp: implementation of the CTestThread class.
//
//////////////////////////////////////////////////////////////////////

#include "TestThread.h"
#include "stdafx.h"

namespace humbug {
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

  CTestThread::CTestThread(CMessageHandler* pmhParent) :
      CThread(pmhParent){
      //start the thread
      Start();
  }

  CTestThread::~CTestThread()
  {}

  /** CTestThread, OnExecute:
   *  Detailed description.
   *  @return TODO
   */
  int CTestThread::OnExecute(){
      //print to stdout
      LOGSTREAM << "Test Thread Executing!";
      //return
      return(0);
  }
}
