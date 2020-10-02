#include "unitref.h"

#include "mere/utils/merestringutils.h"

QString Mere::Store::UnitRef::KEY = "path:%1:type:%2:uuid:%3:";

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
        Q_UNUSED(q_ptr)
    }

    QString path() const
    {
        return m_path;
    }

    void setPath(const QString &path)
    {
        m_path = path;
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

    UnitRefMap map() const
    {
        UnitRefMap ref;

        ref.insert("path", path());
        ref.insert("type", type());
        ref.insert("uuid", uuid());

        return ref;
    }

    QString key() const
    {
        return KEY.arg(path(), type(), uuid().toString());
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

Mere::Store::UnitRef::UnitRef(const QString &ref)
    : d_ptr(new UnitRefPrivate(this))
{
    QVector<QStringRef> parts = ref.splitRef(":");

    setPath(parts.at(1).toString());
    setType(parts.at(3).toString());
    setUuid(parts.at(5).toString());
}

Mere::Store::UnitRef::UnitRef(const QMap<QString, QVariant> &map)
    : d_ptr(new UnitRefPrivate(this))
{
    setPath(map.value("path").toString());
    setType(map.value("type").toString());
    setUuid(map.value("uuid").toString());
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

bool Mere::Store::UnitRef::isValid() const
{
    if (MereStringUtils::isBlank(path()))
        return false;

    if (MereStringUtils::isBlank(type()))
        return false;

    if (uuid().isNull())
        return false;

    return true;
}

QString Mere::Store::UnitRef::key() const
{
    return d_ptr->key();
}

Mere::Store::UnitRefMap Mere::Store::UnitRef::map() const
{
    return d_ptr->map();
}
