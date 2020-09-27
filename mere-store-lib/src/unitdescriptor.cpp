#include "unitdescriptor.h"

UnitDescriptor::~UnitDescriptor()
{

}

UnitDescriptor::UnitDescriptor()
{

}

QUuid UnitDescriptor::uuid() const
{
    return m_uuid;
}

void UnitDescriptor::setUuid(QUuid uuid)
{
    m_uuid = uuid;
}

QString UnitDescriptor::type() const
{
    return m_type;
}

void UnitDescriptor::setType(QString type)
{
    m_type = type;
}

QString UnitDescriptor::path() const
{
    return m_path;
}

void UnitDescriptor::setPath(QString path)
{
    m_path = path;
}

QString UnitDescriptor::createdBy() const
{
    return m_createdBy;
}

void UnitDescriptor::setCreatedBy(const QString &by)
{
    m_createdBy = by;
}

QDateTime UnitDescriptor::createdAt() const
{
    return m_createdAt;
}

void UnitDescriptor::setCreatedAt(const QDateTime &datetime)
{
    m_createdAt = datetime;
}

QString UnitDescriptor::updatedBy() const
{
    return m_updatedBy;
}

void UnitDescriptor::setUpdatedBy(const QString &by)
{
    m_updatedBy = by;
}

QDateTime UnitDescriptor::updatedAt() const
{
    return m_updatedAt;
}

void UnitDescriptor::setUpdatedAt(const QDateTime &datetime)
{
    m_updatedAt = datetime;
}

QMap<QString, QVariant> UnitDescriptor::map() const
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
