#include "meresimplestore.h"

MereSimpleStore::~MereSimpleStore()
{
    qDebug() << "~MereSimpleStore::....";
}

MereSimpleStore::MereSimpleStore(const QString store, QObject *parent)
    : MereAbstractStore(store, parent)
{
    qDebug() << "MereSimpleStore::...." << store;
}


int MereSimpleStore::set(QVariant value)
{
    QString key = QUuid::createUuid().toString();

    leveldb::WriteOptions writeOptions;

    leveldb::Status status = db()->Put(writeOptions, key.toStdString(), value.toString().toStdString());

    qDebug() << "set()::" << status.ok() << key << value << QString::fromStdString(status.ToString());

    // 0  - success
    // !0 - failed
    return !status.ok();
}

int MereSimpleStore::set(const QString key, QVariant value)
{
    leveldb::WriteOptions writeOptions;

    leveldb::Status status = db()->Put(writeOptions, key.toStdString(), value.toString().toStdString());

    qDebug() << "set()::" << status.ok() << key << value << QString::fromStdString(status.ToString());

    // 0  - success
    // !0 - failed
    return !status.ok();
}

QVariant MereSimpleStore::get(const QString &key)
{
    std::string value;

    leveldb::ReadOptions readOptions;

    leveldb::Status s = db()->Get(leveldb::ReadOptions(), key.toStdString(), &value);

    return QString::fromStdString(value);
}

QVariant MereSimpleStore::list()
{
    QMap<QString, QVariant> data;

    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        //qDebug() << QString::fromStdString(it->key().ToString()) << ": "  << QString::fromStdString(it->value().ToString());
        data.insert(QString::fromStdString(it->key().ToString()), QString::fromStdString(it->value().ToString()));
    }
//    assert(it->status().ok());
    delete it;

    return data;
}

QVariant MereSimpleStore::del(const QString &key)
{
    QVariant value = get(key);

    leveldb::WriteOptions writeOptions;

    leveldb::Status status = db()->Delete(writeOptions, key.toStdString());

    qDebug() << "set()::" << status.ok() << key << value << QString::fromStdString(status.ToString());

    // 0  - success
    // !0 - failed
    return !status.ok();
}
