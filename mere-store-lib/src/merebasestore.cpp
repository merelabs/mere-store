#include "merebasestore.h"
#include "engine/leveldb/merestoreleveldbengine.h"

#include "mere/utils/merestringutils.h"

#include <QDir>
#include <QFile>

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
        QString base = "/tmp/store/";

        m_storeHome = base + q_ptr->store();
        m_sliceHome = base + q_ptr->store() + "/slices";

        if (MereStringUtils::isBlank(q_ptr->slice()))
            m_engine->setStore(m_storeHome + "/master");
        else
            m_engine->setStore(m_sliceHome + "/" + q_ptr->slice() + "/master");
    };

    void init()
    {
        //open();
    };

    /*
     * Directiry layout
     * {base}/{store}/master
     *               /.store
     *               /slices/.slices
     *                      /{slice}/master
     *                              /.slice
     */

    int create()
    {
        if (MereStringUtils::isBlank(q_ptr->slice()))
        {
            if (QDir(m_storeHome).exists())
                return 1;

            // Create HOME of the Store
            bool ok = QDir().mkdir(m_storeHome);
            if (!ok)
            {
                // handle error here!
                return 2;
            }

            // Create a file named store
            QFile store(m_storeHome + "/.store");
            if (store.open(QIODevice::ReadWrite))
                store.close();
            else
                ; // handle error here!

            // Create HOME of the Slices
            QDir().mkdir(m_sliceHome);

            // Create a file named slices
            QFile slices(m_sliceHome + "/.slices");
            if (slices.open(QIODevice::ReadWrite))
                slices.close();
            else
                ; // handle error here!
        }
        else
        {
            if (!QDir(m_storeHome).exists())
                return 3;

            // Create HOME of the Slices
            if (!QDir(m_sliceHome).exists())
                QDir().mkdir(m_sliceHome);

            // Create HOME of the Slice
            QDir().mkdir(m_sliceHome + "/" + q_ptr->slice() );

            // Create a file named slice
            QFile slice(m_sliceHome + "/" + q_ptr->slice() + "/.slice");
            if (slice.open(QIODevice::ReadWrite))
                slice.close();
            else
                ; // handle error here!
        }

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
        int err = m_engine->remove();
        if (MereStringUtils::isBlank(q_ptr->slice()))
        {
            if(!err)
            {
                QDir dir(m_storeHome);
                dir.removeRecursively();
            }
        }

        return err;
    };

    leveldb::DB* db()
    {
        return m_engine->db();
    };

private:
    QString m_storeHome;
    QString m_sliceHome;

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

MereBaseStore::MereBaseStore(const QString &store, QObject *parent)
    : MereBaseStore(store, "", parent)
{
    qDebug() << "MereBaseStorePrivate::>>>>>>>>>>>>>>>>>";
}

MereBaseStore::MereBaseStore(const QString &store, const QString &slice, QObject *parent)
    : MereStore(store, slice, parent),
      d_ptr(new MereBaseStorePrivate(this))
{
    qDebug() << "MereBaseStorePrivate::>>>>>>>>>>>>>>>>>";
}


void MereBaseStore::init()
{
    d_ptr->init();
}

int MereBaseStore::create()
{
    qDebug() << "create::>>>>>>>>>>>>>>>>>";
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
