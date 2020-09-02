#ifndef MEREDEFAULTSTORE_H
#define MEREDEFAULTSTORE_H

#include "../merestoreglobal.h"
#include "merejsonstore.h"
#include "../merestoreunit.h"
#include "../engine/merestoreengine.h"

#include <QObject>

class MERE_STORE_LIBSPEC MereDefaultStore : public MereJsonStore
{
    Q_OBJECT
public:
    virtual ~MereDefaultStore();
    explicit MereDefaultStore(const QString store, QObject *parent = nullptr);

    virtual QString path() const;

    virtual void save(MappedStoreUnit unit);
    virtual void create(MappedStoreUnit unit);
    virtual void update(MappedStoreUnit unit);
    virtual void fetch(MappedStoreUnit unit);
    virtual void remove(MappedStoreUnit unit);

    virtual void search(MappedStoreUnit query);
    virtual void list(MappedStoreUnit criteria);

    virtual MereStoreUnit create(MereStoreUnit unit);
    virtual MereStoreUnit update(MereStoreUnit unit);
    virtual MereStoreUnit fetch(MereStoreUnit unit);
    virtual MereStoreUnit remove(MereStoreUnit unit);

protected:
    static QString UNIT_KEY;
    static QString UNIT_META_KEY;
    static QString UNIT_ATTR_KEY;
    static QString UNIT_PROP_KEY;

private:
    int read(const QString pkey, MappedStoreUnit &data);

    int write(const QString unit, const QUuid uuid, const MappedStoreUnit data);
    int remove(const QString pkey);

    QString key(const MereStoreUnit unit) const;

signals:

public slots:

private:
};

#endif // MEREDEFAULTSTORE_H
