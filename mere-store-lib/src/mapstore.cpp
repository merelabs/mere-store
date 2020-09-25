#include "mapstore.h"

#include "mere/utils/merestringutils.h"

QString Mere::Store::MapStore::UNIT_KEY      = "path:%1:type:%2:uuid:%3:";
QString Mere::Store::MapStore::UNIT_META_KEY = UNIT_KEY + "meta:%4";
QString Mere::Store::MapStore::UNIT_ATTR_KEY = UNIT_KEY + "attr:%4";
QString Mere::Store::MapStore::UNIT_LINK_KEY = UNIT_KEY + "link:%4:path:%5:type:%6:uuid:%7:";

Mere::Store::MapStore::~MapStore()
{

}

Mere::Store::MapStore::MapStore(const QString &store, QObject *parent)
    : MapStore(store, "", parent)
{
    //qDebug() << "MereDefaultStore::...." << store;
}

Mere::Store::MapStore::MapStore(const QString &store, const QString &slice, QObject *parent)
    : PairStore(store, slice, parent)
{
    //qDebug() << "MereDefaultStore::...." << store;
}

//FIXME
/*
QVariant MereMapStore::list()
{
    QMap<QString, QVariant> results;

    QString uuid = "";
    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        QString  _key   = QString::fromStdString(it->key().ToString());
        QVariant _value = QString::fromStdString(it->value().ToString());

        //qDebug() << "Key/Value: " << _key << " => " << _value;

        QStringList parts = _key.split(":");
        //qDebug() << "UUID:" << parts.at(2);
        if (uuid.compare(parts.at(2)) != 0)
        {
            uuid = parts.at(2);
            //qDebug() << "New UUID";
            QString pkey(UNIT_KEY.arg(parts.at(0), parts.at(2)));
            std::string skey = pkey.toStdString();
            std::string ekey = skey + "~";

            //qDebug() << "KEY:" << QString::fromStdString(skey);
            //qDebug() << "KEY~:" << QString::fromStdString(ekey);
            MereStoreUnitMap map;
            int err = read(pkey, map);
            if (!err)
                results.insert(uuid, map);
        }
    }

    delete it;


    //qDebug() << "SIZE OF:" << results.size();
    return results;
}
*/
void Mere::Store::MapStore::save(MereStoreUnitMap &unit)
{
    //qDebug() << "Going to save...";

    QUuid uuid = unit.value("uuid").toUuid();
    if (!uuid.isNull())
        update(unit);
    else
        create(unit);
}

int Mere::Store::MapStore::create(MereStoreUnitMap &unit)
{
    //qDebug() << "XXXXXXXXXXXXXXXXXXXXXXXXXX Going to create..." << unit.value("type");

    // Unit Type
    QString type = unit.value("type").toString();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        return 1;
    }

    // Unit Path
//    QString path = unit.value("path", ".").toString();
    QString path(".");

    // Unit UUID
    QUuid uuid = unit.value("uuid").toUuid();
    if (uuid.isNull())
    {
        uuid = QUuid::createUuid();
        unit.insert("uuid", uuid);
    }
    //qDebug() << "YYYYYYYYYYYYYYYYYYY Going to create..." << uuid;

    // Unit Attrs
    MereStoreUnitMap attrs = unit.value("attr").toMap();
    attrs.insert("uuid", uuid);

    QString key(path);
    key = key.append(type);

    write(key, uuid, attrs);

    emit created(unit);

    qDebug() << QString("Unit %1:uuid:%2 added to the system").arg(key).arg(uuid.toString());

    return 0;
}


int Mere::Store::MapStore::update(MereStoreUnitMap &unit)
{
    //qDebug() << "Going to update...";

    // Unit Type
    const QString type = unit.value("type").toString();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        return 1;
    }

    // Unit Path
    //const QString path = unit.value("path", ".").toString();
    QString path(".");

    // Unit UUID
    const QUuid uuid = unit.value("uuid").toUuid();
    if (uuid.isNull())
    {
        qDebug() << "Invalid or missing uuid of the unit...";
        return 3;
    }

    // Unit Attrs
    MereStoreUnitMap attrs = unit.value("attr").toMap();

    QString key(path);
    key = key.append(type);

    write(key, uuid, attrs);

    emit updated(unit);

    qDebug() << QString("Unit %1:uuid:%2 updated to the system").arg(key).arg(uuid.toString());

    return 0;
}


void Mere::Store::MapStore::fetch(MereStoreUnitMap unit)
{
    qDebug() << "Going to fetch...";
    // Unit Type
    const QString type = unit.value("type").toString();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        throw "Invalid or missing type of the unit...";
    }

    // Unit Path
    const QString path = unit.value("path", ".").toString();

    // Unit UUID
    const QUuid uuid = unit.value("uuid").toUuid();
    if (uuid.isNull())
    {
        qDebug() << "Invalid or missing uuid of the unit...";
        //return;
        throw "Invalid or missing uuid of the unit...";
    }

    QString key(path);
    key = key.append(type);

    key = UNIT_KEY.arg(key, uuid.toString());

    unit.remove("attr");

    read(key, unit);

    emit fetched(unit);
}


void Mere::Store::MapStore::remove(MereStoreUnitMap unit)
{
    qDebug() << "Going to remove...";

    // Unit Type
    const QString type = unit.value("type").toString();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        return;
    }

    // Unit Path
    const QString path = unit.value("path", ".").toString();

    // Unit UUID
    const QUuid uuid = unit.value("uuid").toUuid();
    if (uuid.isNull())
    {
        qDebug() << "Invalid or missing uuid of the unit...";
        return;
    }

    QString pkey(path);
    pkey = pkey.append(type);

    pkey = UNIT_KEY.arg(pkey, uuid.toString());

    remove(pkey);

    emit removed(unit);
}


void Mere::Store::MapStore::search(MereStoreUnitMap query)
{
    //qDebug() << "Search for path:" << query.value("path").toString();
    //qDebug() << "Search for type:" << query.value("type").toString();

    // Unit Type
    const QString type = query.value("type").toString();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        return;
    }

    // Unit Path
    const QString path = query.value("path", ".").toString();

    QString pkey(path);
    pkey = pkey.append(type).append(":");

//    pkey = UNIT_KEY.arg(pkey, uuid.toString());

    std::string skey = pkey.toStdString();
    std::string ekey = (pkey + ("~")).toStdString();

    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->Seek(skey); it->Valid() && it->key().ToString() < ekey; it->Next())
    {
        QString  _key   = QString::fromStdString(it->key().ToString());
        QVariant _value = QString::fromStdString(it->value().ToString());

        qDebug() << "Key/Value: " << _key << " => " << _value;

    }

    delete it;
}

//void MereMapStore::list(MereStoreUnitMap criteria)
//{
//    qDebug() << "DEKHA JAK KI HOY!!!" << db();
//    QString pkey;

//    std::string skey = pkey.toStdString();
//    std::string ekey = (pkey + ("~")).toStdString();

////    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
////    for (it->Seek(skey); it->Valid() && it->key().ToString() < ekey; it->Next())
////    {
////        QString  _key   = QString::fromStdString(it->key().ToString());
////        QVariant _value = QString::fromStdString(it->value().ToString());

////        qDebug() << "Key/Value: " << _key << " => " << _value;

////    }
//}

int Mere::Store::MapStore::read(const QString pkey, MereStoreUnitMap &map)
{
    QStringList parts = pkey.split(":");
    if (parts.size() >= 2)
    {
        QString type = parts.at(0).mid(1);
        QString uuid = parts.at(2);

        map.insert("type", type);
        map.insert("uuid", uuid);
    }

    std::string skey = pkey.toStdString();
    std::string ekey = skey + "~";

    //qDebug() << "KEY:" << QString::fromStdString(skey);
    //qDebug() << "KEY~:" << QString::fromStdString(ekey);

    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->Seek(skey); it->Valid() && it->key().ToString() < ekey; it->Next())
    {
        QString  _key   = QString::fromStdString(it->key().ToString());
        QVariant _value = QString::fromStdString(it->value().ToString());

        //qDebug() << "ZZ Key/Value: " << _key << " => " << _value;

        QMap<QString, QVariant> data;

        QString rest = _key.remove(pkey);
        QStringList parts = rest.split(":");

        for (int i = parts.size() - 1; i >=0 ; i--)
        {
            QString part = parts.at(i);
            if (data.isEmpty())
            {
                data.insert(part, _value);
            }
            else
            {
                QMap<QString, QVariant> data1 = data;
                data.clear();
                data.insert(part, data1);
            }
        }

        if (map.contains(data.firstKey()))
        {
            QMap<QString, QVariant> u = map.value(data.firstKey()).toMap();
            QMap<QString, QVariant> d = data.value(data.firstKey()).toMap();
            u.unite(d);
            map.insert(data.firstKey(), u);
        }
        else
        {
            map.unite(data);
        }
    }

    delete it;

    return 0;
}

int Mere::Store::MapStore::write(const QString type, const QUuid uuid, const MereStoreUnitMap &data)
{
    //qDebug() << "ADDING DATA" << uuid << data;
    leveldb::WriteOptions writeOptions;
    leveldb::WriteBatch batch;

    QMapIterator<QString, QVariant> it(data);
    while (it.hasNext())
    {
        it.next();

        QString key = UNIT_ATTR_KEY.arg(type,
                                        uuid.toString(),
                                        it.key());

        QString val(it.value().toString());

        //qDebug() << "ADDING DATA" << key << ":" << val;
        batch.Put(key.toStdString(), val.toStdString());
    }

    db()->Write(writeOptions, &batch);

    return 0;
}

int Mere::Store::MapStore::remove(const QString pkey)
{
    leveldb::WriteOptions writeOptions;
    leveldb::WriteBatch batch;

    std::string skey = pkey.toStdString();
    std::string ekey = (pkey + ("~")).toStdString();
    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->Seek(skey); it->Valid() && it->key().ToString() < ekey; it->Next())
    {
        batch.Delete(it->key().ToString());
    }

    db()->Write(writeOptions, &batch);

    return 0;
}
