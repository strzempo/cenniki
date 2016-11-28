#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QtWidgets>
#include "maintreemodel.h"
#include "treecomponent.h"
#include <QtDebug>
#include "logger/Logger.h"

int main(int argc, char *argv[])
{
    qInstallMessageHandler(Logger::handler);
    qInfo() << "Starting application \"Cenniki\" (c) Kamil Strzempowicz";

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
/*
    QApplication app(argc, argv);
    MainTreeModel model;
   // model.save();
    model.load();
    QTreeView view;
    view.setModel(&model);
    view.show();
    QObject::connect(&view, &QTreeView::doubleClicked, [](const QModelIndex& index){ static_cast<TreeComponent*>(index.internalPointer())->action(); });
*/
    MainTreeModel model;
//    model.load();
    model.generateSampleTree();
    engine.rootContext()->setContextProperty("mainTreeModel", &model);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
