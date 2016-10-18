/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
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
/*---------------------------------------------------------*/
//#define _SCL_SECURE_NO_WARNINGS 1
//#include <boost/assert.hpp>
//#include <array>
//#include <boost/algorithm/cxx14/equal.hpp>
//#include <boost/array.hpp>
//#include <boost/algorithm/string.hpp>
//#include <boost/multiprecision/mpfr.hpp>  // Defines the Backend type that wraps MPFR
#include <boost/numeric/odeint.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

//
#include <iostream>
#include <iomanip>
//#include <sstream>
//#include <string>

using namespace std;
using namespace boost::numeric::odeint;

/*namespace mp = boost::multiprecision;     // Reduce the typing a bit later...
typedef mp::number<mp::mpfr_float_backend<300> >  my_float;*/

//http://www.boost.org/doc/libs/1_58_0/libs/numeric/odeint/doc/html/boost_numeric_odeint/tutorial/using_arbitrary_precision_floating_point_types.html
//typedef number<cpp_dec_float<50> > cpp_dec_float_50;
typedef boost::multiprecision::cpp_dec_float_50 float_50;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<30> > cpp_dec_float_30;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<60> > cpp_dec_float_60;

template<typename T>
constexpr T pi = T(3.141592653589793238462643383);

template<typename T>
T pi_ = T(3.141592653589793238462643383);

int main(int argc, char* argv[]) {

    const unsigned short prec = 60;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Setting precission to " << prec << "." << std::endl;

    std::cout << std::setprecision(prec);

    std::cout << "Template value  is: '" << "3.141592653589793238462643383" << "'."<< std::endl;
    std::cout << "pi<float_60>    is: '" << pi_<cpp_dec_float_60>/3 << "'."<< std::endl;
    std::cout << "pi<float_30>    is: '" << pi_<cpp_dec_float_30>/3 << "'."<< std::endl;
    std::cout << "pi<long double> is: '" << pi<long double>/3 << "'."<< std::endl;
    std::cout << "pi<double>      is: '" << pi<double>/3 << "'."<< std::endl;
    std::cout << "pi<float>       is: '" << pi<float>/3 << "'."<< std::endl;
    std::cout << "pi<int>         is: '" << pi<int>/3 << "'."<< std::endl;

    std::cout << "The end." << std::endl;
}

