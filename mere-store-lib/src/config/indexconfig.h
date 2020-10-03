#ifndef INDEXCONFIG_H
#define INDEXCONFIG_H

#include "config.h"
#include "../index/index.h"

namespace  Mere
{
namespace  Store
{


class IndexConfig //: public Config
{
public:
    explicit IndexConfig();

    Index index(const QString &name) const;
    QList<Index> indexes() const;

    void addIndex(const Index &index);
    void addIndexes(const QList<Index> &indexes);

    void setIndex(const Index &index);
    void setIndexes(const QList<Index> &indexes);

    QMap<QString, QVariant> map() const;

private:
    QList<Index> m_indexes;
};

} // namespace Store
} // namespace Mere

#endif // INDEXCONFIG_H
