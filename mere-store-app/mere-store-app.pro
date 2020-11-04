include(../mere-store-lib/mere-store-lib.pri)
include(../mere-store-cli/mere-store-cli.pri)

QT += core
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mere-store
VERSION = 0.0.1b
TEMPLATE= app

DEFINES += APP_CODE=\\\"store\\\"
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp  \
    src/createview.cpp \
    src/detailview.cpp \
    src/exploreview.cpp \
    src/indexview.cpp \
    src/listview.cpp \
    src/searchview.cpp \
    src/selectview.cpp \
    src/sliceview.cpp \
    src/storeapp.cpp \
    src/storepanel.cpp \
    src/storeview.cpp \
    src/storewin.cpp
HEADERS +=  \
    src/createview.h \
    src/detailview.h \
    src/exploreview.h \
    src/indexview.h \
    src/listview.h \
    src/searchview.h \
    src/selectview.h \
    src/sliceview.h \
    src/storeapp.h \
    src/storepanel.h \
    src/storeview.h \
    src/storewin.h

INCLUDEPATH += /usr/local/include

LIBS += -lmere-utils
LIBS += -lmere-widgets
LIBS += -lmere-store

#INCLUDEPATH += ../mere-store-cli/src
#DEPENDPATH  += ../mere-store-cli/src
#INCLUDEPATH += ../include
##INCLUDEPATH += ../../mere-utils/include
#INCLUDEPATH += ../../mere-config/include
#INCLUDEPATH += /usr/local/include

#DEPENDPATH  +=. ../../mere-config/lib
##DEPENDPATH  +=. ../../mere-utils/lib
#DEPENDPATH += . ../lib

#LIBS += -L../../mere-config/lib  -lmere-config
##LIBS += -L../../mere-utils/lib  -lmere-utils -lmere-widgets
#LIBS += -L../../mere-utils/lib -lmere-widgets
#LIBS += -L$$PWD/../lib -lmere-store -lmere-store-utils
#LIBS += -lX11 -lleveldb


#
# Install
#
unix{
    target.path = /usr/local/bin
    INSTALLS += target
}

RESOURCES += \
    res/store.qrc

