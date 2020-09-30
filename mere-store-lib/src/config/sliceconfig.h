#ifndef SLICECONFIG_H
#define SLICECONFIG_H

#include "indexconfig.h"

#include <QObject>
#include <QVariant>

namespace  Mere
{
namespace  Store
{

class SliceConfig
{
public:
    explicit SliceConfig();

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
