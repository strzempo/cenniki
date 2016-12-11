#ifndef TREECOMPOSITE_H
#define TREECOMPOSITE_H

#include "treecomponent.h"
#include <QList>
//#include <QDebug>

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
   QList<TreeComponent*> MenuItems;
/*
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        Q_UNUSED(version)
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(TreeComponent);
        std::list<TreeComponent*> list = Children.toStdList();
        ar << boost::serialization::make_nvp("MenuItems", list);
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
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(TreeComponent);
        ar & BOOST_SERIALIZATION_NVP(MenuItems);
    }

    friend class boost::serialization::access;
};

BOOST_CLASS_EXPORT_KEY(Menu)

#endif // TREECOMPOSITE_H
