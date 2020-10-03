#include "unitindexer.h"
#include "../store/indexstore.h"

Mere::Store::UnitIndexer::~UnitIndexer()
{

}
Mere::Store::UnitIndexer::UnitIndexer(Store &store, const QString &name, QObject *parent)
    : Indexer(parent),
      m_store(store),
      m_name(name)
{

}

int Mere::Store::UnitIndexer::index(const QString &key, const QVariant &value) const
{
    IndexStore store(m_store, m_name);

    int err = store.open();
    if (!err)
        err = store.set(key, value);

    return err;
}

QMap<QString, QVariant> Mere::Store::UnitIndexer::find(const QString &what) const
{
    QMap<QString, QVariant> records;

    IndexStore store(m_store, m_name);

    int err = store.open();
    if (!err)
    {
        QVariant var = store.list(what);
        if (var.isValid())
            records = var.toMap();
    }

    return records;
}
