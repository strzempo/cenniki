#ifndef TREECOMPOSITE_H
#define TREECOMPOSITE_H

#include "treecomponent.h"
#include <QList>
#include <QDebug>

class Menu : public TreeComponent
{
public:
    explicit Menu();
    explicit Menu(QString title, TreeComponent *parent = nullptr);
    virtual ~Menu();

    virtual void add(TreeComponent* component);
    virtual TreeComponent* child(int row) const;
    virtual int childCount() const;

    virtual int findRowOf(TreeComponent* child) const;

protected:
   QList<TreeComponent*> Children;

    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        Q_UNUSED(version)
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(TreeComponent);
        std::list<TreeComponent*> list = Children.toStdList();
        ar << boost::serialization::make_nvp("MenuItems", list);
        qDebug() << "saved treecomposite:" << Title;
    }
    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        Q_UNUSED(version)
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(TreeComponent);
        std::list<TreeComponent*> list;
        ar >> boost::serialization::make_nvp("MenuItems", list);
        Children = QList<TreeComponent*>::fromStdList(list);
        foreach(TreeComponent* child, Children)
            child->setParent(this);
       // qDebug() << "loaded treecomposite:" << m_title;
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;
};

BOOST_CLASS_EXPORT_KEY(Menu)

#endif // TREECOMPOSITE_H
