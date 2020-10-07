#ifndef MEREDEFAULTSTORE_H
#define MEREDEFAULTSTORE_H

#include "entitystore.h"
#include "../unit.h"
#include "../engine/engine.h"
#include "../index/indexer.h"

namespace Mere
{
namespace Store
{

class MERE_STORE_LIBSPEC UnitStore : public EntityStore
{
    Q_OBJECT
public:
    virtual ~UnitStore();
    explicit UnitStore(const QString &store, QObject *parent = nullptr);
    explicit UnitStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual int create(Unit &unit);
    virtual int update(const Unit &unit) ;
    virtual int fetch(const Ref &ref, Unit &unit) ;
    virtual int remove(const Ref &ref) ;

    virtual QVariant list(const int &limit = 25) override;

     Indexer* indexer(const QString &name);

     QList<UnitRef> find(const QString &index, const QString &what);
     QList<Pair> query(const QString &index, const QString &what);

signals:
     void saved(const Ref &ref);
     void created(const Ref &ref);
     void updated(const Ref &ref);
     void fetched(const Ref &ref);
     void removed(const Ref &ref);
     void matched(QList<Unit> matches);

private:
    // Just to tell compiler to avoid warning!
    using EntityStore::create;
    using EntityStore::update;
    using EntityStore::fetch;
    using EntityStore::remove;
};

} // namespace Store
} // namespace Mere


#endif // MEREDEFAULTSTORE_H
