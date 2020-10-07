#include "storeconfig.h"

Mere::Store::StoreConfig::StoreConfig(const QString &home, QObject *parent)
    : Config(home + "/.store", parent)
{

}

QString Mere::Store::StoreConfig::name() const
{
    return m_name;
}

void Mere::Store::StoreConfig::setName(const QString &name)
{
    m_name = name;
}

Mere::Store::IndexConfig Mere::Store::StoreConfig::index() const
{
    return m_index;
}

void Mere::Store::StoreConfig::setIndex(const IndexConfig &index)
{
    m_index = index;
}
