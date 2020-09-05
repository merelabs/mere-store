#ifndef MEREDEFAULTSTORE_H
#define MEREDEFAULTSTORE_H

#include "../merestoreglobal.h"
#include "meremapstore.h"
#include "../merestoreunit.h"
#include "../engine/merestoreengine.h"

#include <QObject>

class MERE_STORE_LIBSPEC MereUnitStore : public MereMapStore
{
    Q_OBJECT
public:
    virtual ~MereUnitStore();
    explicit MereUnitStore(const QString &store, QObject *parent = nullptr);
    explicit MereUnitStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual QString path() const override;

    virtual MereStoreUnit create(MereStoreUnit unit) override;
    virtual MereStoreUnit update(MereStoreUnit unit) override;
    virtual MereStoreUnit fetch(MereStoreUnit unit) override;
    virtual MereStoreUnit remove(MereStoreUnit unit) override;

//protected:
//    static QString UNIT_KEY;
//    static QString UNIT_META_KEY;
//    static QString UNIT_ATTR_KEY;
//    static QString UNIT_PROP_KEY;

private:
    // Just to tell compiler to avoid warning!
    using MereMapStore::create;
    using MereMapStore::update;
    using MereMapStore::fetch;
    using MereMapStore::remove;
    using MereMapStore::list;

//    int read(const QString pkey, MappedStoreUnit &data);

//    int write(const QString unit, const QUuid uuid, const MappedStoreUnit data);
//    int remove(const QString pkey);

    QString key(const MereStoreUnit unit) const;



signals:

public slots:

private:

};

#endif // MEREDEFAULTSTORE_H
