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
//    IndexStore store(m_store, m_name);

//    // for testing
//    store.create();

//    int err = store.open();
//    if (!err)
//        err = store.set(key, value);

//    return err;
    return 0;
}
