#ifndef SLICECONFIG_H
#define SLICECONFIG_H

#include "config.h"
#include "indexconfig.h"

#include <QObject>
#include <QVariant>

namespace  Mere
{
namespace  Store
{

class SliceConfig : public Config
{
public:
    explicit SliceConfig(const QString &config, QObject *parent = nullptr);

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


#endif // SLICECONFIG_H
