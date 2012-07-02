
#include "../stdafx.h"
#include "src/Project/ProjectModel.h"

ProjectModel::ProjectModel(QObject * parent)
: QAbstractItemModel(parent)
{

	rootNode = NULL;
	QHash<int, QByteArray> roles = this->roleNames();
	roles.insertMulti(ProjectModel::FileIconRole, "fileIcon"); // == Qt::decoration
	roles.insert(ProjectModel::FilePathRole, "filePath");
	roles.insert(ProjectModel::FileNameRole, "fileName");
}

ProjectModel::~ProjectModel(){

    if(rootNode != NULL)
        delete rootNode;
}

void ProjectModel::setRootNode(ProjectNode * node) {

    if(rootNode != NULL)
        delete rootNode; 
    rootNode = node;
    reset();
}

QModelIndex ProjectModel::index(int row, int column, const QModelIndex & parent) const {

	if (!rootNode || row < 0 || column < 0)
		return QModelIndex();
//	ProjectNode *parentNode = nodeFromIndex(parent);
//	ProjectNode *childNode = parentNode->children[row];
//	if (!childNode)
//		return QModelIndex();
//	return createIndex(row, column, childNode);
}

QModelIndex ProjectModel::parent(const QModelIndex & child) const {
  
/*  ProjectNode *node = nodeFromIndex(child);
  if (!node)
  	return QModelIndex();
  ProjectNode *parentNode = node->parent;
  if (!parentNode)
  	return QModelIndex();
  ProjectNode *grandparentNode = parentNode->parent;
  if (!grandparentNode)
  	return QModelIndex();
  
  int row = indexOfNode(grandparentNode, parentNode);
  return createIndex(row, 0, parentNode);
  */
  	return QModelIndex();
}

int ProjectModel::rowCount(const QModelIndex & parent) const {
/*
	if (parent.column() > 0)
		return 0;
	ProjectNode *parentNode = nodeFromIndex(parent);
	if (!parentNode)
		return 0;
	return parentNode->children.size();
    */
    return 1;
}

int ProjectModel::columnCount(const QModelIndex & parent) const {

	return 2;
}

QVariant ProjectModel::data(const QModelIndex & index, int role) const {

/*
	//	if (role == Qt::ToolTipRole)
	//		return QVariant();

	//	if (role == Qt::DisplayRole)
	ProjectNode *node = nodeFromIndex(index);
	if (!node)
		return QVariant();

	switch (role)
	{
	case FileIconRole:
		return getIcon(node);
		break;
	case Qt::TextColorRole:
		switch (node->type)
		{
		case ProjectNode::Root:
			return tr("Root");
		case ProjectNode::Folder:
			return QColor("Red");
		case ProjectNode::File:
			return QColor("Green");
			break;
		}
		break;
	case Qt::ToolTipRole:
		return getTooltipRole(node);
	case Qt::DisplayRole:
		return getDisplayRole(index, node);
	}
    */
	return QVariant();
}

QVariant ProjectModel::headerData(int section, Qt::Orientation orientation, int role) const {

	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		if (section == 0) {
			return tr("ProjectNode");
		} else if (section == 1) {
			return tr("Value");
		}
	}
	return QVariant();
}

QVariant ProjectModel::getIcon(ProjectNode * node) const {
/*
	//dbgOut("------------->FileIconRole called");
	switch (node->type)
	{
		//case ProjectNode::Root:
		//	return tr("Root");
	case ProjectNode::Folder :
		{
			QIcon icon2;
			icon2.addFile(QString::fromUtf8(":/icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
			return icon2;
		}
	case ProjectNode::File :
		{
			QIcon icon3;
			icon3.addFile(QString::fromUtf8(":/icons/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
			return icon3;
		}
	default:
		return QVariant();
	}
    */
		return QVariant();
}

ProjectNode * ProjectModel::nodeFromIndex(const QModelIndex & index) const {

	if (index.isValid()) {
		return static_cast<ProjectNode *>(index.internalPointer());
	} else {
		return rootNode;
	}
}

QVariant ProjectModel::getDisplayRole(const QModelIndex & index, ProjectNode * node) const {

    /*
	if (index.column() == 0)
	{
		switch (node->type)
		{
		case ProjectNode::Root:
			return tr("Root");
		case ProjectNode::Folder:
			return tr("Folder");
		case ProjectNode::File:
			return tr("File");
		case ProjectNode::OrExpression:
			return tr("OR Expression");
		case ProjectNode::AndExpression:
			return tr("AND Expression");
		case ProjectNode::NotExpression:
			return tr("NOT Expression");
		case ProjectNode::Atom:
			return tr("Atom");
		case ProjectNode::Identifier:
			return tr("Identifier");
		case ProjectNode::Operator:
			return tr("Operator");
		case ProjectNode::Punctuator:
			return tr("Punctuator");
		default:
			return tr("Unknown");
		}
	} else if (index.column() == 1) {
		return QString::fromStdString(node->str);
	}
    */
	return QVariant();
}
/*
QVariant ProjectModel::getTooltipRole(ProjectNode * node) const {

	//if (index.column() == 0) {
	//} else if (index.column() == 1) {
	return QString::fromStdString(node->toolTip);
	//}
}
*/
/*
int ProjectModel::indexOfNode(const ProjectNode * parentNode, const ProjectNode * node) const {
        int row = 0;
         ProjectNode::child_const_iterator iter1 = parentNode->children.begin();
         while( iter1 != parentNode->children.end() && *iter1 != node ) {
            iter1++;
            row++;
        }
        if(row > static_cast<int>(parentNode->children.size()))
            row = -1;
    
        return row;
}
*/
