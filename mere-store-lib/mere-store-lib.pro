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
    src/config/config.cpp \
    src/config/indexconfig.cpp \
    src/config/sliceconfig.cpp \
    src/config/storeconfig.cpp \
    src/entry.cpp \
    src/filter/filter.cpp \
    src/group.cpp \
    src/index/index.cpp \
    src/index/indexer.cpp \
    src/index/unitindexer.cpp \
    src/store/basestore.cpp \
    src/engine/engine.cpp \
    src/engine/leveldbengine.cpp \
    src/groupkey.cpp \
    src/store/groupstore.cpp \
    src/store/hexastore.cpp \
    src/store/indexstore.cpp \
    src/store/jsonstore.cpp \
    src/link.cpp \
    src/store/mapstore.cpp \
    src/pairkey.cpp \
    src/store/pairstore.cpp \
    src/pairvalue.cpp \
    src/store/slice.cpp \
    src/store/slicestore.cpp \
    src/store/store.cpp \
    src/unitdescriptor.cpp \
    src/unitkey.cpp \
    src/store/unitstore.cpp \
    src/key.cpp \
    src/pair.cpp \
    src/ref.cpp \
    src/unit.cpp \
    src/unitref.cpp \
    src/value.cpp

HEADERS +=  \
    src/config/config.h \
    src/config/indexconfig.h \
    src/config/sliceconfig.h \
    src/config/storeconfig.h \
    src/entry.h \
    src/filter/filter.h \
    src/global.h \
    src/group.h \
    src/index/index.h \
    src/index/indexer.h \
    src/index/unitindexer.h \
    src/store/basestore.h \
    src/engine/engine.h \
    src/engine/leveldbengine.h \
    src/groupkey.h \
    src/store/groupstore.h \
    src/store/hexastore.h \
    src/store/indexstore.h \
    src/store/jsonstore.h \
    src/link.h \
    src/store/mapstore.h \
    src/pairkey.h \
    src/store/pairstore.h \
    src/pairvalue.h \
    src/store/slice.h \
    src/store/slicestore.h \
    src/unitdescriptor.h \
    src/unitkey.h \
    src/store/unitstore.h \
    src/key.h \
    src/pair.h \
    src/ref.h \
    src/store/store.h \
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

