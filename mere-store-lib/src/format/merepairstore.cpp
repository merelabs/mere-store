#include "merepairstore.h"
#include "../engine/leveldb/merestoreleveldbengine.h"

class MerePairStore::MereSimpleStorePrivate
{
public:
    ~MereSimpleStorePrivate()
    {
    }

    MereSimpleStorePrivate(MerePairStore *q)
        : q_ptr(q)
    {

    }

private:
    MerePairStore *q_ptr;
};

MerePairStore::~MerePairStore()
{
}

MerePairStore::MerePairStore(const QString &store, QObject *parent)
    : MerePairStore(store, "", parent)
{
}

MerePairStore::MerePairStore(const QString &store, const QString &slice, QObject *parent)
    : MereBaseStore(store, slice, parent),
      d_ptr(new MereSimpleStorePrivate(this))
{
}

int MerePairStore::set(QVariant value)
{
    QString key = QUuid::createUuid().toString();

    leveldb::WriteOptions writeOptions;

    leveldb::Status status = db()->Put(writeOptions, key.toStdString(), value.toString().toStdString());

    //qDebug() << "set()::" << status.ok() << key << value << QString::fromStdString(status.ToString());

    // 0  - success
    // !0 - failed
    return !status.ok();
}

int MerePairStore::set(const QString key, QVariant value)
{
    leveldb::WriteOptions writeOptions;

    leveldb::Status status = db()->Put(writeOptions, key.toStdString(), value.toString().toStdString());

    //qDebug() << "set()::" << status.ok() << key << value << QString::fromStdString(status.ToString());

    // 0  - success
    // !0 - failed
    return !status.ok();
}

QVariant MerePairStore::get(const QString &key)
{
    std::string value;

    leveldb::ReadOptions readOptions;

    leveldb::Status s = db()->Get(leveldb::ReadOptions(), key.toStdString(), &value);

    return QString::fromStdString(value);
}

QVariant MerePairStore::list()
{
    QMap<QString, QVariant> data;

    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        data.insert(QString::fromStdString(it->key().ToString()), QString::fromStdString(it->value().ToString()));
    }

    delete it;

    return data;
}

QVariant MerePairStore::list(const QString &key)
{
    QMap<QString, QVariant> records;

    std::string skey = key.toStdString();
    std::string ekey = skey + "~";

    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->Seek(skey); it->Valid() && it->key().ToString() < ekey; it->Next())
    {
        records.insert(QString::fromStdString(it->key().ToString()), QString::fromStdString(it->value().ToString()));
    }

    delete it;

    return records;
}

QVariant MerePairStore::del(const QString &key)
{
    QVariant value = get(key);

    leveldb::WriteOptions writeOptions;

    leveldb::Status status = db()->Delete(writeOptions, key.toStdString());

    // 0  - success
    // !0 - failed
    return !status.ok();
}
