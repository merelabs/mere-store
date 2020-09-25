#include "unit.h"

class Mere::Store::Unit::UnitPrivate
{
public:
    ~UnitPrivate()
    {

    }

    UnitPrivate(Unit *q)
        :q_ptr(q)
    {

    }

    MereStoreUnitAttributes attributes() const
    {
        return m_attributes;
    }

    void setAttributes(MereStoreUnitAttributes attributes)
    {
        m_attributes = attributes;
    }

    void addAttribute(const QString &name, const QVariant &value)
    {
        m_attributes.insert(name, value);
    }

    void addAttributes(MereStoreUnitAttributes attributes)
    {
        QMapIterator<QString, QVariant> it(attributes);
        while (it.hasNext())
        {
            it.next();
            addAttribute(it.key(), it.value());
        }
    }

    MereStoreUnitLinks links() const
        {
            return m_links;
        }

        void setLink(const QString &link, const UnitRef &ref)
        {
            m_links.insert(link, QList<UnitRef>({ref}));
        }

        void setLinks(const QString &link, const QList<UnitRef> &refs)
        {
            m_links.insert(link, refs);
        }

        void addLink(const QString &link, const UnitRef &ref)
        {
            if (m_links.contains(link))
            {
                QList<UnitRef> refs = m_links.value(link);
                refs.append(ref);

                m_links.insert(link, refs);
            }
            else
            {
                m_links.insert(link, QList<UnitRef>({ref}));
            }
        }

        void addLinks(const QString &link, const QList<UnitRef> &refs)
        {
            if (m_links.contains(link))
            {
                QList<UnitRef> _refs = m_links.value(link);
                _refs.append(refs);

                m_links.insert(link, _refs);
            }
            else
            {
                m_links.insert(link, refs);
            }
        }

private:
    MereStoreUnitAttributes m_attributes;
    MereStoreUnitLinks m_links;

    Unit *q_ptr;
};


Mere::Store::Unit::~Unit()
{
    delete d_ptr;
}

Mere::Store::Unit::Unit(const QString &type)
    : d_ptr(new UnitPrivate(this))
{
    setType(type);
}

Mere::Store::MereStoreUnitAttributes Mere::Store::Unit::attributes() const
{
    return d_ptr->attributes();
}

void Mere::Store::Unit::setAttributes(MereStoreUnitAttributes attributes)
{
    d_ptr->setAttributes(attributes);
}

void Mere::Store::Unit::addAttribute(const QString &name, const QVariant &value)
{
    return d_ptr->addAttribute(name, value);
}

void Mere::Store::Unit::addAttributes(MereStoreUnitAttributes attributes)
{
    return d_ptr->addAttributes(attributes);
}

Mere::Store::MereStoreUnitLinks Mere::Store::Unit::links() const
{
    return d_ptr->links();
}

void Mere::Store::Unit::setLink(const QString &link, const UnitRef &ref)
{
    return d_ptr->setLink(link, ref);
}

void Mere::Store::Unit::setLinks(const QString &link, const QList<UnitRef> &refs)
{
    return d_ptr->setLinks(link, refs);
}

void Mere::Store::Unit::addLink(const QString &link, const UnitRef &ref)
{
    return d_ptr->addLink(link, ref);
}

void Mere::Store::Unit::addLinks(const QString &link, const QList<UnitRef> &refs)
{
    return d_ptr->addLinks(link, refs);
}

Mere::Store::MereStoreUnitMap Mere::Store::Unit::map() const
{
    MereStoreUnitMap unit;

    unit.insert("path", path());
    unit.insert("type", type());
    unit.insert("uuid", uuid());
    unit.insert("attr", attributes());

    QList<QVariant> _refs;
    QMap<QString, QVariant> _links;

    MereStoreUnitLinks links = this->links();
    QMapIterator<QString, QList<UnitRef>> it(links);
    while (it.hasNext())
    {
        it.next();

        QString link = it.key();

        QList<UnitRef> refs = it.value();
        QListIterator<UnitRef> i(refs);
        while (i.hasNext())
        {
            UnitRef ref = i.next();

            Mere::Store::UnitRefMap map = ref.map();

            _refs.append(map);
        }

        _links.insert(link, _refs);
    }

    unit.insert("link", _links);
    return unit;
}
