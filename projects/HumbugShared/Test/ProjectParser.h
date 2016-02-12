#ifndef _PROJECTPARSER_H
#define _PROJECTPARSER_H


#include "../global.h"
#include <string>

class ProjectNode;

class ProjectParser {
  public:
    ProjectNode * parse(const std::string & fileName);


  private:
    void addChild(ProjectNode * parent, ProjectNode * child);

    std::string in;

    int pos;

};
#endif
