#include "store.h"
#include "merestoreconfig.h"

class Mere::Store::Store::StorePrivate
{
public:
    ~StorePrivate();
    StorePrivate(const QString &store)
        : m_store(store),
          m_slice("")
    {
    }

    StorePrivate(const QString &store, const QString &slice)
        : m_store(store),
          m_slice(slice)
    {

    }

    QString store() const
    {
        return m_store;
    }

    QString slice() const
    {
        return m_slice;
    }

private:
    QString m_store;
    QString m_slice;

    Mere::Store::Store *q_ptr;
};

Mere::Store::Store::~Store()
{

}

Mere::Store::Store::Store(const QString &store, QObject *parent)
    : QObject(parent),
      d_ptr(new StorePrivate(store))
{

}

Mere::Store::Store::Store(const QString &store, const QString &slice, QObject *parent)
    : QObject(parent),
      d_ptr(new StorePrivate(store, slice))
{

}

QString Mere::Store::Store::store() const
{
    return d_ptr->store();
}

QString Mere::Store::Store::slice() const
{
    return d_ptr->slice();
}
