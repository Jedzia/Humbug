#ifndef __TESTTIMER_H__
#define __TESTTIMER_H__

#include "GUI/Visual/Timer.h"
/*
	==CTestTimer==
	Test case for CTimer
*/
class CTestTimer : public CTimer
{
public:
	//constructor
	CTestTimer(CMessageHandler* pmhParent);
	//destructor
	virtual ~CTestTimer();
	//timer pulse
	void OnTimer();
};

#endif //#ifndef __TESTTIMER_H__
