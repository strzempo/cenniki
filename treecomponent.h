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

#ifndef TREECOMPONENT_H
#define TREECOMPONENT_H

#include "serialization.h"
#include <QString>
#include <QDebug>

class Menu;
class QVariant;

class TreeComponent
{
public:
    explicit TreeComponent();
    explicit TreeComponent(QString title, TreeComponent *parent = nullptr);
    virtual ~TreeComponent() = 0;

    virtual void add(TreeComponent* /*component*/);
    virtual TreeComponent* child(int /*row*/) const;
    virtual int childCount() const;
    virtual TreeComponent* parent();

    virtual int columnCount() const;
    virtual QVariant data(int displayRole);
    virtual int row() const;
    virtual int findRowOf(TreeComponent* /*child*/) const;

    virtual QString title() const;
    virtual void action();
    virtual void setParent(TreeComponent *parent);

protected:
    TreeComponent* Parent;
    QString Title;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
        ar & BOOST_SERIALIZATION_NVP(Title);
        qDebug() << "serialize TreeComponent:" << Title;
    }

    friend class boost::serialization::access;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(TreeComponent)

#endif // TREECOMPONENT_H
