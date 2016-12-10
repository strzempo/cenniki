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
    qDeleteAll(Children);
}

void Menu::add(TreeComponent *component)
{
    Children.append(component);
}

TreeComponent *Menu::child(int row) const
{
    if(row < Children.count())
        return Children.at(row);
    return nullptr;
}

int Menu::childCount() const
{
    return Children.count();
}

int Menu::findRowOf(TreeComponent *child) const
{
    return Children.indexOf(child);
}

