#include "unitstore.h"
#include "../config/config.h"
#include "../unitkey.h"
#include "../index/unitindexer.h"
#include "indexstore.h"

#include "mere/utils/merestringutils.h"

#include <QUuid>
#include <QDateTime>

Mere::Store::UnitStore::~UnitStore()
{

}

Mere::Store::UnitStore::UnitStore(const QString &store, QObject *parent)
    : MapStore(store, parent)
{
}

Mere::Store::UnitStore::UnitStore(const QString &store, const QString &slice, QObject *parent)
    : MapStore(store, slice, parent)
{
}

QVariant Mere::Store::UnitStore::list(const int &limit)
{
    Q_UNUSED(limit)
    QList<QVariant> units;

    QList<QVariant> records = MapStore::list().toList();
    QListIterator<QVariant> it(records);
    while (it.hasNext())
    {
        QVariant vmap = it.next();

        QMap<QString, QVariant> map = vmap.toMap();

        //Unit unit(map);
        ///*
        QString path = map.take("path").toString();
        QString type = map.take("type").toString();
        QString uuid = map.take("uuid").toString();

        Unit *unit = new Unit(type);
        unit->setPath(path);
        unit->setUuid(QUuid::fromString(uuid));

        // Attributes
        MereStoreUnitAttributes attrs = map.take("attr").toMap();
        unit->setAttributes(attrs);

        // Links
        QMap<QString, QVariant> links = map.take("link").toMap();
        QMapIterator<QString, QVariant> lit(links);
        while (lit.hasNext())
        {
            lit.next();

            QList<QVariant> list = lit.value().toList();
            QListIterator<QVariant> listIt(list);
            while (listIt.hasNext())
            {
                QMap<QString, QVariant> map = listIt.next().toMap();
                UnitRef ref(map);

                unit->addLink(lit.key(), ref);
            }
        }
        //*/

        //FIXEM - xtra layer
        QVariant var;
        var.setValue(unit);

        units.append(var);
    }

    qDebug() << "Number of units..." << units.size();
    return units;
}

int Mere::Store::UnitStore::create(Unit &unit)
{
    qDebug() << "Going to create..." << unit.type();

    // Unit Path
    QString path = unit.path();
    if (MereStringUtils::isBlank(path))
        return 1;

    // Unit Type
    QString type = unit.type();
    if (MereStringUtils::isBlank(type))
        return 2;

    // Unit UUID
    QUuid uuid = unit.uuid();
    if (uuid.isNull())
        unit.setUuid(QUuid::createUuid());

    MereStoreUnitMap map = unit.map();

    int err = this->MapStore::create(map);
    if (!err)
    {
        unit.setUuid(map.value("uuid").toUuid());
        emit created(unit);

//        index();
        /*
        Config *config = this->config();
        if (this->type().compare("slice") == 0)
        {
            SliceConfig sliceConfig = config->slice(this->slice());
            IndexConfig indexConfig = sliceConfig.index();

            QList<Index> indexes = indexConfig.indexes();
            QListIterator<Index> it(indexes);
            while (it.hasNext())
            {
                Index index = it.next();
                qDebug() << "Index name:" << index.name();

                Indexer *indexer = this->indexer(index.name());

                QList<QString> attributes = index.attributes();

                QStringList text;
                QListIterator<QString> ait(attributes);
                while (ait.hasNext())
                {
                    QString attribute = ait.next();
                    text << map.value(attribute).toString();
                }

                QString key = QString("%1:path:%2:type:%3:uuid:%4").arg(text.join(" "),
                                                                       unit.path(),
                                                                       unit.type(),
                                                                       unit.uuid().toString());
                QVariant value = QString::number(QDateTime::currentMSecsSinceEpoch());
                indexer->index(key, value);

                indexer->deleteLater() ;
            }

        }
        */
    }

    return err;
}

int Mere::Store::UnitStore::update(Unit &unit)
{
    //qDebug() << "Going to update...";

    // Unit Path
    QString path = unit.path();
    if (MereStringUtils::isBlank(path))
        return 1;

    // Unit Type
    QString type = unit.type();
    if (MereStringUtils::isBlank(type))
        return 2;

    // Unit UUID
    QUuid uuid = unit.uuid();
    if (uuid.isNull())
        return 3;

    MereStoreUnitMap map = unit.map();
    int err = update(map);
    if (!err)
    {
        emit updated(unit);
    }

    return err;
}

int Mere::Store::UnitStore::fetch(Unit &unit)
{
    qDebug() << "Going to fetch...";
    // Unit Path
    QString path = unit.path();
    if (MereStringUtils::isBlank(path))
        return 1;

    // Unit Type
    QString type = unit.type();
    if (MereStringUtils::isBlank(type))
        return 2;

    // Unit UUID
    QUuid uuid = unit.uuid();
    if (uuid.isNull())
        return 3;

    MereStoreUnitMap map = unit.map();
    int err = fetch(map);
    if (!err)
    {
        Unit _unit(map);

        unit.setAttributes(_unit.attributes());
        unit.setLinks(_unit.links());
        emit fetched(unit);
    }

    return err;
}

int Mere::Store::UnitStore::remove(Unit &unit)
{
    qDebug() << "Going to remove...";

    // Unit Path
    QString path = unit.path();
    if (MereStringUtils::isBlank(path))
        return 1;

    // Unit Type
    QString type = unit.type();
    if (MereStringUtils::isBlank(type))
        return 2;

    // Unit UUID
    QUuid uuid = unit.uuid();
    if (uuid.isNull())
        return 3;

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

Mere::Store::Indexer* Mere::Store::UnitStore::indexer(const QString &name)
{
    UnitIndexer *indexer = new UnitIndexer(*this, name);

    return indexer;
}
