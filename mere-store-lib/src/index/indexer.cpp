#include "indexer.h"

Mere::Store::Indexer::Indexer(QObject *parent) : QObject(parent)
{

}

void Mere::Store::Indexer::index() const
{

}

void Mere::Store::Indexer::index(const QString &name) const
{
    Q_UNUSED(name)
}

void Mere::Store::Indexer::index(const Index &index) const
{
    return this->index(index.name());
}

//void Mere::Store::Indexer::index(const QString &key, const QString &value) const
//{
//    qDebug() << "GOING TO INDEX:" << key;
//}
