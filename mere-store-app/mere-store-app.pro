include(../mere-store-lib/mere-store-lib.pri)

QT += core
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mere-store
VERSION = 0.0.1b
TEMPLATE= app

DEFINES += APP_CODE=\\\"about\\\"
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp 
HEADERS += 

#RESOURCES += \
#    res/store.qrc


INCLUDEPATH += src
INCLUDEPATH += ../include
#INCLUDEPATH += ../../mere-utils/include
INCLUDEPATH += ../../mere-config/include
INCLUDEPATH += /usr/local/include

DEPENDPATH  +=. ../../mere-config/lib
#DEPENDPATH  +=. ../../mere-utils/lib
DEPENDPATH += . ../lib

LIBS += -L../../mere-config/lib  -lmere-config
#LIBS += -L../../mere-utils/lib  -lmere-utils -lmere-widgets
LIBS += -L../../mere-utils/lib -lmere-widgets
LIBS += -L$$PWD/../lib -lmere-store -lmere-store-utils
LIBS += -lX11 -lleveldb


#
# Install
#
unix{
    target.path = /usr/local/bin
    INSTALLS += target
}

