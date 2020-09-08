#ifndef MERESTORECONFIG_H
#define MERESTORECONFIG_H

#include "merestoreglobal.h"

#include <QMap>
#include <QObject>
#include <QVariant>
#include <QDebug>

namespace Mere
{
    namespace Store
    {
        const QString NameKey    = "mere.store.name";
        const QString VersionKey = "mere.store.version";
        const QString PathKey    = "mere.store.path";
    }
}

class MERE_STORE_LIBSPEC MereStoreConfig : public QObject
{
    Q_OBJECT
private:
    explicit MereStoreConfig(QObject *parent = nullptr);
    explicit MereStoreConfig(const QString &config, QObject *parent = nullptr);

public:
    void init();

    QString storePath() const;
    void setStorePath(const QString &path);

    QVariant get(const QString &key) const;
    void set(const QString &key, const QVariant &value);

    static MereStoreConfig* instance();

private:
    QMap<QString, QVariant> m_configs;

    QString m_config;
};

#endif // MERESTORECONFIG_H
