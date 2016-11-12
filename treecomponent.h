#ifndef TREECOMPONENT_H
#define TREECOMPONENT_H

#include <QString>

class TreeComposite;
class QVariant;

class TreeComponent
{
public:
    TreeComponent(QString title, TreeComponent *parent = nullptr);
    virtual ~TreeComponent() = 0;

    virtual void add(TreeComponent* /*component*/);
    virtual TreeComponent* child(int /*row*/) const;
    virtual int childCount() const;
    virtual TreeComponent* parent();

    virtual int columnCount() const;
    virtual QVariant data(int /*column*/);
    virtual int row() const;
    virtual int findRowOf(TreeComponent* /*child*/) const;

    virtual QString title() const;
    virtual void action();

protected:
    TreeComponent* m_parent;
    QString m_title;

};

#endif // TREECOMPONENT_H

