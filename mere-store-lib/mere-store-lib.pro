include(../../mere-utils/mere-utils-lib/mere-utils-lib.pri)
#include(../../mere-config/mere-config-lib/mere-config-lib.pri)

QT      = core

CONFIG += c++11
CONFIG += shared

TARGET   = mere-store
VERSION  = 0.0.1
TEMPLATE = lib

DEFINES += LIB_CODE=\\\"store\\\"
DEFINES += LIB_NAME=\\\"$$TARGET\\\"
DEFINES += LIB_VERSION=\\\"$$VERSION\\\"
DEFINES += QT_DEPRECATED_WARNINGS MERE_STORE_LIB

SOURCES +=  \
    src/basestore.cpp \
    src/engine/engine.cpp \
    src/engine/leveldbengine.cpp \
    src/jsonstore.cpp \
    src/mapstore.cpp \
    src/pairstore.cpp \
    src/store.cpp \
    src/unitstore.cpp \
    src/key.cpp \
    src/merestoreconfig.cpp \
    src/merestorefilter.cpp \
    src/merestoreunitdescriptor.cpp \
    src/pair.cpp \
    src/ref.cpp \
    src/unit.cpp \
    src/unitref.cpp \
    src/value.cpp

HEADERS +=  \
    src/basestore.h \
    src/engine/engine.h \
    src/engine/leveldbengine.h \
    src/jsonstore.h \
    src/mapstore.h \
    src/pairstore.h \
    src/unitstore.h \
    src/key.h \
    src/merestoreconfig.h \
    src/merestorefilter.h \
    src/merestoreglobal.h \
    src/merestoreunitdescriptor.h \
    src/pair.h \
    src/ref.h \
    src/store.h \
    src/unit.h \
    src/unitref.h \
    src/value.h

DESTDIR = $$PWD/../lib

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /opt/local/include

LIBS += -L/usr/local/lib
LIBS += -L/opt/local/lib
LIBS += -lleveldb

#
# Install
#
unix {
    target.path = /usr/local/lib
    INSTALLS += target

    INSTALL_PREFIX = /usr/local/include/mere/store
    for(header, HEADERS) {
        sdir = $${dirname(header)}
        sdir = $$replace(sdir, "src", "")
        path = $${INSTALL_PREFIX}$${sdir}

        eval(headers_$${path}.files += $$header)
        eval(headers_$${path}.path = $$path)
        eval(INSTALLS *= headers_$${path})
    }
}

