/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the declaration of
 *             the ProcessProject class.
 * \folder     $(folder)
 * \file       ProcessProject.h
 * \date       2011-09-17
 * \author     Jedzia.
 *
 * modified    2011-09-17, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef _PROCESSPROJECT_H
#define _PROCESSPROJECT_H


#include "../global.h"
//
#include <vector>
#include <string>
#include <CppStructz/config/ConfigOptionList.h>
#include <boost/scoped_ptr.hpp>

//
class GB;
struct ProcessProjectPrivate;
namespace CPPSTRUCTZ_NAMESPACE { namespace config { class ConfigString; }  } 

//! Handle the processing of a complete template-project.
/// Here is a short example, how the ProcessProject class
/// can be used. 
/// Example:
///
/// \include code/ProcessProject-main.cpp
class ProcessProject {
  public:
    //! Command to execute by the main processing unit.
    enum ProcessingMode {
      pmUnknown = 0,///< Wrong or no processing-mode detected.
      pmFiles,///< Use multiple files.
      pmProject,///< Input files are specified by a project-file.
      pmListProjects///< Input files are specified by a project-file.

    };

    //! Holds the parsed command line options.
    struct Options {
        //! The input files specified on the command-line.
        std::vector<std::string> inputfiles;

        //! The name of the project-file if specified.
        std::string outfile;

        //! The name of the project-file if specified.
        std::string projectfile;

        //! Project or multiple file processing is wanted. 
        ProcessingMode processingMode;

        //! The initial working directory.
        std::string cwd;

        //! Contains the list of ConfigOption's.
        CPPSTRUCTZ_NAMESPACE::config::ConfigOptionList * optionList;

        Options();

        ~Options();

    };
    
    //! Constructs a ProcessProject project-processor object. 
    /// \param cmdOptions The specified processing options.
    ProcessProject(const Options * cmdOptions);

    ~ProcessProject();

    //! Starts processing of the project elements.
    void run();


  private:
    //! Hide and prevent copy construction. No implementation.
    ProcessProject(ProcessProject & source);

    //! Hide and disable assignment operator. No implementation.
    ProcessProject & operator=(ProcessProject & source);

    //! Stored project-options
    const Options * options;

    //! Private implementation.
    boost::scoped_ptr<ProcessProjectPrivate> d;

};
#endif
