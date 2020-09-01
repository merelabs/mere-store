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
typedef QMap<QString, QVariant> MappedStoreUnit;
//typedef QMap<QString, QVariant> StoreUnitFields;
typedef QMap<QString, QVariant> StoreUnitAttributes;
//typedef QMap<QString, QVariant> StoreUnitProperties;

class MERE_STORE_LIBSPEC MereStoreUnit
{
public:
    virtual ~MereStoreUnit();
    explicit MereStoreUnit(const QString type);

    QString type() const;
//    void setType(const QString type);

    QUuid uuid() const;
    void setUuid(QUuid uuid);

    QString path() const;
    void setPath(QString path);

//    Metadata meta() const;

    virtual StoreUnit get() const;
    virtual void set(StoreUnit unit);

//    virtual StoreUnitFields fields() const;
//    virtual void setFields(StoreUnitFields fields);

    virtual StoreUnitAttributes attributes() const;
    virtual void setAttributes(StoreUnitAttributes attributes);

//    virtual StoreUnitProperties properties() const;
//    virtual void setProperties(StoreUnitProperties properties);

    StoreUnit map() const;

private:
    class MereStoreUnitPrivate;
    MereStoreUnitPrivate *d_ptr;
};

#endif // MERESTOREUNIT_H
