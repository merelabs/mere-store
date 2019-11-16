#ifndef MERESTOREUNIT_H
#define MERESTOREUNIT_H

#include "merestoreglobal.h"
#include "merestoreunitdescriptor.h"

#include <QMap>
#include <QUuid>
#include <QString>
#include <QVariant>

typedef QMap<QString, QVariant> StoreUnit;
typedef MereStoreUnitDescriptor Metadata;

class MERE_STORE_LIBSPEC MereStoreUnit
{
public:
    virtual ~MereStoreUnit();
    MereStoreUnit();

    QUuid uuid() const;
    void setUuid(QUuid uuid);

    Metadata meta() const;

    StoreUnit unit() const;
    void setUnit(StoreUnit unit);

    virtual QMap<QString, QVariant> map() const;

private:
    QUuid     m_uuid;
    Metadata  m_meta;
    StoreUnit m_unit;
};

#endif // MERESTOREUNIT_H
