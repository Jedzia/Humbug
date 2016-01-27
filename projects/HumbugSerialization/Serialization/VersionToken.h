/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the VersionToken.h class.
 * \file       VersionToken.h
 * \date       2016-01-27
 * \author     Jedzia.
 *
 * modified    2016-01-27, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

#include "../global.h"
//
#include "Token.h"
#include <string>

//

namespace humbug {
namespace serialization {
/** @class VersionToken:
 *  Detailed description.
 */
class VersionToken : public Token {
public:

    VersionToken();
    ~VersionToken();

    /** VersionToken, BlaStr:
     *  Detailed description.
     *  @return TODO
     */
    std::string BlaStr() const { return str; }

    /** VersionToken, BlaStr:
     *  Detailed description.
     *  @param val TODO
     */
    void BlaStr(std::string val) { str = val; }

    /** VersionToken, Language:
     *  Detailed description.
     *  @param x TODO
     *  @return TODO
     */
    const char * Language(int x) const override;


    friend std::ostream& operator<<(std::ostream& o, const VersionToken& obj);

    friend std::istream& operator>>(std::istream& i, VersionToken& obj);

private:

    int m_iMajor;
    int m_iMinor;
    int m_iBuild;
    int m_iRevision;
    std::string str;
};
}
}
