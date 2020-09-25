#ifndef MEREABSTRACTSTORE_H
#define MEREABSTRACTSTORE_H

#include "store.h"
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

namespace Mere
{
namespace Store
{

class MERE_STORE_LIBSPEC BaseStore : public Store
{
    Q_OBJECT
public:
    virtual ~BaseStore();
    explicit BaseStore(const QString &store, QObject *parent = nullptr);
    explicit BaseStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual void init() override;
    virtual QString path() const override;
    virtual QString mime() const override;

    virtual int create() override;
    virtual int open() override;
    virtual int close() override;
    virtual int remove() override;

    leveldb::DB* db();

private:
    class BaseStorePrivate;
    BaseStorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // MEREABSTRACTSTORE_H
