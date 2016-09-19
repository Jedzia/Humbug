#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QAbstractItemModel>

class Node;

class Template : public QAbstractItemModel
{
public:
    Template(QObject *parent = 0);
    ~Template();

    void setRootNode(Node *node);

    QModelIndex index(int row, int column,
                      const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;

private:
    Node *nodeFromIndex(const QModelIndex &index) const;

    Node *rootNode;
};

#endif // TEMPLATE_H
