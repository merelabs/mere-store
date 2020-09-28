#include "indexconfig.h"

Mere::Store::IndexConfig::IndexConfig()
{

}

Mere::Store::Index Mere::Store::IndexConfig::index(const QString &name) const
{
    Index index;

    return index;
}

QList<Mere::Store::Index> Mere::Store::IndexConfig::indexes() const
{
    QList<Mere::Store::Index> indexes;

    return indexes;
}

void Mere::Store::IndexConfig::addIndex(const Index &index)
{

}

void Mere::Store::IndexConfig::addIndexes(const QList<Index> &indexes)
{

}

void Mere::Store::IndexConfig::setIndex(const Index &index)
{

}

void Mere::Store::IndexConfig::setIndexes(const QList<Index> &indexes)
{

}

QMap<QString, QVariant> Mere::Store::IndexConfig::map() const
{
    QMap<QString, QVariant> map;

    QListIterator<Index> it(this->m_indexes);
    while (it.hasNext())
    {
        Index index = it.next();

        map.insert(index.name(), QVariant(index.attributes()));
    }

    return map;
}
