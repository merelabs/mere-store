#include "jsonstore.h"

Mere::Store::JsonStore::~JsonStore()
{

}

Mere::Store::JsonStore::JsonStore(const QString &store, QObject *parent)
    : JsonStore(store, "", parent)
{
}

Mere::Store::JsonStore::JsonStore(const QString &store, const QString &slice, QObject *parent)
    : PairStore(store, slice, parent)
{
}

void Mere::Store::JsonStore::save(QJsonObject unit)
{
    Q_UNUSED(unit)
}

void Mere::Store::JsonStore::create(QJsonObject unit)
{
    Q_UNUSED(unit)
}


void Mere::Store::JsonStore::update(QJsonObject unit)
{
    Q_UNUSED(unit)
}

void Mere::Store::JsonStore::fetch(QJsonObject unit)
{
    Q_UNUSED(unit)
}

void Mere::Store::JsonStore::remove(QJsonObject unit)
{
    Q_UNUSED(unit)
}

void Mere::Store::JsonStore::search(QJsonObject query)
{
    Q_UNUSED(query)
}
