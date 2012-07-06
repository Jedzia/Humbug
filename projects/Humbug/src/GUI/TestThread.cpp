// TestThread.cpp: implementation of the CTestThread class.
//
//////////////////////////////////////////////////////////////////////

#include "TestThread.h"

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
	fprintf(stdout,"Test Thread Executing!\n");
	//return
	return(0);
}

