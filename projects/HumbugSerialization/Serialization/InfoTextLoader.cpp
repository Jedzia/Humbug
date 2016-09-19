/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the InfoTextLoader.cpp class.
 * \file       InfoTextLoader.cpp
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
#include "../stddefs.h"
//
#include "InfoTextLoader.h"
//
#include "VersionToken.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/function.hpp>
#include <boost/tokenizer.hpp>
#include <boost/variant.hpp>
#include <iterator>
#include <regex>
#include <vector>
//
//#include <build/cmake/include/debug.h>

namespace humbug {
namespace serialization {
/** @class my_ctypeIgnore:
 *  Detailed description.
 *  @param str TODO
 *  @param maxNum TODO
 *  @return TODO
 */
class my_ctypeIgnore : public
                       std::ctype<char>{
    mask my_table[table_size];

public:

    my_ctypeIgnore(size_t refs = 0)
        : ctype<char>(&my_table[0], false, refs) {
        std::copy_n(classic_table(), table_size, my_table);
        //my_table['-'] = (mask)space;
        //my_table['-'] = (mask)space;
        //my_table['\"'] = (mask)space;
        //my_table[' '] = static_cast<mask>(alpha);
        my_table['"'] = static_cast<mask>(blank);
        my_table[';'] = static_cast<mask>(blank);
        //my_table[';'] = static_cast<mask>(space);
    }
};

bool InfoTextLoader::ReadAndSplitTextLineByComma(std::istream& instream, LinedataType& parsedLineData) {
    using namespace boost;
    std::string tmp1, line;

    instream >> tmp1;
    trim(tmp1);
    parsedLineData.line = tmp1;
    parsedLineData.typeId = tmp1;
    if(!tmp1.empty() && tmp1[0] == '#') {
        //auto nc = instream.peek();
        getline(instream, line);
        parsedLineData.line += line;
        trim(line);

        //cout << "Comment: " << line << endl;
        parsedLineData.data.push_back(line);
        parsedLineData.isComment = true;
        return true;
    }

    //std::string line = newstr;
    getline(instream, line);
    parsedLineData.line += line;

    //std::vector<std::string> parsedLineData;
    tokenizer<escaped_list_separator<char>> tk(
            line, escaped_list_separator<char>('\\', ',', '\"'));

    for(tokenizer<escaped_list_separator<char>>::iterator i(tk.begin());
        i != tk.end(); ++i)
    {
        auto val = *i;
        static std::locale x(std::locale::classic(), new my_ctypeIgnore);
        //lineStream.imbue(x);
        trim(val, x);

        parsedLineData.isComment = false;
        parsedLineData.data.push_back(val);
    }

    return !parsedLineData.data.empty();
} // ReadAndSplitTextLineByComma

std::ostream& operator<<(std::ostream& out, const InfoTextLoader& obj) {
    return out;
}

std::istream& operator>>(std::istream& in, InfoTextLoader& obj) {
    using namespace humbug::serialization;
    using namespace std;

    const string msgStart = "[std::istream>>InfoTextLoader] ";

    string tmp1, tmp2;

    in >> tmp1;
    if(tmp1 != "InfoCText") {
        string message = msgStart + "First argument is not like <InfoCText>: '" + tmp1 + "'.";
        throw TokenParsingException(message);
    }

    in >> obj.m_vVersion;
    InfoTextLoader::LinedataType linedata;

    for(size_t lnr = 1; InfoTextLoader::ReadAndSplitTextLineByComma(in, linedata); lnr++)
    {
        if(linedata.isComment) {
            //stdcOut("[" << setfill('0') << setw(3) << lnr << "]Comment: " << linedata.line);
            if(obj.m_fOnComment) {
                obj.m_fOnComment(linedata);
            }
        }
        else {
            //stdcOut("[" << setfill('0') << setw(3) << lnr << "]Data   : (" << linedata.data.size()
            // << ") " << linedata.line);
            // parse the stuff
            if(obj.m_fOnParsed) {
                obj.m_fOnParsed(linedata);
            }
        }

        linedata.data.clear();
    }

    in >> tmp2;
    if(!tmp2.empty()) {
        string message = msgStart + "Extra characters after line parse: '" + tmp2 + "'.";
        throw TokenParsingException(message);
    }

    //in >> tmp3;
    //in >> tmp4;
    //in >> tmp5;

    return in;
} // >>
}
}
