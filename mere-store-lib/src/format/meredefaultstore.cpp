#include "meredefaultstore.h"
#include "../merestoreconfig.h"

#include "mere/utils/merestringutils.h"

#include <QUuid>

QString MereDefaultStore::UNIT_KEY      = "%1:uuid:%2:";
QString MereDefaultStore::UNIT_META_KEY = "%1:uuid:%2:meta:%3";
QString MereDefaultStore::UNIT_ATTR_KEY = "%1:uuid:%2:attr:%3";
QString MereDefaultStore::UNIT_PROP_KEY = "%1:uuid:%2:prop:%3";

MereDefaultStore::~MereDefaultStore()
{

}

MereDefaultStore::MereDefaultStore(const QString store, QObject *parent)
    : MereJsonStore(store, parent)
{
    //qDebug() << "MereDefaultStore::...." << store;
}


QString MereDefaultStore::path() const
{
    QString path;

    MereStoreConfig *config = MereStoreConfig::instance();
    QVariant storePath = config->get(Mere::Store::StoreKey);
    if (storePath.isValid())
        path = storePath.toString();
    else
        path = "./";

    return path;
}

MereStoreUnit MereDefaultStore::create(MereStoreUnit unit)
{
    qDebug() << "Going to create..." << unit.type();

    // Unit Type
    QString type = unit.type();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        throw "Invalid or missing type of the unit...";
    }

    // Unit Path
    QString path(".");

    // Unit UUID
    QUuid uuid = QUuid::createUuid();
    if (uuid.isNull()) uuid = QUuid::createUuid();

    // Unit Attrs
    StoreUnitAttributes attrs = unit.attributes();

    QString key(path);
    key = key.append(type);

    write(key, uuid, attrs);

    emit created(unit);

    qDebug() << QString("Unit %1:uuid:%2 added to the system").arg(key).arg(uuid.toString());

    return unit;
}

MereStoreUnit MereDefaultStore::update(MereStoreUnit unit)
{
    qDebug() << "Going to update...";

    // Unit Type
    const QString type = unit.type();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        throw "Invalid or missing type of the unit...";
    }

    // Unit Path
    const QString path(".");

    // Unit UUID
    const QUuid uuid = unit.uuid();
    if (uuid.isNull())
    {
        qDebug() << "Invalid or missing uuid of the unit...";
        throw "Invalid or missing uuid of the unit...";
    }

    // Unit Attrs
    MappedStoreUnit attrs = unit.attributes();

    QString key(path);
    key = key.append(type);

    write(key, uuid, attrs);

    emit updated(unit);

    return unit;
}

MereStoreUnit MereDefaultStore::fetch(MereStoreUnit unit)
{
    qDebug() << "Going to fetch...";
    // Unit Type
    const QString type = unit.type();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        throw "Invalid or missing type of the unit...";
    }

    // Unit Path
    const QString path(".") ;

    // Unit UUID
    const QUuid uuid = unit.uuid();
    if (uuid.isNull())
    {
        qDebug() << "Invalid or missing uuid of the unit...";
        //return;
        throw "Invalid or missing uuid of the unit...";
    }

    QString key(path);
    key = key.append(type);
    key = UNIT_KEY.arg(key, uuid.toString());

    MappedStoreUnit result;
    read(key, result);

    StoreUnitAttributes attributes = result.take("attr").toMap();
    unit.setAttributes(attributes);

    emit fetched(unit);

    return unit;
}

MereStoreUnit MereDefaultStore::remove(MereStoreUnit unit)
{
    MereStoreUnit fetchedUnit = fetch(unit);

    qDebug() << "Going to remove...";

    // Unit Type
    const QString type = unit.type();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        throw "Invalid or missing type of the unit...";
    }

    // Unit Path
    const QString path(".");

    // Unit UUID
    const QUuid uuid = unit.uuid();
    if (uuid.isNull())
    {
        qDebug() << "Invalid or missing uuid of the unit...";
        throw "Invalid or missing uuid of the unit...";
    }

    QString pkey(path);
    pkey = pkey.append(type);

    pkey = UNIT_KEY.arg(pkey, uuid.toString());

    remove(pkey);

    emit removed(fetchedUnit);

    return fetchedUnit;
}

int MereDefaultStore::remove(const QString pkey)
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


int MereDefaultStore::read(const QString pkey, MappedStoreUnit &unit)
{
    std::string skey = pkey.toStdString();
    std::string ekey = (pkey + ("~")).toStdString();

    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->Seek(skey); it->Valid() && it->key().ToString() < ekey; it->Next())
    {
        QString  _key   = QString::fromStdString(it->key().ToString());
        QVariant _value = QString::fromStdString(it->value().ToString());

//        qDebug() << "Key/Value: " << _key << " => " << _value;

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

        if (unit.contains(data.firstKey()))
        {
            QMap<QString, QVariant> u = unit.value(data.firstKey()).toMap();
            QMap<QString, QVariant> d = data.value(data.firstKey()).toMap();
            u.unite(d);
            unit.insert(data.firstKey(), u);
        }
        else
        {
            unit.unite(data);
        }
    }

    delete it;

    return 0;
}

int MereDefaultStore::write(const QString unit, const QUuid uuid, const MappedStoreUnit data)
{
    leveldb::WriteOptions writeOptions;
    leveldb::WriteBatch batch;

    QMapIterator<QString, QVariant> it(data);
    while (it.hasNext())
    {
        it.next();

        QString key = UNIT_ATTR_KEY.arg(unit,
                                        uuid.toString(),
                                        it.key());

        QString val(it.value().toString());

        batch.Put(key.toStdString(), val.toStdString());
    }

    db()->Write(writeOptions, &batch);

    return 0;
}

QString MereDefaultStore::key(const MereStoreUnit unit) const
{
    // Unit Type
    const QString type = unit.type();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        throw "Invalid or missing type of the unit...";
    }

    // Unit Path
    const QString path(".") ;

    // Unit UUID
    const QUuid uuid = unit.uuid();
    if (uuid.isNull())
    {
        qDebug() << "Invalid or missing uuid of the unit...";
        //return;
        throw "Invalid or missing uuid of the unit...";
    }

    QString key(path);
    key = key.append(type);
    key = UNIT_KEY.arg(key, uuid.toString());

    return key;
}



void MereDefaultStore::save(MappedStoreUnit unit)
{
    qDebug() << "Going to save...";

    QUuid uuid = unit.value("uuid").toUuid();
    if (!uuid.isNull())
        update(unit);
    else
        create(unit);
}

void MereDefaultStore::create(MappedStoreUnit unit)
{
    qDebug() << "Going to create..." << unit.value("type");

    // Unit Type
    QString type = unit.value("type").toString();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        return;
    }

    // Unit Path
    QString path = unit.value("path", ".").toString();

    // Unit UUID
    QUuid uuid = unit.value("uuid", QUuid::createUuid()).toUuid();
    if (uuid.isNull()) uuid = QUuid::createUuid();

    // Unit Attrs
    MappedStoreUnit attrs = unit.value("attr").toMap();

    QString key(path);
    key = key.append(type);

    write(key, uuid, attrs);

    emit created(unit);

    //qDebug() << QString("Unit %1:uuid:%2 added to the system").arg(key).arg(uuid.toString());
}


void MereDefaultStore::update(MappedStoreUnit unit)
{
    qDebug() << "Going to update...";

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

    // Unit Attrs
    MappedStoreUnit attrs = unit.value("attr").toMap();

    QString key(path);
    key = key.append(type);

    write(key, uuid, attrs);

    emit updated(unit);

    //qDebug() << QString("Unit %1:uuid:%2 updated to the system").arg(key).arg(uuid.toString());
}


void MereDefaultStore::fetch(MappedStoreUnit unit)
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


void MereDefaultStore::remove(MappedStoreUnit unit)
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


void MereDefaultStore::search(MappedStoreUnit query)
{
    qDebug() << "Search for path:" << query.value("path").toString();
    qDebug() << "Search for type:" << query.value("type").toString();

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

void MereDefaultStore::list(MappedStoreUnit criteria)
{
    qDebug() << "DEKHA JAK KI HOY!!!" << db();
    QString pkey;

    std::string skey = pkey.toStdString();
    std::string ekey = (pkey + ("~")).toStdString();

//    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
//    for (it->Seek(skey); it->Valid() && it->key().ToString() < ekey; it->Next())
//    {
//        QString  _key   = QString::fromStdString(it->key().ToString());
//        QVariant _value = QString::fromStdString(it->value().ToString());

//        qDebug() << "Key/Value: " << _key << " => " << _value;

//    }
}
