#ifndef HumbugLIB_NAMESPACE_FILEDETECTOR_H
#define HumbugLIB_NAMESPACE_FILEDETECTOR_H


#include "HumbugLib/global.h"
//
#include <string>

namespace HumbugLIB_NAMESPACE {

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


} // namespace HumbugLIB_NAMESPACE
#endif
