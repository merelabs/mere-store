#include "merestoreunitref.h"

class MereStoreUnitRef::MereStoreUnitRefPrivate
{
public:
    ~MereStoreUnitRefPrivate()
    {

    }

    MereStoreUnitRefPrivate(MereStoreUnitRef *q)
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

    MereStoreUnitRefMap map() const
    {
        MereStoreUnitRefMap ref;

        ref.insert("path", path());
        ref.insert("type", type());
        ref.insert("uuid", uuid());

        return ref;
    }

private:
    QString   m_path;
    QString   m_type;
    QUuid     m_uuid;

    MereStoreUnitRef *q_ptr;
};

MereStoreUnitRef::~MereStoreUnitRef()
{

}

MereStoreUnitRef::MereStoreUnitRef()
    : d_ptr(new MereStoreUnitRefPrivate(this))
{

}

QString MereStoreUnitRef::type() const
{
    return d_ptr->type();
}

void MereStoreUnitRef::setType(const QString type)
{
    return d_ptr->setType(type);
}

QUuid MereStoreUnitRef::uuid() const
{
    return d_ptr->uuid();
}

void MereStoreUnitRef::setUuid(const QUuid &uuid)
{
    return d_ptr->setUuid(uuid);
}

QString MereStoreUnitRef::path() const
{
    return d_ptr->path();
}

void MereStoreUnitRef::setPath(const QString &path)
{
    return d_ptr->setPath(path);
}

MereStoreUnitRefMap MereStoreUnitRef::map() const
{
    return d_ptr->map();
}
