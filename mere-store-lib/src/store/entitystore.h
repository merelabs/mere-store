#ifndef GROUPSTORE_H
#define GROUPSTORE_H

#include "pairstore.h"


namespace Mere
{
namespace Store
{

class Entity;
class MERE_STORE_LIBSPEC EntityStore : public PairStore
{
    Q_OBJECT
public:
    virtual ~EntityStore();
    explicit EntityStore(const QString &store, QObject *parent = nullptr);
    explicit EntityStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual int create(Entity &entity);
    virtual int update(Entity &entity);

    virtual QVariant list(const QString &key, const int &limit = 0) override;

private:
    using BaseStore::create;

    class EntityStorePrivate;
    EntityStorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // GROUPSTORE_H
