#include "jsonstore.h"
#include "mere/utils/stringutils.h"

#include <QJsonDocument>

Mere::Store::JsonStore::~JsonStore()
{

}

Mere::Store::JsonStore::JsonStore(const QString &store, QObject *parent)
    : PairStore(store, parent)
{
}

Mere::Store::JsonStore::JsonStore(const QString &store, const QString &slice, QObject *parent)
    : PairStore(store, slice, parent)
{
}

int Mere::Store::JsonStore::set(const QString &key, const QVariant &value)
{
    if (!value.isValid() || value.isNull())
        return 1;

    QString json = value.toString();
    if (Mere::Utils::StringUtils::isBlank(json))
        return 2;

    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());

    return set(key, document);
}

int Mere::Store::JsonStore::set(const QString &key, const QJsonArray &value)
{
    return set(key, QJsonDocument(value));
}

int Mere::Store::JsonStore::set(const QString &key, const QJsonObject &value)
{
    return set(key, QJsonDocument(value));
}

int Mere::Store::JsonStore::set(const QString &key, const QJsonDocument &value)
{
    if (!value.isObject() && !value.isArray())
        return 3;

    QString json = value.toJson(QJsonDocument::Compact);

    return PairStore::set(key, json);
}
