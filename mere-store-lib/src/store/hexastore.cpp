#include "hexastore.h"
#include "../hexakey.h"

#include "mere/utils/stringutils.h"

#include <QDateTime>

QString Mere::Store::HexaStore::HEXA_KEY_1 = "s:%1:p:%2:o:%3";
QString Mere::Store::HexaStore::HEXA_KEY_2 = "s:%1:o:%3:p:%2";
QString Mere::Store::HexaStore::HEXA_KEY_3 = "p:%2:s:%1:o:%3";
QString Mere::Store::HexaStore::HEXA_KEY_4 = "p:%2:o:%3:s:%1";
QString Mere::Store::HexaStore::HEXA_KEY_5 = "o:%3:s:%1:p:%2";
QString Mere::Store::HexaStore::HEXA_KEY_6 = "o:%3:p:%2:s:%1";

class Mere::Store::HexaStore::HexaStorePrivate
{
public:
    ~HexaStorePrivate()
    {
    }

    HexaStorePrivate(HexaStore *q)
        : q_ptr(q)
    {
    }

    int add(const QString &subject, const QString &predicate, const QString &object) const
    {
        if (Mere::Utils::StringUtils::isBlank(subject))
            return 1;

        if (Mere::Utils::StringUtils::isBlank(predicate))
            return 2;

        if (Mere::Utils::StringUtils::isBlank(object))
            return 3;

        QMap<QString, QVariant> pairs;

        QString now = QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());

        QList<QString> keys = this->keys(subject, predicate, object);
        QListIterator<QString> it(keys);
        while (it.hasNext())
        {
            pairs.insert(it.next(), now);
        }

        int err = q_ptr->PairStore::set(pairs);

        return err;
    }

    int del(const QString &subject, const QString &predicate, const QString &object) const
    {
        if (Mere::Utils::StringUtils::isBlank(subject))
            return 1;

        if (Mere::Utils::StringUtils::isBlank(predicate))
            return 2;

        if (Mere::Utils::StringUtils::isBlank(object))
            return 3;

        QList<QString> keys = this->keys(subject, predicate, object);

        int err = q_ptr->PairStore::del(keys);

        return err;
    }

    int del(const QString &vertex, const QString &predicate, const HexaStore::Flow &flow) const
    {
        if (Mere::Utils::StringUtils::isBlank(vertex))
            return 1;

        if (Mere::Utils::StringUtils::isBlank(predicate))
            return 2;

        QString prefix;
        switch (flow)
        {
            case InComing:
                prefix = QString("o:%1").arg(vertex);
                break;

            case OutGoing:
                prefix = QString("s:%1").arg(vertex);
                break;
        }

        QMap<QString, QVariant> pairs = q_ptr->PairStore::find(prefix).toMap();
        if (pairs.isEmpty())
            return 3;

        QList<QString> keys;
        QMapIterator<QString, QVariant> it(pairs);
        while (it.hasNext())
        {
            it.next();

            QString key = it.key();
            key = key.remove(prefix);
            key = key.remove(0, 3);

            keys.append(this->keys(vertex, predicate, key));
        }

        int err = q_ptr->PairStore::del(keys);

        return err;
    }

    QList<QString> vertex(const QString &vertex, const HexaStore::Flow &flow) const
    {
        QString prefix;
        switch (flow)
        {
            case InComing:
                prefix = QString("o:%1").arg(vertex);
                break;

            case OutGoing:
                prefix = QString("s:%1").arg(vertex);
                break;
        }

        QMap<QString, QVariant> pairs = q_ptr->PairStore::find(prefix).toMap();

        return pairs.keys();
    }

    QList<QString> vertex(const QString &vertex, const QString &predicate, const HexaStore::Flow &flow) const
    {
        QString prefix;
        switch (flow)
        {
            case InComing:
                prefix = QString("o:%1:p:%2").arg(vertex, predicate);
                break;

            case OutGoing:
                prefix = QString("s:%1:p:%2").arg(vertex, predicate);
                break;
        }

        QList<QString> vertexes;
        QMap<QString, QVariant> pairs = q_ptr->PairStore::find(prefix).toMap();
        QMapIterator<QString, QVariant> it(pairs);
        while (it.hasNext())
        {
            it.next();

            QString key = it.key();
            key = key.remove(prefix);
            key = key.remove(0, 3);

            vertexes.append(key);
//            HexaKey key(it.key());
        }

        return vertexes;
    }

    QList<QString> vertex(const QString &predicate) const
    {
        QString key = QString("p:%1:").arg(predicate);

        QMap<QString, QVariant> pairs = q_ptr->PairStore::find(key).toMap();

        return pairs.keys();
    }

    QList<QString> arc(const QString &subject, const QString &object) const
    {
        QString key = QString("s:%1:o:%2").arg(subject, object);

        QMap<QString, QVariant> pairs = q_ptr->PairStore::find(key).toMap();

        return pairs.keys();
    }

private:
    QList<QString> keys(const QString &subject, const QString &predicate, const QString &object) const
    {
        QList<QString> keys;

        keys.append(HEXA_KEY_1.arg(subject, predicate, object));
        keys.append(HEXA_KEY_2.arg(subject, predicate, object));
        keys.append(HEXA_KEY_3.arg(subject, predicate, object));
        keys.append(HEXA_KEY_4.arg(subject, predicate, object));
        keys.append(HEXA_KEY_5.arg(subject, predicate, object));
        keys.append(HEXA_KEY_6.arg(subject, predicate, object));

        return keys;
    }

private:
    HexaStore *q_ptr;
};

Mere::Store::HexaStore::~HexaStore()
{
}

Mere::Store::HexaStore::HexaStore(const QString &store, QObject *parent)
    : EntityStore(store, parent),
      d_ptr(new HexaStorePrivate(this))
{
}

Mere::Store::HexaStore::HexaStore(const QString &store, const QString &slice, QObject *parent)
    : EntityStore(store, slice, parent),
      d_ptr(new HexaStorePrivate(this))
{
}

int Mere::Store::HexaStore::add(const QString &subject, const QString &predicate, const QString &object) const
{
    return d_ptr->add(subject, predicate, object);
}

int Mere::Store::HexaStore::del(const QString &subject, const QString &predicate, const QString &object) const
{
    return d_ptr->del(subject, predicate, object);
}

int Mere::Store::HexaStore::del(const QString &vertex, const QString &predicate, const HexaStore::Flow &flow) const
{
    return d_ptr->del(vertex, predicate, flow);
}

QList<QString> Mere::Store::HexaStore::vertex(const QString &vertex, const Flow &flow) const
{
    return d_ptr->vertex(vertex, flow);
}

QList<QString> Mere::Store::HexaStore::vertex(const QString &vertex, const QString &predicate, const HexaStore::Flow &flow) const
{
    return d_ptr->vertex(vertex, predicate, flow);
}

QList<QString> Mere::Store::HexaStore::vertex(const QString &predicate) const
{
    return d_ptr->vertex(predicate);
}

QList<QString> Mere::Store::HexaStore::arc(const QString &subject, const QString &object) const
{
    return d_ptr->arc(subject, object);
}
