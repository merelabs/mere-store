#ifndef PAIR_H
#define PAIR_H

#include "pairkey.h"
#include "pairvalue.h"

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

    bool operator==(const Pair &pair)
    {
        return m_key.compare(pair.key()) == 0;
    }

private:
    PairKey m_key;
    PairValue m_value;
};

} // namespace Store
} // namespace Mere

#endif // PAIR_H
