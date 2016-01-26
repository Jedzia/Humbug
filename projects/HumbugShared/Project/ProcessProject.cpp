/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the implementation of
 *             the ProcessProject class.
 * \folder     $(folder)
 * \file       ProcessProject.cpp
 * \date       2011-09-17
 * \author     Jedzia.
 *
 * modified    2011-09-17, Jedzia
 */
/*---------------------------------------------------------*/


#include "../stdafx.h"
//
#include "ProcessProject.h"
#include "HumbugShared/GB.h"
#include "HumbugShared/Project/ProcessProjectPrivate.h"
#include <boost/filesystem.hpp>
#include <CppStructz/config/ConfigString.h>

ProcessProject::Options::Options() {
  LOG_DEBUG("++CONSTRUCT++");
}

ProcessProject::Options::~Options() {
  LOG_DEBUG("--DESTRUCT--");
}

//! Constructs a ProcessProject project-processor object. 
/// \param cmdOptions The specified processing options.
ProcessProject::ProcessProject(const ProcessProject::Options * cmdOptions) 
  : d(new ProcessProjectPrivate(this)), options(cmdOptions) {
}

ProcessProject::~ProcessProject() {
}

//! Starts processing of the project elements.
void ProcessProject::run() {
}

