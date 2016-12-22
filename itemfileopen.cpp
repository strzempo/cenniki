#include "itemfileopen.h"

#include <QUrl>
#include <QDesktopServices>

BOOST_CLASS_EXPORT_IMPLEMENT(ItemFileOpen)

ItemFileOpen::ItemFileOpen() : TreeComponent()
{

}

ItemFileOpen::ItemFileOpen(QString title) : TreeComponent(title)
{
    FileName = "file.pdf";
}

ItemFileOpen::ItemFileOpen(QString title, QString fileName, TreeComponent *parent) : TreeComponent(title, parent)
{
    FileName = fileName;
}

void ItemFileOpen::action()
{
    QDesktopServices::openUrl(QUrl(FileName));
}
