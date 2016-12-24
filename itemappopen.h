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

#ifndef ITEMAPPOPEN_H
#define ITEMAPPOPEN_H

#include "treecomponent.h"
#include <QString>

class ItemAppOpen : public TreeComponent
{
public:
    explicit ItemAppOpen();
    ItemAppOpen(const QString& title, const QString& appName, const QString& aboutText, TreeComponent* parent = nullptr);
    virtual void action();
    virtual QVariant data(int displayRole);

protected:
    QString AppName;
    QString AboutText;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        Q_UNUSED(version)
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(TreeComponent);
        ar & BOOST_SERIALIZATION_NVP(AppName);
        ar & BOOST_SERIALIZATION_NVP(AboutText);
    }
};

BOOST_CLASS_EXPORT_KEY(ItemAppOpen)

#endif // ITEMAPPOPEN_H
