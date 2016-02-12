
#include "../stdafx.h"
#include "ProjectParser.h"

#include "ProjectNode.h"
#include "ProjectProcessor.h"
#include <project.hxx>

ProjectNode * ProjectParser::parse(const std::string & fileName) {

	ProjectNode *node = new ProjectNode(ProjectNode::Root);
	if (fileName.isEmpty())
	{
		return node;
	}

	xml_schema::properties p = xml_schema::properties();
	p.no_namespace_schema_location("D:/E/Projects/C++/Humbug/projects/Humbug/XSD/project.xsd");
	project_type tmplProject(project_(fileName.toStdString(),0, p));
	ProjectProcessor cp(tmplProject);

	dbgOut(fileName.toStdString() << std::endl);

	return cp.run();
	/* exit 
    in = expr;
    in.replace(" ", "");
    pos = 0;

    addChild(node, parseOrExpression());
    return node;*/
}

void ProjectParser::addChild(ProjectNode * parent, ProjectNode * child) {
    if (child) {
        parent->children += child;
        parent->str += child->str;
        child->parent = parent;
    }
}

