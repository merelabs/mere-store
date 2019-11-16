#include "merestoreunitdescriptor.h"

MereStoreUnitDescriptor::~MereStoreUnitDescriptor()
{

}

MereStoreUnitDescriptor::MereStoreUnitDescriptor()
{

}

QUuid MereStoreUnitDescriptor::uuid() const
{
    return m_uuid;
}

void MereStoreUnitDescriptor::setUuid(QUuid uuid)
{
    m_uuid = uuid;
}

QString MereStoreUnitDescriptor::type() const
{
    return m_type;
}

void MereStoreUnitDescriptor::setType(QString type)
{
    m_type = type;
}

QString MereStoreUnitDescriptor::path() const
{
    return m_path;
}

void MereStoreUnitDescriptor::setPath(QString path)
{
    m_path = path;
}

QString MereStoreUnitDescriptor::createdBy() const
{
    return m_createdBy;
}

void MereStoreUnitDescriptor::setCreatedBy(const QString &by)
{
    m_createdBy = by;
}

QDateTime MereStoreUnitDescriptor::createdAt() const
{
    return m_createdAt;
}

void MereStoreUnitDescriptor::setCreatedAt(const QDateTime &datetime)
{
    m_createdAt = datetime;
}

QString MereStoreUnitDescriptor::updatedBy() const
{
    return m_updatedBy;
}

void MereStoreUnitDescriptor::setUpdatedBy(const QString &by)
{
    m_updatedBy = by;
}

QDateTime MereStoreUnitDescriptor::updatedAt() const
{
    return m_updatedAt;
}

void MereStoreUnitDescriptor::setUpdatedAt(const QDateTime &datetime)
{
    m_updatedAt = datetime;
}

QMap<QString, QVariant> MereStoreUnitDescriptor::map() const
{
    QMap<QString, QVariant> map;

    map.insert("uuid", uuid());
    map.insert("type", type());
    map.insert("path", path());
    map.insert("created-by", createdBy());
    map.insert("created-at", createdAt());
    map.insert("updated-by", updatedBy());
    map.insert("updated-at", updatedAt());

    return map;
}
