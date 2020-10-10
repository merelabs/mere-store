#include "hexakey.h"

Mere::Store::HexaKey::HexaKey(const QString &key)
    : PairKey(key)
{

}

// FIXME - consider escape \: or : in content
QString Mere::Store::HexaKey::subject() const
{
    return "";
}

QString Mere::Store::HexaKey::predicate() const
{
    return "";
}

QString Mere::Store::HexaKey::object() const
{
    return "";
}

