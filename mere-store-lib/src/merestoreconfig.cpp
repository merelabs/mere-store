#include "merestoreconfig.h"

#include "mere/utils/merestringutils.h"

MereStoreConfig::MereStoreConfig(QObject *parent) : QObject(parent)
{

}

QVariant MereStoreConfig::get(QString key) const
{
    QVariant value = m_config.value(key);

    //qDebug() << QString("Getting config key/value: %1 => %2").arg(key).arg(value.toString());

    return value;
}

void MereStoreConfig::set(QString key, QVariant value)
{
    //qDebug() << QString("Setting config key/value: %1 => %2").arg(key).arg(value.toString());
    m_config.insert(key, value);
}

QString MereStoreConfig::storePath() const
{
    QString path = get(Mere::Store::StoreKey).toString();

    if (MereStringUtils::isBlank(path))
    {
        path = get(Mere::Store::StoreDefaultKey).toString();
        if (MereStringUtils::isBlank(path))
            path = "./";
    }

    // check for trailing slash
    if (!path.endsWith("/"))
        path = path.append("/");

    return path;
}

void MereStoreConfig::setStorePath(const QString path)
{
    return set(Mere::Store::StoreKey, path);
}

//static
MereStoreConfig* MereStoreConfig::instance()
{
    static MereStoreConfig *_instance = nullptr;
    if (!_instance )
        _instance = new MereStoreConfig();

    return _instance;
}

