#include "config.h"

#include "mere/utils/merestringutils.h"

#include <QDir>
#include <QFile>
#include <QSettings>

Mere::Store::Config::Config(QObject *parent)
    : Config("/usr/local/etc/mere/store.conf", parent)
{

}

Mere::Store::Config::Config(const QString &config, QObject *parent)
    : QObject(parent),
      m_config(config)
{

}

void Mere::Store::Config::init()
{
    if (QFile(m_config).exists())
    {
        QSettings settings(m_config, QSettings::IniFormat);
        set(Mere::Store::PathKey, settings.value(Mere::Store::PathKey));
    }
}

QVariant Mere::Store::Config::get(const QString &key) const
{
    QVariant value = m_configs.value(key);

    //qDebug() << QString("Getting config key/value: %1 => %2").arg(key).arg(value.toString());

    return value;
}

void Mere::Store::Config::set(const QString &key, const QVariant &value)
{
    //qDebug() << QString("Setting config key/value: %1 => %2").arg(key).arg(value.toString());
    m_configs.insert(key, value);
}

QString Mere::Store::Config::path() const
{
    QString path = get(Mere::Store::PathKey).toString();
    if (MereStringUtils::isBlank(path))
            path = "./";

    // check for trailing slash
    if (!path.endsWith(QDir::separator()))
        path = path.append(QDir::separator());

    return path;
}

void Mere::Store::Config::setPath(const QString &path)
{
    return set(Mere::Store::PathKey, path);
}

QString Mere::Store::Config::mime() const
{
    QString mime = get(Mere::Store::MimeKey).toString();
    if (MereStringUtils::isBlank(mime))
            mime = "text/plain";

    return mime;
}

void Mere::Store::Config::setMime(const QString &mime)
{
    return set(Mere::Store::MimeKey, mime);
}

QList<Mere::Store::SliceConfig> Mere::Store::Config::slices() const
{
    return m_slices.values();
}

Mere::Store::SliceConfig Mere::Store::Config::slice(const QString &name) const
{
    SliceConfig config = m_slices.value(name);

    return config;
}

void Mere::Store::Config::addSlice(const SliceConfig &slice)
{
    m_slices.insert(slice.name(), slice);
}

//static
Mere::Store::Config* Mere::Store::Config::instance()
{
    static Config *_instance = nullptr;
    if (!_instance )
    {
        _instance = new Config();
        _instance->init();
    }

    return _instance;
}

