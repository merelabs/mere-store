#ifndef MEREMAPSTORE_H
#define MEREMAPSTORE_H

#include "merejsonstore.h"

class MereMapStore : public MereJsonStore
{
    Q_OBJECT
public:
    virtual ~MereMapStore();
    explicit MereMapStore(const QString &store, QObject *parent = nullptr);
    explicit MereMapStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual void save(MappedStoreUnit unit);
    virtual void create(MappedStoreUnit unit);
    virtual void update(MappedStoreUnit unit);
    virtual void fetch(MappedStoreUnit unit);
    virtual void remove(MappedStoreUnit unit);

    virtual void search(MappedStoreUnit query);
    virtual void list(MappedStoreUnit criteria);

protected:
    int read(const QString pkey, MappedStoreUnit &data);
    int write(const QString unit, const QUuid uuid, const MappedStoreUnit data);
    int remove(const QString pkey);

//    QString key(const MereStoreUnit unit) const;

protected:
    static QString UNIT_KEY;
    static QString UNIT_META_KEY;
    static QString UNIT_ATTR_KEY;
    static QString UNIT_PROP_KEY;


signals:

};

#endif // MEREMAPSTORE_H
