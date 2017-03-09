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

#include "menu.h"

BOOST_CLASS_EXPORT_IMPLEMENT(Menu)

Menu::Menu(): TreeComponent()
{
}

Menu::Menu(QString title, TreeComponent *parent) : TreeComponent(title, parent)
{
}

Menu::~Menu()
{
    qDeleteAll(MenuItems);
}

void Menu::add(TreeComponent *component)
{
    component->setParent(this);
    MenuItems.append(component);
}

void Menu::remove(TreeComponent *component)
{
    MenuItems.removeOne(component);
}

TreeComponent *Menu::child(int row) const
{
    if(row < MenuItems.count())
        return MenuItems.at(row);
    return nullptr;
}

int Menu::childCount() const
{
    return MenuItems.count();
}

int Menu::findRowOf(TreeComponent *child) const
{
    return MenuItems.indexOf(child);
}

