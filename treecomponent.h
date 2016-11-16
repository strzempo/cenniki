#ifndef TREECOMPONENT_H
#define TREECOMPONENT_H

#include "serialization.h"
#include <QString>
#include <QDebug>

class TreeComposite;
class QVariant;

class TreeComponent
{
public:
    explicit TreeComponent();
    explicit TreeComponent(QString title, TreeComponent *parent = nullptr);
    virtual ~TreeComponent() = 0;

    virtual void add(TreeComponent* /*component*/);
    virtual TreeComponent* child(int /*row*/) const;
    virtual int childCount() const;
    virtual TreeComponent* parent();

    virtual int columnCount() const;
    virtual QVariant data(int /*displayRole*/);
    virtual int row() const;
    virtual int findRowOf(TreeComponent* /*child*/) const;

    virtual QString title() const;
    virtual void action();
    virtual void setParent(TreeComponent *parent);

protected:
    TreeComponent* m_parent;
    QString m_title;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
     //   ar & BOOST_SERIALIZATION_NVP(m_parent);
        ar & BOOST_SERIALIZATION_NVP(m_title);
        qDebug() << "serializing treecomponent" << m_title;
    }

    friend class boost::serialization::access;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(TreeComponent)

#endif // TREECOMPONENT_H
