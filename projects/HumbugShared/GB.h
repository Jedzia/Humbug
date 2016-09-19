#ifndef _GB_H
#define _GB_H


// #include "global.h"
#include <string>

class GB {
  public:
    static inline std::string getProjectDirectory();

    static inline std::string getProjectExtension();

    static inline const std::string getTemplateDirectory();


  private:
    //! Path to the project directory
    static std::string projectDirectory;

    static std::string projectExtension;

    //! Path to the project directory
    static std::string templateDirectory;

};
inline std::string GB::getProjectDirectory()
{
  return projectDirectory;
}

inline std::string GB::getProjectExtension()
{
  return projectExtension;
}

inline const std::string GB::getTemplateDirectory()
{
  return templateDirectory;
}

#endif
