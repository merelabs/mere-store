#include "graphstore.h"

class Mere::Store::GraphStore::GraphStorePrivate
{
public:
    virtual ~GraphStorePrivate()
    {
    }

    GraphStorePrivate(GraphStore *q)
        : q_ptr(q)
    {
    }

    int del(const UnitRef &ref, const QString &predicate, HexaStore::Flow flow) const
    {
        const QString vertex = ref.key();

        return q_ptr->del(vertex, predicate, flow);
    }

    QList<Mere::Store::UnitRef> vertex(const UnitRef &ref, HexaStore::Flow flow) const
    {
        QString vertex = ref.key();
        QList<QString> vertexes = q_ptr->vertex(vertex, flow);

        return refs(vertexes);
    }

    QList<Mere::Store::UnitRef> vertex(const UnitRef &ref, const QString &predicate, HexaStore::Flow flow) const
    {
        QString vertex = ref.key();
        QList<QString> vertexes = q_ptr->vertex(vertex, predicate, flow);

        return refs(vertexes);
    }

private:
    QList<Mere::Store::UnitRef> refs(const QList<QString> &vertexes) const
    {
        QList<Mere::Store::UnitRef> refs;

        QListIterator<QString> it(vertexes);
        while (it.hasNext())
        {
            QString vertex = it.next();

            UnitRef ref(vertex);
            refs.append(ref);
        }

        return refs;
    }

private:
    GraphStore *q_ptr;
};

Mere::Store::GraphStore::~GraphStore()
{
}

Mere::Store::GraphStore::GraphStore(const QString &store, QObject *parent)
    : HexaStore(store, parent),
      d_ptr(new GraphStorePrivate(this))
{

}

Mere::Store::GraphStore::GraphStore(const QString &store, const QString &slice, QObject *parent)
    : HexaStore(store, slice, parent),
      d_ptr(new GraphStorePrivate(this))
{

}

int Mere::Store::GraphStore::add(const Ref &subject, const QString &predicate, const Ref &object) const
{
    return this->add(subject.key(), predicate, object.key());
}

int Mere::Store::GraphStore::del(const Ref &subject, const QString &predicate, const Ref &object) const
{
    return this->del(subject.key(), predicate, object.key());
}

int Mere::Store::GraphStore::del(const UnitRef &ref, const QString &predicate, HexaStore::Flow flow) const
{
    return d_ptr->del(ref, predicate, flow);
}

QList<Mere::Store::UnitRef> Mere::Store::GraphStore::vertex(const UnitRef &ref, HexaStore::Flow flow) const
{
    return d_ptr->vertex(ref, flow);
}

QList<Mere::Store::UnitRef> Mere::Store::GraphStore::vertex(const UnitRef &ref, const QString &predicate, HexaStore::Flow flow) const
{
    return d_ptr->vertex(ref, predicate, flow);
}

