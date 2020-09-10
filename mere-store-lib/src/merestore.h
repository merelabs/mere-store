#ifndef MERESTORE_H
#define MERESTORE_H

#include "merestoreglobal.h"
#include "merestoreunit.h"

#include <QMap>
#include <QObject>
#include <QVariant>


namespace Mere
{
    namespace Store
    {
        namespace Type
        {
            const QString STORE = "store";
            const QString SLICE = "slice";
        }
    }
}

class MereStoreConfig;

class MERE_STORE_LIBSPEC MereStore : public QObject
{
    Q_OBJECT
public:
    virtual ~MereStore();
    explicit MereStore(const QString &store, QObject *parent = nullptr);
    explicit MereStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual QString store() const;
    virtual QString slice() const;

    virtual QString path() const = 0;
    virtual QString mime() const = 0;

    // raw - key/value pair
    virtual int set(QVariant value) = 0;
    virtual int set(const QString key, QVariant value) = 0;
    virtual QVariant get(const QString &key) = 0;
    virtual QVariant del(const QString &key) = 0;

    virtual QVariant list() = 0;
    virtual QVariant list(const QString &key) = 0;

    /*
    // mere-unit
    virtual int create(MereStoreUnit &unit) = 0;
    virtual int update(MereStoreUnit &unit) = 0;
    virtual int fetch(MereStoreUnit &unit) = 0;
    virtual int remove(MereStoreUnit &unit) = 0;

    // mapped-unit
    virtual int create(MereStoreUnitMap &unit) = 0;
    virtual int update(MereStoreUnitMap &unit) = 0;
    virtual void fetch(MereStoreUnitMap unit) = 0;
    virtual void remove(MereStoreUnitMap unit) = 0;
    virtual void save(MereStoreUnitMap unit) = 0;
    virtual void search(MereStoreUnitMap criteria) = 0;


    virtual void save(QJsonObject unit) = 0;
    virtual void create(QJsonObject unit) = 0;
    virtual void update(QJsonObject unit) = 0;
    virtual void fetch(QJsonObject unit) = 0;
    virtual void remove(QJsonObject unit) = 0;
    //*/

//protected:
    virtual void init() = 0;
    virtual int create() = 0;
    virtual int open() = 0;
    virtual int close() = 0;
    virtual int remove() = 0;

signals:
    void saved(MereStoreUnitMap data);
    void created(MereStoreUnitMap data);
    void updated(MereStoreUnitMap data);
    void fetched(MereStoreUnitMap data);
    void removed(MereStoreUnitMap data);
    void matched(QList<MereStoreUnitMap> data);

    void saved(MereStoreUnit &unit);
    void created(MereStoreUnit &unit);
    void updated(MereStoreUnit &unit);
    void fetched(MereStoreUnit &unit);
    void removed(MereStoreUnit &unit);
    void matched(QList<MereStoreUnit> matches);

private:
    class MereStorePrivate;
    MereStorePrivate *d_ptr;
};

#endif // MERESTORE_H
