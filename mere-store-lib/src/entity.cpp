#include "entity.h"

class Mere::Store::Entity::EntityPrivate
{
public:
    ~EntityPrivate()
    {

    }

    EntityPrivate(Entity *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }

    int set(const Pair &pair)
    {
        m_pairs.clear();
        m_pairs.append(pair);

        return 0;
    }

    int set(const QList<Pair> &pairs)
    {
        m_pairs.clear();
        m_pairs.append(pairs);

        return 0;
    }

    int add(const Pair &pair)
    {
        m_pairs.append(pair);

        return 0;
    }

    int add(const QList<Pair> &pairs)
    {
        m_pairs.append(pairs);

        return 0;
    }

    int del(const Pair &pair)
    {
        m_pairs.removeOne(pair);

        return 0;
    }

    int del(const QList<Pair> &pairs)
    {
        QListIterator<Pair> it(pairs);
        while (it.hasNext())
        {
            Pair pair = it.next();
            m_pairs.removeOne(pair);
        }

        return 0;
    }

    QList<Mere::Store::Pair> pairs() const
    {
        return m_pairs;
    }

    int add(const QString &key, const QVariant &value)
    {
        m_entries.insert(key, value);

        return 0;
    }

    int set(const QMap<QString, QVariant> &entries)
    {
        m_entries.clear();
        m_entries.insert(entries);

        return 0;
    }

    QMap<QString, QVariant> map() const
    {
//        QMap<QString, QVariant> map;

//        QListIterator<Pair> it(m_pairs);
//        while (it.hasNext())
//        {
//            Pair pair = it.next();
//            map.insert(pair.key(), pair.value());
//        }

//        return map;
        return m_entries;
    }

    UnitRef ref() const
    {
        return m_ref;
    }

    void set(const Ref &ref)
    {
        m_ref.setPath(ref.path());
        m_ref.setType(ref.type());
        m_ref.setUuid(ref.uuid());
    }

private:
    UnitRef m_ref;

    QList<Pair> m_pairs;

    QMap<QString, QVariant> m_entries;
    Entity *q_ptr;
};

Mere::Store::Entity::~Entity()
{

}

Mere::Store::Entity::Entity()
    : d_ptr(new EntityPrivate(this))
{

}

Mere::Store::Entity::Entity(const Ref &ref)
    : d_ptr(new EntityPrivate(this))
{

//    QString key = ref.toString();
    QMap<QString, QVariant> flatten;

    QMap<QString, QVariant> map = ref.map();

    // Attributes
    QMap<QString, QVariant> attributes = map.value("attr").toMap();
    QMapIterator<QString, QVariant> ait(attributes);
    while (ait.hasNext())
    {
        ait.next();

        QString key = QString("path:%1:type:%2:uuid:%3:attr:%4").arg(ref.path(),
                                                                     ref.type(),
                                                                     ref.uuid().toString(),
                                                                     ait.key());
        flatten.insert(key, ait.value());
    }

    // Links
    QMap<QString, QVariant> links = map.value("link").toMap();
    QMapIterator<QString, QVariant> lit(links);
    while (lit.hasNext())
    {
        lit.next();

        QList<QVariant> list = lit.value().toList();

        QListIterator<QVariant> vit(list);
        while (vit.hasNext())
        {
            QMap<QString, QVariant> lref = vit.next().toMap();

            QString key = QString("path:%1:type:%2:uuid:%3:link:%4:path:%5:type:%6:uuid:%7").arg(
                                            ref.path(),
                                            ref.type(),
                                            ref.uuid().toString(),lit.key(),
                                            lref.value("path").toString(),
                                            lref.value("type").toString(),
                                            lref.value("uuid").toString());
            flatten.insert(key, lit.value());
        }
    }

    d_ptr->set(flatten);
    d_ptr->set(ref);
}

Mere::Store::UnitRef Mere::Store::Entity::ref() const
{
    return d_ptr->ref();
}

void Mere::Store::Entity::set(const Ref &ref)
{
    return d_ptr->set(ref);
}

int Mere::Store::Entity::set(const Pair &pair)
{
    return d_ptr->set(pair);
}

int Mere::Store::Entity::set(const QList<Pair> &pairs)
{
    return d_ptr->set(pairs);
}

int Mere::Store::Entity::add(const Pair &pair)
{
    return d_ptr->add(pair);
}

int Mere::Store::Entity::add(const QList<Pair> &pairs)
{
    return d_ptr->add(pairs);
}

int Mere::Store::Entity::del(const Pair &pair)
{
    return d_ptr->del(pair);
}

int Mere::Store::Entity::del(const QList<Pair> &pairs)
{
    return d_ptr->del(pairs);
}

QList<Mere::Store::Pair> Mere::Store::Entity::pairs() const
{
    return d_ptr->pairs();
}

int Mere::Store::Entity::add(const QString &key, const QVariant &value)
{
    return d_ptr->add(key, value);
}

int Mere::Store::Entity::set(const QMap<QString, QVariant> &entries)
{
    return d_ptr->set(entries);
}

QMap<QString, QVariant> Mere::Store::Entity::map() const
{
    return d_ptr->map();
}
