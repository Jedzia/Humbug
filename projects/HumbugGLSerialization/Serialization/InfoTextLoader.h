/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the InfoTextLoader.h class.
 * \file       InfoTextLoader.h
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

#include "../global.h"
//
#include "VersionToken.h"
#include <boost/function.hpp>
#include <string>

//

namespace humbug {
namespace serialization {
/** @class InfoTextLoader:
 *  Detailed description.
 */
class InfoTextLoader {
public:

    typedef std::string LinedataElement;

    struct InfoCTextLoaderData
    {
        InfoCTextLoaderData(/*const LinedataElement& data, const bool is_comment = false*/)
            : /*data(data),*/ isComment(false) {}

        std::string typeId;
        std::string line;
        std::vector<LinedataElement> data;
        bool isComment;
    };

    typedef InfoCTextLoaderData LinedataType;
    typedef boost::function<void (const LinedataType& parsedLineData)> LdataFunc;

    static bool ReadAndSplitTextLineByComma(std::istream& instream, LinedataType& parsedLineData);

    //void OnComment(const LinedataType& parsedLineData);
    //void OnParsed(const LinedataType& parsedLineData);

    /** Brief description of InfoTextLoader, OnParsed
    *  Detailed description.
    *  @param func TODO
    */
    void OnComment(LdataFunc func){
        m_fOnComment = func;
    }

    /** Brief description of InfoTextLoader, OnParsed
     *  Detailed description.
     *  @param func TODO
     */
    void OnParsed(const LdataFunc func){
        m_fOnParsed = func;
    }

    /** Brief description of InfoTextLoader, Version
     *  Detailed description.
     *  @return TODO
     */
    VersionToken Version() const {
        return m_vVersion;
    }

    friend std::ostream& operator<<(std::ostream& out, const InfoTextLoader& obj);
    friend std::istream& operator>>(std::istream& in, InfoTextLoader& obj);

private:

    std::string str;
    LdataFunc m_fOnComment;
    LdataFunc m_fOnParsed;
    VersionToken m_vVersion;
};
}
}
