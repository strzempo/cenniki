QT += quick #qml widgets
CONFIG += c++11

TARGET = cenniki
TEMPLATE = app

#logger lib - my basic Qt logging class
include($$PWD/logger/logger.pri)
#qarchve lib - my boost::xmlarchive implementation for Qt Calsses
include($$PWD/qarchive/qarchive.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    maintreemodel.h \
    treecomponent.h \
    serialization.h \
    itemfileopen.h \
    menu.h \
    itemappopen.h

SOURCES += \
    main.cpp \
    maintreemodel.cpp \
    treecomponent.cpp \
    itemfileopen.cpp \
    menu.cpp \
vectory.cpp \
    itemappopen.cpp

FORMS =

RESOURCES += qml.qrc
