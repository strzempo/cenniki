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

#include "itemfileopen.h"

#include <QUrl>
#include <QDesktopServices>
#include <QCoreApplication>

BOOST_CLASS_EXPORT_IMPLEMENT(ItemFileOpen)

ItemFileOpen::ItemFileOpen() : TreeComponent()
{

}

ItemFileOpen::ItemFileOpen(QString title) : TreeComponent(title)
{
    FileName = "file.pdf";
}

ItemFileOpen::ItemFileOpen(QString title, QString fileName, TreeComponent *parent) : TreeComponent(title, parent)
{
    FileName = fileName;
}

void ItemFileOpen::action()
{
    QUrl url = QUrl::fromLocalFile(QString("%1/%2").arg(qApp->applicationDirPath()).arg(FileName));
    qDebug() << "open URL:" << url;
    QDesktopServices::openUrl(url);
}
