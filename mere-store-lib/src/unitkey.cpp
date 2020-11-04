#include "unitkey.h"

#include <QVector>

int Mere::Store::UnitKey::PATH = 1;
int Mere::Store::UnitKey::TYPE = 3;
int Mere::Store::UnitKey::ID = 5;
int Mere::Store::UnitKey::ATTR = 7;
int Mere::Store::UnitKey::LINK = 12;

Mere::Store::UnitKey::UnitKey(const QString &key)
    : PairKey(key)
{

}

Mere::Store::UnitRef Mere::Store::UnitKey::ref() const
{
    int pos = 0;

    int len = indexOfNth(6);
    if (len == -1)
        len = length();

    QStringRef ref = midRef(pos, len);

    return UnitRef(ref.toString());
}

QStringRef Mere::Store::UnitKey::path() const
{
    QVector<QStringRef> refs = this->splitRef(":");
    if (refs.isEmpty())
        return QStringRef();

    if (refs.size() < (PATH + 1))
        return QStringRef();

    return refs.at(PATH);
}

QStringRef Mere::Store::UnitKey::type() const
{
    QVector<QStringRef> refs = this->splitRef(":");
    if (refs.isEmpty())
        return QStringRef();

    if (refs.size() < (TYPE + 1))
        return QStringRef();

    return refs.at(TYPE);
}

QStringRef Mere::Store::UnitKey::uuid() const
{
    QVector<QStringRef> refs = this->splitRef(":");
    if (refs.isEmpty())
        return QStringRef();

    if (refs.size() < (ID + 1))
        return QStringRef();

    return refs.at(ID);
}

bool Mere::Store::UnitKey::isAttribute() const
{
    return contains(":attr:");
}

QStringRef Mere::Store::UnitKey::attribute() const
{
    QVector<QStringRef> refs = this->splitRef(":");
    if (refs.isEmpty())
        return QStringRef();

    if (refs.size() < (ATTR + 1))
        return QStringRef();

    return refs.at(ATTR);
}

bool Mere::Store::UnitKey::isLink() const
{
    return contains(":link:");
}

Mere::Store::Link Mere::Store::UnitKey::link() const
{
    Link link;
    int len0 = indexOfNth(7);
    if (len0 == -1)
        return link;

    int len1 = indexOfNth(8);
    if (len1 == -1)
        return link;

    int len2 = indexOfNth(14);
    if (len2 == -1)
        len2 = length();

    QString rel = mid(len0 + 1, len1 - len0 - 1);
    QString ref = mid(len1 + 1, len2 - len1 - 1);

    UnitRef unit(ref);

    link.setName(rel);
    link.setUnits(QList<UnitRef>({unit}));

    return link;
}
