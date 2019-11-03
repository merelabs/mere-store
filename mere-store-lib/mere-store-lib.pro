include(../../mere-utils/mere-utils-lib/mere-utils-lib.pri)
include(../../mere-config/mere-config-lib/mere-config-lib.pri)

QT += core

CONFIG += c++11
CONFIG += shared

TARGET = mere-store
VERSION  = 0.0.1b
TEMPLATE = lib

DEFINES += LIB_CODE=\\\"$$TARGET\\\"
DEFINES += LIB_NAME=\\\"$$TARGET\\\"
DEFINES += LIB_VERSION=\\\"$$VERSION\\\"
DEFINES += QT_DEPRECATED_WARNINGS MERE_STORE_LIB

SOURCES +=  \
    src/meredefaultstore.cpp \
    src/merestore.cpp \
    src/merestoreconfig.cpp \
    src/merestorefilter.cpp \
    src/merestoreunit.cpp

HEADERS +=  \
    src/meredefaultstore.h \
    src/merestore.h \
    src/merestoreconfig.h \
    src/merestorefilter.h \
    src/merestoreglobal.h \
    src/merestoreunit.h

DESTDIR = $$PWD/../lib

#INCLUDEPATH += src
#INCLUDEPATH += ../include
#INCLUDEPATH += ../mere-store-utils/include
#INCLUDEPATH += ../../mere-utils/include
#INCLUDEPATH += ../../mere-config/include
#INCLUDEPATH += /usr/local/include

#DEPENDPATH += . ../lib
#LIBS += -L$$PWD/../lib -lmere-store-utils

#DEPENDPATH  +=. ../../mere-utils/lib
#LIBS += -L../../mere-utils/lib  -lmere-utils

#DEPENDPATH  +=. ../../mere-config/lib
#LIBS += -L../../mere-config/lib  -lmere-config

LIBS += -lleveldb

#LIBDIR = $$PWD/../lib
#INCDIR = $$PWD/../include
#DESTDIR = \"$$LIBDIR\"

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

