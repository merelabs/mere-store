#ifndef MERESTORE_H
#define MERESTORE_H

#include "merestoreglobal.h"
#include "merestoreunit.h"

#include <QMap>
#include <QObject>
#include <QVariant>

class MereStoreConfig;

class MERE_STORE_LIBSPEC MereStore : public QObject
{
    Q_OBJECT
public:
    virtual ~MereStore();
    explicit MereStore(const QString store, QObject *parent = nullptr);

    virtual QString store() const;
    virtual QString path() const = 0;

    virtual void save(MappedStoreUnit unit) = 0;
    virtual void search(MappedStoreUnit criteria) = 0;

    virtual void create(MappedStoreUnit unit) = 0;
    virtual void update(MappedStoreUnit unit) = 0;
    virtual void fetch(MappedStoreUnit unit) = 0;
    virtual void remove(MappedStoreUnit unit) = 0;

    virtual MereStoreUnit create(MereStoreUnit unit) = 0;
    virtual MereStoreUnit update(MereStoreUnit unit) = 0;
    virtual MereStoreUnit fetch(MereStoreUnit unit) = 0;
    virtual MereStoreUnit remove(MereStoreUnit unit) = 0;

    virtual int set(QVariant value) = 0;
    virtual int set(const QString key, QVariant value = QVariant("")) = 0;
    virtual QVariant get(const QString &key) = 0;
    virtual QVariant del(const QString &key) = 0;

    virtual QVariant list() = 0;

//protected:
    virtual void init() = 0;
    virtual int create() = 0;
    virtual int open() = 0;
    virtual int close() = 0;
    virtual int remove() = 0;

signals:
    void saved(MappedStoreUnit data);
    void created(MappedStoreUnit data);
    void updated(MappedStoreUnit data);
    void fetched(MappedStoreUnit data);
    void removed(MappedStoreUnit data);
    void matched(QList<MappedStoreUnit> data);

    void saved(MereStoreUnit unit);
    void created(MereStoreUnit unit);
    void updated(MereStoreUnit unit);
    void fetched(MereStoreUnit unit);
    void removed(MereStoreUnit unit);
    void matched(QList<MereStoreUnit> matches);

private:
    class MereStorePrivate;
    MereStorePrivate *d_ptr;
};

#endif // MERESTORE_H
