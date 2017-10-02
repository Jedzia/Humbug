/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the scratchb01.cpp class.
 * \file       scratchb01.cpp
 * \date       2016-01-30
 * \author     Jedzia.
 *
 * modified    2016-01-30, Jedzia
 */
// check for c++14
//#if __cplusplus >= 201402L
#if 1
// Visual Studio 2015
//#if _MSC_VER >= 1900
/*---------------------------------------------------------*/
//#define _SCL_SECURE_NO_WARNINGS 1
//#include <boost/assert.hpp>
//#include <array>
//#include <boost/algorithm/cxx14/equal.hpp>
//#include <boost/array.hpp>
//#include <boost/algorithm/string.hpp>
//#include <boost/multiprecision/mpfr.hpp>  // Defines the Backend type that wraps MPFR
#  include <boost/multiprecision/cpp_dec_float.hpp>
#  include <boost/numeric/odeint.hpp>

//
#  include <iomanip>
#  include <iostream>
//#include <sstream>
//#include <string>

using namespace boost::numeric::odeint;
using namespace std;

/*namespace mp = boost::multiprecision;     // Reduce the typing a bit later...
   typedef mp::number<mp::mpfr_float_backend<300> >  my_float;*/

//http://www.boost.org/doc/libs/1_58_0/libs/numeric/odeint/doc/html/boost_numeric_odeint/tutorial/using_arbitrary_precision_floating_point_types.html
//typedef number<cpp_dec_float<50> > cpp_dec_float_50;
typedef boost::multiprecision::cpp_dec_float_50 float_50;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<30>> cpp_dec_float_30;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<60>> cpp_dec_float_60;

#  if __cplusplus >= 201402L
template<typename T>
constexpr T pi = T(3.141592653589793238462643383);
template<typename T>
T pi_ = T(3.141592653589793238462643383);
#  else
template<class T>
class m {
public:

    const T pi = T(3.141592653589793238462643383);
};

template<class T>
class m_ {
public:

    const T pi = T("3.141592653589793238462643383");
};

#  endif // if __cplusplus >= 201402L

int main(int argc, char* argv[]) {
    const unsigned short prec = 60;
    int div = 1;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Setting precission to " << prec << "." << std::endl;

    std::cout << std::setprecision(prec);

    std::cout << "Template value  is: '" << "3.141592653589793238462643383" << "'." << std::endl;
#  if __cplusplus >= 201402L
    std::cout << "pi<float_60>    is: '" << pi_<cpp_dec_float_60>/ div << "'." << std::endl;
    std::cout << "pi<float_30>    is: '" << pi_<cpp_dec_float_30>/ div << "'." << std::endl;
    std::cout << "pi<long double> is: '" << pi<long double>/ div << "'." << std::endl;
    std::cout << "pi<double>      is: '" << pi<double>/ div << "'." << std::endl;
    std::cout << "pi<float>       is: '" << pi<float>/ div << "'." << std::endl;
    std::cout << "pi<int>         is: '" << pi<int>/ div << "'." << std::endl;
#  else
    std::cout << "pi<float_60>    is: '" << m_<cpp_dec_float_60>().pi / div << "'." << std::endl;
    std::cout << "pi<float_30>    is: '" << m_<cpp_dec_float_30>().pi / div << "'." << std::endl;
    std::cout << "pi<long double> is: '" << m<long double>().pi / div << "'." << std::endl;
    std::cout << "pi<double>      is: '" << m<double>().pi / div << "'." << std::endl;
    std::cout << "pi<float>       is: '" << m<float>().pi / div << "'." << std::endl;
    std::cout << "pi<int>         is: '" << m<int>().pi / div << "'." << std::endl;
#  endif // if __cplusplus >= 201402L

    std::cout << "The end." << std::endl;
} // main

#else // if 1
int main(int argc, char* argv[]) { return 0; }

#endif // if 1
