/**
    cenniki - Menu used in CD with promotion materials for Aliaxis Utilities and Industry.
    Copyright (C) 2016  Kamil 'konserw' Strzempowicz, konserw@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <QtDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>


#include "maintreemodel.h"
#include "logger/Logger.h"

int main(int argc, char *argv[])
{
    qInstallMessageHandler(Logger::handler);
    qInfo() << "Starting application \"Cenniki\" (c) Kamil Strzempowicz";

    MainTreeModel model;
    model.load();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QIcon icon("qrc:/images/icon");
    

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("mainTreeModel", &model);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
