#ifndef MEREJSONSTORE_H
#define MEREJSONSTORE_H

#include "merepairstore.h"

#include "leveldb/cache.h"
#include "leveldb/write_batch.h"

#include <QJsonObject>

class MERE_STORE_LIBSPEC MereJsonStore : public MerePairStore
{
    Q_OBJECT
public:
    virtual ~MereJsonStore();
    explicit MereJsonStore(const QString &store, QObject *parent = nullptr);
    explicit MereJsonStore(const QString &store, const QString &slice, QObject *parent = nullptr);

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

#endif // MEREJSONSTORE_H
