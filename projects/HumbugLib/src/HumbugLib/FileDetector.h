/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the FileDetector.h class.
 * \folder     $(folder)
 * \file       FileDetector.h
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HumbugLIB_NAMESPACE_FILEDETECTOR_H
#define HumbugLIB_NAMESPACE_FILEDETECTOR_H

#include <HumbugLib/global.h>
//
#include <string>

namespace humbuglib {
  class FileDetector {
public:

      enum FileType {
          ftUnknown = 0,
          ftError,
          ftText,
          ftZip,
          ftRar
      };

      FileDetector(const std::string & filename);

      ~FileDetector();

      //! Returns the detected file type.
      inline const FileType getType() const;

private:

      FileType identify(std::ifstream & input_file);

      FileType m_type;
  };

//! Returns the detected file type.
  inline const FileDetector::FileType FileDetector::getType() const {
      return m_type;
  }

  HumbugLIB_END_NAMESPACE
#endif // ifndef HumbugLIB_NAMESPACE_FILEDETECTOR_H
