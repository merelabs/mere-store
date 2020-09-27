#include "pair.h"

Mere::Store::Pair::Pair(const QString &key, const QVariant &value)
    : Pair(PairKey(key), PairValue(value))
{

}

Mere::Store::Pair::Pair(const Key &key, const Mere::Store::Value &value)
    : m_key(key),
      m_value(value)
{

}
