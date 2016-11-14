#ifndef TREECOMPOSITE_H
#define TREECOMPOSITE_H

#include "treecomponent.h"
#include <QList>

class TreeComposite : public TreeComponent
{
public:
    explicit TreeComposite();
    explicit TreeComposite(QString title, TreeComponent *parent = nullptr);
    virtual ~TreeComposite();

    virtual void add(TreeComponent* component);
    virtual TreeComponent* child(int row) const;
    virtual int childCount() const;

    virtual int findRowOf(TreeComponent* child) const;

protected:
   QList<TreeComponent*> m_children;

    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        Q_UNUSED(version)
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(TreeComponent);
        std::list<TreeComponent*> list = m_children.toStdList();
        ar << boost::serialization::make_nvp("m_children", list);
    }
    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        Q_UNUSED(version)
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(TreeComponent);
        std::list<TreeComponent*> list;
        ar >> boost::serialization::make_nvp("m_children", list);
        m_children = QList<TreeComponent*>::fromStdList(list);
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    friend class boost::serialization::access;
};

#endif // TREECOMPOSITE_H
