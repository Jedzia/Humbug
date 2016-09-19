/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      Global definitions, for use in cpp files.
 * \file       defs.h
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

#include <iostream>
/*#include "qtextstream.h"

   //Q_CORE_EXPORT QTextStream &endlw(QTextStream &s);

    QTextStream &endlw(QTextStream &stream) {
        return stream << "\r\n" << "--- FUCK \r\n" << flush;
    };*/

#ifndef QT_VERSION_STR
#  if defined(_MSC_VER)
#    define TMPL_OUTOFLINE_TEMPLATE inline
#  endif
/** Brief description of $(fclass), qDeleteAll
 *  Detailed description.
 *  @param begin TODO
 *  @param end TODO
 */
template<typename ForwardIterator>
TMPL_OUTOFLINE_TEMPLATE void qDeleteAll(ForwardIterator begin, ForwardIterator end){
    while(begin != end) {
        delete *begin;
        ++begin;
    }
}

/** Brief description of $(fclass), qDeleteAll
 *  Detailed description.
 *  @param c TODO
 */
template<typename Container>
inline void qDeleteAll(const Container &c){
    qDeleteAll(c.begin(), c.end());
}

#endif // ifndef QT_VERSION_STR
