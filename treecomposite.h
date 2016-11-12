#ifndef TREECOMPOSITE_H
#define TREECOMPOSITE_H

#include "treecomponent.h"
#include <QList>

class TreeComposite : public TreeComponent
{
public:
    explicit TreeComposite(QString title, TreeComponent *parent = nullptr);
    virtual ~TreeComposite();

    virtual void add(TreeComponent* component);
    virtual TreeComponent* child(int row) const;
    virtual int childCount() const;

    virtual int findRowOf(TreeComponent* child) const;

protected:
   QList<TreeComponent*> m_children;
};

#endif // TREECOMPOSITE_H
