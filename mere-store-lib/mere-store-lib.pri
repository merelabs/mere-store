LIBTARGET = mere-store
BASEDIR   = $${PWD}
INCLUDEPATH *= $${BASEDIR}/include
LIBS += -L$${DESTDIR}  -L../lib -lmere-store
