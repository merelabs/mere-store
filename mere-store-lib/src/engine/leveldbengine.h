#ifndef MERESTORELEVELDBENGINE_H
#define MERESTORELEVELDBENGINE_H

#include "engine.h"

#include <QDebug>

#include "leveldb/db.h"
#include "leveldb/cache.h"

namespace Mere
{
namespace Store
{

class LevelDBEngine : public Engine
{
    Q_OBJECT
public:
    virtual ~LevelDBEngine();
    explicit LevelDBEngine(QObject *parent = nullptr);

    void setStore(const QString store);
    QString store() const;

    int create() override;
    int open() override;
    int close() override;
    int remove() override;

    bool exists() override;

    leveldb::DB* db();

private:
    class LevelDBEnginePrivate;
    LevelDBEnginePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // MERESTORELEVELDBENGINE_H
