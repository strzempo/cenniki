#include "itempdf.h"

#include <QUrl>
#include <QDesktopServices>

BOOST_CLASS_EXPORT_IMPLEMENT(ItemPDF)

ItemPDF::ItemPDF() : TreeComponent()
{

}

ItemPDF::ItemPDF(QString title, QString fileName, TreeComponent *parent) : TreeComponent(title, parent)
{
    m_fileName = fileName;
}

void ItemPDF::action()
{
    QDesktopServices::openUrl(QUrl(m_fileName));
}
