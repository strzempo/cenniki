#include "maintreemodel.h"
#include "treecomposite.h"
#include "itempdf.h"
#include "serialization.h"
#include <fstream>

MainTreeModel::MainTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_rootComponent = new TreeComposite(tr("Main Menu"));
    m_rootComponent->add(new ItemPDF(tr("movie"), "movie.flv", m_rootComponent));
    TreeComposite* submenu = new TreeComposite(tr("Submenu"), m_rootComponent);
    submenu->add(new ItemPDF(tr("First Leaf"), "first.pdf", submenu));
    submenu->add(new ItemPDF(tr("Second Leaf"), "second.pdf", submenu));
    m_rootComponent->add(submenu);
}

MainTreeModel::~MainTreeModel()
{
    delete m_rootComponent;
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
        parentItem = m_rootComponent;
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

    if (parentItem == m_rootComponent)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int MainTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeComponent *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_rootComponent;
    else
        parentItem = static_cast<TreeComponent*>(parent.internalPointer());

    return parentItem->childCount();
}

int MainTreeModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_rootComponent->columnCount();
    else
        return static_cast<TreeComponent*>(parent.internalPointer())->columnCount();
}

QVariant MainTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeComponent *item = static_cast<TreeComponent*>(index.internalPointer());

    return item->data(index.column());
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
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(m_rootComponent);
}

void MainTreeModel::load()
{
    std::ifstream ifs("layout.xml");
    assert(ifs.good());
    boost::archive::xml_iarchive ia(ifs);
    ia >> BOOST_SERIALIZATION_NVP(m_rootComponent);
    assert(m_rootComponent	);
}
