#include "konfig.h"

#include "mere/store/unitstore.h"

Konfig::Konfig(QObject *parent) : QObject(parent)
{

}

QString Konfig::get(const QString &key) const
{
    QString value;
    Mere::Store::Store *s;

    Mere::Store::UnitStore store("");
    s = &store;

    if (key.compare("path") == 0)
        value = s->path();
    else if (key.compare("mime") == 0)
        value = s->mime();

    return value;
}

bool Konfig::set(const QString &key, const QString &value) const
{
    return false;
}
