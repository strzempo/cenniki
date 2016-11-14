#include "treecomponent.h"
#include "treecomposite.h"
#include <QVariant>
#include <QtDebug>

BOOST_CLASS_EXPORT_IMPLEMENT(TreeComponent)

TreeComponent::TreeComponent()
{
    m_parent = nullptr;
}

TreeComponent::TreeComponent(QString title, TreeComponent *parent)
{
    m_parent = parent;
    m_title = title;
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
    return m_title;
}

int TreeComponent::row() const
{
    if(m_parent)
        m_parent->findRowOf(const_cast<TreeComponent*>(this));
    return 0;
}

int TreeComponent::findRowOf(TreeComponent *) const
{
    qDebug() << "finding row of child of leaf?";
    return -1;
}

TreeComponent *TreeComponent::parent()
{
    return m_parent;
}

QString TreeComponent::title() const
{
    return m_title;
}

void TreeComponent::action()
{
    qDebug() << "Empty action";
}

void TreeComponent::setParent(TreeComponent *parent)
{
    m_parent = parent;
}
