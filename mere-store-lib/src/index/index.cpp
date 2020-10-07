#include "index.h"

class Mere::Store::Index::IndexPrivate
{
public:
    ~IndexPrivate()
    {
    }

    IndexPrivate(Index *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }

    QString name() const
    {
        return m_name;
    }

    void setName(const QString &name)
    {
        m_name = name;
    }

    QList<QString> attributes() const
    {
        return m_attributes;
    }

    void addAttribute(const QString &attribute)
    {
        m_attributes.append(attribute);
    }

    void addAttributes(const QList<QString> &attributes)
    {
        m_attributes.append(attributes);
    }

    void setAttribute(const QString &attribute)
    {
        m_attributes.clear();
        m_attributes.append(attribute);
    }

    void setAttributes(const QList<QString> &attributes)
    {
        m_attributes.clear();
        m_attributes.append(attributes);
    }

    bool unique() const
    {
        return m_unique;
    }

    void setUnique(const bool &unique)
    {
        m_unique = unique;
    }

private:
    bool m_unique;
    QString m_name;
    QList<QString> m_attributes;

    Index *q_ptr;
};

Mere::Store::Index::Index()
    : d_ptr(new IndexPrivate(this))
{
}

Mere::Store::Index::Index(const QString &name)
    : d_ptr(new IndexPrivate(this))
{
    setName(name);
}


QString Mere::Store::Index::name() const
{
    return d_ptr->name();
}

void Mere::Store::Index::setName(const QString &name)
{
    return d_ptr->setName(name);
}

QList<QString> Mere::Store::Index::attributes() const
{
    return d_ptr->attributes();
}

void Mere::Store::Index::addAttribute(const QString &attribute)
{
    return d_ptr->addAttribute(attribute);
}

void Mere::Store::Index::addAttributes(const QList<QString> &attributes)
{
    return d_ptr->addAttributes(attributes);
}

void Mere::Store::Index::setAttribute(const QString &attribute)
{
    return d_ptr->setAttribute(attribute);
}

void Mere::Store::Index::setAttributes(const QList<QString> &attributes)
{
    return d_ptr->setAttributes(attributes);
}

bool Mere::Store::Index::unique() const
{
    return d_ptr->unique();
}

void Mere::Store::Index::setUnique(const bool &unique)
{
    d_ptr->setUnique(unique);
}
