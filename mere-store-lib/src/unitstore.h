#ifndef MEREDEFAULTSTORE_H
#define MEREDEFAULTSTORE_H

#include "mapstore.h"
#include "unit.h"
#include "engine/engine.h"

namespace Mere
{
namespace Store
{

class MERE_STORE_LIBSPEC UnitStore : public MapStore
{
    Q_OBJECT
public:
    virtual ~UnitStore();
    explicit UnitStore(const QString &store, QObject *parent = nullptr);
    explicit UnitStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual int create(Unit &unit);
    virtual int update(Unit &unit) ;
    virtual int fetch(Unit &unit) ;
    virtual int remove(Unit &unit) ;

    virtual QVariant list(const int &limit = 25) override;
//    virtual QVariant list(const QString &key, const int &limit = 25) override;

private:
    // Just to tell compiler to avoid warning!
    using MapStore::create;
    using MapStore::update;
    using MapStore::fetch;
    using MapStore::remove;
//    using MereMapStore::list;

    QString key(const Unit unit) const;
};

} // namespace Store
} // namespace Mere


#endif // MEREDEFAULTSTORE_H
