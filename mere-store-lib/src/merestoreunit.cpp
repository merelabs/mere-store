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

Metadata MereStoreUnit::meta() const
{
    return m_meta;
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
    map.insert("meta", meta().map());

//    map.insert("type", type());
//    map.insert("path", path());
    map.insert("unit", unit());
//    map.insert("created-by", createdBy());
//    map.insert("created-at", createdAt());
//    map.insert("updated-by", updatedBy());
//    map.insert("updated-at", updatedAt());

    return map;
}
