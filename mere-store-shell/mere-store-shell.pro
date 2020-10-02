include(../mere-store-lib/mere-store-lib.pri)

QT = core

CONFIG += c++11
CONFIG += console

TARGET = mere-store-shell
VERSION = 0.0.1b
TEMPLATE= app

#DEFINES += APP_CODE=\\\"store\\\"
#DEFINES += APP_NAME=\\\"$$TARGET\\\"
#DEFINES += APP_VERSION=\\\"$$VERSION\\\"
#DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/main.cpp \
    src/command/alias.cpp \
    src/command/close.cpp \
    src/command/config.cpp \
    src/command/create.cpp \
    src/command/del.cpp \
    src/command/get.cpp \
    src/command/help.cpp \
    src/command/history.cpp \
    src/command/insert.cpp \
    src/command/list.cpp \
    src/command/mdel.cpp \
    src/command/mget.cpp \
    src/command/mset.cpp \
    src/command/remove.cpp \
    src/command/select.cpp \
    src/command/set.cpp \
    src/command/switch.cpp \
    src/command/void.cpp \
    src/command/what.cpp \
    src/command.cpp \
    src/context.cpp \
    src/input.cpp \
    src/konfig.cpp \
    src/kvutils.cpp \
    src/linereader.cpp \
    src/parser.cpp \
    src/processor.cpp \
    src/prompt.cpp \
    src/reader.cpp \
    src/shell.cpp \
    src/slice.cpp \
    src/store.cpp \
    src/system.cpp \
    src/type.cpp

HEADERS += \
    src/command/alias.h \
    src/command/close.h \
    src/command/config.h\
    src/command/create.h \
    src/command/del.h \
    src/command/get.h \
    src/command/help.h \
    src/command/history.h \
    src/command/insert.h \
    src/command/list.h \
    src/command/mdel.h \
    src/command/mget.h \
    src/command/mset.h \
    src/command/remove.h \
    src/command/select.h \
    src/command/set.h \
    src/command/switch.h \
    src/command/void.h \
    src/command/what.h \
    src/command.h \
    src/context.h \
    src/input.h \
    src/konfig.h \
    src/kvutils.h \
    src/linereader.h \
    src/parser.h \
    src/processor.h \
    src/prompt.h \
    src/reader.h \
    src/shell.h \
    src/slice.h \
    src/store.h \
    src/system.h \
    src/type.h

RESOURCES +=\
    res/res.qrc


INCLUDEPATH += /usr/local/include

LIBS += -lmere-utils
LIBS += -lmere-store
LIBS += -lleveldb

#
# Install
#
unix{
    target.path = /usr/local/bin
    INSTALLS += target
}
