#include "indexconfig.h"

Mere::Store::IndexConfig::IndexConfig()
{

}

Mere::Store::Index Mere::Store::IndexConfig::index(const QString &name) const
{
    Q_UNUSED(name)
    Index index;

    return index;
}

QList<Mere::Store::Index> Mere::Store::IndexConfig::indexes() const
{
    return m_indexes;
}

void Mere::Store::IndexConfig::addIndex(const Index &index)
{
    m_indexes.append(index);
}

void Mere::Store::IndexConfig::addIndexes(const QList<Index> &indexes)
{
    m_indexes.append(indexes);
}

void Mere::Store::IndexConfig::setIndex(const Index &index)
{
    m_indexes.clear();
    addIndex(index);
}

void Mere::Store::IndexConfig::setIndexes(const QList<Index> &indexes)
{
    m_indexes.clear();
    addIndexes(indexes);
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
