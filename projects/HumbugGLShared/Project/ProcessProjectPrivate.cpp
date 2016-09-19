/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the implementation of
 *             the ProcessProjectPrivate class.
 * \folder     $(folder) 
 * \file       ProcessProjectPrivate.cpp
 * \date       2011-08-11
 * \author     Jedzia.
 *
 * modified    2011-08-21, Jedzia
 */
/*---------------------------------------------------------*/


#include "../stdafx.h"
//
#include "ProcessProjectPrivate.h"
#include "ProcessProject.h"
#include <boost/filesystem.hpp>
#include "../GB.h"
//
#include <build/cmake/include/debug.h>



namespace fs=boost::filesystem;

//! Construct a ProcessProjectPrivate object.
/// \param parent The parent ProcessProject object.
ProcessProjectPrivate::ProcessProjectPrivate(const ProcessProject * parent) 
: p(parent) {
  m_LookupPaths.push_back(GB::getProjectDirectory());
  m_LookupPaths.push_back(GB::getTemplateDirectory());
  //m_LookupPaths.push_back(GB::getWorkDirectory());
}

ProcessProjectPrivate::~ProcessProjectPrivate() {
}

