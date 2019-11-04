#include "merestoreunit.h"

MereStoreUnit::~MereStoreUnit()
{

}

MereStoreUnit::MereStoreUnit()
{

}

QUuid MereStoreUnit::uuid() const
{
    return m_uuid;
}

void MereStoreUnit::setUuid(QUuid uuid)
{
    m_uuid = uuid;
}

QString MereStoreUnit::type() const
{
    return m_type;
}

void MereStoreUnit::setType(QString type)
{
    m_type = type;
}

QString MereStoreUnit::path() const
{
    return m_path;
}

void MereStoreUnit::setPath(QString path)
{
    m_path = path;
}

StoreUnit MereStoreUnit::unit() const
{
    return m_unit;
}

void MereStoreUnit::setUnit(StoreUnit unit)
{
    m_unit = unit;
}

QMap<QString, QVariant> MereStoreUnit::map() const
{
    QMap<QString, QVariant> map;

    map.insert("uuid", uuid());
    map.insert("type", type());
    map.insert("path", path());
    map.insert("unit", unit());

    return map;
}
