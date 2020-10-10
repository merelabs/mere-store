#ifndef GROUPSTORE_H
#define GROUPSTORE_H

#include "mapstore.h"
#include "../entity.h"

namespace Mere
{
namespace Store
{

class MERE_STORE_LIBSPEC EntityStore : public MapStore
{
    Q_OBJECT
public:
    virtual ~EntityStore();
    explicit EntityStore(const QString &store, QObject *parent = nullptr);
    explicit EntityStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual bool found(const Ref &ref);

    virtual int create(const Entity &entity);
    virtual int update(const Entity &entity);
    virtual int fetch(const Ref &ref, Entity &entity);
    virtual int remove(const Ref &ref);

    virtual QVariant list(const int &limit = 25) override;
    virtual QVariant list(const QString &ref, const int &limit = 25) override;

//private:
    using MapStore::create;
    using MapStore::update;
    using MapStore::fetch;
    using MapStore::remove;

    class EntityStorePrivate;
    EntityStorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // GROUPSTORE_H
