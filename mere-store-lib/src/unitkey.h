#ifndef UNITKEY_H
#define UNITKEY_H

#include "pairkey.h"
#include "unitref.h"
#include "link.h"

namespace Mere
{
namespace Store
{

class UnitKey : public PairKey
{
public:
    UnitKey(const QString &key);

    UnitRef ref() const;

    QStringRef path() const;
    QStringRef type() const;
    QStringRef uuid() const;

    bool isAttribute() const;
    QStringRef attribute() const;

    bool isLink() const;

    Mere::Store::Link link() const;

private:
    static int PATH;
    static int TYPE;
    static int UUID;
    static int ATTR;
    static int LINK;
};

} // namespace Store
} // namespace Mere

#endif // UNITKEY_H
