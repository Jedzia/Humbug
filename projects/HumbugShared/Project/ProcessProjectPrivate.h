/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the declaration of
 *             the ProcessProjectPrivate class.
 * \folder     $(folder)
 * \file       ProcessProjectPrivate.h
 * \date       2011-08-11
 * \author     Jedzia.
 *
 * modified    2011-08-21, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef _PROCESSPROJECTPRIVATE_H
#define _PROCESSPROJECTPRIVATE_H


// #include "../global.h"
//
#include <vector>
#include <string>

class ProcessProject;
class GB;

//! Private implementation-details of the ProcessProject class.
struct ProcessProjectPrivate {
    //! Construct a ProcessProjectPrivate object.
    /// \param parent The parent ProcessProject object.
    ProcessProjectPrivate(const ProcessProject * parent);

    ~ProcessProjectPrivate();


  private:
    //! Hide copy construction.
    ProcessProjectPrivate(ProcessProjectPrivate & source);

    //! Hide assignment operator.
    ProcessProjectPrivate & operator=(ProcessProjectPrivate & source);

    //! Parrent Object.
    const ProcessProject * p;

    std::vector<std::string> m_LookupPaths;

};
#endif
