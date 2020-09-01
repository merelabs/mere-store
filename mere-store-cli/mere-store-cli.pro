include(../mere-store-lib/mere-store-lib.pri)

QT      = core
CONFIG += c++11
CONFIG += console

TARGET = mere-store-cli
VERSION = 0.0.1
TEMPLATE= app

DEFINES += APP_CODE=\\\"store\\\"
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp  \
    src/command/alias.cpp \
    src/command/close.cpp \
    src/command/command.cpp \
    src/command/config.cpp \
    src/context.cpp \
    src/command/create.cpp \
    src/command/del.cpp \
    src/command/get.cpp \
    src/input.cpp \
    src/command/insert.cpp \
    src/kvutils.cpp \
    src/command/list.cpp \
    src/merestorecli.cpp \
    src/processor.cpp \
    src/prompt.cpp \
    src/command/remove.cpp \
    src/command/select.cpp \
    src/command/set.cpp \
    src/slice.cpp \
    src/store.cpp \
    src/type.cpp \
    src/command/void.cpp
HEADERS +=  \
    src/command/alias.h \
    src/command/close.h \
    src/command/command.h \
    src/command/config.h \
    src/context.h \
    src/command/create.h \
    src/command/del.h \
    src/command/get.h \
    src/input.h \
    src/command/insert.h \
    src/kvutils.h \
    src/command/list.h \
    src/merestorecli.h \
    src/processor.h \
    src/prompt.h \
    src/command/remove.h \
    src/command/select.h \
    src/command/set.h \
    src/slice.h \
    src/store.h \
    src/type.h \
    src/command/void.h

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /opt/local/include

LIBS += -L/usr/local/lib
LIBS += -L/opt/local/lib
LIBS += -lmere-utils
LIBS += -lleveldb


#
# Install
#
unix{
    target.path = /usr/local/bin
    INSTALLS += target
}

