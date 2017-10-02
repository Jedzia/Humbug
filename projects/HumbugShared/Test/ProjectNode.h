#ifndef _PROJECTNODE_H
#define _PROJECTNODE_H


#include "../global.h"
#include "../Project/ProjectNode.h"
#include <string>
#include <list>

class ProjectNode {
  public:
    enum Type {
      Root,
      Folder,
      File,
      OrExpression,
      AndExpression,
      NotExpression,
      Atom,
      Identifier,
      Operator,
      Punctuator

    };

    ProjectNode(ProjectNode::Type type, std::string & str = std::string(""));

    ~ProjectNode();

    Type type;

    std::string str;

    std::string toolTip;

    ProjectNode * parent;

    std::list<ProjectNode*> children;

};
#endif
