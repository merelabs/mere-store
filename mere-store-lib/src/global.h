#ifndef MERESTOREGLOBAL_H
#define MERESTOREGLOBAL_H

#include <QtCore/qglobal.h>
#include <QDebug>

#if defined(MERE_STORE_LIB)
#  define MERE_STORE_LIBSPEC Q_DECL_EXPORT
#else
#  define MERE_STORE_LIBSPEC Q_DECL_IMPORT
#endif

#endif // MERESTOREGLOBAL_H
