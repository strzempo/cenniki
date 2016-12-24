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

#include "itemappopen.h"
#include "maintreemodel.h"

#include <QUrl>
#include <QDesktopServices>

BOOST_CLASS_EXPORT_IMPLEMENT(ItemAppOpen)

ItemAppOpen::ItemAppOpen()
{

}

void ItemAppOpen::action()
{
    QDesktopServices::openUrl(QUrl(AppName));
}

QVariant ItemAppOpen::data(int displayRole)
{
    if(displayRole == MainTreeModel::nodeAboutRole)
        return AboutText;
    else
        return TreeComponent::data(displayRole);
}

ItemAppOpen::ItemAppOpen(const QString &title, const QString &appName, const QString &aboutText, TreeComponent *parent) : TreeComponent(title, parent)
{
    AppName = appName;
    AboutText = aboutText;
}
