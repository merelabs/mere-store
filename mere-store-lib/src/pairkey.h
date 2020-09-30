#ifndef PAIRKEY_H
#define PAIRKEY_H

#include "key.h"

namespace Mere
{
namespace Store
{

class PairKey: public Key
{
public:
    PairKey(const QString &key);

    bool hasPart() const;
    int numberOfParts() const;
    int indexOfNth(int nth) const;
};

} // namespace Store
} // namespace Mere

#endif // PAIRKEY_H
