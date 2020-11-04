#include "pairstore.h"
#include "../pair.h"
#include "../engine/leveldbengine.h"

#include "mere/utils/stringutils.h"

#include <QUuid>
#include <QRegularExpression>

class Mere::Store::PairStore::PairStorePrivate
{
public:
    ~PairStorePrivate()
    {
    }

    PairStorePrivate(PairStore *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }

private:
    PairStore *q_ptr;
};

Mere::Store::PairStore::~PairStore()
{
}

Mere::Store::PairStore::PairStore(const QString &store, QObject *parent)
    : PersistStore(store, parent),
      d_ptr(new PairStorePrivate(this))
{
}

Mere::Store::PairStore::PairStore(const QString &store, const QString &slice, QObject *parent)
    : PersistStore(store, slice, parent),
      d_ptr(new PairStorePrivate(this))
{
}

int Mere::Store::PairStore::set(const QVariant &value)
{
    if(!value.isValid() || value.isNull())
        return 1;

    QString key = QUuid::createUuid().toString();

    leveldb::WriteOptions writeOptions;

    leveldb::Status status = db()->Put(writeOptions, key.toStdString(), value.toString().toStdString());

    //qDebug() << "set()::" << status.ok() << key << value << QString::fromStdString(status.ToString());

    // 0  - success
    // !0 - failed
    return !status.ok();
}

int Mere::Store::PairStore::set(const QString &key, const QVariant &value)
{
    if (Mere::Utils::StringUtils::isBlank(key))
        return 1;

    if (!value.isValid())
        return 2;

    leveldb::WriteOptions writeOptions;

    leveldb::Status status = db()->Put(writeOptions, key.toStdString(), value.toString().toStdString());

    //qDebug() << "set()::" << status.ok() << key << value << QString::fromStdString(status.ToString());

    // 0  - success
    // !0 - failed
    return !status.ok();
}

int Mere::Store::PairStore::set(const QMap<QString, QVariant> &pairs)
{
//    qDebug() << "PAIRS:::" << pairs;
    leveldb::WriteOptions writeOptions;
    leveldb::WriteBatch batch;

    QMapIterator<QString, QVariant> it(pairs);
    while (it.hasNext())
    {
        it.next();

        QString key = it.key();
        if (Mere::Utils::StringUtils::isBlank(key))
            continue;

        QVariant val = it.value();
        if (!val.isValid())
            continue;

        batch.Put(key.toStdString(), val.toString().toStdString());
    }

    leveldb::Status status = db()->Write(writeOptions, &batch);

    return !status.ok();
}

int Mere::Store::PairStore::set(const QList<Pair> &pairs)
{
    leveldb::WriteOptions writeOptions;
    leveldb::WriteBatch batch;

    QListIterator<Pair> it(pairs);
    while (it.hasNext())
    {
        Pair pair = it.next();

        QString key = pair.key();
        if (Mere::Utils::StringUtils::isBlank(key))
            continue;

        QVariant val = pair.value();
        if (!val.isValid())
            continue;

        batch.Put(key.toStdString(), val.toString().toStdString());
    }

    leveldb::Status status = db()->Write(writeOptions, &batch);

    return !status.ok();
}

QVariant Mere::Store::PairStore::get(const QString &key)
{
    if (Mere::Utils::StringUtils::isBlank(key))
        return QVariant(QVariant::Invalid);

    std::string value;

    leveldb::ReadOptions readOptions;

    leveldb::Status s = db()->Get(readOptions, key.toStdString(), &value);

    return QString::fromStdString(value);
}

QVariant Mere::Store::PairStore::get(const QList<QString> &keys)
{
    if (keys.isEmpty())
        return QVariant(QVariant::Invalid);

    std::string value;
    leveldb::ReadOptions readOptions;

    QMap<QString, QVariant> rows;

    QListIterator<QString> it(keys);
    while (it.hasNext())
    {
        QString key = it.next();
        leveldb::Status s = db()->Get(readOptions, key.toStdString(), &value);

        rows.insert(key, QString::fromStdString(value));
    }

    return rows;
}

int Mere::Store::PairStore::del(const QString &key)
{
    if (Mere::Utils::StringUtils::isBlank(key))
        return 1;

    leveldb::WriteOptions writeOptions;

    leveldb::Status status = db()->Delete(writeOptions, key.toStdString());

    // 0  - success
    // !0 - failed
    return !status.ok();
}

int Mere::Store::PairStore::del(const QList<QString> &keys)
{
    leveldb::WriteOptions writeOptions;
    leveldb::WriteBatch batch;

    QListIterator<QString> it(keys);
    while (it.hasNext())
    {
        QString key = it.next();

        if (Mere::Utils::StringUtils::isBlank(key))
            continue;

        batch.Delete(key.toStdString());
    }

    leveldb::Status status = db()->Write(writeOptions, &batch);

    // 0  - success
    // !0 - failed
    return !status.ok();
}

int Mere::Store::PairStore::del(const QRegExp &regex)
{
    QString pattern = regex.pattern();

    std::string skey = "";
    if (pattern.startsWith("^"))
        skey = pattern.toStdString();

    std::string ekey = skey + "~";

    leveldb::WriteOptions writeOptions;
    leveldb::WriteBatch batch;

    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->Seek(skey); it->Valid() && it->key().ToString() < ekey; it->Next())
    {
        QString _key = QString::fromStdString(it->key().ToString());

        int pos = regex.indexIn(_key);
        if (pos == -1) continue;

        batch.Delete(_key.toStdString());
    }

    delete it;

    leveldb::Status status = db()->Write(writeOptions, &batch);

    // 0  - success
    // !0 - failed
    return !status.ok();
}

QVariant Mere::Store::PairStore::list(const int &limit)
{
    QMap<QString, QVariant> records;

    uint count = limit;

    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid() && count; it->Next(), count--)
    {
        records.insert(QString::fromStdString(it->key().ToString()), QString::fromStdString(it->value().ToString()));
    }

    delete it;

    return records;
}

QVariant Mere::Store::PairStore::list(const QString &key, const int &limit)
{
    QMap<QString, QVariant> records;

    std::string skey = key.toStdString();

    int count = limit;
    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->Seek(skey); it->Valid() && (limit == 0 || count != 0); it->Next())
    {
        QString _key = QString::fromStdString(it->key().ToString());
        QString _val = QString::fromStdString(it->value().ToString());

        qDebug() << "KEY::" << _key;
        records.insert(_key, _val);

        if (limit != 0) --count;
    }
    delete it;

    return records;
}

QVariant Mere::Store::PairStore::list(const QMap<QString, QVariant> &filter, const int &limit)
{
    Q_UNUSED(filter);
    Q_UNUSED(limit)
    QMap<QString, QVariant> records;

    return records;
}

QVariant Mere::Store::PairStore::list(const QRegExp &regex, const int &limit)
{
    QMap<QString, QVariant> records;

    QString pattern = regex.pattern();

    std::string skey = "";
    if (pattern.startsWith("^"))
        skey = pattern.toStdString();

    int count = limit;
    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->Seek(skey); it->Valid() && (limit == 0 || count != 0); it->Next())
    {
        QString _key = QString::fromStdString(it->key().ToString());
        int pos = regex.indexIn(_key);
        if (pos == -1) continue;

        QString _val = QString::fromStdString(it->value().ToString());

        records.insert(_key, _val);

        if (limit != 0) --count;
    }
    delete it;

    return records;
}

QVariant Mere::Store::PairStore::find(const QString &key, const int &limit)
{
    QMap<QString, QVariant> records;

    std::string skey = key.toStdString();
    std::string ekey = skey + "~";

    int count = limit;
    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->Seek(skey); it->Valid() && it->key().ToString() < ekey && (limit == 0 || count != 0); it->Next())
    {
        QString _key = QString::fromStdString(it->key().ToString());
        QString _val = QString::fromStdString(it->value().ToString());

        records.insert(_key, _val);

        if (limit != 0) --count;
    }

    delete it;

    return records;
}
