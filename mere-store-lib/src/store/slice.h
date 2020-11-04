#ifndef SLICE_H
#define SLICE_H

#include "store.h"

namespace Mere
{
namespace Store
{

class Index;

class Slice
{
public:
    explicit Slice(const QString &store, const QString &slice);

signals:

private:
    QString m_store;

    QString m_slice;
    QList<Index> m_indexes;
};

} // namespace Store
} // namespace Mere


#endif // SLICE_H
