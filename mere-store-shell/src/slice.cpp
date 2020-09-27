#include "slice.h"
#include "store.h"

#include "mere/store/unitstore.h"
#include "mere/store/pairstore.h"

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
    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        err = s->set(value);

    return err == 0;
}

bool Slice::set(const QString &key, const QVariant &value)
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        err = s->set(key, value);

    return err == 0;
}

QVariant Slice::get(const QString &key)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        value = s->get(key);

    return value;
}

QVariant Slice::del(const QString &key)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        value = s->del(key);

    return value;
}

QVariant Slice::list()
{
    QVariant value(QVariant::Invalid);

    Mere::Store::Store *s;

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

    Mere::Store::Store *s;

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

    Mere::Store::Store *s;

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

    Mere::Store::Store *s;

    Mere::Store::PairStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    if (!err)
        value = s->list(key, limit);

    return value;
}
