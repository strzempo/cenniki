//#include <QGuiApplication>
//#include <QQmlApplicationEngine
#include <QApplication>
#include <QtWidgets>
#include "maintreemodel.h"
#include "treecomponent.h"
#include <QtDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
/*
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    engine.addImageProvider(QLatin1String("iconProvider"), new IconProvider());
*/
    MainTreeModel model;
   // model.save();
    model.load();
    QTreeView view;
    view.setModel(&model);
    view.show();
    QObject::connect(&view, &QTreeView::doubleClicked, [](const QModelIndex& index){ static_cast<TreeComponent*>(index.internalPointer())->action(); });
    return app.exec();
}
