#include "treecomposite.h"

TreeComposite::TreeComposite(QString title, TreeComponent *parent) : TreeComponent(title, parent)
{
}

TreeComposite::~TreeComposite()
{
    qDeleteAll(m_children);
}

void TreeComposite::add(TreeComponent *component)
{
    m_children.append(component);
}

TreeComponent *TreeComposite::child(int row) const
{
    if(row < m_children.count())
        return m_children.at(row);
    return nullptr;
}

int TreeComposite::childCount() const
{
    return m_children.count();
}

int TreeComposite::findRowOf(TreeComponent *child) const
{
    return m_children.indexOf(child);
}

