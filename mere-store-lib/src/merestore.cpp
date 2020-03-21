#include "merestore.h"
#include "merestoreconfig.h"

MereStore::~MereStore()
{
    close();
}

MereStore::MereStore(const QString store, QObject *parent)
    : QObject(parent),
      m_store(store)
{
    qDebug() << "....";
}

void MereStore::init()
{
    m_path = path();
    open();
}

QString MereStore::path() const
{
    QString path;

    MereStoreConfig *config = MereStoreConfig::instance();
    QVariant storePath = config->get(Mere::Store::StoreKey);
    if (storePath.isValid())
        path = storePath.toString();

    return path;
}

void MereStore::open()
{
    QString store(m_path);
    store = store.append(m_store);

    leveldb::Options options;
    options.create_if_missing = true;
    options.block_cache = leveldb::NewLRUCache(10 * 1048576);

    leveldb::Status status = leveldb::DB::Open(options, store.toStdString(), &m_db);
    if (false == status.ok())
    {
        qDebug() << "Unable to open/create test database: " << store;
    }
}

void MereStore::close()
{
    qDebug() << ">>>>>>>>";
    qDebug() << "Closing database" << m_path.append(m_store);
    if (m_db)
        delete m_db;
}

leveldb::DB* MereStore::db()
{
    return m_db;
}
