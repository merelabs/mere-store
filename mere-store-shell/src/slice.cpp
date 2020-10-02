#include "slice.h"
#include "store.h"

#include "mere/store/store/unitstore.h"
#include "mere/store/store/jsonstore.h"
#include "mere/store/store/pairstore.h"

Slice::Slice(const QString &store, const QString &slice, QObject *parent)
    : QObject(parent),
      m_store(store),
      m_slice(slice)
{

}

Mere::Store::PairStore* Slice::slice(const QString &type) const
{
    Mere::Store::PairStore *store;

    if (type.compare("json") == 0)
        store = new Mere::Store::JsonStore(m_store, m_slice);
    else if (type.compare("mson") == 0)
        store = new Mere::Store::UnitStore(m_store, m_slice);
    else
        store = new Mere::Store::PairStore(m_store, m_slice);

    return store;
}

bool Slice::create() const
{
    Mere::Store::BaseStore slice(m_store, m_slice);

    return slice.create() == 0;
}

bool Slice::create(const Mere::Store::Index &index) const
{
    Mere::Store::BaseStore slice(m_store, m_slice);

    return slice.create(index) == 0;
}

bool Slice::remove() const
{
    Mere::Store::BaseStore slice(m_store, m_slice);

    int ok = slice.remove();

    return ok == 0;
}

bool Slice::select() const
{
    Mere::Store::BaseStore slice(m_store, m_slice);

    int ok = slice.open();

    return ok == 0;
}

bool Slice::close() const
{
    Mere::Store::BaseStore slice(m_store, m_slice);

    int ok = slice.close();

    return ok == 0;
}

bool Slice::set(const QVariant &value, const QString &type)
{
    Mere::Store::PairStore *s = slice(type);

    int err = s->open();
    if (!err)
        err = s->set(value);

    delete s;

    return err == 0;
}

bool Slice::set(const QString &key, const QVariant &value, const QString &type)
{
    Mere::Store::PairStore *s = slice(type);

    int err = s->open();
    if (!err)
        err = s->set(key, value);

    delete s;

    return err == 0;
}

QVariant Slice::get(const QString &key) const
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore slice(m_store, m_slice);

    int err = slice.open();
    if (!err)
        value = slice.get(key);

    return value;
}

QVariant Slice::get(const QList<QString> &keys) const
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore slice(m_store, m_slice);

    int err = slice.open();
    if (!err)
        value = slice.get(keys);

    return value;
}

bool Slice::del(const QString &key) const
{
    bool ok = false;

    Mere::Store::PairStore slice(m_store, m_slice);

    int err = slice.open();
    if (!err)
        ok = slice.del(key);

    return ok;
}

bool Slice::del(const QList<QString> &keys) const
{
    bool ok = false;

    Mere::Store::PairStore slice(m_store, m_slice);

    int err = slice.open();
    if (!err)
        ok = slice.del(keys);

    return ok;
}

QVariant Slice::list()
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore slice(m_store, m_slice);

    int err = slice.open();
    if (!err)
        value = slice.list();

    return value;
}

QVariant Slice::list(const uint &limit)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore slice(m_store, m_slice);

    int err = slice.open();
    if (!err)
        value = slice.list(limit);

    return value;
}

QVariant Slice::list(const QString &key)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore slice(m_store, m_slice);

    int err = slice.open();
    if (!err)
        value = slice.list(key);

    return value;
}

QVariant Slice::list(const QString &key, const uint &limit)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore slice(m_store, m_slice);

    int err = slice.open();
    if (!err)
        value = slice.list(key, limit);

    return value;
}
