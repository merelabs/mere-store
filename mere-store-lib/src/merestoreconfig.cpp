#include "merestoreconfig.h"

#include "mere/utils/merestringutils.h"

#include <QDir>
#include <QFile>
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
    if (QFile(m_config).exists())
    {
        QSettings settings(m_config, QSettings::IniFormat);
        set(Mere::Store::PathKey, settings.value(Mere::Store::PathKey));
    }
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

QString MereStoreConfig::path() const
{
    QString path = get(Mere::Store::PathKey).toString();
    if (MereStringUtils::isBlank(path))
            path = "./";

    // check for trailing slash
    if (!path.endsWith(QDir::separator()))
        path = path.append(QDir::separator());

    return path;
}

void MereStoreConfig::setPath(const QString &path)
{
    return set(Mere::Store::PathKey, path);
}

QString MereStoreConfig::mime() const
{
    QString mime = get(Mere::Store::MimeKey).toString();
    if (MereStringUtils::isBlank(mime))
            mime = "text/plain";

    return mime;
}

void MereStoreConfig::setMime(const QString &mime)
{
    return set(Mere::Store::MimeKey, mime);
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

