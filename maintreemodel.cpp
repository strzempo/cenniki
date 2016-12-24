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

#include "maintreemodel.h"
#include "menu.h"
#include "itemfileopen.h"
#include "serialization.h"
#include "itemappopen.h"
#include "vectory.cpp"

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
    int pos = parentItem->childCount();
    beginInsertRows(parent, pos, pos);
    parentItem->add(new Menu(title, parentItem));
    endInsertRows();
    return true;
}

bool MainTreeModel::insertItem(const QString& title, const QModelIndex &parent)
{
    TreeComponent *parentItem = getItem(parent);
    int pos = parentItem->childCount()-1;
    pos = pos < 0 ? 0 : pos;
    beginInsertRows(parent, pos, pos);
    parentItem->add(new ItemFileOpen(title, "", parentItem));
    endInsertRows();
    return true;
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
    ia >> BOOST_SERIALIZATION_NVP(RootComponent);
    assert(RootComponent);
}

void MainTreeModel::generateSampleTree()
{
    std::vector<std::vector<std::string> > menu_items;
    std::vector<std::vector<std::vector<std::string> > > div;
    std::vector<std::vector<std::vector<std::string> > > pliki;
    vectory(menu_items, div, pliki);
#ifdef PRINT
    qDebug() << "menu_items:";
    for(uint i=0; i < menu_items.size(); ++i)
        for(uint j=0; j<menu_items[i].size(); ++j)
            qDebug() << QString("[%1][%2] %3").arg(i).arg(j).arg(QString::fromStdString(menu_items[i][j]));
    qDebug() << "div:";
    for(uint i=0; i < div.size(); ++i)
        for(uint j=0; j<div[i].size(); ++j)
            for(uint k=0; k<div[i][j].size(); ++k)
                qDebug() << QString("[%1][%2][%3] %4").arg(i).arg(j).arg(k).arg(QString::fromStdString(div[i][j][k]));
    qDebug() << "pliki:";
    for(uint i=0; i < pliki.size(); ++i)
        for(uint j=0; j<pliki[i].size(); ++j)
            for(uint k=0; k<pliki[i][j].size(); ++k)
                qDebug() << QString("[%1][%2][%3] %4").arg(i).arg(j).arg(k).arg(QString::fromStdString(pliki[i][j][k]));
#endif
    //Main menu
    RootComponent = new Menu(tr("Main Menu"));
    for(uint i=0; i<6; ++i)
    {
        QString title = QString::fromStdString(div[0][0][i]);
        if(i < 4) RootComponent->add(new ItemFileOpen(title, QString::fromStdString(menu_items[0][i])));
        else RootComponent->add(new Menu(title));
    }
    RootComponent->add(new ItemAppOpen("Kemy", "kemy.exe", "Program do sprawdzania odporności chemicznej materiałów i uszczelnień"));
    //broszury
    for(uint i=0; i<7; i++)
        RootComponent->child(4)->add(new ItemFileOpen(QString::fromStdString(div[0][2][i]), QString::fromStdString(menu_items[1][i])));
    //katalogi
    for(uint i=0; i<8; ++i)
    {
     //   qDebug() << QString("[%1] %4").arg(i).arg(QString::fromStdString(div[0][1][i]));
        Menu* cur = new Menu(QString::fromStdString(div[0][1][i]));
        RootComponent->child(5)->add(cur);
        if(i < 6) for(uint j=0; j<div[i+1][0].size(); ++j)
        {
   //         qDebug() << QString("\t[%1][%2][%3] %4").arg(i+1).arg(0).arg(j).arg(QString::fromStdString(div[i+1][0][j]));
            TreeComponent* cur2;
            if((i!=0 && j==0) || ((i==2 || i==4 || i==5) && j==1))
                cur2 = new ItemFileOpen(QString::fromStdString(div[i+1][0][j]), QString::fromStdString(pliki[i+3][j][0]));
            else
                cur2 = new Menu(QString::fromStdString(div[i+1][0][j]));
            cur->add(cur2);
            if(j < 2 && i == 0) for(uint k=0; k<3; ++k)
            {
                QString title;
                if(j==0) title = QString::fromStdString(div[i+1][1][k]);
                else if(j==1) title = QString::fromStdString(div[i+1][5][k]);
                cur2->add(new Menu(title));
            }
        }
        else if(i==6) for(uint j=0; j < div[0][3].size(); ++j)
        {
       //     qDebug() << QString("\t[%1][%2][%3] %4").arg(0).arg(3).arg(j).arg(QString::fromStdString(div[0][3][j]));
            cur->add(new ItemFileOpen(QString::fromStdString(div[0][3][j]), QString::fromStdString(pliki[9][0][j])));
        }
        else if(i==7) for(uint j=0; j < div[0][4].size(); ++j)
        {
         //   qDebug() << QString("\t[%1][%2][%3] %4").arg(0).arg(4).arg(j).arg(QString::fromStdString(div[0][4][j]));
            cur->add(new ItemFileOpen(QString::fromStdString(div[0][4][j]), QString::fromStdString(pliki[10][0][j])));
        }

    }
}

QHash<int, QByteArray> MainTreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[nodeNameRole] = "nodeName";
    roles[nodeAboutRole] = "nodeAbout";
    return roles;
}

void MainTreeModel::invokeAction(const QModelIndex &index) const
{
    static_cast<TreeComponent*>(index.internalPointer())->action();
}

QModelIndex MainTreeModel::rootIndex() const
{
    return createIndex(0, 0, RootComponent);
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
