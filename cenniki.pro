QT += quick widgets #qml quick widgets
CONFIG += c++11

TARGET = cenniki
TEMPLATE = app

#logger lib - my basic Qt logging class
#PRE_TARGETDEPS = $$PWD/logger.a
include($$PWD/logger/logger.pri)
#INCLUDEPATH += $$PWD/logger
#DEPENDSPATH += $$PWD/logger
#LIBS += -L$$PWD/logger/ -llogger

#boost serialization dependancy
unix: LIBS += -L/usr/lib/ -lboost_serialization
win32 {
    CONFIG += windows release
    INCLUDEPATH += "$(BOOST_ROOT)"
    LIBS += "-L$(BOOST_LIBRARYDIR)" #/libboost_serialization-vc120-mt-1_59.lib"
}

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    maintreemodel.h \
    treecomponent.h \
    qstring_serialization.h \
    serialization.h \
    itemfileopen.h \
    menu.h

SOURCES += \
    main.cpp \
    maintreemodel.cpp \
    treecomponent.cpp \
    itemfileopen.cpp \
    menu.cpp

RESOURCES += qml.qrc
