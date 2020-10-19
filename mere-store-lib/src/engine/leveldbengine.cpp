#include "leveldbengine.h"

#include "mere/utils/merestringutils.h"
#include <QDir>

class Mere::Store::LevelDBEngine::LevelDBEnginePrivate
{
public:
    ~LevelDBEnginePrivate()
    {
        close();
    }

    LevelDBEnginePrivate(LevelDBEngine *q)
        : m_db(nullptr),
          q_ptr(q)
    {
        Q_UNUSED(q_ptr)
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

        // qDebug() << "create()::" << status.ok() << QString::fromStdString(m_store.toStdString()) << QString::fromStdString(status.ToString());
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

        if (!status.ok())
            qDebug() << "open()::" << status.ok() << QString::fromStdString(m_store.toStdString()) << QString::fromStdString(status.ToString());

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

    bool exists()
    {
        bool err = open();
        close();

        return err;
    };

    leveldb::DB* db()
    {
        return m_db;
    };

private:
    QString m_store;
    leveldb::DB* m_db;
    LevelDBEngine *q_ptr;
};

Mere::Store::LevelDBEngine::~LevelDBEngine()
{
    if (d_ptr)
    {
        delete d_ptr;
        d_ptr = nullptr;
    }
}

Mere::Store::LevelDBEngine::LevelDBEngine(QObject *parent)
    : Engine(parent),
      d_ptr(new LevelDBEnginePrivate(this))
{

}

void Mere::Store::LevelDBEngine::setStore(const QString store)
{
    d_ptr->setStore(store);
}

QString Mere::Store::LevelDBEngine::store() const
{
    return d_ptr->store();
}

int Mere::Store::LevelDBEngine::create()
{
    return d_ptr->create();
}

int Mere::Store::LevelDBEngine::open()
{
    return d_ptr->open();
}

int Mere::Store::LevelDBEngine::close()
{
    return d_ptr->close();
}

int Mere::Store::LevelDBEngine::remove()
{
    return d_ptr->remove();
}

bool Mere::Store::LevelDBEngine::exists()
{
    return d_ptr->exists();
}

leveldb::DB* Mere::Store::LevelDBEngine::db()
{
    return d_ptr->db();
}
