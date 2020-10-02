#include "entry.h"

class Mere::Store::Entry::EntryPrivate
{
public:
    ~EntryPrivate()
    {

    }

    EntryPrivate(Entry *q)
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

    QMap<QString, QVariant> map() const
    {
        QMap<QString, QVariant> map;

        QListIterator<Pair> it(m_pairs);
        while (it.hasNext())
        {
            Pair pair = it.next();
            map.insert(pair.key(), pair.value());
        }

        return map;
    }

private:
    QList<Pair> m_pairs;
    Entry *q_ptr;
};

Mere::Store::Entry::Entry()
    : d_ptr(new EntryPrivate(this))
{

}

int Mere::Store::Entry::set(const Pair &pair)
{
    return d_ptr->set(pair);
}

int Mere::Store::Entry::set(const QList<Pair> &pairs)
{
    return d_ptr->set(pairs);
}

int Mere::Store::Entry::add(const Pair &pair)
{
    return d_ptr->add(pair);
}

int Mere::Store::Entry::add(const QList<Pair> &pairs)
{
    return d_ptr->add(pairs);
}

int Mere::Store::Entry::del(const Pair &pair)
{
    return d_ptr->del(pair);
}

int Mere::Store::Entry::del(const QList<Pair> &pairs)
{
    return d_ptr->del(pairs);
}

QList<Mere::Store::Pair> Mere::Store::Entry::pairs() const
{
    return d_ptr->pairs();
}

QMap<QString, QVariant> Mere::Store::Entry::map() const
{
    return d_ptr->map();
}

