#include "mapstore.h"
#include "../unitkey.h"
#include "../link.h"

#include "mere/utils/merestringutils.h"

QString Mere::Store::MapStore::UNIT_KEY      = "path:%1:type:%2:uuid:%3:";
QString Mere::Store::MapStore::UNIT_META_KEY = UNIT_KEY + "meta:%4:";
QString Mere::Store::MapStore::UNIT_ATTR_KEY = UNIT_KEY + "attr:%4:";
QString Mere::Store::MapStore::UNIT_LINK_KEY = UNIT_KEY + "link:%4:path:%5:type:%6:uuid:%7:";

Mere::Store::MapStore::~MapStore()
{

}

Mere::Store::MapStore::MapStore(const QString &store, QObject *parent)
    : PairStore(store, parent)
{
}

Mere::Store::MapStore::MapStore(const QString &store, const QString &slice, QObject *parent)
    : PairStore(store, slice, parent)
{
}

QVariant Mere::Store::MapStore::list(const int &limit)
{
    QString uuid;
    uint count = limit;

    QMap<QString, QVariant> records;
    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->  Next())
    {
        QString  _key   = QString::fromStdString(it->key().ToString());
        QVariant _value = QString::fromStdString(it->value().ToString());

        UnitKey unitKey(_key);
        QStringRef _uuid = unitKey.uuid();

        if (uuid.compare(_uuid.toString()) != 0)
        {
            uuid = _uuid.toString();
            if (--count < 0)
                break;
        }

        records.insert(_key, _value);
    }
    delete it;

    // FLAT RECORDS TO MAPS
    uuid = "";
    QList<QVariant> units;

    QMap<QString, QVariant> unitMap;
    //QMap<QString, QVariant> unitMapAttr;

    QMapIterator<QString, QVariant> rit(records);
    while (rit.hasNext())
    {
        rit.next();

        QString  key   = rit.key();
        QVariant value = rit.value();

        UnitKey unitKey(key);
        QStringRef _uuid = unitKey.uuid();

        if (uuid.compare(_uuid.toString()) != 0)
        {
            if (!unitMap.isEmpty())
            {
                units.append(unitMap);
                unitMap.clear();
            }

            uuid = _uuid.toString();

            unitMap.insert("path", unitKey.path().toString());
            unitMap.insert("type", unitKey.type().toString());
            unitMap.insert("uuid", unitKey.uuid().toString());
        }

        if (unitKey.isAttribute())
        {
            QMap<QString, QVariant> attrs = unitMap.value("attr").toMap();
            attrs.insert(unitKey.attribute().toString(), value);

            unitMap.insert("attr", attrs);
        }
        else if (unitKey.isLink())
        {
            Link link = unitKey.link();
            QList<UnitRef> refs = link.units();

            UnitRef ref = refs.first();
            QMap<QString, QVariant> map = ref.map();

            QMap<QString, QVariant> links = unitMap.value("link").toMap();

            QList<QVariant> list;
            if (links.contains(link.name()))
            {
                list = links.value(link.name()).toList();
            }

            list.append(map);
            links.insert(link.name(), list);

            unitMap.insert("link", links);
        }
    }
    if (!unitMap.isEmpty())
    {
        units.append(unitMap);
        unitMap.clear();
    }

    //qDebug() << "Number Of mapped-units:" << units.size();

    return units;
}

void Mere::Store::MapStore::save(MereStoreUnitMap &unit)
{
    //qDebug() << "Going to save...";

    QUuid uuid = unit.value("uuid").toUuid();
    if (!uuid.isNull())
        update(unit);
    else
        create(unit);
}

int Mere::Store::MapStore::create(MereStoreUnitMap &map)
{
    //qDebug() << "Going to create..." << map.value("type");

    // Unit Path
    QString path = map.value("path").toString();
    if (MereStringUtils::isBlank(path))
    {
        path = ".";
        map.insert("path", path);
    }

    // Unit Type
    QString type = map.value("type").toString();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        return 1;
    }

    // Unit UUID
    QUuid uuid = map.value("uuid").toUuid();
    if (uuid.isNull())
    {
        uuid = QUuid::createUuid();
        map.insert("uuid", uuid);
    }

    int err = write(map);
    if (!err)
    {
        emit created(map);
        qDebug() << QString("Unit path:%1:type:%2:uuid:%3 added to the system").arg(path, type, uuid.toString());
    }

    return err;
}

int Mere::Store::MapStore::update(MereStoreUnitMap &map)
{
    Q_UNUSED(map)
    //qDebug() << "Going to update..." << map;

//    // Unit Path
//    const QString path = map.value("path").toString();
//    if (MereStringUtils::isBlank(path))
//    {
//        qDebug() << "Invalid or missing path of the unit...";
//        return 1;
//    }

//    // Unit Type
//    const QString type = map.value("type").toString();
//    if (MereStringUtils::isBlank(type))
//    {
//        qDebug() << "Invalid or missing type of the unit...";
//        return 2;
//    }

//    // Unit UUID
//    const QUuid uuid = map.value("uuid").toUuid();
//    if (uuid.isNull())
//    {
//        qDebug() << "Invalid or missing uuid of the unit...";
//        return 3;
//    }

//    int err = write(map);
//    if (!err)
//    {
//        emit updated(map);

//        qDebug() << QString("Unit path:%1:type:%2:uuid:%3 updated to the system").arg(path, type, uuid.toString());
//    }

    return 0;
}

int Mere::Store::MapStore::fetch(MereStoreUnitMap &map)
{
    //qDebug() << "Going to fetch...";
    // Unit Path
    const QString path = map.value("path").toString();
    if (MereStringUtils::isBlank(path))
    {
        //qDebug() << "Invalid or missing path of the unit...";
        return 1;
    }

    // Unit Type
    const QString type = map.value("type").toString();
    if (MereStringUtils::isBlank(type))
    {
        //qDebug() << "Invalid or missing type of the unit...";
        return 2;
    }

    // Unit UUID
    const QUuid uuid = map.value("uuid").toUuid();
    if (uuid.isNull())
    {
        //qDebug() << "Invalid or missing uuid of the unit...";
        return 3;
    }

    int err = read(map);
    if (!err)
    {
        emit fetched(map);
    }

    return err;
}

void Mere::Store::MapStore::remove(MereStoreUnitMap unit)
{
    //qDebug() << "Going to remove...";

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

int Mere::Store::MapStore::read(MereStoreUnitMap &map)
{
    // Unit Path
    QString path = map.value("path").toString();

    // Unit Type
    QString type = map.value("type").toString();

    // Unit UUID
    QString uuid = map.value("uuid").toString();

    QString pkey = UNIT_KEY.arg(path, type, uuid);

    int err = read(pkey, map);

    return err;
}

int Mere::Store::MapStore::read(const QString pkey, MereStoreUnitMap &map)
{
    QMap<QString, QVariant> parts = PairStore::list(pkey).toMap();

    QMapIterator<QString, QVariant> rit(parts);
    while (rit.hasNext())
    {
        rit.next();

        QString  key   = rit.key();
        QVariant value = rit.value();

        UnitKey unitKey(key);
        QStringRef _uuid = unitKey.uuid();

        if (unitKey.isAttribute())
        {
            QMap<QString, QVariant> attrs = map.value("attr").toMap();
            attrs.insert(unitKey.attribute().toString(), value);

            map.insert("attr", attrs);
        }
        else if (unitKey.isLink())
        {
            Link link = unitKey.link();
            QList<UnitRef> refs = link.units();

            UnitRef ref = refs.first();
            QMap<QString, QVariant> _map = ref.map();

            QMap<QString, QVariant> links = map.value("link").toMap();

            QList<QVariant> list;
            if (links.contains(link.name()))
            {
                list = links.value(link.name()).toList();
            }

            list.append(_map);
            links.insert(link.name(), list);

            map.insert("link", links);
        }
    }

    //qDebug() << "ROWS:" << parts;
    //qDebug() << "UNIT:" << map;
    return 0;
}

int Mere::Store::MapStore::write(const MereStoreUnitMap &map)
{
    QMap<QString, QVariant> pairs;

    // Unit Path
    QString path = map.value("path").toString();

    // Unit Type
    QString type = map.value("type").toString();

    // Unit UUID
    QString uuid = map.value("uuid").toString();

    // Attributes
    QMap<QString, QVariant> attrs = map.value("attr").toMap();
    QMapIterator<QString, QVariant> ait(attrs);
    while (ait.hasNext())
    {
        ait.next();

        QString key = UNIT_ATTR_KEY.arg(path, type, uuid, ait.key());
        pairs.insert(key, ait.value());
    }

    // Links
    QMap<QString, QVariant> links = map.value("link").toMap();
    //qDebug() << "LINKS" << links;

    QMapIterator<QString, QVariant> lit(links);
    while (lit.hasNext())
    {
        lit.next();

        QList<QVariant> list = lit.value().toList();

        QListIterator<QVariant> vit(list);
        while (vit.hasNext())
        {
            QMap<QString, QVariant> ref = vit.next().toMap();

            QString key = UNIT_LINK_KEY.arg(path, type, uuid,
                                            lit.key(),
                                            ref.value("path").toString(),
                                            ref.value("type").toString(),
                                            ref.value("uuid").toString());
            pairs.insert(key, lit.value());
        }
    }

    int err = set(pairs);
    //if (!err)
    //    qDebug() << QString("Unit path:%1:type:%2:uuid:%3 saved to the system").arg(path, type, uuid);

    return err;
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
