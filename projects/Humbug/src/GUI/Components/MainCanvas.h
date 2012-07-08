#ifndef __MAINCANVAS_H__
#define __MAINCANVAS_H__

#include "Canvas.h"

//main canvas, abstract primary display surface
class CMainCanvas : public CCanvas  
{
public:
	//constructor
	CMainCanvas ( int width , int height , int bpp , Uint32 flags ) ;
	//destructor
	virtual ~CMainCanvas ( ) ;
};

#endif 
