#ifndef MERESTORE_H
#define MERESTORE_H

#include "merestoreglobal.h"
#include "unit.h"

#include <QMap>
#include <QObject>
#include <QVariant>

class MereStoreConfig;

namespace Mere
{
namespace Store
{
namespace Type
{
    const QString STORE = "store";
    const QString SLICE = "slice";
}

class MERE_STORE_LIBSPEC Store : public QObject
{
    Q_OBJECT
public:
    virtual ~Store();
    explicit Store(const QString &store, QObject *parent = nullptr);
    explicit Store(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual QString store() const;
    virtual QString slice() const;

    virtual QString path() const = 0;
    virtual QString mime() const = 0;

    // raw - key/value pair
    virtual int set(QVariant value) = 0;
    virtual int set(const QString key, QVariant value) = 0;
    virtual int set(const QMap<QString, QVariant> &pairs) = 0;
    virtual int set(const QList<QPair<QString, QVariant>> &pairs) = 0;

    virtual QVariant get(const QString &key) = 0;
    virtual QVariant get(const QList<QString> &keys) = 0;

    virtual int del(const QString &key) = 0;
    virtual int del(const QList<QString> &keys) = 0;

    virtual QVariant list(const int &limit = 25) = 0;
    virtual QVariant list(const QString &key, const int &limit = 25) = 0;
    virtual QVariant list(const QMap<QString, QVariant> &filter, const int &limit = 25) = 0;

//protected:
    virtual void init() = 0;
    virtual int create() = 0;
    virtual int open() = 0;
    virtual int close() = 0;
    virtual int remove() = 0;

signals:
    // move from here
    void saved(MereStoreUnitMap data);
    void created(MereStoreUnitMap data);
    void updated(MereStoreUnitMap data);
    void fetched(MereStoreUnitMap data);
    void removed(MereStoreUnitMap data);
    void matched(QList<MereStoreUnitMap> data);

    void saved(Unit &unit);
    void created(Unit &unit);
    void updated(Unit &unit);
    void fetched(Unit &unit);
    void removed(Unit &unit);
    void matched(QList<Unit> matches);

private:
    class StorePrivate;
    StorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // MERESTORE_H
