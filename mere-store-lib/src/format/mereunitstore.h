#ifndef MEREDEFAULTSTORE_H
#define MEREDEFAULTSTORE_H

#include "meremapstore.h"
#include "../merestoreunit.h"
#include "../engine/merestoreengine.h"

class MERE_STORE_LIBSPEC MereUnitStore : public MereMapStore
{
    Q_OBJECT
public:
    virtual ~MereUnitStore();
    explicit MereUnitStore(const QString &store, QObject *parent = nullptr);
    explicit MereUnitStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual int create(MereStoreUnit &unit) override;
    virtual int update(MereStoreUnit &unit) override;
    virtual int fetch(MereStoreUnit &unit) override;
    virtual int remove(MereStoreUnit &unit) override;

private:
    // Just to tell compiler to avoid warning!
    using MereMapStore::create;
    using MereMapStore::update;
    using MereMapStore::fetch;
    using MereMapStore::remove;
//    using MereMapStore::list;

    QString key(const MereStoreUnit unit) const;
};

#endif // MEREDEFAULTSTORE_H
