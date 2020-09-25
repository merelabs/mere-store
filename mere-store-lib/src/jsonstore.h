#ifndef MEREJSONSTORE_H
#define MEREJSONSTORE_H

#include "pairstore.h"

#include "leveldb/cache.h"
#include "leveldb/write_batch.h"

#include <QJsonObject>

namespace Mere
{
namespace Store
{

class MERE_STORE_LIBSPEC JsonStore : public PairStore
{
    Q_OBJECT
public:
    virtual ~JsonStore();
    explicit JsonStore(const QString &store, QObject *parent = nullptr);
    explicit JsonStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual void save(QJsonObject unit) ;
    virtual void create(QJsonObject unit) ;
    virtual void update(QJsonObject unit) ;
    virtual void fetch(QJsonObject unit) ;
    virtual void remove(QJsonObject unit) ;

    virtual void search(QJsonObject query);
//    virtual void list(QJsonObject criteria);

private:
    // Just to tell compiler to avoid warning!
//    using MerePairStore::save;
//    using MerePairStore::create;
//    using MerePairStore::update;
//    using MerePairStore::fetch;
//    using MerePairStore::remove;
//    using MereSimpleStore::list;
//    using MerePairStore::search;

signals:


};

} // namespace Store
} // namespace Mere

#endif // MEREJSONSTORE_H
