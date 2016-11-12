#ifndef ITEMPDF_H
#define ITEMPDF_H

#include "treecomponent.h"
#include <QString>

class ItemPDF : public TreeComponent
{
public:
    explicit ItemPDF(QString title, QString fileName, TreeComponent* parent);
    virtual void action();

protected:
    QString m_fileName;
};

#endif // ITEMPDF_H
