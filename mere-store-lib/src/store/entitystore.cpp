#include "entitystore.h"
#include "../entity.h"

class Mere::Store::EntityStore::EntityStorePrivate
{
public:
    ~EntityStorePrivate()
    {
    }

    EntityStorePrivate(EntityStore *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }

private:
    EntityStore *q_ptr;
};

Mere::Store::EntityStore::~EntityStore()
{
}

Mere::Store::EntityStore::EntityStore(const QString &store, QObject *parent)
    : PairStore(store, parent),
      d_ptr(new EntityStorePrivate(this))
{
}

Mere::Store::EntityStore::EntityStore(const QString &store, const QString &slice, QObject *parent)
    : PairStore(store, slice, parent),
      d_ptr(new EntityStorePrivate(this))
{
}

int Mere::Store::EntityStore::create(Entity &entity)
{
    QMap<QString, QVariant> map = entity.map();

    return this->set(map);
}

int Mere::Store::EntityStore::update(Entity &entity)
{
    QMap<QString, QVariant> map = entity.map();

    return this->set(map);
}

QVariant Mere::Store::EntityStore::list(const QString &key, const int &limit)
{
    Q_UNUSED(limit)
    return PairStore::list("^" + key);
}
