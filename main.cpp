#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QtWidgets>
#include "maintreemodel.h"
#include "treecomponent.h"
#include <QtDebug>
#include "logger/Logger.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    /*
    return 0;
    */
    /*
    std::ofstream ofs("layout.xml");
    assert(ofs.good());
    q_xml_oarchive oa(ofs);
    QStringList qs;
    qs << "aaa" << "bbb " << "ccc";

    oa << BOOST_SERIALIZATION_NVP(qs);
    ofs.close();
    qs.clear();

    std::ifstream ifs("layout.xml");
    assert(ifs.good());
    q_xml_iarchive ia(ifs);
    ia >> BOOST_SERIALIZATION_NVP(qs);
    qDebug() << qs;
    return 0;
*/
    qInstallMessageHandler(Logger::handler);
    qInfo() << "Starting application \"Cenniki\" (c) Kamil Strzempowicz";
/*
*/
/*    MainTreeModel model;
   // model.save();
 //   model.load();
    QTreeView view;
    view.setModel(&model);
    view.show();
    QObject::connect(&view, &QTreeView::doubleClicked, [](const QModelIndex& index){ static_cast<TreeComponent*>(index.internalPointer())->action(); });
*/
#define QML

#ifdef QML
    MainTreeModel model;
    model.generateSampleTree();
    model.save();
//    model.load();
  //  return 0;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("mainTreeModel", &model);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
#else
    QApplication app(argc, argv);
    MainWindow win;
    win.show();
#endif
    return app.exec();
}
