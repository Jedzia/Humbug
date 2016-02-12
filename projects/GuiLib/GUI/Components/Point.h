//sentinel
#ifndef __GUI_COMPONENTS_POINT_H__
#define __GUI_COMPONENTS_POINT_H__
#include <boost/numeric/ublas/vector.hpp>

namespace gui {
namespace components {
//point class
class CPoint {
    //x and y
    int m_x;
    int m_y;

public:

    //constructor
    CPoint (int x = 0, int y = 0);
    CPoint(const CPoint& pt);
    explicit CPoint(const boost::numeric::ublas::vector<double>& vec);
    explicit CPoint(const boost::numeric::ublas::vector<long double>& vec);
    explicit CPoint(const boost::numeric::ublas::vector<float>& vec);
    explicit CPoint(const boost::numeric::ublas::vector<int>& vec);

    //destructor
    virtual ~CPoint ();

    //properties
    int& X ();

    int& Y ();

    int GetX () const;

    int GetY () const;

    void SetX (int x);

    void SetY (int y);

    //setter
    CPoint& Set (int x, int y);

    CPoint Offset (int x, int y);

    CPoint& Copy(const CPoint& pt);

    //move
    CPoint& Move (int dx, int dy);

    CPoint& Add (const CPoint& pt);

    CPoint& Subtract(const CPoint& pt);

    //scale
    CPoint& Scale (int scalar);

    //distance
    int Distance(const CPoint& pt);

    //assignment
    CPoint& operator = (const CPoint& pt);

    CPoint& operator += (const CPoint& pt);

    CPoint& operator -= (const CPoint& pt);

    CPoint& operator *= (int scalar);

    CPoint& operator /= (int scalar);

    //unary
    CPoint operator - () const;

    CPoint operator + () const;

    CPoint operator + (const CPoint& pt) const;

    CPoint operator - (const CPoint& pt) const;

    CPoint operator * (int scalar) const;

    CPoint operator / (int scalar) const;

    //comparison
    bool operator == (const CPoint& pt) const;

    bool operator != (const CPoint& pt) const;

    bool operator<(const CPoint& pt) const;

    // conversion
    operator boost::numeric::ublas::vector<double>() const;
    operator boost::numeric::ublas::vector<long double>() const;
    operator boost::numeric::ublas::vector<float>() const;
    operator boost::numeric::ublas::vector<int>() const;
};

CPoint operator * (int scalar, CPoint& pt);
} // namespace components
} // namespace gui

#endif // ifndef __GUI_COMPONENTS_POINT_H__
