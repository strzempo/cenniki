/**
    cenniki - Menu used in CD with promotion materials for Aliaxis Utilities and Industry.
    Copyright (C) 2016  Kamil 'konserw' Strzempowicz, konserw@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <fstream>

#ifndef BOOST_NO_EXCEPTIONS
#include <exception>
#include "boost/archive/archive_exception.hpp"
#endif

#include "maintreemodel.h"
#include "menu.h"
#include "itemfileopen.h"
#include "serialization.h"
#include "itemappopen.h"

MainTreeModel::MainTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    RootComponent = nullptr;
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

    if (parentItem == RootComponent || parentItem == nullptr)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int MainTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeComponent *parentItem;

    if (!parent.isValid())
        parentItem = RootComponent;
    else
        parentItem = static_cast<TreeComponent*>(parent.internalPointer());

    return parentItem->childCount();
}

int MainTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
    if (!parent.isValid())
        return RootComponent->columnCount();
    else
        return static_cast<TreeComponent*>(parent.internalPointer())->columnCount();
}

QVariant MainTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeComponent *item = static_cast<TreeComponent*>(index.internalPointer());

    return item->data(role);
}

Qt::ItemFlags MainTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool MainTreeModel::insertMenu(const QString& title, const QModelIndex &parent)
{
    TreeComponent *parentItem = getItem(parent);
    int row = parentItem->childCount();
    qDebug() << "inserting item on row" << row << "in menu" << parentItem->title();
    beginInsertRows(parent, row, row);
    parentItem->add(new Menu(title, parentItem));
    endInsertRows();
    return true;
}

bool MainTreeModel::insertItem(const QString& title, const QModelIndex &parent)
{
    TreeComponent *parentItem = getItem(parent);
    int row = parentItem->childCount();
    qDebug() << "inserting item on row" << row << "in menu" << parentItem->title();
    beginInsertRows(parent, row, row);
    parentItem->add(new ItemFileOpen(title, "file.pdf", parentItem));
    endInsertRows();
    return true;
}

void MainTreeModel::removeItem(const QModelIndex &index)
{
    if( !index.isValid() )
    {
        qWarning() << "invalid index passed";
        return;
    }

    QModelIndex parentIndex = index.parent();
    Menu* parent;
    if(parentIndex.isValid())
        parent = static_cast<Menu*>(parentIndex.internalPointer());
    else
        parent = static_cast<Menu*>(RootComponent);
    int row = index.row();
    qDebug() << "removing item on row" << row << "in menu" << parent->title();
    beginRemoveRows(parentIndex, row, row);
    parent->remove(row);
    endRemoveRows();
}

void MainTreeModel::removeItem(const QModelIndex &parentIndex, const QModelIndex &index)
{
    if( !index.isValid() )
    {
        qWarning() << "invalid index passed";
        return;
    }
    Menu* parent;
    if(parentIndex.isValid())
        parent = static_cast<Menu*>(parentIndex.internalPointer());
    else
        parent = static_cast<Menu*>(RootComponent);
    int row = index.row();
    qDebug() << "removing item on row" << row << "in menu" << parent->title();
    beginRemoveRows(parentIndex, row, row);
    parent->remove(row);
    endRemoveRows();
}

bool MainTreeModel::isMenu(const QModelIndex &item) const
{
    if(!item.isValid())
        return true;
    return static_cast<TreeComponent*>(getItem(item))->isMenu();
}

void MainTreeModel::reorder(const QModelIndex &parentIndex, int oldPos, int newPos)
{
    Menu* parent;
    if(parentIndex.isValid())
        parent = static_cast<Menu*>(parentIndex.internalPointer());
    else
        parent = static_cast<Menu*>(RootComponent);

    int rowCount = parent->childCount();
#ifdef VERBOSE
    qDebug() << "pre-move";
    qDebug() << "number | item title";
    for(int i=0; i < rowCount; ++i)
    {
        TreeComponent* item = parent->child(i);
        qDebug() << item->getSequenceNumber() << "\t|" << item->title();
    }
#endif

    for(int i=0; i < rowCount; ++i)
    {
        TreeComponent* item = parent->child(i);
        int curPos = item->getSequenceNumber();
        int destPos = curPos;
        if(curPos == oldPos)
            destPos = newPos;
        else if(oldPos < newPos && curPos > oldPos && curPos <= newPos)
            destPos--;
        else if(oldPos > newPos && curPos < oldPos && curPos >= newPos)
            destPos++;
        item->setSequenceNumber(destPos);
    }

#ifdef VERBOSE
    qDebug() << "post-move";
    qDebug() << "number | item title";
    for(int i=0; i < rowCount; ++i)
    {
        TreeComponent* item = parent->child(i);
        qDebug() << item->getSequenceNumber() << "\t|" << item->title();
    }
#endif
}

void MainTreeModel::reorder(const QModelIndex &parentIndex, const QModelIndex &index, int newPos)
{
    if(!index.isValid())
    {
        qWarning() << "invalid index";
        return;
    }
    int oldPos = static_cast<TreeComponent*>(index.internalPointer())->getSequenceNumber();
    if (oldPos != newPos)
        reorder(parentIndex, oldPos, newPos);
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
    if(RootComponent != nullptr)
        delete RootComponent;

    std::ifstream ifs("layout.xml");
    assert(ifs.good());
    q_xml_iarchive ia(ifs);
    try{
        ia >> BOOST_SERIALIZATION_NVP(RootComponent);
        assert(RootComponent);
    }
    catch(boost::archive::archive_exception e){
        delete RootComponent;
        qCritical() << "archive exception code" << e.code;
        qFatal(e.what());
    }
    catch(std::exception e){
        delete RootComponent;
        qFatal(e.what());
    }
}

QHash<int, QByteArray> MainTreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[nodeNameRole] = "nodeName";
    roles[nodeAboutRole] = "nodeAbout";
    roles[nodeSequenceRole] = "nodeSequence";
    return roles;
}

void MainTreeModel::invokeAction(const QModelIndex &index) const
{
    static_cast<TreeComponent*>(index.internalPointer())->action();
}

QString MainTreeModel::sectionName(const QModelIndex &index) const
{
    if(!index.isValid())
        return QString();
    return static_cast<TreeComponent*>(index.internalPointer())->title();
}

TreeComponent *MainTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeComponent *item = static_cast<TreeComponent*>(index.internalPointer());
        if (item)
            return item;
    }
    return RootComponent;
}
