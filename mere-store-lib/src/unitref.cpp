#include "unitref.h"

#include "mere/utils/stringutils.h"

class Mere::Store::UnitRef::UnitRefPrivate
{
public:
    ~UnitRefPrivate()
    {

    }

    UnitRefPrivate(UnitRef *q)
        : m_id(""),
          m_type(""),
          m_path(""),
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

    QString id() const
    {
        return m_id;
    }

    void setId(const QString &id)
    {
        m_id = id;
    }


private:
    QString m_id;
    QString m_type;
    QString m_path;

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
    setId(parts.at(5).toString());
}

Mere::Store::UnitRef::UnitRef(const QMap<QString, QVariant> &map)
    : d_ptr(new UnitRefPrivate(this))
{
    setPath(map.value("path").toString());
    setType(map.value("type").toString());
    setId(map.value("uuid").toString());
}

QString Mere::Store::UnitRef::type() const
{
    return d_ptr->type();
}

void Mere::Store::UnitRef::setType(const QString type)
{
    return d_ptr->setType(type);
}

QString Mere::Store::UnitRef::id() const
{
    return d_ptr->id();
}

void Mere::Store::UnitRef::setId(const QString &id)
{
    return d_ptr->setId(id);
}

QString Mere::Store::UnitRef::path() const
{
    return d_ptr->path();
}

void Mere::Store::UnitRef::setPath(const QString &path)
{
    return d_ptr->setPath(path);
}

//bool Mere::Store::UnitRef::isValid() const
//{
//    if (Mere::Utils::StringUtils::isBlank(path()))
//        return false;

//    if (Mere::Utils::StringUtils::isBlank(type()))
//        return false;

//    if (uuid().isNull())
//        return false;

//    return true;
//}

//QString Mere::Store::UnitRef::key() const
//{
//    return d_ptr->key();
//}

//Mere::Store::UnitRefMap Mere::Store::UnitRef::map() const
//{
//    return d_ptr->map();
//}
