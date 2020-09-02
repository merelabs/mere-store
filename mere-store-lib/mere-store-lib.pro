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
    src/format/meredefaultstore.cpp \
    src/format/merejsonstore.cpp \
    src/engine/merestoreengine.cpp \
    src/engine/leveldb/merestoreleveldbengine.cpp \
    src/format/meresimplestore.cpp \
    src/merebasestore.cpp \
    src/merestore.cpp \
    src/merestoreconfig.cpp \
    src/merestorefilter.cpp \
    src/merestoreunit.cpp \
    src/merestoreunitdescriptor.cpp

HEADERS +=  \
    src/format/meredefaultstore.h \
    src/format/merejsonstore.h \
    src/engine/merestoreengine.h \
    src/engine/leveldb/merestoreleveldbengine.h \
    src/format/meresimplestore.h \
    src/merebasestore.h \
    src/merestore.h \
    src/merestoreconfig.h \
    src/merestorefilter.h \
    src/merestoreglobal.h \
    src/merestoreunit.h \
    src/merestoreunitdescriptor.h

DESTDIR = $$PWD/../lib

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /opt/local/include

LIBS += -L/usr/local/lib
LIBS += -L/opt/local/lib
LIBS += -lleveldb

#defineTest(copy) {
#    source = $$1
#    target = $$2

#    for(file, source) {
#        sdir = $${dirname(file)}
#        sdir = $$replace(sdir, "src", "")
#        path = $${target}$${sdir}

#        QMAKE_POST_LINK += $$QMAKE_MKDIR $$quote($$path) $$escape_expand(\\n\\t)
#        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$file) $$quote($$path) $$escape_expand(\\n\\t)
#    }

#    export(QMAKE_POST_LINK)
#}

#copy($$HEADERS, $$PWD/../include/mere/store)

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

