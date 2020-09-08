#include "store.h"

#include "mere/store/format/mereunitstore.h"

#include <QJsonDocument>
#include <QJsonObject>
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
    MereStore *s;

    MereUnitStore store(m_store);
    s = &store;

    int ok = s->create();
    //qDebug() << " Store::create()... " << ok;

    return ok == 0;
}

bool Store::select() const
{
    MereStore *s;

    MereUnitStore store(m_store);
    s = &store;

    int ok = s->open();
    //qDebug() << " Store::select()... " << ok;

    return ok == 0;
}

bool Store::close() const
{
    MereStore *s;

    MereUnitStore store(m_store);
    s = &store;

    int ok = s->close();
    //qDebug() << " Store::close()... " << ok;

    return ok == 0;
}


bool Store::remove() const
{
    MereStore *s;

    MereUnitStore store(m_store);
    s = &store;

    int ok = s->remove();
    //qDebug() << " Store::remove()... " << ok;

    return ok == 0;
}

bool Store::set(const QVariant value)
{
    MereStore *s;

    MereUnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        err = s->set(value);

    //qDebug() << " Store::set()... " << err;

    return err == 0;
}

bool Store::set(const QString key, const QVariant value)
{
    MereStore *s;

    MereUnitStore store(m_store);
    s = &store;

    int err = s->open();
    if (!err)
        err = s->set(key, value);

    //qDebug() << " Store::set()... " << err;

    return err == 0;
}

QVariant Store::get(const QString key)
{
    QVariant value;

    MereStore *s;

    MereUnitStore store(m_store);
    s = &store;

    int err = s->open();
    //qDebug() << " Store::set()... " << err;

    if (!err)
        value = s->get(key);

    //qDebug() << " Store::set()... " << value;

    return value;
}

QVariant Store::list()
{
    QVariant value;

    MereStore *s;

    MereUnitStore store(m_store);
    s = &store;

    int err = s->open();
    //qDebug() << " Store::list()... " << err;

    if (!err)
        value = s->list();

    //qDebug() << " Store::set()... " << value;

    return value;
}

QVariant Store::del(const QString &key)
{
    QVariant value;

    MereStore *s;

    MereUnitStore store(m_store);
    s = &store;

    int err = s->open();
    //qDebug() << " Store::del()... " << err;

    if (!err)
        value = s->del(key);

    //qDebug() << " Store::del()... " << value;

    return value;

}
