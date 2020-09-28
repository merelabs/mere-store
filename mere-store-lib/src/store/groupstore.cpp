#include "groupstore.h"

class Mere::Store::GroupStore::GroupStorePrivate
{
public:
    ~GroupStorePrivate()
    {
    }

    GroupStorePrivate(GroupStore *q)
        : q_ptr(q)
    {

    }

private:
    GroupStore *q_ptr;
};

Mere::Store::GroupStore::~GroupStore()
{
}

Mere::Store::GroupStore::GroupStore(const QString &store, QObject *parent)
    : GroupStore(store, "", parent)
{
}

Mere::Store::GroupStore::GroupStore(const QString &store, const QString &slice, QObject *parent)
    : PairStore(store, slice, parent),
      d_ptr(new GroupStorePrivate(this))
{
}

QVariant Mere::Store::GroupStore::list(const QString &key, const int &limit)
{
    return PairStore::list("^" + key);
}
