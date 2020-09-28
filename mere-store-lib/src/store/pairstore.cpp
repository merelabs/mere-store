#include "pairstore.h"
#include "../engine/leveldbengine.h"

#include "mere/utils/merestringutils.h"

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

    }

private:
    PairStore *q_ptr;
};

Mere::Store::PairStore::~PairStore()
{
}

Mere::Store::PairStore::PairStore(const QString &store, QObject *parent)
    : PairStore(store, "", parent)
{
}

Mere::Store::PairStore::PairStore(const QString &store, const QString &slice, QObject *parent)
    : BaseStore(store, slice, parent),
      d_ptr(new PairStorePrivate(this))
{
}

int Mere::Store::PairStore::set(QVariant value)
{
    if(!value.isValid())
        return 1;

    QString key = QUuid::createUuid().toString();

    leveldb::WriteOptions writeOptions;

    leveldb::Status status = db()->Put(writeOptions, key.toStdString(), value.toString().toStdString());

    //qDebug() << "set()::" << status.ok() << key << value << QString::fromStdString(status.ToString());

    // 0  - success
    // !0 - failed
    return !status.ok();
}

int Mere::Store::PairStore::set(const QString key, QVariant value)
{
    if (MereStringUtils::isBlank(key))
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
    leveldb::WriteOptions writeOptions;
    leveldb::WriteBatch batch;

    QMapIterator<QString, QVariant> it(pairs);
    while (it.hasNext())
    {
        it.next();

        QString key = it.key();
        if (MereStringUtils::isBlank(key))
            continue;

        QVariant val = it.value();
        if (!val.isValid())
            continue;

        batch.Put(key.toStdString(), val.toString().toStdString());
    }

    leveldb::Status status = db()->Write(writeOptions, &batch);

    return !status.ok();
}

int Mere::Store::PairStore::set(const QList<QPair<QString, QVariant>> &pairs)
{
    leveldb::WriteOptions writeOptions;
    leveldb::WriteBatch batch;

    QListIterator<QPair<QString, QVariant>> it(pairs);
    while (it.hasNext())
    {
        QPair<QString, QVariant> pair = it.next();

        QString key = pair.first;
        if (MereStringUtils::isBlank(key))
            continue;

        QVariant val = pair.second;
        if (!val.isValid())
            continue;

        batch.Put(key.toStdString(), val.toString().toStdString());
    }

    leveldb::Status status = db()->Write(writeOptions, &batch);

    return !status.ok();
}

QVariant Mere::Store::PairStore::get(const QString &key)
{
    if (MereStringUtils::isBlank(key))
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
    if (MereStringUtils::isBlank(key))
        return 1;

    QVariant value = get(key);

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

        if (MereStringUtils::isBlank(key))
            continue;

        batch.Delete(key.toStdString());
    }

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

    QRegularExpression re(key);
    uint count = limit;

    // find the string to search
    QString str = key;
    if (str.startsWith("^"))
        str = str.remove(0, 1);

    if (str.endsWith("$"))
        str.chop(1);

    // ...
    std::string skey;
    if (key.startsWith("^"))
        skey = str.toStdString();
    else
        skey = "";

    std::string ekey = skey + "~";

    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->Seek(skey); it->Valid() && it->key().ToString() < ekey; it->Next())
    {
        QString _key = QString::fromStdString(it->key().ToString());
        QString _val = QString::fromStdString(it->value().ToString());

        QRegularExpressionMatch match = re.match(_key);
        if(!match.hasMatch())
            continue;

        records.insert(_key, _val);
        count--;
    }

    delete it;

    return records;
}

QVariant Mere::Store::PairStore::list(const QMap<QString, QVariant> &filter, const int &limit)
{
    QMap<QString, QVariant> records;

    return records;
}
