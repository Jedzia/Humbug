
#include "../stdafx.h"
#include "ProjectNode.h"

ProjectNode::ProjectNode(ProjectNode::Type type, std::string & str) {

	this->type = type;
	this->str = str;
	parent = 0;
	//nodecount++;
	//dbgOut(__FUNCTION__ << " [" << nodecount << "]" << std::endl);
}

ProjectNode::~ProjectNode(){

	//dbgOut(__FUNCTION__ << " [" << nodecount << "]" << std::endl);
	//nodecount--;
	qDeleteAll(children);
}

