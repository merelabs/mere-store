#ifndef INDEXSTORE_H
#define INDEXSTORE_H

#include "pairstore.h"

#include <QObject>

namespace Mere
{
namespace Store
{

class IndexStore : public PairStore
{
    Q_OBJECT
public:
    explicit IndexStore(const Store &store, const Index &index, QObject *parent = nullptr);
    explicit IndexStore(const Store &store, const QString &name, QObject *parent = nullptr);
};

} // namespace Store
} // namespace Mere

#endif // INDEXSTORE_H
