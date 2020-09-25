#ifndef VALUE_H
#define VALUE_H

#include <QVariant>

namespace Mere
{
namespace Store
{

class Value : QVariant
{
public:
    Value(const QVariant &value);
};

} // namespace Store
} // namespace Mere

#endif // VALUE_H
