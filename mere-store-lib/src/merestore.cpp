#include "merestore.h"
#include "merestoreconfig.h"

class MereStore::MereStorePrivate
{
public:
    ~MereStorePrivate();
    MereStorePrivate(const QString &store)
        : m_store(store),
          m_slice("")
    {
        //qDebug() << "MereStorePrivate::...." << store;
    }

    MereStorePrivate(const QString &store, const QString &slice)
        : m_store(store),
          m_slice(slice)
    {
        qDebug() << "MereStorePrivate::...." << store;
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

    MereStore *q_ptr;
};

MereStore::~MereStore()
{
    //close();
}

MereStore::MereStore(const QString &store, QObject *parent)
    : QObject(parent),
      d_ptr(new MereStorePrivate(store))
{
    //qDebug() << "MereStore::...." << store;
}

MereStore::MereStore(const QString &store, const QString &slice, QObject *parent)
    : QObject(parent),
      d_ptr(new MereStorePrivate(store, slice))
{
    //qDebug() << "MereStore::...." << store;
}

QString MereStore::store() const
{
    return d_ptr->store();
}

QString MereStore::slice() const
{
    return d_ptr->slice();
}
