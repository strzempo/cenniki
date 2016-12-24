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

#include "treecomponent.h"
#include "menu.h"
#include "maintreemodel.h"
#include <QVariant>
#include <QtDebug>

BOOST_CLASS_EXPORT_IMPLEMENT(TreeComponent)

TreeComponent::TreeComponent()
{
    Parent = nullptr;
}

TreeComponent::TreeComponent(QString title, TreeComponent *parent)
{
    Parent = parent;
    Title = title;
}

TreeComponent::~TreeComponent()
{

}

void TreeComponent::add(TreeComponent *)
{
    qDebug() << "adding child to leaf?";
}

TreeComponent *TreeComponent::child(int) const
{
    qDebug() << "getting child of leaf?";
    return nullptr;
}

int TreeComponent::childCount() const
{
    return 0;
}

int TreeComponent::columnCount() const
{
    return 1;
}

QVariant TreeComponent::data(int displayRole)
{
    if(displayRole == MainTreeModel::nodeNameRole)
        return Title;
    return QVariant();
}

int TreeComponent::row() const
{
    if(Parent)
        Parent->findRowOf(const_cast<TreeComponent*>(this));
    return 0;
}

int TreeComponent::findRowOf(TreeComponent *) const
{
    qDebug() << "finding row of child of leaf?";
    return -1;
}

TreeComponent *TreeComponent::parent()
{
    return Parent;
}

QString TreeComponent::title() const
{
    return Title;
}

void TreeComponent::action()
{
    qDebug() << "Empty action";
}

void TreeComponent::setParent(TreeComponent *parent)
{
    Parent = parent;
}
