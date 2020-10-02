#include "basestore.h"
#include "indexstore.h"
#include "../config/config.h"
#include "../config/sliceconfig.h"
#include "../config/indexconfig.h"
#include "../engine/leveldbengine.h"

#include "mere/utils/merestringutils.h"

#include <QDir>
#include <QFile>

class Mere::Store::BaseStore::BaseStorePrivate
{
public:
    virtual ~BaseStorePrivate()
    {
        if (m_engine)
        {
            delete m_engine;
            m_engine = nullptr;
        }
    }

    BaseStorePrivate(BaseStore *q)
        : q_ptr(q),
          m_engine(new LevelDBEngine())
    {
    };

    virtual QString type() const
    {
        return Mere::Store::Type::STORE;
    }

    void init()
    {
    };

    /*
     * Layout of the storage system
     *
     * 1. {base}|
     * 2.       |- {store}
     * 3.                 |- master
     * 4.                 |- .store
     * 5                  |- indexes
     * 6.                 |         |- .indexes
     * 7.                 |         |- {index}
     * 8.                 |                   |- master
     * 9.                 |                   |- .index
     * 10.                |- slices
     * 11.                         |- .slices
     * 12.                         |- {slice}
     * 13.                                   |- master
     * 14.                                   |- .slice
     * 15.                                   |- indexes
     * 16.                                              |- .indexes
     * 17.                                              |-{index}
     * 18.                                                       |- master
     * 19                                                        |- .index
     *
     * base - base location where our stores are stored specified in configuratio
     *        file as mere.store.path
     *        Example: (1)
     *
     * path - defined in the configuration file as mere.store.path; also known as
     *        'base' location of the system
     *        Example: (1)
     *
     * home - location of the store or slice
     *        Example: (2), (7), (12) and (17) respectivly home of the store, index of
     *        the store(2), slice and index of the slice(12).
     */

    virtual int create()
    {
        int err = layout();
        if (err) return err;

        store();

        return m_engine->create();
    };

    int open()
    {
        store();

        return m_engine->open();
    };

    int close()
    {
        store();

        return m_engine->close();
    };

    int remove()
    {
        store();

        int err = m_engine->remove();
        if (err) return 1;

        QDir dir(home());
        bool ok = dir.removeRecursively();
        if (!ok) return 2;

        return 0;
    };

    QString home()
    {
        QString home = "";

        QString store = q_ptr->store();
        QFileInfo info(store);
        if (info.isAbsolute())
            home = store;
        else
            home = path() + store;

        return home;
    }

    int create(const Index &index)
    {
        return createIndex(index);
    }

    leveldb::DB* db()
    {
        return m_engine->db();
    };

private:
    QString path()
    {
        QString path = q_ptr->path();

        if (!path.endsWith(QDir::separator()))
            path = path.append(QDir::separator());

        return path;
    }

    void store()
    {
        store(this->home());
    }

    void store(const QString &home)
    {
        QTextStream(stdout) << "HOME:" << home << Qt::endl;
        m_engine->setStore(home + "/master");
    }

    int layout()
    {
        QString home = this->home();

        if (QDir(home).exists())
        {
            QTextStream(stdout) << "An entry is already there; please choose a different path."
                                << Qt::endl;
            return 2;
        }

        // Create HOME of the store and/or slice
        if(!QDir().mkpath(home))
        {
            QTextStream(stdout) << "System failed to create required path:" << Qt::endl
                                << home
                                << "Please check for the permission of the path."
                                << Qt::endl;
            return 3;
        }

        // Create a hidden file named .store
        if (q_ptr->type().compare(Mere::Store::Type::STORE) == 0)
        {
            QFile hidden(home + "/.store");
            if (!hidden.open(QIODevice::ReadWrite))
                return 4;
            hidden.close();
        }

        return 0;
    }

    int createIndex(const Index &index)
    {
        qDebug() << "INDEX : " <<q_ptr->store();
        BaseStore store(q_ptr->store(), index);
        int err = store.create();
        if (!err)
        {

        }

        return err;
    }

private:
    BaseStore *q_ptr;
    LevelDBEngine *m_engine;

    class BaseIndexPrivate;
    friend class BaseIndexPrivate;
};

class Mere::Store::BaseStore::BaseSlicePrivate : public Mere::Store::BaseStore::BaseStorePrivate
{
public:
    virtual ~BaseSlicePrivate()
    {

    }

    BaseSlicePrivate(BaseStore *q)
        : BaseStorePrivate(q)
    {
    }

    QString type() const override
    {
        return Mere::Store::Type::SLICE;
    }

    int create() override
    {
        int err = BaseStorePrivate::create();
        if (!err)
        {
            QFile hidden(this->home() + "/.slice");
            if (!hidden.open(QIODevice::ReadWrite))
                return 1;
            hidden.close();

        }

        return err;
    }
};

class Mere::Store::BaseStore::BaseIndexPrivate : public Mere::Store::BaseStore::BaseStorePrivate
{
public:
    virtual ~BaseIndexPrivate()
    {

    }

    BaseIndexPrivate(BaseStore *q)
        : BaseStorePrivate(q)
    {
    };

    BaseIndexPrivate(const Index &index, BaseStore *q)
        : BaseStorePrivate(q),
          m_index(index)
    {
    };

    QString type() const override
    {
        return Mere::Store::Type::INDEX;
    }

    int create() override
    {
        int err = BaseStorePrivate::create();
        if (!err)
        {
            QFile hidden(this->home() + "/.index");
            if (!hidden.open(QIODevice::ReadWrite))
                return 1;
            hidden.close();

        }

        return err;
    }

private:
    Index m_index;

    friend class BaseStorePrivate;
};

Mere::Store::BaseStore::~BaseStore()
{
    if (d_ptr)
    {
        delete d_ptr;
        d_ptr = nullptr;
    }
}

Mere::Store::BaseStore::BaseStore(const QString &store, QObject *parent)
    : Store(store),
      d_ptr(new BaseStorePrivate(this))
{

}

Mere::Store::BaseStore::BaseStore(const Store &store, const QString &slice, QObject *parent)
    : BaseStore(store.store(), slice, parent)
{
}

Mere::Store::BaseStore::BaseStore(const QString &store, const QString &slice, QObject *parent)
    : Store(store + "/slices/" +slice, parent),
      d_ptr(new BaseSlicePrivate(this))
{

}

Mere::Store::BaseStore::BaseStore(const Store &store, const Index &index, QObject *parent)
    : BaseStore(store.store(), index, parent)
{
}

Mere::Store::BaseStore::BaseStore(const QString &store, const Index &index, QObject *parent)
    : Store(store + "/indexes/" + index.name(), parent),
      d_ptr(new BaseIndexPrivate(this))
{
}

QString Mere::Store::BaseStore::type() const
{
    return d_ptr->type();
}

Mere::Store::Config* Mere::Store::BaseStore::config() const
{
    return Config::instance();
}

void Mere::Store::BaseStore::init()
{
    d_ptr->init();
}

QString Mere::Store::BaseStore::path() const
{
    Config *config = Config::instance();

    return config->path();
}

QString Mere::Store::BaseStore::mime() const
{
    Config *config = Config::instance();

    return config->mime();
}

QString Mere::Store::BaseStore::home() const
{
    return d_ptr->home();
}

int Mere::Store::BaseStore::create()
{
    return d_ptr->create();
}

int Mere::Store::BaseStore::open()
{
    return d_ptr->open();
}

int Mere::Store::BaseStore::close()
{
    return d_ptr->close();
}

int Mere::Store::BaseStore::remove()
{
    return d_ptr->remove();
}

int Mere::Store::BaseStore::create(const Index &index)
{
    return d_ptr->create(index);
}

leveldb::DB* Mere::Store::BaseStore::db()
{
    return d_ptr->db();
}
