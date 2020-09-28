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
    virtual int create(MereStoreUnitMap &map);
    virtual int update(MereStoreUnitMap &map);
    virtual int fetch(MereStoreUnitMap &map);
    virtual void remove(MereStoreUnitMap unit);

    virtual void search(MereStoreUnitMap query);
    virtual QVariant list(const int &limit = 25) override;

protected:
    int read(MereStoreUnitMap &map);
    int write(const MereStoreUnitMap &map);

    int read(const QString pkey, MereStoreUnitMap &map);
    int remove(const QString pkey);

//    QString key(const MereStoreUnit unit) const;
    using BaseStore::create;
    using BaseStore::remove;

private:

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
