#ifndef SLICE_H
#define SLICE_H

#include "store.h"

namespace Mere
{
namespace Store
{

class Slice
{
public:
    explicit Slice(const QString &store, const QString &slice);

signals:

private:
    const QString &m_store;
    const QString &m_slice;
};

} // namespace Store
} // namespace Mere


#endif // SLICE_H
