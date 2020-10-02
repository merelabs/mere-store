#ifndef MEREABSTRACTSTORE_H
#define MEREABSTRACTSTORE_H

#include "store.h"
#include "../config/config.h"

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
    // store
    explicit BaseStore(const QString &store, QObject *parent = nullptr);

    // slice
    explicit BaseStore(const Store &store, const QString &slice, QObject *parent = nullptr);
    explicit BaseStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    QString type() const override;

    virtual Config *config() const override;

    virtual void init() override;
    virtual QString path() const override;
    virtual QString mime() const override;
    virtual QString home() const override;

    virtual int create() override;
    virtual int open() override;
    virtual int close() override;
    virtual int remove() override;

    virtual int create(const Index &index) override;

    leveldb::DB* db();

private:
    // index
    explicit BaseStore(const Store &store, const Index &index, QObject *parent = nullptr);
    explicit BaseStore(const QString &store, const Index &index, QObject *parent = nullptr);

private:
    class BaseStorePrivate;
    BaseStorePrivate *d_ptr;

    class BaseSlicePrivate;
    class BaseIndexPrivate;
};

} // namespace Store
} // namespace Mere

#endif // MEREABSTRACTSTORE_H
