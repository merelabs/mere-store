#include "store.h"

#include "mere/store/store/basestore.h"
#include "mere/store/store/unitstore.h"

#include <QFileInfo>

Store::Store(QObject *parent)
    : Store("", parent)
{

}

Store::Store(QString store, QObject *parent)
    : QObject(parent),
      m_store(store)
{

}

bool Store::create() const
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int err = s->create();

    return err == 0;
}

bool Store::create(const Mere::Store::Index &index) const
{
    Mere::Store::BaseStore s(m_store);
    int err = s.create(index);

    return err == 0;
}

bool Store::select() const
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int ok = s->open();

    return ok == 0;
}

bool Store::close() const
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int ok = s->close();

    return ok == 0;
}


bool Store::remove() const
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int ok = s->remove();

    return ok == 0;
}

bool Store::set(const QVariant &value)
{
    Mere::Store::PairStore *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        err = s->set(value);

    return err == 0;
}

bool Store::set(const QString &key, const QVariant &value)
{
    Mere::Store::PairStore *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        err = s->set(key, value);

    return err == 0;
}

QVariant Store::get(const QString &key) const
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        value = s->get(key);

    return value;
}

QVariant Store::get(const QList<QString> &keys) const
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        value = s->get(keys);

    return value;
}

bool Store::del(const QString &key) const
{
    bool ok = false;

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        ok = s->del(key);

    return ok;
}

bool Store::del(const QList<QString> &keys) const
{
    bool ok = false;

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        ok = s->del(keys);

    return ok;
}

QVariant Store::list()
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        value = s->list();

    return value;
}

QVariant Store::list(const uint &limit)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        value = s->list(limit);

    return value;
}

QVariant Store::list(const QString &key)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        value = s->list(key);

    return value;
}

QVariant Store::list(const QString &key, const uint &limit)
{
    QVariant value(QVariant::Invalid);

    Mere::Store::PairStore *s;

    Mere::Store::UnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        value = s->list(key, limit);

    return value;
}
