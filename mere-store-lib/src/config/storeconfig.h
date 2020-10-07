#ifndef STORECONFIG_H
#define STORECONFIG_H

#include "config.h"
#include "indexconfig.h"

#include <QObject>
#include <QVariant>


namespace  Mere
{
namespace  Store
{

class StoreConfig : public Config
{
public:
    explicit StoreConfig(const QString &home, QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    IndexConfig index() const;
    void setIndex(const IndexConfig &index);

private:
    QString m_name;
    IndexConfig m_index;

};

}
}

#endif // STORECONFIG_H
