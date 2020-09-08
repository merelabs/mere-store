#include "merestoreconfig.h"

#include "mere/utils/merestringutils.h"

#include <QDir>
#include <QSettings>

MereStoreConfig::MereStoreConfig(QObject *parent)
    : MereStoreConfig("/usr/local/etc/mere/store.conf", parent)
{

}

MereStoreConfig::MereStoreConfig(const QString &config, QObject *parent)
    : QObject(parent),
      m_config(config)
{

}

void MereStoreConfig::init()
{
    QSettings settings(m_config, QSettings::IniFormat);
    set(Mere::Store::PathKey, settings.value(Mere::Store::PathKey));
}

QVariant MereStoreConfig::get(const QString &key) const
{
    QVariant value = m_configs.value(key);

    //qDebug() << QString("Getting config key/value: %1 => %2").arg(key).arg(value.toString());

    return value;
}

void MereStoreConfig::set(const QString &key, const QVariant &value)
{
    //qDebug() << QString("Setting config key/value: %1 => %2").arg(key).arg(value.toString());
    m_configs.insert(key, value);
}

QString MereStoreConfig::storePath() const
{
    QString path = get(Mere::Store::PathKey).toString();
    if (MereStringUtils::isBlank(path))
            path = "./";

    // check for trailing slash
    if (!path.endsWith(QDir::separator()))
        path = path.append(QDir::separator());

    return path;
}

void MereStoreConfig::setStorePath(const QString &path)
{
    return set(Mere::Store::PathKey, path);
}

//static
MereStoreConfig* MereStoreConfig::instance()
{
    static MereStoreConfig *_instance = nullptr;
    if (!_instance )
    {
        _instance = new MereStoreConfig();
        _instance->init();
    }

    return _instance;
}

