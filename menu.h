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

#ifndef TREECOMPOSITE_H
#define TREECOMPOSITE_H

#include "treecomponent.h"
#include <QList>

class Menu : public TreeComponent
{
public:
    explicit Menu();
    explicit Menu(QString title, TreeComponent *parent = nullptr);
    virtual ~Menu();

    virtual void add(TreeComponent* component) override;
    virtual void remove(int n);
    virtual TreeComponent* child(int row) const override;
    virtual int childCount() const override;

    virtual int findRowOf(TreeComponent* child) const override;

    virtual bool isMenu() const override;

protected:
   QList<TreeComponent*> MenuItems;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(TreeComponent);
        ar & BOOST_SERIALIZATION_NVP(MenuItems);
        if (Archive::is_loading::value)
        {
            int i=0;
            foreach (TreeComponent* it, MenuItems)
            {
                it->setParent(this);
                if(version < 1)
                    it->setSequenceNumber(i++);
#ifdef VERBOSE
                qDebug() << it->getSequenceNumber();
#endif
            }
        }
    }

    friend class boost::serialization::access;
};

BOOST_CLASS_VERSION(Menu, 1)
BOOST_CLASS_EXPORT_KEY(Menu)

#endif // TREECOMPOSITE_H
