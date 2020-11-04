#include "unitstore.h"
#include "../config/config.h"
#include "../unitkey.h"
#include "../index/unitindexer.h"
#include "indexstore.h"
#include "../config/sliceconfig.h"
#include "../config/storeconfig.h"
#include "../entity.h"

#include "mere/utils/stringutils.h"

#include <QUuid>
#include <QDateTime>
#include <QList>

Mere::Store::UnitStore::~UnitStore()
{

}

Mere::Store::UnitStore::UnitStore(const QString &store, QObject *parent)
    : EntityStore(store, parent)
{
}

Mere::Store::UnitStore::UnitStore(const QString &store, const QString &slice, QObject *parent)
    : EntityStore(store, slice, parent)
{
}

QVariant Mere::Store::UnitStore::list(const int &limit)
{
    qDebug() << "KEY" << limit;
    QList<Unit *> units;

    QVariant list = EntityStore::list(limit);
    if (!list.isValid()) return 0;

    QList<Entity *> entities = list.value<QList<Entity *> >();
    QListIterator<Entity *> it(entities);
    while (it.hasNext())
    {
        Entity *entity = it.next();

        QMap<QString, QVariant> attributes;
        QList<Link> links;

        QMap<QString, QVariant> entries = entity->map();
        QMapIterator<QString, QVariant> eit(entries);
        while (eit.hasNext())
        {
            eit.next();

            UnitKey key(eit.key());
            if (key.isAttribute())
            {
                attributes.insert(key.attribute().toString(), eit.value());
            }
            if (key.isLink())
            {
                links.append(key.link());
            }
        }

        UnitRef ref = entity->ref();

        Unit *unit = new Unit();
        unit->setPath(ref.path());
        unit->setType(ref.type());
        unit->setId(ref.id());
        unit->setAttributes(attributes);
        unit->setLinks(links);

        units.append(unit);

        delete entity;
    }

//    qDebug() << "Number of units..." << units.size();

    return QVariant::fromValue(units);
}

int Mere::Store::UnitStore::create(Unit &unit)
{
    qDebug() << "Going to create..." << unit.type();
    // Unit UUID
    QString id = unit.id();
    if (Mere::Utils::StringUtils::isBlank(id))
        unit.setId(QUuid::createUuid().toString());

    if(!unit.isValid())
        return 1;

    Entity entity(unit);
    int err = this->EntityStore::create(entity);
    if (!err)
    {
        emit created(unit);

        //
        // INDEX
        //
        Config *config = nullptr;

        if(this->type().compare("slice") == 0)
            config =  new SliceConfig (this->home());
        else if(this->type().compare("slice") == 0)
            config = new StoreConfig (this->home());

        if (config)
        {
            QMap<QString, QVariant> settings = config->section("index");
            delete config;

            if (!settings.isEmpty())
            {

                QList<Index> indexes;

                QMapIterator<QString, QVariant> it(settings);
                while (it.hasNext())
                {
                    it.next();
                    QString name = it.key();

                    Index index(name);

                    QVariant value = it.value();
                    QList<QString> attributes = value.toString().split(",");
                    QListIterator<QString> it(attributes);
                    while (it.hasNext())
                    {
                        QString attribute = it.next();
                        index.setAttribute(attribute);
                    }

                    indexes.append(index);
                }

                // index
                QMap<QString, QVariant> attrs = unit.attributes();
                QListIterator<Index> iit(indexes);
                while (iit.hasNext())
                {
                    Index index = iit.next();

                    Indexer *indexer = this->indexer(index.name());

                    QList<QString> attributes = index.attributes();

                    QStringList text;
                    QListIterator<QString> ait(attributes);
                    while (ait.hasNext())
                    {
                        QString attribute = ait.next();
                        text << attrs.value(attribute).toString();
                    }

                    indexer->index(text.join(" "), unit);
                    indexer->deleteLater() ;
                }
            }
        }
        //*/
    }

    return err;
}

int Mere::Store::UnitStore::update(const Unit &unit)
{
    if(!unit.isValid())
        return 1;

    Entity entity(unit);
    int err = this->EntityStore::update(entity);
    if (!err)
    {
        emit updated(unit);

        // FIXME - Find of the index value really gets changed
        //         otherwise wasing of resources or BAD program

        //
        // RE-INDEX
        //
        Config *config = nullptr;

        if(this->type().compare("slice") == 0)
            config =  new SliceConfig (this->home());
        else if(this->type().compare("slice") == 0)
            config = new StoreConfig (this->home());

        if (config)
        {
            QMap<QString, QVariant> settings = config->section("index");
            delete config;

            if (!settings.isEmpty())
            {

                QList<Index> indexes;

                QMapIterator<QString, QVariant> it(settings);
                while (it.hasNext())
                {
                    it.next();
                    QString name = it.key();

                    Index index(name);

                    QVariant value = it.value();
                    QList<QString> attributes = value.toString().split(",");
                    QListIterator<QString> it(attributes);
                    while (it.hasNext())
                    {
                        QString attribute = it.next();
                        index.setAttribute(attribute);
                    }

                    indexes.append(index);
                }

                // index
                QMap<QString, QVariant> attrs = unit.attributes();
                QListIterator<Index> iit(indexes);
                while (iit.hasNext())
                {
                    Index index = iit.next();

                    Indexer *indexer = this->indexer(index.name());

                    QList<QString> attributes = index.attributes();

                    QStringList text;
                    QListIterator<QString> ait(attributes);
                    while (ait.hasNext())
                    {
                        QString attribute = ait.next();
                        text << attrs.value(attribute).toString();
                    }

                    indexer->reindex(text.join(" "), unit);
                    indexer->deleteLater();
                }
            }
        }
    }

    return err;
}

int Mere::Store::UnitStore::fetch(const Ref &ref, Unit &unit)
{
    if(!ref.isValid())
        return 1;

    Entity entity;
    int err = EntityStore::fetch(ref, entity);
    if (err) return err;

    QMap<QString, QVariant> attributes;
    QList<Link> links;

    QMap<QString, QVariant> entries = entity.map();
    QMapIterator<QString, QVariant> it(entries);
    while (it.hasNext())
    {
        it.next();

        UnitKey key(it.key());
        if (key.isAttribute())
        {
            attributes.insert(key.attribute().toString(), it.value());
        }
        if (key.isLink())
        {
            links.append(key.link());
        }
    }

    unit.setAttributes(attributes);
    unit.setLinks(links);

    return 0;
}

int Mere::Store::UnitStore::remove(const Ref &ref)
{
    qDebug() << "Going to remove...";
    if(!ref.isValid())
        return 1; 

    int err = EntityStore::remove(ref);
    if (err) return err;

    emit removed(ref);

    //
    // REMOVE INDEX
    //
    Config *config = nullptr;

    if(this->type().compare("slice") == 0)
        config =  new SliceConfig (this->home());
    else if(this->type().compare("slice") == 0)
        config = new StoreConfig (this->home());

    if (config)
    {
        QMap<QString, QVariant> settings = config->section("index");
        delete config;

        if (!settings.isEmpty())
        {
            QList<Index> indexes;
            QMapIterator<QString, QVariant> it(settings);
            while (it.hasNext())
            {
                it.next();
                Index index(it.key());

                Indexer *indexer = this->indexer(index.name());
                indexer->remove(ref);
                indexer->deleteLater();
            }
        }
    }

    return 0;
}

Mere::Store::Indexer* Mere::Store::UnitStore::indexer(const QString &name)
{
    UnitIndexer *indexer = new UnitIndexer(*this, name);

    return indexer;
}

QList<Mere::Store::UnitRef> Mere::Store::UnitStore::find(const QString &index, const QString &what)
{
    QList<UnitRef> refs;

    Mere::Store::Indexer *indexer = this->indexer(index);

    refs = indexer->find(what);

    delete indexer;

    return refs;
}

 QList<Mere::Store::Pair> Mere::Store::UnitStore::query(const QString &index, const QString &what)
 {
     QList<Pair> pairs;

     Mere::Store::Indexer *indexer = this->indexer(index);

     pairs = indexer->query(what);

     delete indexer;

     return pairs;
 }
