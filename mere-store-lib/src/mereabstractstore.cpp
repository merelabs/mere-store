#include "mereabstractstore.h"

#include <QDir>

class MereAbstractStore::MereAbstractStorePrivate
{
public:
    ~MereAbstractStorePrivate()
    {
        qDebug() << "~MereAbstractStorePrivate::...." << m_db;

        if (m_db)
        {
            delete m_db;
            m_db = 0;
        }
    }

    MereAbstractStorePrivate(MereAbstractStore *q)
        : m_db(0),
          q_ptr(q)
    {
        qDebug() << "MereAbstractStorePrivate::....";
    };

    void init()
    {
        open();
    };

    int create()
    {
        qDebug() << "create():....1";
        m_path = q_ptr->path();
        qDebug() << "create():....2";

        QString store(m_path);
        store = store.append(q_ptr->store());

        leveldb::Options options;
        options.create_if_missing = true;
        options.error_if_exists = true;

        options.block_cache = leveldb::NewLRUCache(10 * 1048576);

        leveldb::Status status = leveldb::DB::Open(options, store.toStdString(), &m_db);

        qDebug() << "create()::" << status.ok() << QString::fromStdString(store.toStdString()) << QString::fromStdString(status.ToString());
        // 0  - success
        // !0 - failed
        return !status.ok();
    };

    int open()
    {
        qDebug() << "open():....1";
        m_path = q_ptr->path();
        qDebug() << "open():....2";


        QString store(m_path);
        store = store.append(q_ptr->store());

        leveldb::Options options;
        options.create_if_missing = false;
        options.error_if_exists = false;

        options.block_cache = leveldb::NewLRUCache(10 * 1048576);

        leveldb::Status status = leveldb::DB::Open(options, store.toStdString(), &m_db);

        qDebug() << "open()::" << status.ok() << QString::fromStdString(store.toStdString()) << QString::fromStdString(status.ToString());

        // 0  - success
        // !0 - failed
        return !status.ok();
    };

    int close()
    {
        qDebug() << "close():....1";
        m_path = q_ptr->path();
        qDebug() << "close():....2";


        QString store(m_path);
        store = store.append(q_ptr->store());

        qDebug() << "1... Closing database..." << m_path;
        qDebug() << "2... Closing database..." << q_ptr->store();

        qDebug() << "XX Closing database" << store << m_db;
        if (m_db)
        {
            qDebug() << "YY Closing database" << store << m_db;
            delete m_db;
            m_db = 0;
        }
        qDebug() << "ZZ Closing database" << store << m_db;

        return 0;
    };

    int remove()
    {
        int err = open();
        if (err) return err;

        close();

        qDebug() << "remove():....1";
        m_path = q_ptr->path();
        qDebug() << "remove():....2";


        QString store(m_path);
        store = store.append(q_ptr->store());


        QDir dir(store);
        dir.removeRecursively();

        return 0;
    };

    leveldb::DB* db()
    {
        return m_db;
    };

private:
    QString m_path;
    leveldb::DB *m_db;

    MereAbstractStore *q_ptr;
};

MereAbstractStore::~MereAbstractStore()
{
    //close();
    //d_ptr->close();

    qDebug() << "~MereAbstractStore::...." << d_ptr->db();
    if (d_ptr)
    {
        delete d_ptr;
        d_ptr = 0;
    }
}

MereAbstractStore::MereAbstractStore(const QString store, QObject *parent)
    : MereStore(store, parent),
      d_ptr(new MereAbstractStorePrivate(this))
{
    qDebug() << "MereAbstractStore::...." << store;
}

void MereAbstractStore::init()
{
//    m_path = path();
//    open();
    d_ptr->init();
}

int MereAbstractStore::create()
{
    qDebug() << "Creating database" << this->path().append(this->store());
    return d_ptr->create();
}

int MereAbstractStore::open()
{
    qDebug() << "Opening database" << this->path().append(this->store());
    return d_ptr->open();
}

int MereAbstractStore::close()
{
    qDebug() << "2...>>>>>>>>>>>";
    qDebug() << "Closing database" << this->path().append(this->store());
    return d_ptr->close();
}

int MereAbstractStore::remove()
{
    qDebug() << "Removing database" << this->path().append(this->store());

    return d_ptr->remove();
}

leveldb::DB* MereAbstractStore::db()
{
    qDebug() << ">>>>>>>>>>>>>>";
    return d_ptr->db();
}
