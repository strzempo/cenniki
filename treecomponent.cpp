#include "treecomponent.h"
#include "menu.h"
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

QVariant TreeComponent::data(int)
{
    return Title;
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
