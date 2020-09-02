#include "merestore.h"
#include "merestoreconfig.h"

class MereStore::MereStorePrivate
{
public:
    ~MereStorePrivate();
    MereStorePrivate(const QString store)
        : m_store(store)
    {
        //qDebug() << "MereStorePrivate::...." << store;
    }

    QString store() const
    {
        return m_store;
    }

private:
    QString m_store;

    MereStore *q_ptr;
};

MereStore::~MereStore()
{
    //close();
}

MereStore::MereStore(const QString store, QObject *parent)
    : QObject(parent),
      d_ptr(new MereStorePrivate(store))
{
    //qDebug() << "MereStore::...." << store;
}

QString MereStore::store() const
{
    return d_ptr->store();
}
