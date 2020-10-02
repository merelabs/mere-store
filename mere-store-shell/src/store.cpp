#include "store.h"

#include "mere/store/store/basestore.h"
#include "mere/store/store/jsonstore.h"
#include "mere/store/store/unitstore.h"

Store::Store(QString store, QObject *parent)
    : QObject(parent),
      m_store(store)
{
}

Mere::Store::PairStore* Store::store(const QString &type) const
{
    Mere::Store::PairStore *store;

    if (type.compare("json") == 0)
        store = new Mere::Store::JsonStore(m_store);
    else if (type.compare("mson") == 0)
        store = new Mere::Store::UnitStore(m_store);
    else
        store = new Mere::Store::PairStore(m_store);

    return store;
}

bool Store::create() const
{
    Mere::Store::BaseStore store(m_store);

    return store.create() == 0;
}

bool Store::create(const Mere::Store::Index &index) const
{
    Mere::Store::BaseStore store(m_store);

    return store.create(index) == 0;
}

bool Store::select() const
{
    Mere::Store::BaseStore store(m_store);

    return store.open() == 0;
}

bool Store::close() const
{
    Mere::Store::BaseStore store(m_store);

    return store.close() == 0;
}

bool Store::remove() const
{
    Mere::Store::BaseStore store(m_store);

    return store.remove() == 0;
}

bool Store::set(const QVariant &value, const QString &type)
{
    Mere::Store::PairStore *s = this->store(type);

    int err = s->open();
    if (!err)
        err = s->set(value);

    delete s;

    return err == 0;
}

bool Store::set(const QString &key, const QVariant &value, const QString &type)
{
    Mere::Store::PairStore *s = this->store(type);

    int err = s->open();
    if (!err)
        err = s->set(key, value);

    delete s;

    return err == 0;
}

QVariant Store::get(const QString &key) const
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore store(m_store);

    int err = store.open();
    if (!err)
        value = store.get(key);

    return value;
}

QVariant Store::get(const QList<QString> &keys) const
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore store(m_store);

    int err = store.open();
    if (!err)
        value = store.get(keys);

    return value;
}

bool Store::del(const QString &key) const
{
    bool ok = false;

    Mere::Store::PairStore store(m_store);

    int err = store.open();
    if (!err)
        ok = store.del(key);

    return ok;
}

bool Store::del(const QList<QString> &keys) const
{
    bool ok = false;

    Mere::Store::PairStore store(m_store);

    int err = store.open();
    if (!err)
        ok = store.del(keys);

    return ok;
}

QVariant Store::list()
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore store(m_store);

    int err = store.open();
    if (!err)
        value = store.list();

    return value;
}

QVariant Store::list(const uint &limit)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore store(m_store);

    int err = store.open();
    if (!err)
        value = store.list(limit);

    return value;
}

QVariant Store::list(const QString &key)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore store(m_store);

    int err = store.open();
    if (!err)
        value = store.list(key);

    return value;
}

QVariant Store::list(const QString &key, const uint &limit)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore store(m_store);

    int err = store.open();
    if (!err)
        value = store.list(key, limit);

    return value;
}
