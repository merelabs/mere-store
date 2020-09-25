#include "basestore.h"
#include "merestoreconfig.h"
#include "engine/leveldbengine.h"

#include "mere/utils/merestringutils.h"

#include <QDir>
#include <QFile>

class Mere::Store::BaseStore::BaseStorePrivate
{
public:
    ~BaseStorePrivate()
    {
        if (m_engine)
        {
            delete m_engine;
            m_engine = 0;
        }
    }

    BaseStorePrivate(BaseStore *q)
        : q_ptr(q),
          m_engine(new LevelDBEngine())
    {

    };

    void init()
    {

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

    QString base()
    {
        return base(path());
    }

    QString base(const QString &path)
    {
        return path + q_ptr->store();
    }

    QString home()
    {
        return this->home(this->base());
    }

    QString home(const QString &base)
    {
        return MereStringUtils::isBlank(q_ptr->slice()) ? base : (base + "/slices/" + q_ptr->slice());
    }

    void store()
    {
        m_engine->setStore(this->home() + "/master");
    }

    void store(const QString &home)
    {
        m_engine->setStore(home + "/master");
    }

    int layout()
    {
        QString path = this->path();

        if (!QDir(path).exists() && !QDir().mkpath(path))
            return 1;

        QString base = this->base(path);
        QString home = this->home(base);

        if (QDir(home).exists())
            return 2;

        // Create HOME of the Store/Slice
        if(!QDir().mkdir(home))
            return 3;

        // Create a file named .store/.slice
        QString file = MereStringUtils::isBlank(q_ptr->slice()) ? ".store" : ".slice";
        QFile hidden(home + "/" + file);
        if (!hidden.open(QIODevice::ReadWrite))
            return 4;

        hidden.close();

        // its store
        if (MereStringUtils::isBlank(q_ptr->slice()))
        {
            // Create HOME of the Slices
            if(!QDir().mkdir(home + "/slices"))
                return 5;

            // Create a file named slices
            QFile slices(home + "/slices/.slices");
            if (!slices.open(QIODevice::ReadWrite))
                return 6;

            slices.close();
        }

        return 0;
    }

private:
    BaseStore *q_ptr;
    LevelDBEngine *m_engine;
};

Mere::Store::BaseStore::~BaseStore()
{
    if (d_ptr)
    {
        delete d_ptr;
        d_ptr = 0;
    }
}

Mere::Store::BaseStore::BaseStore(const QString &store, QObject *parent)
    : BaseStore(store, "", parent)
{

}

Mere::Store::BaseStore::BaseStore(const QString &store, const QString &slice, QObject *parent)
    : Store(store, slice, parent),
      d_ptr(new BaseStorePrivate(this))
{

}

void Mere::Store::BaseStore::init()
{
    d_ptr->init();
}

QString Mere::Store::BaseStore::path() const
{
    MereStoreConfig *config = MereStoreConfig::instance();

    return config->path();
}

QString Mere::Store::BaseStore::mime() const
{
    MereStoreConfig *config = MereStoreConfig::instance();

    return config->mime();
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

leveldb::DB* Mere::Store::BaseStore::db()
{
    return d_ptr->db();
}
