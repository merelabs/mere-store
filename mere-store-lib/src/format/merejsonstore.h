#ifndef MEREJSONSTORE_H
#define MEREJSONSTORE_H

#include "meresimplestore.h"

#include <QObject>

class MereJsonStore : public MereSimpleStore
{
    Q_OBJECT
public:
    virtual ~MereJsonStore();
    explicit MereJsonStore(const QString store, QObject *parent = nullptr);

    virtual void save(MappedStoreUnit unit);
    virtual void create(MappedStoreUnit unit);
    virtual void update(MappedStoreUnit unit);
    virtual void fetch(MappedStoreUnit unit);
    virtual void remove(MappedStoreUnit unit);

    virtual void search(MappedStoreUnit query);
    virtual void list(MappedStoreUnit criteria);

//private:
    // Just to tell compiler to avoid warning!
    using MereSimpleStore::create;
    using MereSimpleStore::remove;
    using MereSimpleStore::list;

signals:


};

#endif // MEREJSONSTORE_H
