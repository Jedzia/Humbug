// TestThread.cpp: implementation of the CTestThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestThread.h"

namespace humbug {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//constructor
CTestThread::CTestThread(CMessageHandler* pmhParent):
CThread(pmhParent)
{
	//start the thread
	Start();
}

CTestThread::~CTestThread()
{
}

//execute
int CTestThread::OnExecute()
{
	//print to stdout
    std::cout << "Test Thread Executing!" << std::endl;
	//return
	return(0);
}

}
