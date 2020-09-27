#ifndef PAIRVALUE_H
#define PAIRVALUE_H

#include "value.h"

namespace Mere
{
namespace Store
{

class PairValue : public Value
{
public:
    PairValue(const QVariant &value);
};

} // namespace Store
} // namespace Mere

#endif // PAIRVALUE_H
