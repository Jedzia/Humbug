
#include "../stdafx.h"
#include "ProjectProcessor.h"
#include "ProjectNode.h"

// Todo: implement a project manager

ProjectProcessor::ProjectProcessor(const project_type & tmplProject)
: subcount(0), tmplProject(tmplProject)
{


}

ProjectProcessor::~ProjectProcessor(){

}

ProjectNode * ProjectProcessor::run(ProjectNode * root) {

	if (root == NULL)
	{
		root = new ProjectNode(ProjectNode::Root, "Root");
	}
	//root->children += new ProjectNode(ProjectNode::File, "Moese");
	project::folder_sequence& folders = tmplProject->folder();
	project::file_sequence& files = tmplProject->file();
	processFolder(folders, root);
	processFile(files, root);
	return root;
}

ProjectNode * ProjectProcessor::test(ProjectNode * root)
{

	if (root == NULL)
	{
		root = new ProjectNode(ProjectNode::Root, "Root");
	}
	addChild(root, new ProjectNode(ProjectNode::File, "Moese"));
	ProjectNode* subfolder = new ProjectNode(ProjectNode::Folder, "SubFolder");
	addChild(root, subfolder);
	addChild(subfolder, new ProjectNode(ProjectNode::File, "SubFolder.file"));
	addChild(subfolder, new ProjectNode(ProjectNode::File, "SubFolder.file2"));

	subfolder = new ProjectNode(ProjectNode::Folder, "OtherSubFolder");
	addChild(root, subfolder);
	addChild(subfolder, new ProjectNode(ProjectNode::File, "OtherSubFolder.file"));
	addChild(subfolder, new ProjectNode(ProjectNode::File, "OtherSubFolder.file2"));

	return root;
}

void ProjectProcessor::processFile(const folderType::file_sequence & files, ProjectNode * parrent, int level) {

	for( folderType::file_const_iterator i(files.begin());
		i != files.end();
		++i )
	{
		// Element "greeting" und Element "name" ausgeben
		indent(level);
		dbgOut("folderType File: [" << level << "] " << i->name() << std::endl);
		ProjectNode *curFile = new ProjectNode(ProjectNode::File, QString::fromStdString(i->name()));
		addChild(parrent, curFile);
	}
}

//void ProcessFolder( project::folder_sequence &folders );
void ProjectProcessor::processFolder(const folderType::folder_sequence & folders, ProjectNode * parrent, int level) {
 
	folderType::folder_const_iterator i(folders.begin());
	for(; i != folders.end(); ++i )
	{
		//dbgOut(std::cout << "folderType Folder: [" << level << "] " << i->name() << std::endl);
		indent(level);
		dbgOut("folderType Folder: [" << level << "] " << i->name() << std::endl);
		ProjectNode *curFolder = new ProjectNode(ProjectNode::Folder, QString::fromStdString(i->name()));
		addChild(parrent, curFolder);
		processFolder(i->folder(), curFolder, level + 1);
		processFile(i->file(), curFolder, level);
		//ProcessFile(static_cast<const project::file_sequence>(i->file()));
	}
}

void ProjectProcessor::indent(int level) {

	for (int i = 0; i < level ; i++)
	{
		dbgOut("\t");
	}
}

void ProjectProcessor::addChild(ProjectNode * parent, ProjectNode * child)
{
	if (child) {
		parent->children += child;
		parent->str += child->str;
		child->parent = parent;
		child->toolTip = "toolTipText: " + child->str;
	}
}

