QT += core
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG += shared

TARGET = mere-store-utils
TEMPLATE = lib


DEFINES += QT_DEPRECATED_WARNINGS MERE_STORE_UTILS_LIB

SOURCES += \
    merestoreutils.cpp
HEADERS += \
    merestoreutils.h \
    merestoreutilsglobal.h

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /opt/local/include

LIBS += -L/usr/local/lib
LIBS += -L/opt/local/lib
LIBS += -lmere-store


#
# Install
#
unix {
    target.path = /usr/local/lib
    INSTALLS += target

    INSTALL_PREFIX = /usr/local/include/mere/store/utils
    for(header, HEADERS) {
        sdir = $${dirname(header)}
        sdir = $$replace(sdir, "src", "")
        path = $${INSTALL_PREFIX}$${sdir}

        eval(headers_$${path}.files += $$header)
        eval(headers_$${path}.path = $$path)
        eval(INSTALLS *= headers_$${path})
    }
}
