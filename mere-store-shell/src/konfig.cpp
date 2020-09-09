#include "konfig.h"

#include "mere/store/format/mereunitstore.h"

Konfig::Konfig(QObject *parent) : QObject(parent)
{

}

QString Konfig::get(const QString &key) const
{
    MereStore *s;

    MereUnitStore store("");
    s = &store;

    return s->path();
}

bool Konfig::set(const QString &key, const QString &values) const
{
    return false;
}
