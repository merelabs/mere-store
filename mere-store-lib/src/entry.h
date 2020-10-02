#ifndef ENTRY_H
#define ENTRY_H

#include "pair.h"
#include "unitref.h"

namespace Mere
{
namespace Store
{

class Entry
{
public:
    explicit Entry();

    UnitRef ref() const;

    int set(const Pair &pair);
    int set(const QList<Pair> &pairs);

    int add(const Pair &pair);
    int add(const QList<Pair> &pairs);

    int del(const Pair &pair);
    int del(const QList<Pair> &pairs);

    QList<Pair> pairs() const;
    QMap<QString, QVariant> map() const;

private:
    class EntryPrivate;
    EntryPrivate *d_ptr;
};

} // namespace Store
} // namespace Mere

#endif // ENTRY_H
