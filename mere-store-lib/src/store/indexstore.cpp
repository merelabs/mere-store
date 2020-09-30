#include "indexstore.h"

Mere::Store::IndexStore::IndexStore(const Store &store, const Index &index, QObject *parent)
    : PairStore(store.home() + "/indexes/"+ index.name())
{

}

Mere::Store::IndexStore::IndexStore(const Store &store, const QString &name, QObject *parent)
    : PairStore(store.home() + "/indexes/"+ name)
{

}
