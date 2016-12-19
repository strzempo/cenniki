#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QtWidgets>
#include "maintreemodel.h"
#include "treecomponent.h"
#include <QtDebug>
#include "logger/Logger.h"

#include "vectory.cpp"

int main(int argc, char *argv[])
{
    std::vector<std::vector<std::string> > menu_items;
    std::vector<std::vector<std::vector<std::string> > > div;
    std::vector<std::vector<std::vector<std::string> > > pliki;
    vectory(menu_items, div, pliki);
    qDebug() << "menu_items:";
    for(int i=0; i < menu_items.size(); ++i)
        for(int j=0; j<menu_items[i].size(); ++j)
            qDebug() << QString("[%1][%2] %3").arg(i).arg(j).arg(QString::fromStdString(menu_items[i][j]));
    qDebug() << "div:";
    for(int i=0; i < div.size(); ++i)
        for(int j=0; j<div[i].size(); ++j)
            for(int k=0; k<div[i][j].size(); ++k)
                qDebug() << QString("[%1][%2][%3] %4").arg(i).arg(j).arg(k).arg(QString::fromStdString(div[i][j][k]));
    qDebug() << "pliki:";
    for(int i=0; i < pliki.size(); ++i)
        for(int j=0; j<pliki[i].size(); ++j)
            for(int k=0; k<pliki[i][j].size(); ++k)
                qDebug() << QString("[%1][%2][%3] %4").arg(i).arg(j).arg(k).arg(QString::fromStdString(pliki[i][j][k]));
    return 0;
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
    model.generateSampleTree();
    model.save();
    model.load();
  //  return 0;
    engine.rootContext()->setContextProperty("mainTreeModel", &model);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
