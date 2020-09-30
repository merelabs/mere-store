#include "slice.h"
#include "store.h"

#include "mere/store/store/unitstore.h"
#include "mere/store/store/pairstore.h"

Slice::Slice(QObject *parent)
    : Slice("", "", parent)
{

}

Slice::Slice(const QString &store, const QString &slice, QObject *parent)
    : QObject(parent),
      m_store(store),
      m_slice(slice)
{

}

bool Slice::create() const
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int ok = s->create();

    return ok == 0;
}

bool Slice::create(const Mere::Store::Index &index) const
{
    Mere::Store::BaseStore store(m_store);
    Mere::Store::BaseStore slice(store, m_slice);

    int err = slice.create(index);

    return err == 0;
}

bool Slice::remove() const
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int ok = s->remove();

    return ok == 0;
}

bool Slice::select() const
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int ok = s->open();

    return ok == 0;
}

bool Slice::close() const
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int ok = s->close();

    return ok == 0;
}

bool Slice::set(const QVariant &value)
{
    Mere::Store::PairStore *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        err = s->set(value);

    return err == 0;
}

bool Slice::set(const QString &key, const QVariant &value)
{
    Mere::Store::PairStore *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        err = s->set(key, value);

    return err == 0;
}

QVariant Slice::get(const QString &key) const
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        value = s->get(key);

    return value;
}

QVariant Slice::get(const QList<QString> &keys) const
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        value = s->get(keys);

    return value;
}

bool Slice::del(const QString &key) const
{
    bool ok = false;

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        ok = s->del(key);

    return ok;
}

bool Slice::del(const QList<QString> &keys) const
{
    bool ok = false;

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        ok = s->del(keys);

    return ok;
}

QVariant Slice::list()
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::PairStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        value = s->list();

    return value;
}

QVariant Slice::list(const uint &limit)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::PairStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        value = s->list(limit);

    return value;
}

QVariant Slice::list(const QString &key)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::PairStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        value = s->list(key);

    return value;
}

QVariant Slice::list(const QString &key, const uint &limit)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::PairStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        value = s->list(key, limit);

    return value;
}
