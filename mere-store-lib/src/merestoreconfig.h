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
        const QString AppKey            = "mere.store.name";
        const QString VersionKey        = "mere.store.version";
        const QString StoreKey          = "mere.store.store";
        const QString StoreDefaultKey   = "mere.store.store.default";
    }
}

class MERE_STORE_LIBSPEC MereStoreConfig : public QObject
{
    Q_OBJECT
private:
    explicit MereStoreConfig(QObject *parent = nullptr);

public:
    static MereStoreConfig* instance();


    QString storePath() const;
    void setStorePath(const QString path);

    QVariant get(QString key) const;
    void set(QString key, QVariant value);

private:
    QMap<QString, QVariant> m_config;
};

#endif // MERESTORECONFIG_H
