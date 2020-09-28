#include "indexer.h"

Mere::Store::Indexer::Indexer(QObject *parent) : QObject(parent)
{

}

void Mere::Store::Indexer::index() const
{

}

void Mere::Store::Indexer::index(const QString &name) const
{

}

void Mere::Store::Indexer::index(const Index &index) const
{
    return this->index(index.name());
}
