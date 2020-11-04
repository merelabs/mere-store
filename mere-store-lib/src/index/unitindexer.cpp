#include "unitindexer.h"
#include "../store/indexstore.h"
#include "indexkey.h"

#include <QDateTime>

Mere::Store::UnitIndexer::~UnitIndexer()
{

}

Mere::Store::UnitIndexer::UnitIndexer(Store &store, const QString &name, QObject *parent)
    : Indexer(parent),
      m_store(store),
      m_name(name)
{

}

int Mere::Store::UnitIndexer::index(const QString &key, const Ref &ref) const
{
    IndexStore store(m_store, m_name);

    int err = store.open();
    if (!err)
    {
        QVariant value = QString::number(QDateTime::currentMSecsSinceEpoch());
        err = store.set(key + ":" + ref.key(), value);
    }

    return err;
}

int Mere::Store::UnitIndexer::reindex(const QString &key, const Ref &ref) const
{
    int err = remove(ref);
    if (!err)
        err= index(key, ref);

    return err;
}

int Mere::Store::UnitIndexer::remove(const Ref &ref) const
{
    IndexStore store(m_store, m_name);
    int err = store.open();
    if (!err)
    {
        QRegExp re(QRegExp::escape(ref.key()));
        err = store.del(re);
    }

    return err;
}

Mere::Store::UnitRef Mere::Store::UnitIndexer::findOne(const QString &what) const
{
    UnitRef ref;

    IndexStore store(m_store, m_name);
    int err = store.open();
    if (!err)
    {
        QVariant var = store.list("^" + what + ":");
        if (var.isValid())
        {
            QMap<QString, QVariant> records = var.toMap();
            QMapIterator<QString, QVariant> it(records);
            while (it.hasNext())
            {
                it.next();

                QString key = it.key();

                IndexKey indexKey(key);
                ref = indexKey.ref();
                break;
            }
        }
    }

    return ref;
}

QList<Mere::Store::UnitRef> Mere::Store::UnitIndexer::find(const QString &what) const
{
    QList<Mere::Store::UnitRef> refs;

    IndexStore store(m_store, m_name);
    int err = store.open();
    if (err) return refs;

    QVariant var = store.find(what);
    if (var.isValid())
    {
        QMap<QString, QVariant> records = var.toMap();
        QMapIterator<QString, QVariant> it(records);
        while (it.hasNext())
        {
            it.next();

            QString key = it.key();

            IndexKey indexKey(key);
            refs.append(indexKey.ref());
        }
    }

    return refs;
}

QList<Mere::Store::Pair> Mere::Store::UnitIndexer::query(const QString &what) const
{
    QList<Pair> pairs;

    IndexStore store(m_store, m_name);
    int err = store.open();
    if (err) return pairs;

    QVariant var = store.find(what);
    if (var.isValid())
    {
        QMap<QString, QVariant> records = var.toMap();
        QMapIterator<QString, QVariant> it(records);
        while (it.hasNext())
        {
            it.next();

            IndexKey indexKey(it.key());

            Pair pair(indexKey.what(), QVariant::fromValue(indexKey.ref()));
            pairs.append(pair);
        }
    }

    return pairs;
}
