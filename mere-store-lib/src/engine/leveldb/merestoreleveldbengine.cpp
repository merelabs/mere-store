#include "merestoreleveldbengine.h"

#include "mere/utils/merestringutils.h"
#include <QDir>

class MereStoreLevelDBEngine::MereStoreLevelDBEnginePrivate
{
public:
    ~MereStoreLevelDBEnginePrivate()
    {
//        qDebug() << "~MereStoreLevelDBEnginePrivate::...." << m_db;
        close();
    }

    MereStoreLevelDBEnginePrivate(MereStoreLevelDBEngine *q)
        : m_db(0),
          q_ptr(q)
    {
//        qDebug() << "MereStoreLevelDBEnginePrivate::....";
    };

    void setStore(const QString store)
    {
        m_store = store;
    }

    QString store() const
    {
        return m_store;
    }

    int create()
    {
        leveldb::Options options;
        options.create_if_missing = true;
        options.error_if_exists = true;

        options.block_cache = leveldb::NewLRUCache(10 * 1048576);

        leveldb::Status status = leveldb::DB::Open(options, m_store.toStdString(), &m_db);

        //qDebug() << "create()::" << status.ok() << QString::fromStdString(m_store.toStdString()) << QString::fromStdString(status.ToString());
        // 0  - success
        // !0 - failed
        return !status.ok();
    };

    int open()
    {
        leveldb::Options options;
        options.create_if_missing = false;
        options.error_if_exists = false;

        options.block_cache = leveldb::NewLRUCache(10 * 1048576);

        leveldb::Status status = leveldb::DB::Open(options, m_store.toStdString(), &m_db);

        //qDebug() << "open()::" << status.ok() << QString::fromStdString(m_store.toStdString()) << QString::fromStdString(status.ToString());

        // 0  - success
        // !0 - failed
        return !status.ok();
    };

    int close()
    {
        if (m_db)
        {
            delete m_db;
            m_db = 0;
        }

        return 0;
    };

    int remove()
    {
        int err = open();
        if (err) return err;

        close();

        QDir dir(m_store);
        dir.removeRecursively();

        return 0;
    };

    leveldb::DB* db()
    {
        return m_db;
    };

private:
    QString m_store;
    leveldb::DB* m_db;
    MereStoreLevelDBEngine *q_ptr;
};

MereStoreLevelDBEngine::~MereStoreLevelDBEngine()
{
    if (d_ptr)
    {
        delete d_ptr;
        d_ptr = 0;
    }
}

MereStoreLevelDBEngine::MereStoreLevelDBEngine(QObject *parent)
    : MereStoreEngine(parent),
      d_ptr(new MereStoreLevelDBEnginePrivate(this))
{

}

void MereStoreLevelDBEngine::setStore(const QString store)
{
    d_ptr->setStore(store);
}

QString MereStoreLevelDBEngine::store() const
{
    return d_ptr->store();
}

int MereStoreLevelDBEngine::create()
{
    return d_ptr->create();
}

int MereStoreLevelDBEngine::open()
{
    return d_ptr->open();
}

int MereStoreLevelDBEngine::close()
{
    return d_ptr->close();
}

int MereStoreLevelDBEngine::remove()
{
    return d_ptr->remove();
}

leveldb::DB* MereStoreLevelDBEngine::db()
{
    return d_ptr->db();
}
