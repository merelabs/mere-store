#include "unitstore.h"
#include "merestoreconfig.h"

#include "mere/utils/merestringutils.h"

#include <QUuid>

Mere::Store::UnitStore::~UnitStore()
{

}

Mere::Store::UnitStore::UnitStore(const QString &store, QObject *parent)
    : UnitStore(store, "", parent)
{

}

Mere::Store::UnitStore::UnitStore(const QString &store, const QString &slice, QObject *parent)
    : MapStore(store, slice, parent)
{

}

//QVariant MereUnitStore::list()
//{
//    QMap<QString, QVariant> units;

//    QMap<QString, QVariant> results = MereMapStore::list().toMap();
//    QMapIterator<QString, QVariant> it(results);
//    while (it.hasNext())
//    {
//        it.next();
//        QString key = it.key();
//        QVariant val = it.value();

//        MereStoreUnitMap map = val.toMap();

//        QString type = map.value("type").toString();
//        QString uuid = map.value("uuid").toString();
//        MereStoreUnitAttributes attrs = map.take("attr").toMap();

//        MereStoreUnit *unit = new MereStoreUnit(type);
//        unit->setUuid(uuid);
//        unit->setAttributes(attrs);

//        QVariant var;
//        var.setValue(unit);

//        units.insert(key, var);
//    }

//    return units;
//}

int Mere::Store::UnitStore::create(Unit &unit)
{
    //qDebug() << "Going to create..." << unit.type();

    MereStoreUnitMap map = unit.map();
    int err = create(map);
    if (err) return err;

    unit.setUuid(map.value("uuid").toUuid());

    emit created(unit);

    return 0;
}

int Mere::Store::UnitStore::update(Unit &unit)
{
    //qDebug() << "Going to update...";

    MereStoreUnitMap map = unit.map();
    int err = update(map);
    if (err) return err;

    emit updated(unit);

    return 0;
}

int Mere::Store::UnitStore::fetch(Unit &unit)
{
    qDebug() << "Going to fetch...";
    // Unit Type
    const QString type = unit.type();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        return 1;
    }

    // Unit Path
    const QString path(".") ;

    // Unit UUID
    const QUuid uuid = unit.uuid();
    if (uuid.isNull())
    {
        qDebug() << "Invalid or missing uuid of the unit...";
        return 3;
    }

    QString key(path);
    key = key.append(type);
    key = UNIT_KEY.arg(key, uuid.toString());

    MereStoreUnitMap result;
    read(key, result);

    MereStoreUnitAttributes attributes = result.take("attr").toMap();
    unit.setAttributes(attributes);

    emit fetched(unit);

    return 0;
}

int Mere::Store::UnitStore::remove(Unit &unit)
{
//    MereStoreUnit fetchedUnit = fetch(unit);

    qDebug() << "Going to remove...";

    // Unit Type
    const QString type = unit.type();
    if (MereStringUtils::isBlank(type))
    {
        qDebug() << "Invalid or missing type of the unit...";
        return 1;
    }

    // Unit Path
    const QString path(".");

    // Unit UUID
    const QUuid uuid = unit.uuid();
    if (uuid.isNull())
    {
        qDebug() << "Invalid or missing uuid of the unit...";
        return 3;
    }

    QString pkey(path);
    pkey = pkey.append(type);

    pkey = UNIT_KEY.arg(pkey, uuid.toString());

    remove(pkey);

    emit removed(unit);

    return 0;
}

QString Mere::Store::UnitStore::key(const Unit unit) const
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

