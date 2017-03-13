QT += quick
CONFIG += c++11

#TARGET = editor
#DEFINES += EDITOR
#TARGET = cenniki
TEMPLATE = app

#logger lib - my basic Qt logging class
include($$PWD/logger/logger.pri)
#qarchve lib - my boost::xmlarchive implementation for Qt Calsses
include($$PWD/qarchive/qarchive.pri)
unix: LIBS += /usr/lib/libboost_serialization.a
win32 {
    CONFIG += windows release
    INCLUDEPATH += "$(BOOST_ROOT)"
    LIBS += "-L$(BOOST_LIBRARYDIR)" \
             -llibboost_serialization-vc120-mt-1_58
#            -llibboost_serialization-vc120-mt-s-1_58
#    CONFIG+= static
#    QMAKE_CXXFLAGS -= -MD
#    QMAKE_CXXFLAGS += -MT
}
#QMAKE_LFLAGS_WINDOWS += /NODEFAULTLIB:MSVCRT
#QMAKE_LFLAGS_WINDOWS += /NODEFAULTLIB:LIBCMT

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
    itemappopen.cpp

FORMS =

RESOURCES += qml.qrc
