#ifndef GROUPSTORE_H
#define GROUPSTORE_H

#include "pairstore.h"

namespace Mere
{
namespace Store
{


class MERE_STORE_LIBSPEC GroupStore : public PairStore
{
    Q_OBJECT
public:
    virtual ~GroupStore();
    explicit GroupStore(const QString &store, QObject *parent = nullptr);
    explicit GroupStore(const QString &store, const QString &slice, QObject *parent = nullptr);

    virtual QVariant list(const QString &key, const int &limit = 0) override;

private:
    class GroupStorePrivate;
    GroupStorePrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // GROUPSTORE_H
