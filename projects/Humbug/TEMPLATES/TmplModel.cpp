#include "stdafx.h"
#include <QtCore>

#include "$Template$.h"
#include "$Template$Parser.h"

$Template$::$Template$(QObject *parent)
    : QAbstractItemModel(parent)
{
    root$Node$ = 0;
}

$Template$::~$Template$()
{
    delete root$Node$;
}

void $Template$::setRoot$Node$($Node$ *node)
{
    delete root$Node$;
    root$Node$ = node;
    reset();
}

QModelIndex $Template$::index(int row, int column,
                                const QModelIndex &parent) const
{
    if (!root$Node$ || row < 0 || column < 0)
        return QModelIndex();
    $Node$ *parent$Node$ = nodeFromIndex(parent);
    $Node$ *child$Node$ = parent$Node$->children.value(row);
    if (!child$Node$)
        return QModelIndex();
    return createIndex(row, column, child$Node$);
}

QModelIndex $Template$::parent(const QModelIndex &child) const
{
    $Node$ *node = nodeFromIndex(child);
    if (!node)
        return QModelIndex();
    $Node$ *parent$Node$ = node->parent;
    if (!parent$Node$)
        return QModelIndex();
    $Node$ *grandparent$Node$ = parent$Node$->parent;
    if (!grandparent$Node$)
        return QModelIndex();

    int row = grandparent$Node$->children.indexOf(parent$Node$);
    return createIndex(row, 0, parent$Node$);
}

int $Template$::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;
    $Node$ *parent$Node$ = nodeFromIndex(parent);
    if (!parent$Node$)
        return 0;
    return parent$Node$->children.count();
}

int $Template$::columnCount(const QModelIndex & /* parent */) const
{
    return 2;
}

QVariant $Template$::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    $Node$ *node = nodeFromIndex(index);
    if (!node)
        return QVariant();

    if (index.column() == 0) {
        switch (node->type) {
        case $Node$::Root:
             return tr("Root");
        case $Node$::OrExpression:
            return tr("OR Expression");
        case $Node$::AndExpression:
            return tr("AND Expression");
        case $Node$::NotExpression:
            return tr("NOT Expression");
        case $Node$::Atom:
            return tr("Atom");
        case $Node$::Identifier:
            return tr("Identifier");
        case $Node$::Operator:
            return tr("Operator");
        case $Node$::Punctuator:
            return tr("Punctuator");
        default:
            return tr("Unknown");
        }
    } else if (index.column() == 1) {
        return node->str;
    }
    return QVariant();
}

QVariant $Template$::headerData(int section,
                                  Qt::Orientation orientation,
                                  int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0) {
            return tr("$Node$");
        } else if (section == 1) {
            return tr("Value");
        }
    }
    return QVariant();
}

$Node$ *$Template$::nodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        return static_cast<$Node$ *>(index.internalPointer());
    } else {
        return root$Node$;
    }
}
