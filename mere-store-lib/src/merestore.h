#ifndef MERESTORE_H
#define MERESTORE_H

#include "merestoreglobal.h"

#include "leveldb/db.h"
#include "leveldb/cache.h"
#include "leveldb/write_batch.h"

#include <QMap>
#include <QObject>
#include <QVariant>
#include <QDebug>

class MereStoreConfig;

typedef QMap<QString, QVariant> T;

class MERE_STORE_LIBSPEC MereStore : public QObject
{
    Q_OBJECT
public:
    virtual ~MereStore();

    virtual void save(T unit) = 0;
    virtual void create(T unit) = 0;
    virtual void update(T unit) = 0;
    virtual void fetch(T unit) = 0;
    virtual void remove(T unit) = 0;
    virtual void list(T criteria) = 0;

//protected:
    explicit MereStore(const QString store, QObject *parent = nullptr);
    virtual QString path() const;

    void init();
    void open();
    void close();

    leveldb::DB* db();

signals:
    void saved(T data);
    void created(T data);
    void updated(T data);
    void fetched(T data);
    void removed(T data);
    void matched(QList<T> data);

public slots:

private:
    QString m_path;
    QString m_store;

    leveldb::DB *m_db;
};

#endif // MERESTORE_H
