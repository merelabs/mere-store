#ifndef MEREMAPSTORE_H
#define MEREMAPSTORE_H

#include "merejsonstore.h"

class MERE_STORE_LIBSPEC MereMapStore : public MereJsonStore
{
    Q_OBJECT
public:
    virtual ~MereMapStore();
    explicit MereMapStore(const QString &store, QObject *parent = nullptr);
    explicit MereMapStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual void save(MereStoreUnitMap unit);
    virtual int create(MereStoreUnitMap &unit);
    virtual int update(MereStoreUnitMap &unit);
    virtual void fetch(MereStoreUnitMap unit);
    virtual void remove(MereStoreUnitMap unit);

    virtual void search(MereStoreUnitMap query);
//    virtual void list(MereStoreUnitMap criteria);

protected:
    int read(const QString pkey, MereStoreUnitMap &map);
    int write(const QString type, const QUuid uuid, const MereStoreUnitMap &data);
    int remove(const QString pkey);

//    QString key(const MereStoreUnit unit) const;

protected:
    static QString UNIT_KEY;
    static QString UNIT_META_KEY;
    static QString UNIT_ATTR_KEY;
    static QString UNIT_PROP_KEY;

private:
    // Just to tell compiler to avoid warning!
//    using MereJsonStore::save;
//    using MereJsonStore::create;
//    using MereJsonStore::update;
//    using MereJsonStore::fetch;
//    using MereJsonStore::remove;
//    using MereJsonStore::list;
};

#endif // MEREMAPSTORE_H
