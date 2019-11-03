QT += core
QT -= gui
QT += x11extras

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TARGET = mere-store-utils
TEMPLATE = lib

DEFINES += QT_DEPRECATED_WARNINGS MERE_STORE_UTILS_LIB

SOURCES +=
HEADERS +=

LIBDIR = $$PWD/../lib
INCDIR = $$PWD/../include
DESTDIR = \"$$LIBDIR\"

QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$PWD/$$HEADERS) $$quote($$INCDIR) $$escape_expand(\\n\\t)

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

