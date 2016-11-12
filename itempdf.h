#ifndef ITEMPDF_H
#define ITEMPDF_H

#include "treecomponent.h"
#include <QString>

class ItemPDF : public TreeComponent
{
public:
    explicit ItemPDF();
    ItemPDF(QString title, QString fileName, TreeComponent* parent);
    virtual void action();

protected:
    QString m_fileName;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        Q_UNUSED(version)
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(TreeComponent);
        ar & BOOST_SERIALIZATION_NVP(m_fileName);
    }
};

#endif // ITEMPDF_H
