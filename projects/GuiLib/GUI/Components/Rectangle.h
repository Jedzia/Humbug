#ifndef __GUI_COMPONENTS_RECTANGLE_H__
#define __GUI_COMPONENTS_RECTANGLE_H__

//#include <boost/shared_ptr.hpp>
#include "SDL.h"
#include "Point.h"
#include <iostream>

/*struct SDL_Rect;
typedef short           int16_t;
typedef int16_t		int;
typedef unsigned short  int_t;
typedef int_t	int;*/

namespace gui {
namespace components {

//CRectangle--abstract an SDL_Rect
class CRectangle
{
private:
	//internal representation of a SDL_Rect
	/*struct CRectangleImpl;
	boost::scoped_ptr<CRectangleImpl> pimpl_;*/
	SDL_Rect m_rect;
public:
    /*SDL_Rect SDLRect() const
    {
        return m_rect;
    }*/

    //constructors--direct member assignment
	CRectangle ( int x = 0 , int y = 0 , int w = 0 , int h = 0 ) ;
	CRectangle ( CPoint xy , CPoint wh ) ;
	//copy from SDL_Rect
	CRectangle ( SDL_Rect rc ) ;
	//copy from SDL_Rect*
	CRectangle ( SDL_Rect* prc ) ;
	//copy from another CRectangle
	CRectangle ( const CRectangle& rc ) ;
	virtual ~CRectangle ( ) ;

	//accessors for x, y, h, and w
	int& X ( ) ;
	int& Y ( ) ;
	int& W ( ) ;
	int& H ( ) ;

	//getters
	int GetX() const;
	int GetY() const;
	int GetW() const;
	int GetH() const;

	//setters
	void SetX(int x);
	void SetY(int y);
	void SetW(int w);
	void SetH(int h);

	//conversion operators
	//convert to SDL_Rect
	operator SDL_Rect ( ) ;
	//convert to SDL_Rect*
	operator SDL_Rect* ( ) ;
	//convert to CPoint
	operator CPoint ( ) ;

	//set values for members
	CRectangle& Set ( int x , int y , int w , int h ) ;
	//copy member values from another CRectangle
	CRectangle& Copy ( CRectangle& rc ) ;

	//set to an empty rectangle
	CRectangle& SetEmpty ( ) ;
	//check for emptiness
	bool IsEmpty ( ) ;

	//offset rectangle by coordinates or point
	CRectangle& Offset ( int dx , int dy ) ;
	CRectangle& Offset ( CPoint& pt ) ;

	//move to a position, either coordinates or point
	CRectangle& Move ( int x , int y ) ;
	CRectangle& Move ( const CPoint& pt ) ;

	//intersect with another rectangle
	CRectangle& Intersect ( CRectangle& rc ) ;
	//create union with another rectangle
	CRectangle& Union ( CRectangle& rc ) ;

	//check if a point is within the rectangle
	bool Contains ( int x , int y ) ;
	bool Contains ( CPoint& pt ) ;

    // Todo: all to const refs
	//assignment operators
	//CRectangle& operator = ( CRectangle& rc ) ;
	CRectangle& operator = ( const CRectangle& rc ) ;
	CRectangle& operator += ( const CPoint& pt ) ;
	CRectangle& operator -= ( const CPoint& pt ) ;
	CRectangle& operator += ( CRectangle& rc ) ;
	CRectangle& operator -= ( CRectangle& rc ) ;

	//arithmetic operators
	CRectangle operator + ( const CPoint& pt ) ;
	CRectangle operator - ( const CPoint& pt ) ;
	CRectangle operator + ( CRectangle& rc ) ;
	CRectangle operator - ( CRectangle& rc ) ;

	//comparisons
	bool operator == ( CRectangle& rc ) ;
	bool operator == ( const CRectangle& rc ) ;
	bool operator != ( CRectangle& rc ) ;

	//clip or wrap points
	CPoint Clip ( CPoint pt ) ;
	CPoint Wrap ( CPoint pt ) ;

    friend std::ostream& operator<<(std::ostream& o, const CRectangle& r);
};

//add/subtract point and rectangle
CRectangle operator + ( CPoint& pt , CRectangle& rc ) ;
CRectangle operator - ( CPoint& pt , CRectangle& rc ) ;


std::ostream& operator<<(std::ostream& o, const CRectangle& r);

} // namespace components
} // namespace gui

#endif
