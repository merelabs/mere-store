#ifndef HEXAKEY_H
#define HEXAKEY_H

#include "pairkey.h"

namespace Mere
{
namespace Store
{

class HexaKey : public PairKey
{
public:
    explicit HexaKey(const QString &key);
    QString subject() const;
    QString predicate() const;
    QString object() const;
};

} // namespace Store
} // namespace Mere

#endif // HEXAKEY_H
