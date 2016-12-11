#include "maintreemodel.h"
#include "menu.h"
#include "itemfileopen.h"
#include "serialization.h"
#include <fstream>

MainTreeModel::MainTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

MainTreeModel::~MainTreeModel()
{
    delete RootComponent;
}

QVariant MainTreeModel::headerData(int, Qt::Orientation, int) const
{
    return QVariant();
}

QModelIndex MainTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeComponent *parentItem;

    if (!parent.isValid())
        parentItem = RootComponent;
    else
        parentItem = static_cast<TreeComponent*>(parent.internalPointer());

    TreeComponent *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex MainTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeComponent *childItem = static_cast<TreeComponent*>(index.internalPointer());
    TreeComponent *parentItem = childItem->parent();

    if (parentItem == RootComponent)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int MainTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeComponent *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = RootComponent;
    else
        parentItem = static_cast<TreeComponent*>(parent.internalPointer());

    return parentItem->childCount();
}

int MainTreeModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return RootComponent->columnCount();
    else
        return static_cast<TreeComponent*>(parent.internalPointer())->columnCount();
}

QVariant MainTreeModel::data(const QModelIndex &index, int role) const
{
 //   qDebug() << "index passed:" << index;
    if (!index.isValid())
        return QVariant();
/*
    if (role != Qt::DisplayRole)
        return QVariant();
*/
    TreeComponent *item = static_cast<TreeComponent*>(index.internalPointer());

    return item->data(role);
}

Qt::ItemFlags MainTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

void MainTreeModel::save()
{
    std::ofstream ofs("layout.xml");
    assert(ofs.good());
    q_xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(RootComponent);
}

void MainTreeModel::load()
{
    std::ifstream ifs("layout.xml");
    assert(ifs.good());
    q_xml_iarchive ia(ifs);
    ia >> BOOST_SERIALIZATION_NVP(RootComponent);
    assert(RootComponent);
}

void MainTreeModel::generateSampleTree()
{
    RootComponent = new Menu(tr("Main Menu"));
    RootComponent->add(new ItemFileOpen(tr("movie"), "movie.flv", RootComponent));
    Menu* submenu = new Menu(tr("Submenu"), RootComponent);
    submenu->add(new ItemFileOpen(tr("First Leaf"), "first.pdf", submenu));
    submenu->add(new ItemFileOpen(tr("Second Leaf"), "second.pdf", submenu));
    RootComponent->add(submenu);
}

QHash<int, QByteArray> MainTreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[nodeNameRole] = "nodeName";
    return roles;
}

void MainTreeModel::invokeAction(const QModelIndex &index) const
{
    static_cast<TreeComponent*>(index.internalPointer())->action();
}

QString MainTreeModel::sectionName(const QModelIndex &index) const
{
    //qDebug() << static_cast<TreeComponent*>(index.internalPointer())->title();
    if(!index.isValid())
        return QString();
    return static_cast<TreeComponent*>(index.internalPointer())->title();
}
