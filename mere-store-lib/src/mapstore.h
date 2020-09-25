#ifndef MEREMAPSTORE_H
#define MEREMAPSTORE_H

#include "pairstore.h"

#include "leveldb/cache.h"
#include "leveldb/write_batch.h"

namespace Mere
{
namespace Store
{

class MERE_STORE_LIBSPEC MapStore : public PairStore
{
    Q_OBJECT
public:
    virtual ~MapStore();
    explicit MapStore(const QString &store, QObject *parent = nullptr);
    explicit MapStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual void save(MereStoreUnitMap &unit);
    virtual int create(MereStoreUnitMap &unit);
    virtual int update(MereStoreUnitMap &unit);
    virtual void fetch(MereStoreUnitMap unit);
    virtual void remove(MereStoreUnitMap unit);

    virtual void search(MereStoreUnitMap query);
//    virtual void list(MereStoreUnitMap criteria);
//    virtual QVariant list() override;

protected:
    int read(const QString pkey, MereStoreUnitMap &map);
    int write(const QString type, const QUuid uuid, const MereStoreUnitMap &data);
    int remove(const QString pkey);

//    QString key(const MereStoreUnit unit) const;
    using BaseStore::create;
    using BaseStore::remove;

protected:
    static QString UNIT_KEY;
    static QString UNIT_META_KEY;
    static QString UNIT_ATTR_KEY;
    static QString UNIT_LINK_KEY;

private:
};

} // namespace Store
} // namespace Mere

#endif // MEREMAPSTORE_H
