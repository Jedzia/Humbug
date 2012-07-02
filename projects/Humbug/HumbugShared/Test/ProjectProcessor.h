#ifndef _PROJECTPROCESSOR_H
#define _PROJECTPROCESSOR_H


#include "../global.h"
#include <memory>

#include <project.hxx>
class ProjectNode;

typedef ::std::auto_ptr< ::project > project_type;
class ProjectProcessor {
  public:
    ProjectProcessor(const project_type & tmplProject);

    ~ProjectProcessor();

    ProjectNode * run(ProjectNode * root = NULL);

    static ProjectNode * test(ProjectNode * root = NULL);


  private:
    void processFile(const folderType::file_sequence & files, ProjectNode * parrent, int level = 0);

    //void ProcessFolder( project::folder_sequence &folders );
    void processFolder(const folderType::folder_sequence & folders, ProjectNode * parrent, int level = 0);

    void indent(int level);

    static void addChild(ProjectNode * parent, ProjectNode * child);

    int subcount;

    const project_type & tmplProject;

};
#endif
