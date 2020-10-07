#include "indexkey.h"

Mere::Store::IndexKey::IndexKey(const QString &key)
    : Key(key)
{

}

QString Mere::Store::IndexKey::what() const
{
    QString what = "";

    int pos = this->indexOf(":");
    if (pos != -1)
        what = left(pos);

    return what;
}

Mere::Store::UnitRef Mere::Store::IndexKey::ref() const
{
    QString ref = "";

    int pos = this->indexOf(":");
    if (pos != -1)
        ref = mid(pos + 1);

    return UnitRef(ref);
}
