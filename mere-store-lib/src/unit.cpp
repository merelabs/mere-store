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
        Q_UNUSED(q_ptr)
    }

    MereStoreUnitAttributes attributes() const
    {
        return m_attributes;
    }

    void setAttributes(QMap<QString, QVariant> attributes)
    {
        m_attributes.clear();
        m_attributes.insert(attributes);
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

    QList<Link> links() const
    {
        return m_links;
    }

    void setLink(const QString &name, const UnitRef &ref)
    {
        setLink(Link(name, ref));
    }

    void setLinks(const QString &name, const QList<UnitRef> &refs)
    {
        setLink(Link(name, refs));
    }

    void addLink(const QString &name, const UnitRef &ref)
    {
        bool found = false;

        QList<Link> links = this->links();
        QListIterator<Link> it(links);
        while (it.hasNext())
        {
            Link link = it.next();
            if (name.compare(link.name()) == 0)
            {
                link.addUnit(ref);
                found = true;
                break;
            }
        }

        if (!found)
        {
            Link link(name, ref);
            addLink(link);
        }
    }

    void addLinks(const QString &name, const QList<UnitRef> &refs)
    {
        bool found = false;
        QList<Link> links = this->links();
        QListIterator<Link> it(links);
        while (it.hasNext())
        {
            Link link = it.next();
            if (name.compare(link.name()) == 0)
            {
                link.addUnits(refs);
                found = true;
                break;
            }
        }

        if (!found)
        {
            Link link(name, refs);
            addLink(link);
        }
    }

    void setLink(const Link &link)
    {
        m_links.clear();
        addLink(link);
    }

    void setLinks(const QList<Link> &links)
    {
        m_links.clear();
        addLinks(links);
    }

    void addLink(const Link &link)
    {
        bool found = false;
        QListIterator<Link> it(m_links);
        while (it.hasNext())
        {
            Link _link = it.next();
            if (_link.name().compare(link.name()) == 0)
            {
                _link.addUnits(link.units());
                found = true;
                break;
            }
        }

        if (!found)
            m_links.append(link);
    }

    void addLinks(const QList<Link> &links)
    {
        QListIterator<Link> it(links);
        while (it.hasNext())
        {
            Link link = it.next();
            addLink(link);
        }
    }

private:
    MereStoreUnitAttributes m_attributes;
    QList<Link> m_links;

    Unit *q_ptr;
};


Mere::Store::Unit::~Unit()
{
    delete d_ptr;
    d_ptr = nullptr;
}

Mere::Store::Unit::Unit()
    : d_ptr(new UnitPrivate(this))
{
    setPath(".");
}

Mere::Store::Unit::Unit(const QString &type)
    : d_ptr(new UnitPrivate(this))
{
    setPath(".");
    setType(type);
}

Mere::Store::Unit::Unit(const QMap<QString, QVariant> &map)
    : d_ptr(new UnitPrivate(this))
{
    QString id   = map.value("id").toString();
    QString type = map.value("type").toString();
    QString path = map.value("path").toString();

    setId(id);
    setType(type);
    setPath(path);

    // Attributes
    MereStoreUnitAttributes attrs = map.value("attr").toMap();
    setAttributes(attrs);

    // Links
    QMap<QString, QVariant> links = map.value("link").toMap();
    QMapIterator<QString, QVariant> lit(links);
    while (lit.hasNext())
    {
        lit.next();

        QList<QVariant> list = lit.value().toList();
        QListIterator<QVariant> listIt(list);
        while (listIt.hasNext())
        {
            QMap<QString, QVariant> map = listIt.next().toMap();
            UnitRef ref(map);

            addLink(lit.key(), ref);
        }
    }
}

Mere::Store::MereStoreUnitAttributes Mere::Store::Unit::attributes() const
{
    return d_ptr->attributes();
}

void Mere::Store::Unit::setAttributes(MereStoreUnitAttributes attributes)
{
    return d_ptr->setAttributes(attributes);
}

void Mere::Store::Unit::addAttribute(const QString &name, const QVariant &value)
{
    return d_ptr->addAttribute(name, value);
}

void Mere::Store::Unit::addAttributes(MereStoreUnitAttributes attributes)
{
    return d_ptr->addAttributes(attributes);
}

QList<Mere::Store::Link> Mere::Store::Unit::links() const
{
    return d_ptr->links();
}

void Mere::Store::Unit::setLink(const QString &name, const UnitRef &ref)
{
    return d_ptr->setLink(name, ref);
}

void Mere::Store::Unit::setLinks(const QString &name, const QList<UnitRef> &refs)
{
    return d_ptr->setLinks(name, refs);
}

void Mere::Store::Unit::setLink(const Link &link)
{
    return d_ptr->setLink(link);
}

void Mere::Store::Unit::setLinks(const QList<Link> &links)
{
    return d_ptr->setLinks(links);
}

void Mere::Store::Unit::addLink(const QString &name, const UnitRef &ref)
{
    return d_ptr->addLink(name, ref);
}

void Mere::Store::Unit::addLinks(const QString &link, const QList<UnitRef> &refs)
{
    return d_ptr->addLinks(link, refs);
}

Mere::Store::MereStoreUnitMap Mere::Store::Unit::map() const
{
    MereStoreUnitMap unit;

    MereStoreUnitMap base = Ref::map();

    unit.insert(base);

    // attributes
    unit.insert("attr", attributes());

    // links
//    unit.insert("link", links());

    QList<QVariant> _refs;
    QMap<QString, QVariant> _links;

    QList<Link> links = this->links();
    QListIterator<Link> it(links);
    while (it.hasNext())
    {
        Link link = it.next();

        QList<UnitRef> refs = link.units();

        QListIterator<UnitRef> i(refs);
        while (i.hasNext())
        {
            UnitRef ref = i.next();
            _refs.append(ref.map());
        }

        _links.insert(link.name(), _refs);
    }

    unit.insert("link", _links);
    return unit;
}
