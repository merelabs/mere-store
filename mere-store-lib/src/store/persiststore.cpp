#include "persiststore.h"

class Mere::Store::PersistStore::PersistStorePrivate
{
public:
    virtual ~PersistStorePrivate()
    {
    }

    PersistStorePrivate(PersistStore *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }

private:
    PersistStore *q_ptr;
};

Mere::Store::PersistStore::~PersistStore()
{
    if (d_ptr)
    {
        delete d_ptr;
        d_ptr = nullptr;
    }
}

Mere::Store::PersistStore::PersistStore(const QString &store, QObject *parent)
    : BaseStore(store, parent),
      d_ptr(new PersistStorePrivate(this))
{
}

Mere::Store::PersistStore::PersistStore(const QString &store, const QString &slice, QObject *parent)
    : BaseStore(store, slice, parent),
      d_ptr(new PersistStorePrivate(this))
{
}
