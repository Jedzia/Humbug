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
/*---------------------------------------------------------*/
#define _SCL_SECURE_NO_WARNINGS 1
#include <boost/assert.hpp>
#include <array>
#include <boost/algorithm/cxx14/equal.hpp>
#include <boost/array.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include <string>

inline void TestArrayFoo() {
    std::array<int, 9> marr;
    marr[0] = 123456;

    boost::array<int, 4> a = { { 1, 2, 3 } };
    boost::array<int, 4> b = { 1, 2, 3 };

    auto seq1 = { 0, 1, 2 };
    auto seq2 = { 0, 1, 2, 3, 4 };
     
    bool r1 = std::equal(seq1.begin(), seq1.end(), seq2.begin()); // true
    //bool r2 = std::equal(seq2.begin(), seq2.end(), seq1.begin()); // Undefined behavior
    bool r3 = boost::algorithm::equal(seq1.begin(), seq1.end(), seq2.begin(), seq2.end()); // false
}

int main(int argc, char* argv[]) {
    int x = 42;
    x++;
    BOOST_ASSERT(x == 42);
    TestArrayFoo();
    std::cout << "The end." << std::endl;
}
