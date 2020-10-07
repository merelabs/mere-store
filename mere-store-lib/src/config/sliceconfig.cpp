#include "sliceconfig.h"

Mere::Store::SliceConfig::SliceConfig(const QString &home, QObject *parent)
    : Config(home + "/.slice", parent)
{

}

QString Mere::Store::SliceConfig::name() const
{
    return m_name;
}

void Mere::Store::SliceConfig::setName(const QString &name)
{
    m_name = name;
}

Mere::Store::IndexConfig Mere::Store::SliceConfig::index() const
{
    return m_index;
}

void Mere::Store::SliceConfig::setIndex(const IndexConfig &index)
{
    m_index = index;
}
