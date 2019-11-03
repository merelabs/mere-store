#ifndef MERESTOREUNIT_H
#define MERESTOREUNIT_H

#include "merestoreglobal.h"

#include <QMap>
#include <QUuid>
#include <QString>
#include <QVariant>

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

    virtual QMap<QString, QVariant> map() const;

private:
    QUuid   m_uuid;
    QString m_type;
    QString m_path;
};

#endif // MERESTOREUNIT_H
