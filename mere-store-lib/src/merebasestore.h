#ifndef MEREABSTRACTSTORE_H
#define MEREABSTRACTSTORE_H

#include "merestoreglobal.h"
#include "merestore.h"

#include "leveldb/db.h"
#include "leveldb/cache.h"
#include "leveldb/write_batch.h"

class MERE_STORE_LIBSPEC MereBaseStore : public MereStore
{
    Q_OBJECT
public:
    virtual ~MereBaseStore();
    explicit MereBaseStore(const QString store, QObject *parent = nullptr);
    virtual void init() override;

    virtual int create() override;
    virtual int open() override;
    virtual int close() override;
    virtual int remove() override;

    leveldb::DB* db();

signals:

private:
    class MereBaseStorePrivate;
    MereBaseStorePrivate *d_ptr;
};

#endif // MEREABSTRACTSTORE_H
