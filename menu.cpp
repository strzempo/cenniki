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

