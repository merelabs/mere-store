#ifndef PAIR_H
#define PAIR_H

#include "key.h"
#include "value.h"

#include <QPair>

namespace Mere
{
namespace Store
{

class Pair
{
    public:
        Pair(const QString &key, const QVariant &value);
        Pair(const Key &key, const Value &value);

        QString key() const;
        QVariant value() const;

    private:
        Key m_key;
        Value m_value;
};

} // namespace Store
} // namespace Mere

#endif // PAIR_H
