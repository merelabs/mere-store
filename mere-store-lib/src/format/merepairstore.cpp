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

//QVariant MerePairStore::list()
//{
//    QMap<QString, QVariant> data;

//    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
//    for (it->SeekToFirst(); it->Valid(); it->Next())
//    {
//        data.insert(QString::fromStdString(it->key().ToString()), QString::fromStdString(it->value().ToString()));
//    }

//    delete it;

//    return data;
//}

QVariant MerePairStore::del(const QString &key)
{
    QVariant value = get(key);

    leveldb::WriteOptions writeOptions;

    leveldb::Status status = db()->Delete(writeOptions, key.toStdString());

    // 0  - success
    // !0 - failed
    return !status.ok();
}

QVariant MerePairStore::list(const uint &limit)
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

QVariant MerePairStore::list(const QString &key, const uint &limit)
{
    QMap<QString, QVariant> records;

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
    for (it->Seek(skey); it->Valid() && it->key().ToString() < ekey && count; it->Next())
    {
        QString _key = QString::fromStdString(it->key().ToString());
        QString _val = QString::fromStdString(it->value().ToString());

        MatchCriteria criteria = this->criteria(key);
        switch (criteria)
        {
            case MatchCriteria::StartWith:
                // do nothing
                break;

            case MatchCriteria::EndWith:
                if(!_key.endsWith(str))
                    continue;
                break;

            case MatchCriteria::Match:
                if(_key.compare(str) != 0)
                    continue;
                break;

            case MatchCriteria::Contain:
                if (!_key.contains(str))
                    continue;
                break;
        }

        records.insert(_key, _val);
        count--;
    }

    delete it;

    return records;
}

QVariant MerePairStore::list(const QMap<QString, QVariant> &filter, const uint &limit)
{
    QMap<QString, QVariant> records;

    return records;
}

MereStore::MatchCriteria MerePairStore::criteria(const QString &query)
{
    MereStore::MatchCriteria criteria;

    if (query.startsWith("^") && query.endsWith("$"))
        criteria =  MereStore::MatchCriteria::Match;
    else if (query.startsWith("^"))
        criteria =  MereStore::MatchCriteria::StartWith;
    else if (query.endsWith("$"))
        criteria =  MereStore::MatchCriteria::EndWith;
    else
        criteria = MereStore::MatchCriteria::Contain;

    return criteria;
}
