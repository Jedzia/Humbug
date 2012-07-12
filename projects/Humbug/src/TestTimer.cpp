// TestTimer.cpp: implementation of the CTestTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestTimer.h"

//constructor
CTestTimer::CTestTimer(CMessageHandler* pmhParent):
CTimer(pmhParent,1000)
{
	//start the timer
	Start();
}

//destructor
CTestTimer::~CTestTimer()
{
	//do nothing
}

//timer pulse
void CTestTimer::OnTimer()
{
	//print to stdout
    std::cout << "Timer pulse!" << std::endl;
}

