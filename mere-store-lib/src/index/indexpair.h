#ifndef INDEXPAIR_H
#define INDEXPAIR_H

#include "../pair.h"
#include "../unitref.h"

namespace Mere
{
namespace Store
{

class IndexPair //: public Pair
{
public:
    explicit IndexPair(const QString &key, const UnitRef &ref);

};

} // namespace Store
} // namespace Mere

#endif // INDEXPAIR_H
