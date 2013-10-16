#ifndef __GUI_COMPONENTS_RECTANGLE_H__
#define __GUI_COMPONENTS_RECTANGLE_H__

//#include <boost/shared_ptr.hpp>
#include "sdl.h"
#include "point.h"
#include <iostream>

/*struct SDL_Rect;
typedef short           int16_t;
typedef int16_t		Sint16;
typedef unsigned short  uint16_t;
typedef uint16_t	Uint16;*/

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
	//constructors--direct member assignment
	CRectangle ( Sint16 x = 0 , Sint16 y = 0 , Uint16 w = 0 , Uint16 h = 0 ) ;
	CRectangle ( CPoint xy , CPoint wh ) ;
	//copy from SDL_Rect
	CRectangle ( SDL_Rect rc ) ;
	//copy from SDL_Rect*
	CRectangle ( SDL_Rect* prc ) ;
	//copy from another CRectangle
	CRectangle ( const CRectangle& rc ) ;
	virtual ~CRectangle ( ) ;

	//accessors for x, y, h, and w
	Sint16& X ( ) ;
	Sint16& Y ( ) ;
	Uint16& W ( ) ;
	Uint16& H ( ) ;

	//getters
	Sint16 GetX() const;
	Sint16 GetY() const;
	Uint16 GetW() const;
	Uint16 GetH() const;

	//setters
	void SetX(Sint16 x);
	void SetY(Sint16 y);
	void SetW(Uint16 w);
	void SetH(Uint16 h);

	//conversion operators
	//convert to SDL_Rect
	operator SDL_Rect ( ) ;
	//convert to SDL_Rect*
	operator SDL_Rect* ( ) ;
	//convert to CPoint
	operator CPoint ( ) ;

	//set values for members
	CRectangle& Set ( Sint16 x , Sint16 y , Uint16 w , Uint16 h ) ;
	//copy member values from another CRectangle
	CRectangle& Copy ( CRectangle& rc ) ;

	//set to an empty rectangle
	CRectangle& SetEmpty ( ) ;
	//check for emptiness
	bool IsEmpty ( ) ;

	//offset rectangle by coordinates or point
	CRectangle& Offset ( Sint16 dx , Sint16 dy ) ;
	CRectangle& Offset ( CPoint& pt ) ;

	//move to a position, either coordinates or point
	CRectangle& Move ( Sint16 x , Sint16 y ) ;
	CRectangle& Move ( const CPoint& pt ) ;

	//intersect with another rectangle
	CRectangle& Intersect ( CRectangle& rc ) ;
	//create union with another rectangle
	CRectangle& Union ( CRectangle& rc ) ;

	//check if a point is within the rectangle
	bool Contains ( Sint16 x , Sint16 y ) ;
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
