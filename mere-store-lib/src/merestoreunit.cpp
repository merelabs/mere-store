#include "merestoreunit.h"

class MereStoreUnit::MereStoreUnitPrivate
{
public:
    ~MereStoreUnitPrivate()
    {

    }

    MereStoreUnitPrivate(MereStoreUnit *q)
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

    void setLink(const QString &link, const MereStoreUnitRef &ref)
    {
        m_links.insert(link, QList<MereStoreUnitRef>({ref}));
    }

    void setLinks(const QString &link, const QList<MereStoreUnitRef> &refs)
    {
        m_links.insert(link, refs);
    }

    void addLink(const QString &link, const MereStoreUnitRef &ref)
    {
        if (m_links.contains(link))
        {
            QList<MereStoreUnitRef> refs = m_links.value(link);
            refs.append(ref);

            m_links.insert(link, refs);
        }
        else
        {
            m_links.insert(link, QList<MereStoreUnitRef>({ref}));
        }
    }

    void addLinks(const QString &link, const QList<MereStoreUnitRef> &refs)
    {
        if (m_links.contains(link))
        {
            QList<MereStoreUnitRef> _refs = m_links.value(link);
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

    MereStoreUnit *q_ptr;
};


MereStoreUnit::~MereStoreUnit()
{
    delete d_ptr;
}

MereStoreUnit::MereStoreUnit(const QString &type)
    : d_ptr(new MereStoreUnitPrivate(this))
{
    setType(type);
}

MereStoreUnitAttributes MereStoreUnit::attributes() const
{
    return d_ptr->attributes();
}

void MereStoreUnit::setAttributes(MereStoreUnitAttributes attributes)
{
    d_ptr->setAttributes(attributes);
}

void MereStoreUnit::addAttribute(const QString &name, const QVariant &value)
{
    return d_ptr->addAttribute(name, value);
}

void MereStoreUnit::addAttributes(MereStoreUnitAttributes attributes)
{
    return d_ptr->addAttributes(attributes);
}

MereStoreUnitLinks MereStoreUnit::links() const
{
    return d_ptr->links();
}

void MereStoreUnit::setLink(const QString &link, const MereStoreUnitRef &ref)
{
    return d_ptr->setLink(link, ref);
}

void MereStoreUnit::setLinks(const QString &link, const QList<MereStoreUnitRef> &refs)
{
    return d_ptr->setLinks(link, refs);
}

void MereStoreUnit::addLink(const QString &link, const MereStoreUnitRef &ref)
{
    return d_ptr->addLink(link, ref);
}

void MereStoreUnit::addLinks(const QString &link, const QList<MereStoreUnitRef> &refs)
{
    return d_ptr->addLinks(link, refs);
}

MereStoreUnitMap MereStoreUnit::map() const
{
    MereStoreUnitMap unit;

    unit.insert("path", path());
    unit.insert("type", type());
    unit.insert("uuid", uuid());
    unit.insert("attr", attributes());

    QList<QVariant> _refs;
    QMap<QString, QVariant> _links;

    MereStoreUnitLinks links = this->links();
    QMapIterator<QString, QList<MereStoreUnitRef>> it(links);
    while (it.hasNext())
    {
        it.next();

        QString link = it.key();

        QList<MereStoreUnitRef> refs = it.value();
        QListIterator<MereStoreUnitRef> i(refs);
        while (i.hasNext())
        {
            MereStoreUnitRef ref = i.next();

            MereStoreUnitRefMap map = ref.map();

            _refs.append(map);
        }

        _links.insert(link, _refs);
    }

    unit.insert("link", _links);

    return unit;
}
