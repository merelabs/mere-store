#include "merestoreutils.h"

#include "mere/store/merestoreunit.h"
#include "mere/utils/merestringutils.h"

MappedStoreUnit MereStoreUtils::toMap(Unit unit)
{
    MappedStoreUnit map;

    // Unit Type
    //map.insert("type", unit.type());

    // Unit Path
    //map.insert("path", unit.path());
    //map.insert("path", ".");

    // Unit UUID
    //map.insert("uuid", unit.uuid());

    // Unit Attrs
//    unit.type();
//    map.insert("attr", unit.attributes());

    unit.map();
}

/*
MereStoreUnit MereStoreUtils::fromMap(const MappedStoreUnit &map)
{
    // Unit Type
//    QString type = map.value("type").toString();
//    if (MereStringUtils::isBlank(type))
//    {
//        qDebug() << "Invalid or missing type of the unit...";
//        throw "Invalid or missing type of the unit...";
//    }
//    MereStoreUnit unit(type);

//    // Unit Path
//    QString path = map.value("path", ".").toString();
//    unit.setPath(path);

//    // Unit UUID
//    QUuid uuid = map.value("uuid", QUuid::createUuid()).toUuid();
//    unit.setUuid(uuid);

//    // Unit Attrs
//    StoreUnitAttributes attrs = map.value("attr").toMap();
//    //unit.setAttributes(attrs);

//    return unit;

    MereStoreUnit unit("asa");

    return unit;;
}


*/
