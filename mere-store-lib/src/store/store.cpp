#include "store.h"

#include <QFileInfo>
class Mere::Store::Store::StorePrivate
{
public:
    virtual ~StorePrivate()
    {

    }

    StorePrivate(const QString &store, Store *q)
        : m_store(store),
          q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }

    QString store() const
    {
        return m_store;
    }

    void setStore(const QString &store)
    {
        m_store = store;
    }

    QString type() const
    {
        return m_type;
    }

private:
    QString m_store;
    QString m_type;

    Mere::Store::Store *q_ptr;
};

Mere::Store::Store::~Store()
{
    if (d_ptr)
    {
        delete d_ptr;
        d_ptr = nullptr;
    }
}

Mere::Store::Store::Store(const QString &name, QObject *parent)
    : d_ptr(new StorePrivate(name, this))
{
    Q_UNUSED(parent)
}

QString Mere::Store::Store::type() const
{
    return d_ptr->type();
}

QString Mere::Store::Store::store() const
{
    return d_ptr->store();
}
