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

StoreUnitFields MereStoreUnit::fields() const
{
    return m_fields;
}

void MereStoreUnit::fields(StoreUnitFields fields)
{
    m_fields = fields;
}

StoreUnitAttributes MereStoreUnit::attributes() const
{
    return m_attributes;
}

void MereStoreUnit::attributes(StoreUnitAttributes attributes)
{
    m_attributes = attributes;
}

StoreUnitProperties MereStoreUnit::properties() const
{
    return m_properties;
}

void MereStoreUnit::properties(StoreUnitProperties properties)
{
    m_properties = properties;
}

StoreUnit MereStoreUnit::get() const
{
    QMap<QString, QVariant> get;

    return get;
}

void MereStoreUnit::set(StoreUnit unit)
{
    m_unit = unit;
}

QMap<QString, QVariant> MereStoreUnit::map() const
{
    QMap<QString, QVariant> map;

    map.insert("uuid", uuid());
    map.insert("meta", meta().map());
    map.insert("unit", get());
    map.insert("flds", fields());
    map.insert("attr", attributes());
    map.insert("prop", properties());

    return map;
}
