#include "merestoreunit.h"

class MereStoreUnit::MereStoreUnitPrivate
{
public:
    ~MereStoreUnitPrivate()
    {

    }

    MereStoreUnitPrivate(const QString type, MereStoreUnit *q)
        : m_type(type),
          q_ptr(q)
    {

    }

    QString type() const
    {
        return m_type;
    }

//    void setType(const QString type)
//    {
//        m_type = type;
//    }

    QUuid uuid() const
    {
        return m_uuid;
    }

    void setUuid(QUuid uuid)
    {
        m_uuid = uuid;
    }

    QString path() const
    {
        return m_path;
    }

    void setPath(QString path)
    {
        m_path = path;
    }

    Metadata meta() const
    {
        return m_meta;
    }


    StoreUnitAttributes attributes() const
    {
        return m_attributes;
    }

    void setAttributes(StoreUnitAttributes attributes)
    {
        m_attributes = attributes;
    }

    StoreUnit get() const
    {
        return m_unit;
    }

    void set(StoreUnit unit)
    {
        m_unit = unit;
    }


private:
    QString   m_type;
    QUuid     m_uuid;
    QString   m_path;
    Metadata  m_meta;
    StoreUnit m_unit;

//    StoreUnitFields     m_fields;
    StoreUnitAttributes m_attributes;
//    StoreUnitProperties m_properties;

    MereStoreUnit *q_ptr;
};


MereStoreUnit::~MereStoreUnit()
{
    delete d_ptr;
}

MereStoreUnit::MereStoreUnit(const QString type)
    : d_ptr(new MereStoreUnitPrivate(type, this))
{

}

QString MereStoreUnit::type() const
{
    return d_ptr->type();
}

//void MereStoreUnit::setType(const QString type)
//{
//    d_ptr->setType(type);
//}

QUuid MereStoreUnit::uuid() const
{
    return d_ptr->uuid();
}

void MereStoreUnit::setUuid(QUuid uuid)
{
    d_ptr->setUuid(uuid);
}

QString MereStoreUnit::path() const
{
    return d_ptr->path();
}

void MereStoreUnit::setPath(QString path)
{
    d_ptr->setPath(path);
}

//Metadata MereStoreUnit::meta() const
//{
//    return m_meta;
//}

//StoreUnitFields MereStoreUnit::fields() const
//{
//    return m_fields;
//}

//void MereStoreUnit::setFields(StoreUnitFields fields)
//{
//    m_fields = fields;
//}

StoreUnitAttributes MereStoreUnit::attributes() const
{
    return d_ptr->attributes();
}

void MereStoreUnit::setAttributes(StoreUnitAttributes attributes)
{
    d_ptr->setAttributes(attributes);
}

//StoreUnitProperties MereStoreUnit::properties() const
//{
//    return m_properties;
//}

//void MereStoreUnit::setProperties(StoreUnitProperties properties)
//{
//    m_properties = properties;
//}

StoreUnit MereStoreUnit::get() const
{
    return d_ptr->get();
}

void MereStoreUnit::set(StoreUnit unit)
{
    d_ptr->set(unit);
}

StoreUnit MereStoreUnit::map() const
{
    StoreUnit unit;

    unit.insert("type", type());
    unit.insert("uuid", uuid());
//    map.insert("meta", meta().map());
//    map.insert("unit", get());
//    map.insert("flds", fields());
    unit.insert("attr", attributes());
//    map.insert("prop", properties());

    return unit;
}
