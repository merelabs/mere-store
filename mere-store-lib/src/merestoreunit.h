#ifndef MERESTOREUNIT_H
#define MERESTOREUNIT_H

#include "merestoreglobal.h"
#include "merestoreunitdescriptor.h"

#include <QMap>
#include <QUuid>
#include <QString>
#include <QVariant>

typedef MereStoreUnitDescriptor Metadata;
typedef QMap<QString, QVariant> StoreUnit;
typedef QMap<QString, QVariant> StoreUnitFields;
typedef QMap<QString, QVariant> StoreUnitAttributes;
typedef QMap<QString, QVariant> StoreUnitProperties;

class MERE_STORE_LIBSPEC MereStoreUnit
{
public:
    virtual ~MereStoreUnit();
    MereStoreUnit();

    QUuid uuid() const;
    void setUuid(QUuid uuid);

    Metadata meta() const;

    virtual StoreUnit get() const;
    virtual void set(StoreUnit unit);

    virtual StoreUnitFields fields() const;
    virtual void fields(StoreUnitFields fields);

    virtual StoreUnitAttributes attributes() const;
    virtual void attributes(StoreUnitAttributes attributes);

    virtual StoreUnitProperties properties() const;
    virtual void properties(StoreUnitProperties properties);

    QMap<QString, QVariant> map() const;

private:
    QUuid     m_uuid;
    Metadata  m_meta;
    StoreUnit m_unit;

    StoreUnitFields     m_fields;
    StoreUnitAttributes m_attributes;
    StoreUnitProperties m_properties;
};

#endif // MERESTOREUNIT_H
