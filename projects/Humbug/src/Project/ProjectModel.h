#ifndef _PROJECTMODEL_H
#define _PROJECTMODEL_H


#include "../global.h"
#include <QAbstractItemModel>

#include <QObject>


class ProjectNode;

class ProjectModel : public QAbstractItemModel {
  public:
    enum Roles {
      FileIconRole =  Qt::DecorationRole,
      FilePathRole =  Qt::UserRole + 1,
      FileNameRole

    };

    ProjectModel(QObject * parent);

    ~ProjectModel();

    void setRootNode(ProjectNode * node);

    QModelIndex index(int row, int column, const QModelIndex & parent) const;

    QModelIndex parent(const QModelIndex & child) const;

    int rowCount(const QModelIndex & parent) const;

    int columnCount(const QModelIndex & parent) const;

    QVariant data(const QModelIndex & index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QVariant getIcon(ProjectNode * node) const;


  private:
    ProjectNode * nodeFromIndex(const QModelIndex & index) const;

    QVariant getDisplayRole(const QModelIndex & index, ProjectNode * node) const;

    QVariant getTooltipRole(ProjectNode * node) const;


  public:
    int indexOfNode(const ProjectNode * parentNode, const ProjectNode * node) const;


  private:
    ProjectNode * rootNode;

};
#endif
