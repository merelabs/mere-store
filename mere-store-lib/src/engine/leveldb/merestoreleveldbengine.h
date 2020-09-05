#ifndef MERESTORELEVELDBENGINE_H
#define MERESTORELEVELDBENGINE_H

#include "../merestoreengine.h"

#include <QDebug>

#include "leveldb/db.h"
#include "leveldb/cache.h"

class MereStoreLevelDBEngine : public MereStoreEngine
{
    Q_OBJECT
public:
    virtual ~MereStoreLevelDBEngine();
    explicit MereStoreLevelDBEngine(QObject *parent = nullptr);

    void setStore(const QString store);
    QString store() const;

    int create() override;
    int open() override;
    int close() override;
    int remove() override;

    bool exists() override;

    leveldb::DB* db();

private:
    class MereStoreLevelDBEnginePrivate;
    MereStoreLevelDBEnginePrivate *d_ptr;
};

#endif // MERESTORELEVELDBENGINE_H
