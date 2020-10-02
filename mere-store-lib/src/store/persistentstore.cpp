#include "persistentstore.h"

class Mere::Store::PersistentStore::PersistentStorePrivate
{
public:
    virtual ~PersistentStorePrivate()
    {
    }

    PersistentStorePrivate(PersistentStore *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }

private:
    PersistentStore *q_ptr;
};

Mere::Store::PersistentStore::~PersistentStore()
{

}

Mere::Store::PersistentStore::PersistentStore(const QString &store, QObject *parent)
    : BaseStore(store, parent),
      d_ptr(new PersistentStorePrivate(this))
{

}

Mere::Store::PersistentStore::PersistentStore(const QString &store, const QString &slice, QObject *parent)
    : BaseStore(store, slice, parent),
      d_ptr(new PersistentStorePrivate(this))
{
}
