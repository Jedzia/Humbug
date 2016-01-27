/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Token.h class.
 * \file       Token.h
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

#include "../global.h"
//
#include <exception>
#include <string>
//

namespace humbug {
namespace serialization {
/** @class TokenParsingException:
 *  Detailed description.
 */
class TokenParsingException : public std::exception
{
public:
    explicit TokenParsingException(const std::string & what_arg);
};

/** @class Token:
 *  Detailed description.
 */
class Token {
public:

    Token();
    virtual ~Token();

    /** Token, Str:
     *  Detailed description.
     *  @return TODO
     */
    std::string Str() const { return str; }

    /** Token, Str:
     *  Detailed description.
     *  @param val TODO
     */
    void Str(std::string val) { str = val; }

    /** Token, Language:
     *  Detailed description.
     *  @param x TODO
     *  @return TODO
     */
    virtual const char * Language(int x) const;

private:

    int i;
    std::string str;
};
}
}
