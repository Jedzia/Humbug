/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the defs.h class.
 * \folder     $(folder)
 * \file       defs.h
 * \date       2011-08-11
 * \author     Jedzia.
 *
 * modified    2011-08-21, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef DEFS_H
#define DEFS_H
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
template <typename ForwardIterator>
TMPL_OUTOFLINE_TEMPLATE void qDeleteAll(ForwardIterator begin, ForwardIterator end)
{
    while (begin != end) {
        delete *begin;
        ++begin;
    }
}

template <typename Container>
inline void qDeleteAll(const Container &c)
{
    qDeleteAll( c.begin(), c.end() );
}

#endif // ifndef QT_VERSION_STR
#endif // ifndef DEFS_H
