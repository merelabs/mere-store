#include "unitref.h"

class Mere::Store::UnitRef::UnitRefPrivate
{
public:
    ~UnitRefPrivate()
    {

    }

    UnitRefPrivate(UnitRef *q)
        : m_path(""),
          m_type(""),
          m_uuid(0),
          q_ptr(q)
    {

    }

    QString type() const
    {
        return m_type;
    }

    void setType(const QString &type)
    {
        m_type = type;
    }

    QUuid uuid() const
    {
        return m_uuid;
    }

    void setUuid(const QUuid &uuid)
    {
        m_uuid = uuid;
    }

    QString path() const
    {
        return m_path;
    }

    void setPath(const QString &path)
    {
        m_path = path;
    }

    UnitRefMap map() const
    {
        UnitRefMap ref;

        ref.insert("path", path());
        ref.insert("type", type());
        ref.insert("uuid", uuid());

        return ref;
    }

private:
    QString   m_path;
    QString   m_type;
    QUuid     m_uuid;

    UnitRef *q_ptr;
};

Mere::Store::UnitRef::~UnitRef()
{

}

Mere::Store::UnitRef::UnitRef()
    : d_ptr(new UnitRefPrivate(this))
{

}

QString Mere::Store::UnitRef::type() const
{
    return d_ptr->type();
}

void Mere::Store::UnitRef::setType(const QString type)
{
    return d_ptr->setType(type);
}

QUuid Mere::Store::UnitRef::uuid() const
{
    return d_ptr->uuid();
}

void Mere::Store::UnitRef::setUuid(const QUuid &uuid)
{
    return d_ptr->setUuid(uuid);
}

QString Mere::Store::UnitRef::path() const
{
    return d_ptr->path();
}

void Mere::Store::UnitRef::setPath(const QString &path)
{
    return d_ptr->setPath(path);
}

Mere::Store::UnitRefMap Mere::Store::UnitRef::map() const
{
    return d_ptr->map();
}
