#include "merebasestore.h"
#include "engine/leveldb/merestoreleveldbengine.h"

#include <QDir>

class MereBaseStore::MereBaseStorePrivate
{
public:
    ~MereBaseStorePrivate()
    {
        if (m_engine)
        {
            delete m_engine;
            m_engine = 0;
        }
    }

    MereBaseStorePrivate(MereBaseStore *q)
        : q_ptr(q),
          m_engine(new MereStoreLevelDBEngine())
    {
        //qDebug() << "STORE:" << q_ptr->store();
        m_engine->setStore("/tmp/" + q_ptr->store());
    };

    void init()
    {
        //open();
    };

    int create()
    {
        return m_engine->create();
    };

    int open()
    {
        return m_engine->open();
    };

    int close()
    {
        return m_engine->close();
    };

    int remove()
    {
        return m_engine->remove();
    };

    leveldb::DB* db()
    {
        return m_engine->db();
    };

private:
    MereBaseStore *q_ptr;
    MereStoreLevelDBEngine *m_engine;
};

MereBaseStore::~MereBaseStore()
{
    if (d_ptr)
    {
        delete d_ptr;
        d_ptr = 0;
    }
}

MereBaseStore::MereBaseStore(const QString store, QObject *parent)
    : MereStore(store, parent),
      d_ptr(new MereBaseStorePrivate(this))
{
}

void MereBaseStore::init()
{
    d_ptr->init();
}

int MereBaseStore::create()
{
    return d_ptr->create();
}

int MereBaseStore::open()
{
    return d_ptr->open();
}

int MereBaseStore::close()
{
    return d_ptr->close();
}

int MereBaseStore::remove()
{
    return d_ptr->remove();
}

leveldb::DB* MereBaseStore::db()
{
    return d_ptr->db();
}
