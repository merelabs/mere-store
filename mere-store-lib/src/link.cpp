#include "link.h"

class Mere::Store::Link::LinkPrivate
{
public:
    ~LinkPrivate()
    {

    }

    LinkPrivate(Link *q)
        :q_ptr(q)
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

    QList<UnitRef> units() const
    {
        return m_units;
    }

    void addUnit(const UnitRef &ref)
    {
        if (m_units.contains(ref))
            return;

        m_units.append(ref);
    }

    void addUnits(const QList<UnitRef> &refs)
    {
        QListIterator<UnitRef> it(refs);
        while (it.hasNext())
        {
            UnitRef ref = it.next();
            addUnit(ref);
        }
    }

    void setUnits(const QList<UnitRef> &refs)
    {
        m_units.clear();
        m_units.append(refs);
    }

    QMap<QString, QVariant> map() const
    {
        QMap<QString, QVariant> map;
        QList<QVariant> list;

        QList<UnitRef> refs =  this->units();
        QListIterator<UnitRef> it(refs);
        while (it.hasNext())
        {
            UnitRef ref = it.next();
            QMap<QString, QVariant> _map = ref.map();
            list.append(_map);
        }

        map.insert(name(), list);

        return map;
    }

private:
    QString m_name;
    QList<UnitRef> m_units;

    Link *q_ptr;
};

Mere::Store::Link::~Link()
{

}

Mere::Store::Link::Link()
    : d_ptr(new LinkPrivate(this))
{

}

Mere::Store::Link::Link(const QString &name, const UnitRef &ref)
    : Link()
{
    setName(name);
    setUnits(QList<UnitRef>({ref}));
}

Mere::Store::Link::Link(const QString &name, const QList<UnitRef> &refs)
    : Link()
{
    setName(name);
    setUnits(refs);
}

QString Mere::Store::Link::name() const
{
    return d_ptr->name();
}

void Mere::Store::Link::setName(const QString &name)
{
    return d_ptr->setName(name);
}

QList<Mere::Store::UnitRef> Mere::Store::Link::units() const
{
    return d_ptr->units();
}

void Mere::Store::Link::addUnit(const UnitRef &ref)
{
    return d_ptr->addUnit(ref);
}

void Mere::Store::Link::addUnits(const QList<UnitRef> &refs)
{
    return d_ptr->addUnits(refs);
}

void Mere::Store::Link::setUnits(const QList<UnitRef> &refs)
{
    return d_ptr->setUnits(refs);
}

QMap<QString, QVariant> Mere::Store::Link::map() const
{
    return d_ptr->map();
}
