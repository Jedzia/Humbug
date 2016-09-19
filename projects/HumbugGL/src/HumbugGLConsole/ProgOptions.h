/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the declaration of
 *             the ProgOptions class.
 * \folder     $(folder)
 * \file       ProgOptions.h
 * \date       2011-08-11
 * \author     Jedzia.
 *
 * modified    2011-08-21, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef _PROGOPTIONS_H
#define _PROGOPTIONS_H

//#include "../global.h"
//#include <HumbugGLShared/Project/MainOptions.h>
#include <algorithm>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

typedef wchar_t hchar_t;

// A helper function to simplify the main part.
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    std::copy( v.begin(), v.end(), std::ostream_iterator<T>(std::cout, " ") );
    return os;
}

template<class T>
std::wostream& operator<<(std::wostream& os, const std::vector<T>& v) {
    std::copy( v.begin(), v.end(), std::ostream_iterator<T, wchar_t>(std::wcout, L" ") );
    return os;
}

class MainOptions {
};

//!  Command line parser.
/// Parses the command line arguments and prepares a Option struct with
/// the data representation of the command line arguments for easy processing.
class ProgOptions {
private:

    static const char * const DESCR_ALL;
    static const char * const DESCR_GENERAL;
    static const char * const DESCR_OUTPUT;
    static const char * const DESCR_BACKEND;
    static const char * const SUBST_DELIM;

public:

    //! Represents the result of the command line parser.
    enum Result {
        rsOk = 0, ///< Processed without errors.
        rsHelpRequested, ///< Help requested by --help or -h
        rsProgOptionsError, ///< The specified options are not valid.
        rsFatalError, ///< Internal error/exception occured.
        rsNoInputFiles, ///< No input files specified.
        rsNoOutputFiles, ///< No output files specified.
        rsUnknown ///< Unknown error, not initialized. Alarm!
    };

    //! Constructs a new ProgOptions object and parse the command line arguments.
    ProgOptions(int ac, hchar_t* * av);

    //! Destructor
    ~ProgOptions();

    //! Bla
    const hchar_t * language(int x) const;

    //! Gets the parsed command line options.
    inline MainOptions& getPoptions() { return *m_poptions; }

    //! Is true if the command line options are valid.
    inline bool isValid() const { return m_result == rsOk; }

    //! Returns true if the command line options are valid or help is requested.
    inline bool isOk() const { return m_result <= rsHelpRequested; }

    //! Returns true if help was requested by the --help command line switch.
    inline bool isHelpRequested() const { return m_result == rsHelpRequested; }

    inline bool isDebugPrint() const;
    
    inline bool isSimulate() const;

    //! Gets the parse result.
    inline Result getResult() const;

    inline int getDebugLevel() const;

private:

    void initGeneral(boost::program_options::options_description & optionGroup);

    void initInput(boost::program_options::options_description & optionGroup);

    void initOutput(boost::program_options::options_description & optionGroup);

    void initBackend(boost::program_options::options_description & optionGroup);

    Result prepareInputFiles(MainOptions & m_p,
            const boost::program_options::variables_map & vm);

    Result prepareTemplates(MainOptions & m_p,
            const boost::program_options::variables_map & vm);

    //!  Internal preparation of the command line arguments to the Options structure.
    //
    // bool operator!(void) { return IsOk(); }
    Result prepare(int ac, hchar_t* * av, MainOptions & m_p);

    //! Holds the internal Options data.
    MainOptions* m_poptions;

    //! Count of the command line arguments.
    int m_ac;

    //! Hold the raw command line argument data.
    hchar_t* * m_av;

    //! Internal storage for the result of the command line argument preparation.
    Result m_result;

    //! Use debugging output.
    bool mDebug;
    int mDebugLevel;
    bool mSimulate;
};
inline bool ProgOptions::isDebugPrint() const {
    return mDebug;
}

inline bool ProgOptions::isSimulate() const {
    return mSimulate;
}

//! Gets the parse result.
inline ProgOptions::Result ProgOptions::getResult() const {
    return m_result;
}

inline int ProgOptions::getDebugLevel() const {
    return mDebugLevel;
}

#endif // ifndef _PROGOPTIONS_H
