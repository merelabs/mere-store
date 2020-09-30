#ifndef SLICE_H
#define SLICE_H

#include "store.h"

namespace Mere
{
namespace Store
{

class Slice
{
//    Q_OBJECT
public:
//    explicit Slice(const Store &store, const QString &name);

signals:

private:
    const Store &m_store;
    const QString m_name;
};

} // namespace Store
} // namespace Mere


#endif // SLICE_H
