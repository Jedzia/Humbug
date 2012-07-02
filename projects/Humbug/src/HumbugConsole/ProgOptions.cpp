/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the implementation of
 *             the ProgOptions class.
 * \folder     $(folder)
 * \file       ProgOptions.cpp
 * \date       2011-08-11
 * \author     Jedzia.
 *
 * modified    2011-08-21, Jedzia
 */
/*---------------------------------------------------------*/
#include "ProgOptions.h"
#include "HumbugConsole/stdafx.h"
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>

//#include <CppStructz/config/ConfigOptionList.h>
//#include <CppStructz/config/ConfigString.h>

//#include <CppStructz/log/LogHelper.h>
//using namespace CPPSTRUCTZ_NAMESPACE::config;
using namespace boost;
using namespace std;
namespace po = boost::program_options;
const char * const ProgOptions::DESCR_ALL = "Allowed options";
const char * const ProgOptions::DESCR_GENERAL = "General options";
const char * const ProgOptions::DESCR_OUTPUT = "Output options";
const char * const ProgOptions::DESCR_BACKEND = "Backend options";
const char * const ProgOptions::SUBST_DELIM = "=";

//#include <build/cmake/include/debug.h>
ProgOptions::ProgOptions(int ac, char* * av) :
    mDebug(false),
    mDebugLevel(0),
    m_ac(ac),
    m_av(av),
    m_poptions(new MainOptions)   {
    dbgOut(__FUNCTION__ << std::endl);
    //m_poptions->processingMode = ProcessProject::pmUnknown;

    //(m_poptions.optionList).reset(new ConfigOptionList());
    //m_poptions->optionList = new ConfigOptionList;
    //m_poptions->optionList->addOption( new ConfigString("Code", "MyCodeTempl", "Template") );
    m_result = prepare(m_ac, m_av, *m_poptions);
}

//! Destructor
ProgOptions::~ProgOptions(){
    //delete (m_poptions->optionList);
    //m_poptions->optionList = NULL;
    delete (m_poptions);
    dbgOut(__FUNCTION__ << std::endl);
}

//! Bla
const char * ProgOptions::language(int x) const {
    return "AsciiDoc";
}

void ProgOptions::initGeneral(boost::program_options::options_description & optionGroup) {
    optionGroup.add_options()
        ("help,h", "produce a help message")

    //("help-module", value<string>()->implicit(),
    //("help-module", po::wvalue<wstring>(),
        ("help-module", po::value<string>()->implicit_value( string("list") ),
        "produce a help for a given module")
        ("version", "output the version number")

    //("vfatal", "verbosity level: display only fatal errors.")
        ("verror", "verbosity level: display errors.")
        ("vwarn", "verbosity level: display warn messages.")
        ("vinfo", "verbosity level: display info messages.")
        ("vdebug,v", "verbosity level: display debug messages.")
        ("vtrace", "verbosity level: display trace messages.")
        ("input-file", po::value< vector<string> >(), "input file")
        ("project-file", po::value< string >(), "project file")
        ("subst", po::value< vector<string> >(), "template substitution. "
        "Example: \n--subst \"TEMPLATE=This is my replacement text\"")
    ;
} // initGeneral

void ProgOptions::initInput(boost::program_options::options_description & optionGroup) {
    optionGroup.add_options()
        ("input-xxx", po::value< vector<string> >(), "input xxx ")
    ;
}

void ProgOptions::initOutput(boost::program_options::options_description & optionGroup) {
    optionGroup.add_options()
        ("display", po::wvalue<wstring>(), "display to use")
        ("outfile,o", po::value<string>(), "Filename for the output")
    ;
}

void ProgOptions::initBackend(boost::program_options::options_description & optionGroup) {
    optionGroup.add_options()
        ("num-threads", po::wvalue<int>(), "the initial number of threads")
    ;
}

ProgOptions::Result ProgOptions::prepareInputFiles(MainOptions & m_p,
        const boost::program_options::variables_map & vm) {
    if ( vm.count("project-file") && vm.count("input-file") ) {
        return rsProgOptionsError;
    }

    if ( vm.count("input-file") ) {
        //m_p.inputfiles = vm["input-file"].as< vector<string> >();
        //csz::dbg << _T("Input files are: ") <<
        //m_p.inputfiles << LOGGER_ENDMSG;
        //m_p.processingMode = ProcessProject::pmFiles;
    }

    if ( vm.count("project-file") ) {
        //m_p.projectfile = vm["project-file"].as<string>();
        //m_p.processingMode = ProcessProject::pmProject;
    }

    //if (m_p.processingMode == ProcessProject::pmUnknown) {
    //    return rsNoInputFiles;
    //}

    return rsOk;
} // prepareInputFiles

ProgOptions::Result ProgOptions::prepareTemplates(MainOptions & m_p,
        const boost::program_options::variables_map & vm) {
    if ( !vm.count("subst") ) {
        return rsNoInputFiles;
    }

    const vector<string>& templates = vm["subst"].as< vector<string> >();
    int cnt = 1;

    for( vector<string>::const_iterator i = templates.begin(),
         end = templates.end();
         i != end; ++i )
    {
        const std::string& item = (*i);
        string::size_type tpos = item.find_first_of(SUBST_DELIM);
        string templateStr(item, 0, tpos);
        string substituteStr( item, tpos + 1, item.length() );
        //ConfigString* s = new ConfigString(templateStr, substituteStr, "Templates");
        //m_p.optionList->addOption(s);
        cnt++;
    }
    return rsOk;
} // prepareTemplates

//!  Internal preparation of the command line arguments to the Options structure.
//
// bool operator!(void) { return IsOk(); }
ProgOptions::Result ProgOptions::prepare(int ac, char* * av, MainOptions & m_p) {
    try {
        //csz::dbg << "Static debug message, Prepare Options " << LOGGER_ENDMSG;

        // Declare three groups of options.
        po::options_description general(DESCR_GENERAL);
        initGeneral(general);
        po::options_description output(DESCR_OUTPUT);
        initOutput(output);
        po::options_description backend("Backend options");
        initBackend(backend);

        // Declare an options description instance which will include
        // all the options
        po::options_description all(DESCR_ALL);
        all.add(general).add(output).add(backend);

        // Declare an options description instance which will be shown
        // to the user
        po::options_description visible(DESCR_ALL);
        visible.add(general).add(output);
        po::positional_options_description p;
        p.add("input-file", -1);

        // Process input data.
        //store(parse_command_line(ac, av, all), vm);
        po::variables_map vm;
        po::store(po::command_line_parser(ac, av).
                options(all).positional(p).run(), vm);
        po::notify(vm);

        // debugging level and display detail.
        if ( vm.count("vdebug") ) {
            cout << "Juhu, vdebug gewaehlt" << std::endl;
            mDebug = true;
            mDebugLevel = 5;
        }
        else if ( vm.count("vtrace") )   {
            cout << "Juhu, vtrace gewaehlt" << std::endl;
            mDebug = true;
            mDebugLevel = 6;
        }

        // help options
        if ( vm.count("help") ) {
            cout << visible;
            return rsHelpRequested;
        }

        // detailed help display
        if ( vm.count("help-module") ) {
            const string& s = vm["help-module"].as<string>();

            //if ( s == _T("output") ) {
            if ( s == "list" ) {
                cout << "List of help-modules: output backend" << endl;
            }
            else if ( s == "output" )   {
                cout << output;
            }
            else if ( s == "backend" )   {
                cout << backend;
            }
            else {
                cout << "Unknown module '" <<
                s << "' in the --help-module option\n";
                return rsProgOptionsError;
            }

            return rsHelpRequested;
        }

        if ( vm.count("num-threads") ) {
            wcout << _T("The 'num-threads' options was set to ") <<
            vm["num-threads"].as<int>() << "\n";
        }

        if ( vm.count("num-threads") ) {
            wcout << _T("The 'num-threads' options was set to ") <<
            vm["num-threads"].as<int>() << "\n";
        }

        if ( vm.count("display") ) {
            //wcout << L"The 'display' option was set to "
            wcout << _T("The 'display' option was set to ") <<
            vm["display"].as<wstring>() << "\n";
        }

        // Prepare input parameters
        Result inResult = prepareInputFiles(m_p, vm);

        if ( inResult != rsOk) {
            cout << visible;
            cout << endl;
            cout << "You have to specify a project-file OR input-file(s) on the command line." <<
            endl;
            return inResult;
        }

        // Prepare output parameters
        if ( vm.count("outfile") ) {
            //wcout << L"The 'display' option was set to "
            cout << "The 'outfile' option was set to " <<
            vm["outfile"].as<string>() << "\n";
            //m_p.outfile = vm["outfile"].as<string>();
            //m_p.optionList->addOption( new ConfigString("OutFile", m_p.outfile, "Templates") );
        }

        // check for valid output parameters.
        //if ( m_p.processingMode == ProcessProject::pmFiles && m_p.outfile.empty() ) {
        //    return rsNoOutputFiles;
        //}

        inResult = prepareTemplates(m_p, vm);
    }
    catch (std::exception& e) {
        cout << ">> " << e.what() << " <<\n";
        return rsFatalError;
    }
    return rsOk;
} // prepare

