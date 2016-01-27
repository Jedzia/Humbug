/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the VersionToken.cpp class.
 * \file       VersionToken.cpp
 * \date       2016-01-27
 * \author     Jedzia.
 *
 * modified    2016-01-27, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
#include "../stddefs.h"
//
#include "VersionToken.h"
//
//#include <build/cmake/include/debug.h>

namespace humbug {
namespace serialization {
using namespace std;
VersionToken::VersionToken() : m_iMajor(-1), m_iMinor(-1), m_iBuild(-1), m_iRevision(-1) {
    //dbgOut(__FUNCTION__);
}

VersionToken::~VersionToken(void) {
    //dbgOut(__FUNCTION__);
}

const char * VersionToken::Language(int x) const {
    return "AsciiDoc";
}

ostream& operator<<(ostream& o, const VersionToken& obj) {
    o << "Version ";
    
    o << obj.m_iMajor;
    o << ".";
    o << obj.m_iMinor;
    o << ".";
    o << obj.m_iBuild;
    o << ".";
    o << obj.m_iRevision;
    return o;
}

/** @class my_ctypePoint:
 *  Detailed description.
 *  @param i TODO
 *  @param obj TODO
 *  @return TODO
 */
class my_ctypePoint : public ctype<char>{
    mask my_table[table_size];

public:

    my_ctypePoint(size_t refs = 0)
        : ctype<char>(&my_table[0], false, refs) {
        copy_n(classic_table(), table_size, my_table);
        //my_table['-'] = (mask)space;
        //my_table['-'] = (mask)space;
        //my_table['\"'] = (mask)space;
        //my_table[' '] = (mask)alpha;
        //my_table[','] = static_cast<mask>(blank);
        my_table['.'] = static_cast<mask>(space);
    }
};

istream& operator>>(istream& i, VersionToken& obj) {
    const string msgStart = "[std::istream>>VersionToken] ";
    string tmp1, tmp2;
    i >> tmp1;
    transform(tmp1.begin(), tmp1.end(), tmp1.begin(), ::tolower);
    if(tmp1 != "version") {
        string message = msgStart + "First argument is not like [V|v]ersion: '" + tmp1 + "'.";
        throw TokenParsingException(message);
    }

    i >> tmp2;

    if(tmp2.empty()) {
        string message = msgStart + "Version argument is empty. Should be in the form (Major.Minor.Build.Revision).";
        throw TokenParsingException(message);
    }

    stringstream iss(tmp2);
    static locale filterLocale(locale::classic(), new my_ctypePoint);
    iss.imbue(filterLocale);

    vector<string> tokens {
        istream_iterator<string>{
            iss
        },
        istream_iterator<string>{}
    };

    size_t tokensize = tokens.size();
    if(tokensize < 1) {
        string message = msgStart + "Version argument is not valid. Should be in the form (Major.Minor.Build.Revision).";
        throw TokenParsingException(message);
    }

    if (tokensize >= 1) {
        obj.m_iMajor = stoi(tokens[0]);
    }

    if(tokensize >= 2) {
        obj.m_iMinor = stoi(tokens[1]);
    }

    if(tokensize >= 3) {
        obj.m_iBuild = stoi(tokens[2]);
    }

    if(tokensize >= 4) {
        obj.m_iRevision = stoi(tokens[3]);
    }

    if(tokensize >= 5) {
        string message = msgStart + "Version argument is not in the form (Major.Minor.Build.Revision): '" + tmp2 + "'.";
        throw TokenParsingException(message);
    }

    return i;
} // >>
}
}
