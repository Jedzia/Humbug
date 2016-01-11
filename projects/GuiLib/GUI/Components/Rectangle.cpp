// Rect.cpp: implementation of the CRectangle class.
#include "../../stdafx.h"
#include "Rectangle.h"

namespace gui {
namespace components {

#define pimpl_ this
/*struct CRectangle::CRectangleImpl {

	SDL_Rect m_rect;

	void slurp(std::string& data, const std::string& filename, bool is_binary = false)
	{
	}
};*/

CRectangle::CRectangle ( int x , int y , int w , int h )
//: pimpl_(new CRectangle::CRectangleImpl)
{
	Set ( x , y , w , h ) ;
}

CRectangle::CRectangle ( CPoint xy , CPoint wh )
//: pimpl_(new CRectangle::CRectangleImpl)
{
    Set ( xy.GetX() , xy.GetY() , wh.GetX() , wh.GetY() ) ;
}

CRectangle::CRectangle ( SDL_Rect rc )
//: pimpl_(new CRectangle::CRectangleImpl)
{
	Set ( rc.x , rc.y , rc.w , rc.h ) ;
}

CRectangle::CRectangle ( const SDL_Rect* prc )
//: pimpl_(new CRectangle::CRectangleImpl)
{
	Set ( prc->x , prc->y , prc->w , prc->h ) ;
}

CRectangle::CRectangle ( const CRectangle& rc )
//: pimpl_(new CRectangle::CRectangleImpl)
{
	Set ( rc.GetX() , rc.GetY() , rc.GetW() , rc.GetH() ) ;
	//( *this ) = rc ;
}

CRectangle::~CRectangle ( )
{
}

int& CRectangle::X ( )
{
	return ( pimpl_->m_rect.x ) ;
}

int& CRectangle::Y ( )
{
	return ( pimpl_->m_rect.y ) ;
}

int& CRectangle::W ( )
{
	return ( pimpl_->m_rect.w ) ;
}

int& CRectangle::H ( )
{
	return ( pimpl_->m_rect.h ) ;
}

//getters
int CRectangle::GetX() const
{
	return(pimpl_->m_rect.x);
}

int CRectangle::GetY() const
{
	return(pimpl_->m_rect.y);
}

int CRectangle::GetW() const
{
	return(pimpl_->m_rect.w);
}

int CRectangle::GetH() const
{
	return(pimpl_->m_rect.h);
}

//setters
void CRectangle::SetX(int x)
{
	pimpl_->m_rect.x=x;
}

void CRectangle::SetY(int y)
{
	pimpl_->m_rect.y=y;
}

void CRectangle::SetW(int w)
{
	pimpl_->m_rect.w=w;
}

void CRectangle::SetH(int h)
{
	pimpl_->m_rect.h=h;
}

CRectangle::operator SDL_Rect ( )
{
	return ( pimpl_->m_rect ) ;
}

CRectangle::operator SDL_Rect* ( )
{
	return ( &pimpl_->m_rect ) ;
}

CRectangle::operator CPoint ( )
{
	CPoint pt ;
	pt.Set ( X ( ) , Y ( ) ) ;
	return ( pt ) ;
}

CRectangle& CRectangle::Set ( int x , int y , int w , int h )
{
	X ( ) = x ;
	Y ( ) = y ;
	W ( ) = w ;
	H ( ) = h ;
	return ( *this ) ;
}

CRectangle& CRectangle::Copy ( CRectangle& rc )
{
	( *this ) = rc ;
	return ( *this ) ;
}

CRectangle& CRectangle::SetEmpty ( )
{
	Set ( 0 , 0 , 0 , 0 ) ;
	return ( *this ) ;
}

bool CRectangle::IsEmpty ( )
{
	return ( W ( ) == 0 && H ( ) == 0 ) ;
}

CRectangle& CRectangle::Offset ( int dx , int dy )
{
	X ( ) += dx ;
	Y ( ) += dy ;
	return ( *this ) ;
}

CRectangle& CRectangle::Offset ( CPoint& pt )
{
	Offset ( pt.X ( ) , pt.Y ( ) ) ;
	return ( *this ) ;
}

CRectangle& CRectangle::Move ( int x , int y )
{
	X ( ) = x ;
	Y ( ) = y ;
	return ( *this ) ;
}

CRectangle& CRectangle::Move ( const CPoint& pt )
{
	Move ( pt.GetX ( ) , pt.GetY ( ) ) ;
	return ( *this ) ;
}

CRectangle& CRectangle::Intersect ( CRectangle& rc )
{
	( *this ) -= rc ;
	return ( *this ) ;
}

CRectangle& CRectangle::Union ( CRectangle& rc )
{
	( *this ) += rc ;
	return ( *this ) ;
}

bool CRectangle::Contains ( int x , int y )
{
	x -= X ( ) ;
	y -= Y ( ) ;
	return ( x >= 0 && y >= 0 && x < W ( ) && y < H ( ) ) ;
}

bool CRectangle::Contains ( CPoint& pt )
{
	return ( Contains ( pt.GetX ( ) , pt.GetY ( ) ) ) ;
}

/*CRectangle& CRectangle::operator = ( CRectangle& rc )
{
	X ( ) = rc.GetX ( ) ;
	Y ( ) = rc.GetY ( ) ;
	W ( ) = rc.GetW ( ) ;
	H ( ) = rc.GetH ( ) ;
	return ( *this ) ;
}*/

CRectangle& CRectangle::operator = ( const CRectangle& rc )
{
	X ( ) = rc.GetX ( ) ;
	Y ( ) = rc.GetY ( ) ;
	W ( ) = rc.GetW ( ) ;
	H ( ) = rc.GetH ( ) ;
	return ( *this ) ;
}

CRectangle& CRectangle::operator += ( const CPoint& pt )
{
	X ( ) += pt.GetX() ;
	Y ( ) += pt.GetY() ;
	return ( *this ) ;
}

CRectangle& CRectangle::operator -= ( const CPoint& pt )
{
	X ( ) -= pt.GetX() ;
	Y ( ) -= pt.GetY() ;
	return ( *this ) ;
}

CRectangle& CRectangle::operator += ( CRectangle& rc )
{
	//( *this ) = ( *this ) + rc ;
	CRectangle tmp = ( *this ) + rc ;
	Copy(tmp);
	return ( *this ) ;
}

CRectangle& CRectangle::operator -= ( CRectangle& rc )
{
	//( *this ) = ( *this ) - rc ;
	CRectangle tmp = ( *this ) - rc ;
	Copy(tmp);
	return ( *this ) ;
}

CRectangle CRectangle::operator + ( const CPoint& pt )
{
	CRectangle result = ( *this ) ;
	result += pt ;
	return ( result ) ;
}

CRectangle CRectangle::operator - ( const CPoint& pt )
{
	CRectangle result = ( *this ) ;
	result -= pt ;
	return ( result ) ;
}

CRectangle CRectangle::operator + ( CRectangle& rc )
{
	int left1 , top1 , right1, bottom1 ;
	int left2 , top2 , right2, bottom2 ;

	CRectangle result ;
	result.SetEmpty ( ) ;

	left1 = X ( ) ;
	top1 = Y ( ) ;
	right1 = X ( ) + W ( ) ;
	bottom1 = Y ( ) + H ( ) ;

	left2 = rc.X ( ) ;
	top2 = rc.Y ( ) ;
	right2 = rc.X ( ) + rc.W ( ) ;
	bottom2 = rc.Y ( ) + rc.H ( ) ;

	if ( left1 > left2 ) left1 = left2 ;
	if ( top1 > top2 ) top1 = top2 ;
	if ( right1 < right2 ) right1 = right2 ;
	if ( bottom1 < bottom2 ) bottom1 = bottom2 ;

	right1 -= left1 ;
	bottom1 -= top1 ;

	if ( right1 > 0 && bottom1 > 0 )
	{
		result.X ( ) = left1 ;
		result.Y ( ) = top1 ;
		result.W ( ) = right1 ;
		result.H ( ) = bottom1 ;
	}

	return ( result ) ;
}

CRectangle CRectangle::operator - ( CRectangle& rc )
{
	int left1 , top1 , right1, bottom1 ;
	int left2 , top2 , right2, bottom2 ;

	CRectangle result ;
	result.SetEmpty ( ) ;

	left1 = X ( ) ;
	top1 = Y ( ) ;
	right1 = X ( ) + W ( ) ;
	bottom1 = Y ( ) + H ( ) ;

	left2 = rc.X ( ) ;
	top2 = rc.Y ( ) ;
	right2 = rc.X ( ) + rc.W ( ) ;
	bottom2 = rc.Y ( ) + rc.H ( ) ;

	if ( left1 < left2 ) left1 = left2 ;
	if ( top1 < top2 ) top1 = top2 ;
	if ( right1 > right2 ) right1 = right2 ;
	if ( bottom1 > bottom2 ) bottom1 = bottom2 ;

	right1 -= left1 ;
	bottom1 -= top1 ;

	if ( right1 > 0 && bottom1 > 0 )
	{
		result.X ( ) = left1 ;
		result.Y ( ) = top1 ;
		result.W ( ) = right1 ;
		result.H ( ) = bottom1 ;
	}

	return ( result ) ;
}

bool CRectangle::operator == ( const CRectangle& rc )
{
	return ( X ( ) == rc.GetX ( ) && Y ( ) == rc.GetY ( ) && W ( ) == rc.GetW ( ) && H ( ) == rc.GetH ( ) ) ;
}

bool CRectangle::operator == ( CRectangle& rc )
{
	return ( X ( ) == rc.X ( ) && Y ( ) == rc.Y ( ) && W ( ) == rc.W ( ) && H ( ) == rc.H ( ) ) ;
}

bool CRectangle::operator != ( CRectangle& rc )
{
	return ( !( ( *this ) == rc ) );
}

CRectangle operator + ( CPoint& pt , CRectangle& rc )
{
	CRectangle result = rc ;
	result += pt ;
	return ( result ) ;
}

CRectangle operator - ( CPoint& pt , CRectangle& rc )
{
	CRectangle result = rc ;
	result -= pt ;
	return ( result ) ;
}

CPoint CRectangle::Clip ( CPoint pt )
{
	if ( pt.X ( ) < X ( ) ) pt.X ( ) = X ( ) ;
	if ( pt.Y ( ) < Y ( ) ) pt.Y ( ) = Y ( ) ;
	if ( pt.X ( ) >= X ( ) + W ( ) ) pt.X ( ) = X ( ) + W ( ) - 1 ;
	if ( pt.Y ( ) >= Y ( ) + H ( ) ) pt.Y ( ) = Y ( ) + H ( ) - 1 ;
	return ( pt ) ;
}

CPoint CRectangle::Wrap ( CPoint pt )
{
	if ( IsEmpty ( ) ) return ( CPoint ( 0 , 0 ) ) ;
	while ( pt.X ( ) < X ( ) ) pt.X ( ) += W ( ) ;
	while ( pt.Y ( ) < Y ( ) ) pt.Y ( ) += H ( ) ;
	while ( pt.X ( ) >= X ( ) + W ( ) ) pt.X ( ) -= W ( ) ;
	while ( pt.Y ( ) >= Y ( ) + H ( ) ) pt.Y ( ) -= H ( ) ;
	return ( pt ) ;
}

std::ostream& operator<<(std::ostream& o, const CRectangle& r) {
    return o << "CRectangle[ X=" << r.GetX() << ", Y=" << r.GetY()
		<< ", W=" << r.GetW() << ", H=" << r.GetH()
		<< " ]";
}

} // namespace components
} // namespace gui
