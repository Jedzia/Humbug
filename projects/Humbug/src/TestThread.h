#ifndef __TESTTHREAD_H__
#define __TESTTHREAD_H__

#include "GUI/Visual/Thread.h"

/*
	==CTestThread==
	Test case for CThread
*/
class CTestThread : public CThread
{
public:
	//constructor
	CTestThread(CMessageHandler* pmhParent);
	virtual ~CTestThread();
	//execute
	int OnExecute();
};

#endif //#ifndef __TESTTHREAD_H__
