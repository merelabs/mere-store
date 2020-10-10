#include "entitystore.h"
#include "../entity.h"
#include "../unitkey.h"

class Mere::Store::EntityStore::EntityStorePrivate
{
public:
    ~EntityStorePrivate()
    {
    }

    EntityStorePrivate(EntityStore *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }

private:
    EntityStore *q_ptr;
};

Mere::Store::EntityStore::~EntityStore()
{
}

Mere::Store::EntityStore::EntityStore(const QString &store, QObject *parent)
    : MapStore(store, parent),
      d_ptr(new EntityStorePrivate(this))
{
}

Mere::Store::EntityStore::EntityStore(const QString &store, const QString &slice, QObject *parent)
    : MapStore(store, slice, parent),
      d_ptr(new EntityStorePrivate(this))
{
}

int Mere::Store::EntityStore::create(const Entity &entity)
{
    UnitRef ref = entity.ref();

    bool found = this->found(ref);
    if (found) return 1;

    QMap<QString, QVariant> map = entity.map();

    return this->set(map);
}

int Mere::Store::EntityStore::update(const Entity &entity)
{
    UnitRef ref = entity.ref();

    Entity fetchedEntity;
    int err = fetch(ref, fetchedEntity);
    if (err) return err;

    bool synced = true;

    QMap<QString, QVariant> fetchedEntries = fetchedEntity.map();

    QMap<QString, QVariant> entries = entity.map();
    QMapIterator<QString, QVariant> it(entries);
    while (it.hasNext())
    {
        it.next();
        QString key = it.key();

        if (fetchedEntries.contains(key))
        {
            QVariant fetchedValue = fetchedEntries.value(key);
            if (fetchedValue != it.value())
            {
                synced = false;
            }
            else
            {
                entries.remove(key);
            }
        }
        else
        {
            synced = false;
        }
    }

    if (synced)
    {
        qDebug() << "Nothing to sync actually!";
        return 0;
    }

    return this->set(entries);
}

int Mere::Store::EntityStore::fetch(const Ref &ref, Entity &entity)
{
    QString key = ref.toString();

    QVariant list = PairStore::find(key);
    if (!list.isValid()) return 1;

    QMap<QString, QVariant> entries = list.toMap();
    if (entries.isEmpty()) return 2;

    return entity.set(entries);
}

bool Mere::Store::EntityStore::found(const Ref &ref)
{
    QString key = ref.toString();

    QVariant list = PairStore::find(key, 1);
    if (!list.isValid()) return false;

    QMap<QString, QVariant> entries = list.toMap();
    if (entries.isEmpty()) return false;

    return true;
}

int Mere::Store::EntityStore::remove(const Ref &ref)
{
    if(!ref.isValid()) return 1;

    bool found = this->found(ref);
    if (!found) return 2;

    QRegExp regex(QRegExp::escape(ref.toString()));
    if (!regex.isValid() || regex.isEmpty()) return 3;

    int err = del(regex);

    return err;
}

QVariant Mere::Store::EntityStore::list(const int &limit)
{
    QList<Entity *> entities;

    uint count = limit;

    QString entityKey;
    Entity *entity = nullptr;

    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid() && (limit == 0 || count != 0); it->Next())
    {
        QString key   = QString::fromStdString(it->key().ToString());
        QString value = QString::fromStdString(it->value().ToString());

        UnitKey unitKey(key);

        if(entityKey.compare(unitKey.ref().toString()) != 0)
        {
            entityKey = unitKey.ref().toString();
            entity = new Entity(unitKey.ref());

            entities.append(entity);
            if (limit != 0) --count;
        }

        entity->add(key, value);
    }

    delete it;

    return QVariant::fromValue(entities);
}

QVariant Mere::Store::EntityStore::list(const QString &ref, const int &limit)
{
    QList<Entity *> entities;

    uint count = limit;

    QString entityKey;
    Entity *entity = nullptr;

    std::string skey = ref.toStdString();

    leveldb::Iterator* it = db()->NewIterator(leveldb::ReadOptions());
    for (it->Seek(skey); it->Valid() && (limit == 0 || count != 0); it->Next())
    {
        QString key   = QString::fromStdString(it->key().ToString());
        QString value = QString::fromStdString(it->value().ToString());

        UnitKey unitKey(key);

        if(entityKey.compare(unitKey.ref().toString()) != 0)
        {
            entityKey = unitKey.ref().toString();
            entity = new Entity(unitKey.ref());

            entities.append(entity);
            if (limit != 0) --count;
        }

        entity->add(key, value);
    }

    delete it;

    return QVariant::fromValue(entities);
}
