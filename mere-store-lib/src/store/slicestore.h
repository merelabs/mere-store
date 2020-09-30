#ifndef SLITESTORE_H
#define SLITESTORE_H

#include "unitstore.h"

namespace Mere
{
namespace Store
{

class SliceStore : public UnitStore
{
    Q_OBJECT
public:
    explicit SliceStore(const Store &store, const QString &name, QObject *parent = nullptr);

signals:

};

} // namespace Store
} // namespace Mere


#endif // SLITESTORE_H
