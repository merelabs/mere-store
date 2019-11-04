#ifndef MERESTOREUNIT_H
#define MERESTOREUNIT_H

#include "merestoreglobal.h"

#include <QMap>
#include <QUuid>
#include <QString>
#include <QVariant>

typedef QMap<QString, QVariant> StoreUnit;

class MERE_STORE_LIBSPEC MereStoreUnit
{
public:
    virtual ~MereStoreUnit();
    MereStoreUnit();

    QUuid uuid() const;
    void setUuid(QUuid uuid);

    QString type() const;
    void setType(QString type);

    QString path() const;
    void setPath(QString path);

    StoreUnit unit() const;
    void setUnit(StoreUnit unit);

    virtual QMap<QString, QVariant> map() const;

private:
    QUuid     m_uuid;
    QString   m_type;
    QString   m_path;
    StoreUnit m_unit;
};

#endif // MERESTOREUNIT_H
