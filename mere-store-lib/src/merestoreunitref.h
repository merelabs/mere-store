#ifndef MERESTOREUNITREF_H
#define MERESTOREUNITREF_H

#include "merestoreglobal.h"

#include <QUuid>

typedef QMap<QString, QVariant> MereStoreUnitRefMap;

class MERE_STORE_LIBSPEC MereStoreUnitRef
{
public:
    ~MereStoreUnitRef();
    explicit MereStoreUnitRef();

    QString type() const;
    void setType(const QString type);

    QUuid uuid() const;
    void setUuid(const QUuid &uuid);

    QString path() const;
    void setPath(const QString &path);

    MereStoreUnitRefMap map() const;

private:
    class MereStoreUnitRefPrivate;
    MereStoreUnitRefPrivate *d_ptr;
};

//Q_DECLARE_METATYPE(MereStoreUnitRef);
//Q_DECLARE_METATYPE(MereStoreUnitRef*);
//Q_DECLARE_OPAQUE_POINTER(MereStoreUnitRef::MereStoreUnitRefPrivate);
//Q_DECLARE_OPAQUE_POINTER(MereStoreUnitRef::MereStoreUnitRefPrivate*);

#endif // MERESTOREUNITREF_H
