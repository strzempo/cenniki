QT += qml quick widgets
CONFIG += c++11
LIBS += -L/usr/lib/ -lboost_serialization

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    iconprovider.h \
    maintreemodel.h \
    treecomponent.h \
    treecomposite.h \
    itempdf.h \
    qstring_serialization.h \
    serializable.h

SOURCES += \
    main.cpp \
    iconprovider.cpp \
    maintreemodel.cpp \
    treecomposite.cpp \
    treecomponent.cpp \
    itempdf.cpp \
    serializable.cpp
