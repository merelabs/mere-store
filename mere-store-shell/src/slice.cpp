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
    //qDebug() << " Slice::create()... " << ok;

    return ok == 0;
}

bool Slice::remove() const
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int ok = s->remove();
    //qDebug() << " Slice::remove()... " << ok;

    return ok == 0;
}

bool Slice::select() const
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int ok = s->open();
    //qDebug() << " Slice::select()... " << ok;

    return ok == 0;
}

bool Slice::close() const
{
    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int ok = s->close();
    //qDebug() << " Slice::close()... " << ok;

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

    //qDebug() << " Slice::set()... " << err;

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
    QVariant value;

    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    //qDebug() << " Slice::get()... " << err;

    if (!err)
        value = s->get(key);

    //qDebug() << " Slice::get()... " << value;

    return value;
}

QVariant Slice::del(const QString &key)
{
    QVariant value;

    Mere::Store::Store *s;

    Mere::Store::UnitStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    //qDebug() << " Slice::del()... " << err;

    if (!err)
        value = s->del(key);

    //qDebug() << " Slice::del()... " << value;

    return value;
}

QVariant Slice::list()
{
    QVariant value;

    Mere::Store::Store *s;

    Mere::Store::PairStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    //qDebug() << " Slice::list()... " << err;

    if (!err)
        value = s->list();

    //qDebug() << " Slice::set()... " << value;

    return value;
}


QVariant Slice::list(const uint &limit)
{
    QVariant value;

    Mere::Store::Store *s;

    Mere::Store::PairStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    //qDebug() << " Slice::list()... " << err;

    if (!err)
        value = s->list(limit);

    //qDebug() << " Slice::set()... " << value;

    return value;
}

QVariant Slice::list(const QString &key)
{
    QVariant value;

    Mere::Store::Store *s;

    Mere::Store::PairStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    //qDebug() << " Slice::list()... " << err;

    if (!err)
        value = s->list(key);

    //qDebug() << " Slice::set()... " << value;

    return value;
}

QVariant Slice::list(const QString &key, const uint &limit)
{
    QVariant value;

    Mere::Store::Store *s;

    Mere::Store::PairStore slice(m_store, m_slice);
    s = &slice;

    int err = s->open();
    //qDebug() << " Slice::list()... " << err;

    if (!err)
        value = s->list(key, limit);

    //qDebug() << " Slice::set()... " << value;

    return value;
}
