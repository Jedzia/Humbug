// TestTimer.cpp: implementation of the CTestTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "TestTimer.h"
#include "stdafx.h"

namespace humbug {
//constructor
  CTestTimer::CTestTimer(CMessageHandler* pmhParent) :
      CTimer(pmhParent, 1000){
      //start the timer
      Start();
  }

//destructor
  CTestTimer::~CTestTimer(){
      //do nothing
  }

//timer pulse
  void CTestTimer::OnTimer(){
      //print to stdout
      LOGSTREAM << "Timer pulse!";
  }
}
