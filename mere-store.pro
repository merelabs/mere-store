TEMPLATE = subdirs
CONFIG +=ordered
SUBDIRS = \
    mere-store-daemon \
        mere-store-utils   \  # mere-store-utils
        mere-store-lib     \  # mere-store-lib
        mere-store-shell   \  # mere-store-shell
        mere-store-app     \  # mere-store-app
#        mere-store-tests   \  # mere-store-tests

mere-store-lib.depends   = mere-store-utils
mere-store-app.depends   = mere-store-lib
mere-store-shell.depends = mere-store-lib
#mere-store-tests.depends = mere-store-lib

