#ifndef MEREABSTRACTSTORE_H
#define MEREABSTRACTSTORE_H

#include "merestore.h"
#include "leveldb/db.h"

class MERE_STORE_LIBSPEC MereBaseStore : public MereStore
{
    Q_OBJECT
public:
    virtual ~MereBaseStore();
    explicit MereBaseStore(const QString &store, QObject *parent = nullptr);
    explicit MereBaseStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual void init() override;
    virtual QString path() const override;

    virtual int create() override;
    virtual int open() override;
    virtual int close() override;
    virtual int remove() override;

    leveldb::DB* db();

private:
    class MereBaseStorePrivate;
    MereBaseStorePrivate *d_ptr;
};

#endif // MEREABSTRACTSTORE_H
