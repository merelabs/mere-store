#include "value.h"

Mere::Store::Value::Value(const QVariant &value)
    : QVariant(value)
{
    Q_UNUSED(value)
}
